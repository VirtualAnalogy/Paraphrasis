/*
  ==============================================================================

    LorisSynthesiser.cpp
    Created: 28 Aug 2014 4:31:27pm
    Author:  Tomas Medek

  ==============================================================================
*/

#include "LorisSynthesiser.h"

//==============================================================================
LorisVoice::LorisVoice() : tailOff(0.0), sampleIndex(0), synth(buffer)
{
    play = false;
}

//==============================================================================
bool LorisVoice::canPlaySound(SynthesiserSound* sound)
{
    return dynamic_cast <LorisSound*>(sound) != 0;
}

//==============================================================================
void LorisVoice::startNote(int midiNoteNumber, float velocity,
               SynthesiserSound* /*sound*/, int /*currentPitchWheelPosition*/)
{
    // This will be called during the rendering callback, so must be fast and thread-safe.
    const ScopedLock sl(lock);
    
    level = velocity;
    sampleIndex = 0;
    tailOff = 0.0;
    
    synth.reset();
    synth.playNote(MidiMessage::getMidiNoteInHertz (midiNoteNumber));
    
    play = true;
}

//==============================================================================
void LorisVoice::stopNote(bool allowTailOff)
{
    // This will be called during the rendering callback, so must be fast and thread-safe.
    
    if (allowTailOff)
    {
        // start a tail-off by setting this flag. The render callback will pick up on
        // this and do a fade out, calling clearCurrentNote() when it's finished.
        
        if (tailOff == 0.0) // we only need to begin a tail-off if it's not already doing so - the
            // stopNote method could be called more than once.
            tailOff = 1.0;
    }
    else
    {
        // we're being told to stop playing immediately, so reset everything..
        stop();
    }
}

//==============================================================================
void LorisVoice::pitchWheelMoved(int /*newValue*/)
{
    // This will be called during the rendering callback, so must be fast and thread-safe.
    
}

//==============================================================================
void LorisVoice::controllerMoved(int /*controllerNumber*/, int /*newValue*/)
{
    // This will be called during the rendering callback, so must be fast and thread-safe.
    
}

//==============================================================================
void LorisVoice::aftertouchChanged(int /*newAftertouchValue*/)
{
    // This will be called during the rendering callback, so must be fast and thread-safe.
    
}

//==============================================================================
void LorisVoice::renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
    if (!play)
    {
        return;
    }
    
    const ScopedLock sl(lock);
    
    synth.synthesizeNext(numSamples);
    
    if (tailOff > 0.)
    {
        while (--numSamples >= 0)
        {
            double currentSample = sampleIndex < buffer.size() ? buffer[sampleIndex] * tailOff : 0.0;
            
            tailOff *= 0.99;
            
            if (tailOff <= 0.005)
            {
                stop();
                break;
            }
            
            for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                outputBuffer.addSample(i, startSample, level * currentSample);
            
            ++startSample;
            ++sampleIndex;
        }
    }
    else
    {
        while (--numSamples >= 0)
        {
            double currentSample = sampleIndex < buffer.size() ? buffer[sampleIndex] : 0.0;
            
            for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                outputBuffer.addSample(i, startSample, level * currentSample);
            
            ++startSample;
            ++sampleIndex;
        }
    }
}

//==============================================================================
void LorisVoice::stop()
{
    play = false;
    tailOff = 0.;
    sampleIndex = 0;
    clearCurrentNote();
}

//==============================================================================
void LorisVoice::setup(Loris::PartialList &partials, double pitch)
{
    const ScopedLock sl(lock);
    synth.setup(partials, pitch);
}

//==============================================================================
void LorisVoice::setCurrentPlaybackSampleRate(double rate)
{
    const ScopedLock sl(lock);
    SynthesiserVoice::setCurrentPlaybackSampleRate(rate);
    synth.setSampleRate(getSampleRate());
}