#ifndef INCLUDE_REALTIME_OSCILLATOR_H
#define INCLUDE_REALTIME_OSCILLATOR_H
/*
 * This is the Loris C++ Class Library, implementing analysis, 
 * manipulation, and synthesis of digitized sounds using the Reassigned 
 * Bandwidth-Enhanced Additive Sound Model.
 *
 * Loris is Copyright (c) 1999-2010 by Kelly Fitz and Lippold Haken,
 * Copyright (c) 2014 Tomas Medek
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
 * RealtimeOscillator.h
 *
 * Implementation of class Loris::RealtimeOscillator, a Bandwidth-Enhanced RealtimeOscillator.
 *
 * Tomas Medek, 20 Sep 2014
 * tom@virtualanalogy.org
 *
 */

#include "Oscillator.h"


// from juce_PlatformDefs.h
#ifdef _MSC_VER
	#ifdef noexcept
		#undef noexcept
	#endif
	#define noexcept  throw()
	#if defined (_MSC_VER) && _MSC_VER > 1600
		#define _ALLOW_KEYWORD_MACROS 1 // (to stop VC2012 complaining)
	#endif
#endif

//  begin namespace
namespace Loris {

class Breakpoint;

// ---------------------------------------------------------------------------
//  class Oscillator
//
//! Class Oscillator represents the state of a single bandwidth-enhanced
//! sinusoidal oscillator used for synthesizing sounds from Reassigned
//! Bandwidth-Enhanced analysis data. Oscillator encapsulates the oscillator
//! state, including the instantaneous radian frequency (radians per
//! sample), amplitude, bandwidth coefficient, and phase, and a 
//! bandlimited stochastic modulator. 
//!
//! Class Synthesizer uses an instance of Oscillator to synthesize
//! bandwidth-enhanced Partials.
//
class RealtimeOscillator : public Oscillator
{
//  --- implementation ---

    double m_frequencyScaling;

//  --- interface ---
public:
//  --- construction ---

    //! Construct a new Oscillator with all state parameters initialized to 0.
    RealtimeOscillator( void );
     
    //  Copy, assignment, and destruction are free.
    //
    //  Copied and assigned Oscillators have the duplicate state
    //  variables and the filters have the same coefficients,
    //  but the state of the filter delay lines is not copied.

// --- oscillation ---
     
    //! Reset the instantaneous envelope parameters 
    //! (frequency, amplitude, bandwidth, and phase).
    //! The sample rate is needed to convert the 
    //! Breakpoint frequency (Hz) to radians per sample.
    void resetEnvelopes( const Breakpoint & bp, double srate ) noexcept override;

    //! Reset the instantaneous envelope parameters
    //! (frequency, amplitude, bandwidth, and phase).
    //! The Breakpoint frequency (Hz) is in radians per sample
    //! and is scaled by frequency scaling.
    void restoreEnvelopes( const Breakpoint & bp) noexcept;
    
    //! Set internal frequency scaling.
    void setFrequencyScaling( double scaling ) noexcept;

    //! Accumulate bandwidth-enhanced sinusoidal samples modulating the
    //! oscillator state from its current values of radian frequency, amplitude,
    //! and bandwidth to the specified target values. Accumulate samples into
    //! the half-open (STL-style) range of doubles, starting at begin, and
    //! ending before end (no sample is accumulated at end). The caller must
    //! insure that the indices are valid. Target frequency and bandwidth are
    //! checked to prevent aliasing and bogus bandwidth enhancement.
    void oscillate( float * begin, float * end, const Breakpoint & bp, double srate) noexcept;

// --- accessors ---

    //! Return the instantaneous envelope parameters
    //! (frequency, amplitude, bandwidth, and phase).
    //! The Breakpoint frequency (Hz) is in radians per sample
    //! and is scaled by frequency scaling.
    Breakpoint envelopes() noexcept;
    
    //! Retun thr frequency scaling factor.
    double frequencyScaling( void ) const noexcept{ return m_frequencyScaling; }
    
};  //  end of class RealtimeOscillator

}   //  end of namespace Loris

#endif /* ndef INCLUDE_REALTIME_OSCILLATOR_H */
