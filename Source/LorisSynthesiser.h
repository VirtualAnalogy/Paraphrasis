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

#ifndef LORISSYNTHESISER_H_INCLUDED
#define LORISSYNTHESISER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "Synthesizer.h"
#include "RealTimeSynthesizer.h"
#include "Resampler.h"

using namespace juce;

//==============================================================================
/** Describes the sounds that LorisSynthesiser can play. */
class LorisSound : public SynthesiserSound
{
public:
    LorisSound() {}
    
    bool appliesToNote(const int /*midiNoteNumber*/)  noexcept override { return true; }
    bool appliesToChannel(const int /*midiChannel*/)  noexcept override { return true; }
};

//==============================================================================
/**
 * Loris synthesiser voice for LorisSynthesiser. It makes a sound based on Partials
 * generated from Loris analysis. It synthesise only in mono!
 */
class LorisVoice : public SynthesiserVoice
{
    enum BufferSize { kDefaultSynthesiserBufferSize = 8192 };
    
public:
    /** Create new instance.
       @param tailTimeSec lenght of tail of the sound
     */
    LorisVoice(double tailTimeSec = 0.01);
    
    bool canPlaySound(SynthesiserSound* sound) noexcept override;
    
    void startNote(int midiNoteNumber, float velocity,
                   SynthesiserSound* /*sound*/, int /*currentPitchWheelPosition*/) noexcept override;
    
    void stopNote(float /*velocity*/, bool allowTailOff) noexcept override;
    
    void pitchWheelMoved(int /*newValue*/)  noexcept override;
    void controllerMoved(int /*controllerNumber*/, int /*newValue*/) noexcept override;
    void aftertouchChanged(int /*newAftertouchValue*/)  noexcept override;
    
    void renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples) noexcept override;
    
    void setCurrentPlaybackSampleRate(double rate) noexcept override;
    
    /** Setup voice to imitate sound with given partials. */
    void setup(Loris::PartialList &partials, double pitch) noexcept;
    
private:
    
    /** Stop current note. */
    void stop() noexcept;
    
    bool synthesise;      // Flag to determine if synthesiser should synthesise
    
    double level;         // Gain of synthesised sound.
    
    double tailOff;       //
    int tailSamples;      // Lenght of tail in samples.
    double tailTimeSec;   // Lenght of tail in seconds.
        
    Loris::RealTimeSynthesizer synth;  // This makes the sound.
    CriticalSection lock; // For safe processing.
    
    std::vector<float> buffer;         // Synthesiser's innner buffer.
};

//==============================================================================
/**
   LorisSynthesiser voice for LorisSynthesiser. It makes a sound based on Partials
   generated from Loris analysis.
 */
class LorisSynthesiser : public Synthesiser
{
public:
    
    /**
       Setup synthesiser's voices using partials.
       @param partials data gathered at analysis stage
       @param samplePitch original pitch of partils data.
     */
    void setup(Loris::PartialList &partials, double samplePitch)
    {
        allNotesOff(0, false); // clear all notes before setting new partials
        
        this->partials.clear();
        this->partials = std::move(partials);
        partials.clear(); // invalidate partials due to std::move
        
        this->samplePitch = samplePitch;
        
        update(this->partials, this->samplePitch);
    }
    
    void setCurrentPlaybackSampleRate(double newRate) override
    {
        juce::Synthesiser::setCurrentPlaybackSampleRate(newRate);
    
        update(this->partials, this->samplePitch);
    }

private:
    Loris::PartialList partials;
    double samplePitch;
    
    void update(Loris::PartialList &partials, double samplePitch)
    {
        Loris::PartialList resampledPartials(partials);
        
        if ( ! resampledPartials.empty() )
        {
            Loris::Resampler resampler(1 / getSampleRate());
            resampler.setPhaseCorrect(true);
            resampler.quantize(resampledPartials.begin(), resampledPartials.end());
        }
        
        LorisVoice *voice;
        int numVoices = getNumVoices();
        for (int i = 0; i < numVoices; i++)
        {
            voice = dynamic_cast<LorisVoice *>(getVoice(i));
            if (voice)
                voice->setup(resampledPartials, samplePitch);
        }
    }
    
};


#endif  // LORISSYNTHESISER_H_INCLUDED
