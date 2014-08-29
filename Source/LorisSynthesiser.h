/*
  ==============================================================================

    LorisSynthesiser.h
    Created: 28 Aug 2014 4:31:27pm
    Author:  Tomas Medek

  ==============================================================================
*/

#ifndef LORISSYNTHESISER_H_INCLUDED
#define LORISSYNTHESISER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "Synthesizer.h"
#include "RealTimeSynthesizer.h"

using namespace juce;

//==============================================================================
class LorisSound : public SynthesiserSound
{
public:
    LorisSound() {}
    
    bool appliesToNote(const int /*midiNoteNumber*/)
    {
        return true;
    }
    bool appliesToChannel(const int /*midiChannel*/)
    {
        return true;
    }
};

//==============================================================================
/** A simple demo synth voice that just plays a sine wave.. */
class LorisVoice  : public SynthesiserVoice
{
public:
    LorisVoice();
    
    bool canPlaySound(SynthesiserSound* sound);
    
    void startNote(int midiNoteNumber, float velocity,
                   SynthesiserSound* /*sound*/, int /*currentPitchWheelPosition*/) override;
    
    void stopNote(bool allowTailOff) override;
    
    void pitchWheelMoved(int /*newValue*/) override;
    void controllerMoved(int /*controllerNumber*/, int /*newValue*/) override;
    void aftertouchChanged(int /*newAftertouchValue*/) override;
    
    void renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;
    
    void setup(Loris::PartialList &partials, double pitch);
    void setCurrentPlaybackSampleRate(double rate) override;
    
    
private:
    
    void stop();
    
    std::vector<double> buffer;
    int sampleIndex;
    bool play;
    
    double level;
    double tailOff;
        
    Loris::RealTimeSynthesizer synth;
    CriticalSection lock;
};

class LorisSynthesiser : public Synthesiser
{
public:
    
    void setup(Loris::PartialList &partials, double samplePitch)
    {
        allNotesOff(0, false); // clear all notes before setting new partials
        LorisVoice* voice;
        int numVoices = getNumVoices();
        for (int i = 0; i < numVoices; i++)
        {
            voice = dynamic_cast<LorisVoice *>(getVoice(i));
            if (voice)
                voice->setup(partials, samplePitch);
        }
        this->partials.clear();
        this->partials = std::move(partials);
        partials.clear();
    }

private:
    Loris::PartialList partials;
    
};


#endif  // LORISSYNTHESISER_H_INCLUDED
