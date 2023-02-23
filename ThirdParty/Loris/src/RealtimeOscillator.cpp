/*
 * This is the Loris C++ Class Library, implementing analysis,
 * manipulation, and synthesis of digitized sounds using the Reassigned
 * Bandwidth-Enhanced Additive Sound Model.
 *
 * Loris is Copyright (c) 1999-2010 by Kelly Fitz and Lippold Haken, 2013 Tomas Medek
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY, without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 * RealtimeOscillator.C
 *
 * Implementation of class Loris::RealtimeOscillator, a Bandwidth-Enhanced RealtimeOscillator.
 *
 * Tomas Medek, 20 Sep 2014
 * tom@virtualanalogy.org
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif
#include "RealtimeOscillator.h"
#include "Filter.h"
#include "Partial.h"
#include "Notifier.h"
#include <cmath>
#include <cstring>
#include <vector>

#if defined(HAVE_M_PI) && (HAVE_M_PI)
const double Pi = M_PI;
#else
const double Pi = 3.14159265358979324;
#endif
const double TwoPi = 2*Pi;

#if defined(__aarch64__)
#include "../../sse2neon/sse2neon.h"
#else
#include <xmmintrin.h>
#endif

typedef union {
	__m128 v;    // SSE 4 x float vector
	float a[4];  // scalar array of 4 floats
} converter;

float vectorGetByIndex(__m128 V, unsigned int i) {
	converter c;
	c.v = V;
	return c.a[i];
}

void vectorSetByIndex(__m128 &V, unsigned int i, float v) {
	converter c;
	c.v = V;
	c.a[i] = v;
	V = c.v;
}

//TODO:
__m128 tmp_cos(__m128 v)
{
	__m128 out;
	vectorSetByIndex(out, 0, cos(vectorGetByIndex(v, 0)));
	vectorSetByIndex(out, 1, cos(vectorGetByIndex(v, 1)));
	vectorSetByIndex(out, 2, cos(vectorGetByIndex(v, 2)));
	vectorSetByIndex(out, 3, cos(vectorGetByIndex(v, 3)));
	return out;
}

//  begin namespace
namespace Loris {
// ---------------------------------------------------------------------------
//  RealtimeOscillator construction
// ---------------------------------------------------------------------------
//  Initialize stochastic modulators and state variables.
//
RealtimeOscillator::RealtimeOscillator( void ) :
Oscillator(),
m_frequencyScaling ( 1 )
{
}
// ---------------------------------------------------------------------------
//  resetEnvelopes
// ---------------------------------------------------------------------------
//  Reset the instantaneous envelope parameters
//  (frequency, amplitude, bandwidth, and phase).
//  The Breakpoint frequency (Hz) is in radians per sample.
void
RealtimeOscillator::restoreEnvelopes( const Breakpoint & bp) noexcept
{
	//  Remember that the oscillator only knows about
	//  radian frequency! Convert!
	m_instfrequency = bp.frequency();
	m_instamplitude = bp.amplitude();
	m_instbandwidth = bp.bandwidth();
	m_determphase = bp.phase();
	
	//  clamp bandwidth:
	if ( m_instbandwidth > 1. )
	{
		m_instbandwidth = 1.;
	}
	else if ( m_instbandwidth < 0. )
	{
		m_instbandwidth = 0.;
	}
	//  don't alias:
	if ( m_instfrequency > Pi )
	{
		m_instamplitude = 0.;
	}
	
	//  Reset the fitler state too.
	m_filter.clear();
}

// ---------------------------------------------------------------------------
//  resetEnvelopes
// ---------------------------------------------------------------------------
//  Reset the instantaneous envelope parameters
//  (frequency, amplitude, bandwidth, and phase).
//  The sample rate is needed to convert the
//  Breakpoint frequency (Hz) to radians per sample.
//
void
RealtimeOscillator::resetEnvelopes( const Breakpoint & bp, double srate ) noexcept
{
	//  Remember that the oscillator only knows about
	//  radian frequency! Convert!
	m_instfrequency = m_frequencyScaling * bp.frequency() * TwoPi / srate;
	m_instamplitude = bp.amplitude();
	m_instbandwidth = bp.bandwidth();
	m_determphase = bp.phase();
	
	//  clamp bandwidth:
	if ( m_instbandwidth > 1. )
	{
		m_instbandwidth = 1.;
	}
	else if ( m_instbandwidth < 0. )
	{
		m_instbandwidth = 0.;
	}
	//  don't alias:
	if ( m_instfrequency > Pi )
	{
		m_instamplitude = 0.;
	}
	
	//  Reset the fitler state too.
	m_filter.clear();
}

// ---------------------------------------------------------------------------
//  envelopes
// ---------------------------------------------------------------------------
//  Get envelopes state. Frequency is in radian per sec.
//
Breakpoint RealtimeOscillator::envelopes() noexcept
{
	Breakpoint bp(m_instfrequency, m_instamplitude, m_instbandwidth);
	bp.setPhase(m_determphase);
	
	return bp;
}

// ---------------------------------------------------------------------------
//  m2pi
// ---------------------------------------------------------------------------
//  O'Donnell's phase wrapping function.
//
static inline double m2pi( double x )
{
	using namespace std; // floor should be in std
#define ROUND(x) (floor(.5 + (x)))
	return x + ( TwoPi * ROUND(-x/TwoPi) );
}

// ---------------------------------------------------------------------------
//  setFrequencyScaling
// ---------------------------------------------------------------------------
// Set internal frequency scaling.
//
void
RealtimeOscillator::setFrequencyScaling(double scaling) noexcept
{
	m_frequencyScaling = scaling;
}

// ---------------------------------------------------------------------------
//  oscillate
// ---------------------------------------------------------------------------
//  Accumulate bandwidth-enhanced sinusoidal samples modulating the
//  oscillator state from its current values of radian frequency,
//  amplitude, and bandwidth to the specified target values, into
//  the specified half-open range of floats. SSE2 instructions are used.
//
//  The caller must ensure that the range is valid. Target parameters
//  are bounds-checked.
//
void
RealtimeOscillator::oscillate( float * begin, float * end,
							  const Breakpoint & bp, double srate, int dSample) noexcept
{
	double targetFreq = m_frequencyScaling * bp.frequency() * TwoPi / srate;     //  radians per sample
	double targetAmp = bp.amplitude();
	double targetBw = bp.bandwidth();
	
	//  clamp bandwidth:
	if ( targetBw > 1. )
	{
		targetBw = 1.;
	}
	else if ( targetBw < 0. )
	{
		targetBw = 0.;
	}
	
	//  don't alias:
	if ( targetFreq > Pi )  //  radian Nyquist rate
	{
		targetAmp = 0.;
	}
	//  compute trajectories:
	const double dTime = 1. / dSample; //(end - begin);
	const double dFreqOver2 = 0.5 * (targetFreq - m_instfrequency) * dTime;
	//	split frequency update in two steps, update phase using average
	//	frequency, after adding only half the frequency step
	
	const double dAmp = (targetAmp - m_instamplitude)  * dTime;
	//        const double dBw = (targetBw - m_instbandwidth)  * dTime;
	//  Use temporary local variables for speed.
	//  Probably not worth it when I am computing square roots
	//  and cosines...
	double ph = m_determphase;
	//        double f = m_instfrequency;
	//        double a = m_instamplitude;
	//        double bw = m_instbandwidth;
	
	// Ignore bandwidth
	//	Also use a more efficient sample loop when the bandwidth is zero.
	//        if (false 0 < bw || 0 < dBw )
	//        {
	//            double am, nz;
	//            for ( double * putItHere = begin; putItHere != end; ++putItHere )
	//            {
	//                //  use math functions in namespace std:
	//                using namespace std;
	//
	//                //  compute amplitude modulation due to bandwidth:
	//                //
	//                //  This will give the right amplitude modulation when scaled
	//                //  by the Partial amplitude:
	//                //
	//                //  carrier amp: sqrt( 1. - bandwidth ) * amp
	//                //  modulation index: sqrt( 2. * bandwidth ) * amp
	//                //
	//                nz = m_filter.apply( m_modulator.sample() );
	//                am = sqrt( 1. - bw ) + ( nz * sqrt( 2. * bw ) );
	//
	//                //  compute a sample and add it into the buffer:
	//                *putItHere += am * a * cos( ph );
	//
	//                //  update the instantaneous oscillator state:
	//                f += dFreqOver2;
	//                ph += f;   //  frequency is radians per sample
	//                f += dFreqOver2;
	//                a += dAmp;
	//                bw += dBw;
	//                if (bw < 0.)
	//                {
	//                    bw = 0.;
	//                }
	//            }   // end of sample computation loop
	//        }
	//        else
	{
		//          Vectorized loop
		double a4[4] = { m_instamplitude };
		double f4[4] = { m_instfrequency };
		__m128 ph4 = { (float) m_determphase };
		
		for (unsigned int i = 1; i < 4; i++)
		{
			f4[i] = f4[i - 1] + dFreqOver2;
			float tmp = vectorGetByIndex(ph4, i - 1);
			vectorSetByIndex(ph4, i, tmp + f4[i]);
			f4[i] = f4[i] + dFreqOver2;
			a4[i] = a4[i - 1] + dAmp;
		}
		
		__m128 cosVal;
		float * putItHere = begin;
		for ( ; putItHere + 4  < end; putItHere += 4 )
		{
			cosVal = tmp_cos(ph4);
			
			for (unsigned int i = 0; i < 4; i++)
			{
				putItHere[i] += (a4[i] == 0 ? 0 : a4[i] * vectorGetByIndex(cosVal, i));
			}
			
			f4[0] = f4[3] + dFreqOver2;
			vectorSetByIndex(ph4, 0, vectorGetByIndex(ph4, 3) + f4[0]);
			f4[0] = f4[0] + dFreqOver2;
			a4[0] = a4[3] + dAmp;
			for (unsigned int i = 1; i < 4; i++)
			{
				f4[i] = f4[i - 1] + dFreqOver2;
				vectorSetByIndex(ph4, i, vectorGetByIndex(ph4, i - 1) + f4[i]);
				f4[i] = f4[i] + dFreqOver2;
				a4[i] = a4[i - 1] + dAmp;
			}
		}   // end of sample computation loop
		
		for ( ; putItHere != end; ++putItHere )
		{
			//  use math functions in namespace std:
			using namespace std;
			
			//	no modulation when there is no bandwidth
			
			//  compute a sample and add it into the buffer:
			*putItHere += (a4[0] == 0 ? 0 : a4[0] * cos(vectorGetByIndex(ph4, 0)));
			
			//  update the instantaneous oscillator state:
			f4[0] += dFreqOver2;
			vectorSetByIndex(ph4, 0, vectorGetByIndex(ph4, 0) + f4[0]); //  frequency is radians per sample
			f4[0] += dFreqOver2;
			a4[0] += dAmp;
			
		}   // end of
		
		ph = vectorGetByIndex(ph4, 0);
		targetAmp = a4[0];
		targetFreq = f4[0];
	}
	
	//  wrap phase to prevent eventual loss of precision at
	//  high oscillation frequencies:
	//  (Doesn't really matter much exactly how we wrap it,
	//  as long as it brings the phase nearer to zero.)
	m_determphase = m2pi( ph );
	
	//  set the state variables to their target values,
	//  just in case they didn't arrive exactly (overshooting
	//  amplitude or, especially, bandwidth, could be bad, and
	//  it does happen):
	m_instfrequency = targetFreq;
	m_instamplitude = targetAmp;
	m_instbandwidth = targetBw;
}

}   //  end of namespace Loris
