/*
 * This is the Loris C++ Class Library, implementing analysis, 
 * manipulation, and synthesis of digitized sounds using the Reassigned 
 * Bandwidth-Enhanced Additive Sound Model.
 *
 * Loris is Copyright (c) 1999-2010, 2014 by Kelly Fitz and Lippold Haken and Tomas medek
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
 * RealTimeSynthesizer.C
 *
 * Implementation of class Loris::RealTimeSynthesizer, a synthesizer of
 * bandwidth-enhanced Partials.
 *
 * Tomas Medek, 24 Jul 20149
 * tom@virtualanalogy.org
 *
 *
 */
#if HAVE_CONFIG_H
    #include "config.h"
#endif
#include "RealtimeSynthesizer.h"
#include "RealtimeOscillator.h"
#include "Breakpoint.h"
#include "BreakpointUtils.h"
#include "Envelope.h"
#include "LorisExceptions.h"
#include "Notifier.h"
#include "Partial.h"
#include "Resampler.h"
#include "phasefix.h"

#include <algorithm>
#include <cmath>
#include <assert.h>

//  begin namespace
namespace Loris {
// ---------------------------------------------------------------------------
//  Synthesizer constructor
// ---------------------------------------------------------------------------
//!	Construct a Synthesizer using the default parameters and sample
//!	buffer (a standard library vector). Since Partials generated by the 
//! Loris Analyzer generally begin and end at non-zero amplitude, zero-amplitude
//!	Breakpoints are inserted at either end of the Partial, at a temporal
//!	distance equal to the fade time, to reduce turn-on and turn-off
//!	artifacts.
//!
//! \sa Synthesizer::Parameters
//!
//!	\param	buffer The vector (of floats) into which rendered samples
//!			   should be accumulated.
//!	\throw	InvalidArgument if any of the parameters is invalid.
RealTimeSynthesizer::RealTimeSynthesizer( std::vector<float> & buffer ) :
    Synthesizer( xxx )
{
    this->buffer = &buffer;
}

// ---------------------------------------------------------------------------
//  setup
// ---------------------------------------------------------------------------
//!	Prepare internal structures for synthesis. PartialList is transformed to
//! to more conveniant structure for real-time processing. reset() is also called.
//! Fade in/out Breakpoints are inserted at either end of the Partial.
//! Partials with start times earlier than the Partial fade
//! time will have shorter onset fades. 
//!
//! \param  partials The Partials to synthesize.
//! \param  pitch original pitch of the partials
//! \return Nothing.
//! \post   This RealTimeSynthesizer's is ready for synthesise the sound specified
//!         by given partials.
void RealTimeSynthesizer::setup(PartialList & partials, double pitch) noexcept
{
    this->partials.clear();
    this->pitch = pitch;
    clearPartialsBeingProcessed();
    
    // assuming I am getting sorted partials by time
    for (auto it : partials)
    {
        if (it.numBreakpoints() <= 0) continue;
        
        PartialStruct pStruct;
        
        pStruct.numBreakpoints = it.numBreakpoints() + 2;// + fade in + fade out

        pStruct.breakpoints.reserve(pStruct.numBreakpoints);
        pStruct.label = it.label();
        
        pStruct.startTime = ( m_fadeTimeSec < it.startTime() ) ? ( it.startTime() - m_fadeTimeSec ) : 0.;// compute fade in bp time
        pStruct.endTime = it.endTime() + m_fadeTimeSec;// compute fade out bp time

        
        // breakpoints
        Partial::const_iterator jt = it.begin();
        // fade in breakpoint, compute fade in time
        pStruct.breakpoints.push_back(std::make_pair(pStruct.startTime, BreakpointUtils::makeNullBefore( jt.breakpoint(), it.startTime() - pStruct.startTime)));
        

        
        double sumF = 0;
        
        for (; jt != it.end(); jt++)
        {
            sumF += jt->frequency();
            pStruct.breakpoints.push_back(std::make_pair(jt.time(), jt.breakpoint()));
        }
        
        pStruct.avgFrequency = sumF / (float) it.numBreakpoints();
        
        // fade out breakpoint
        jt--;
        pStruct.breakpoints.push_back(std::make_pair(jt.time() + m_fadeTimeSec, BreakpointUtils::makeNullAfter( jt.breakpoint(), m_fadeTimeSec )));
        
        this->partials.push_back(pStruct);
//        pStruct.breakpoints[0].second.setAmplitude(pStruct.breakpoints[1].second.amplitude());
    }

    
    reset();
}

// ---------------------------------------------------------------------------
//  setup
// ---------------------------------------------------------------------------
//!	Set sample rate.
//!
//! \param  rate new sample rate
//! \return Nothing.
void RealTimeSynthesizer::setSampleRate(double rate)
{
    Synthesizer::setSampleRate(rate);

    //  better to compute this only once:
    OneOverSrate = 1. / m_srateHz;
}
    
// ---------------------------------------------------------------------------
//  reset
// ---------------------------------------------------------------------------
//!	Reset RealtimeSynthesizer to render sound from the beging.
//!
//! \post   Sound is rendered in original pitch.
//! \return Nothing.
void RealTimeSynthesizer::reset() noexcept
{
    partialIdx = 0;
    processedSamples = 0;
    clearPartialsBeingProcessed();
}

// ---------------------------------------------------------------------------
//  setPitch
// ---------------------------------------------------------------------------
//!	Change pitch of sound.
//!
//! \param  New pitch in frequency of the sound.
//! \return Nothing.
void RealTimeSynthesizer::setPitch(double frequency) noexcept
{
    m_osc.setFrequencyScaling(frequency / pitch);
}

// ---------------------------------------------------------------------------
//  synthesizeNext
// ---------------------------------------------------------------------------
//!	Synthesize next block of samples of the partials. The synthesizer
//! will resize the inner buffer as necessary. Previous contents of the buffer
//! are overwritten.
//!
//! \param  sample Number of samples to synthesize.
//! \return Nothing.
//! \post   Internal state of synthesizer changes - it is ready to synthesize
//!         next block of samples starting at 'previous count of samples' + samples.
void RealTimeSynthesizer::synthesizeNext( int samples ) noexcept
{
    //TODO: check processedSamples overflow
    processedSamples += samples;// for performance reason this is computed at the beginning
    PartialStruct *partial;
    
    // prepare buffer for new data
    if (buffer->capacity() < samples)
        buffer->reserve(samples);
    memset(buffer->data(), 0, samples * sizeof(decltype(buffer->data())));
    
    
    // process partials being processed
    int size = partialsBeingProcessed.size();
    for (int i = 0; i < size; i++)
    {
        partial = partialsBeingProcessed.front();
        synthesize( *partial, buffer->data(), samples );
        
        if ( partial->state.lastBreakpointIdx < partial->numBreakpoints - 1)
            partialsBeingProcessed.push( partial );
        
        partialsBeingProcessed.pop();
    }
    
    // partials to be processed
    int partialSize = partials.size();
    for (; partialIdx < partialSize; partialIdx++)
    {
        partial = &(partials[partialIdx]);
        
        // setup partial for synthesis
        partial->state.currentSamp = index_type( (partial->startTime * m_srateHz) + 0.5 );   //  cheap rounding

        if (partial->state.currentSamp > processedSamples)
            break;
        
        partial->state.lastBreakpointIdx = PartialStruct::NoBreakpointProcessed;
        partial->state.envelope = partial->breakpoints[0].second;
        partial->state.breakpointFinished = true;

        //  cache the previous frequency (in Hz) so that it can be used to reset the phase when necessary
        partial->state.prevFrequency = m_osc.frequencyScaling() * partial->breakpoints[1].second._frequency;// 0 is null breakpoint
        
        int sampleCount = processedSamples - partial->state.currentSamp; // how much sample to be processed during this call
        int sampleDelta = samples - sampleCount; // delta when partial should start

        synthesize( *partial, buffer->data() + sampleDelta, sampleCount );
        
        if ( partial->state.lastBreakpointIdx < partial->numBreakpoints - 1)
            partialsBeingProcessed.push(partial);
    }
}
    
// ---------------------------------------------------------------------------
//  synthesize
// ---------------------------------------------------------------------------
//! Synthesize a bandwidth-enhanced sinusoidal Partial.
//!
//! \param  buffer  The samples buffer.
//! \param  samples Number of samples to be synthesized.
//! \param  p       The Partial to synthesize.
//! \return Nothing.
//! \pre    The buffer has to have capacity to contain all samples.
//! \post   This RealTimeSynthesizer's sample buffer (vector) contain synthesised
//!         partials and storeed inner state of synthesiser.
//!
void RealTimeSynthesizer::synthesize( PartialStruct &p, float * buffer, const int samples) noexcept
{
    if (p.state.lastBreakpointIdx == PartialStruct::NoBreakpointProcessed)
        m_osc.resetEnvelopes( p.state.envelope, m_srateHz );
    else
        m_osc.restoreEnvelopes( p.state.envelope );
        
    int sampleCounter = 0;
	int sampleDiff = 0;
    int i;
    for (i = p.state.lastBreakpointIdx + 1;  i < p.numBreakpoints; ++i )
    {
        index_type tgtSamp = index_type( (p.breakpoints[i].first * m_srateHz) + 0.5 );   //  cheap rounding
        
        sampleCounter += sampleDiff = tgtSamp - p.state.currentSamp;
        
        if (sampleCounter > samples)// if this breakpoint is longer...
        {
            // cropp it...
            sampleDiff -= (sampleCounter - samples); // substract the overflowing number of samples to get max possible sample diff
            sampleCounter = samples; // we can process max "samples" count
        }
        
        Breakpoint *bp = &(p.breakpoints[i].second);
        //  if the current oscillator amplitude is
        //  zero, and the target Breakpoint amplitude
        //  is not, reset the oscillator phase so that
        //  it matches exactly the target Breakpoint 
        //  phase at tgtSamp:
//        if ( m_osc.amplitude() == 0. && p.state.breakpointFinished )
        if ( i == PartialStruct::NoBreakpointProcessed + 1 && p.state.breakpointFinished )
        {
            //  recompute the phase so that it is correct
            //  at the target Breakpoint (need to do this
            //  because the null Breakpoint phase was computed
            //  from an interval in seconds, not samples, so
            //  it might be inaccurate):
            //
            //  double favg = 0.5 * ( prevFrequency + it.breakpoint().frequency() );
            //  double dphase = 2 * Pi * favg * ( tgtSamp - currentSamp ) / m_srateHz;
            
            double dphase = Pi * ( p.state.prevFrequency + m_osc.frequencyScaling() * bp->frequency() ) * ( tgtSamp - p.state.currentSamp ) * OneOverSrate;
            
            // If we transposed/pitch-shifted the sound using sample rate change, the transpose octave above would
            // mean create new signal with every second sample missing, so the partial would start earlier. If we
            // would like to have partial transposed but in the same time t0 as original,  what the new phase will be?
            // It will be the original phase with the phase change during the delta of time. What delta of time is it?
            // The start time in sample-removing pitch shifted signal would be half of time if we transpose octave up so the
            // delta time is t0 - t0/transposeFactor. So the new phase goes like this (here we do not have time t0 so we get
            // it from partial[iSamp]/float(fs)).
            double phaseFixed = (bp->phase() + 2*Pi*p.avgFrequency*p.state.currentSamp*OneOverSrate*(m_osc.frequencyScaling()-1));

            m_osc.setPhase( phaseFixed - dphase );
        }
        
        int samplesToBp = tgtSamp - p.state.currentSamp;
        m_osc.oscillate( buffer, buffer + sampleDiff, *bp, m_srateHz, samplesToBp );

		buffer += sampleDiff;// move buffer pointer
        
		p.state.currentSamp += sampleDiff;
        p.state.breakpointFinished = tgtSamp == p.state.currentSamp;

        if (p.state.breakpointFinished)
        {
            //  remember the frequency, may need it to reset the
            //  phase if a Null Breakpoint is encountered:
//            m_osc.resetEnvelopes(*bp, m_srateHz);
//            p.state.prevFrequency = bp->frequency();
            
            p.state.prevFrequency = m_osc.envelopes().frequency();
//                m_osc.setPhase(bp->phase());
        }
        
        if (sampleCounter == samples)
        {
            i--; // there is still something to be done in this break point
            break;
        }
	}
    
    p.state.envelope = m_osc.envelopes();
    p.state.lastBreakpointIdx = i;
}
    
}   //  end of namespace Loris
