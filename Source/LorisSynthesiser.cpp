/*
  This is Paraphrasis synthesiser.
 
  Copyright (c) 2014 by Tomas Medek
 
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
 
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY, without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.
 
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 
  tom@virtualanalogy.com
 
*/

#include "LorisSynthesiser.h"
#include "ParameterDefitions.h"

//==============================================================================
/** Create new instance.
    @param tailTimeSec lenght of tail of the sound
 */
LorisVoice::LorisVoice(double tailTimeSec) :  tailTimeSec(tailTimeSec), synth(buffer)
{
    synthesise = false;
    tailOff = false;
    
    tailSamples = tailTimeSec * getSampleRate();
    
    buffer.reserve(kDefaultSynthesiserBufferSize);
}

//==============================================================================
bool LorisVoice::canPlaySound(SynthesiserSound* sound) noexcept
{
    return dynamic_cast <LorisSound*>(sound) != 0;
}

//==============================================================================
void LorisVoice::startNote(int midiNoteNumber, float velocity,
               SynthesiserSound* /*sound*/, int /*currentPitchWheelPosition*/) noexcept
{
    // This will be called during the rendering callback, so must be fast and thread-safe.
    const ScopedLock sl(lock);
    
    level = velocity;
    tailOff = false;
    
    synth.reset();
    synth.setPitch(MidiMessage::getMidiNoteInHertz (midiNoteNumber));
    
    synthesise = true;
}

//==============================================================================
void LorisVoice::stopNote(float /*velocity*/, bool allowTailOff) noexcept
{
    // This will be called during the rendering callback, so must be fast and thread-safe.
    
    if (allowTailOff)
    {
        // start a tail-off by setting this flag. The render callback will pick up on
        // this and do a fade out, calling clearCurrentNote() when it's finished.
        if (tailOff == false)
            tailOff = true;
    }
    else
    {
        // we're being told to stop playing immediately, so reset everything..
        stop();
    }
}

//==============================================================================
void LorisVoice::pitchWheelMoved(int /*newValue*/) noexcept
{
    // This will be called during the rendering callback, so must be fast and thread-safe.
    
}

//==============================================================================
void LorisVoice::controllerMoved(int /*controllerNumber*/, int /*newValue*/) noexcept
{
    // This will be called during the rendering callback, so must be fast and thread-safe.
    
}

//==============================================================================
void LorisVoice::aftertouchChanged(int /*newAftertouchValue*/) noexcept
{
    // This will be called during the rendering callback, so must be fast and thread-safe.
    
}

//==============================================================================
/** Setup voice to imitate sound with given partials. */
void LorisVoice::renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples) noexcept
{
    if (!synthesise) return;
    
    const ScopedLock sl(lock);
    
    synth.synthesizeNext(numSamples);
    
    double tailDiff = 0.;
    
    if (tailOff)
    {
        tailDiff = level * (double) numSamples / (double) tailSamples;// change level due to tail position
        if (level < tailDiff) // prevent negative gain
            tailDiff = level;
    }

    outputBuffer.addFromWithRamp(0, startSample, buffer.data(), numSamples, level, level - tailDiff);
    
    if (tailOff)
    {
        level -= tailDiff;

        if (level <= 0.005) // this number is from Juce synthesiser tutorial.
            stop();
    }
}

//==============================================================================
/** Stop current note. */
void LorisVoice::stop() noexcept
{
    synthesise = false;
    tailOff = false;
    clearCurrentNote();
}

//==============================================================================
void LorisVoice::setup(Loris::PartialList &partials, double pitch) noexcept
{
    const ScopedLock sl(lock);
    synth.setup(partials, pitch);
}

//==============================================================================
void LorisVoice::setCurrentPlaybackSampleRate(double rate) noexcept
{
    const ScopedLock sl(lock);
    
    SynthesiserVoice::setCurrentPlaybackSampleRate(rate);
    
    synth.setSampleRate(getSampleRate());
    
    tailSamples = tailTimeSec * getSampleRate();
}