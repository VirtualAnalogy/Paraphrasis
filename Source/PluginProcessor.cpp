/*
 ==============================================================================
 This file was auto-generated!
 It contains the basic startup code for a Juce application.
 ==============================================================================
 */
// My stuff
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ParameterDefitions.h"
// Loris
#include "Analyzer.h"
#include "AiffFile.h"
#include "PartialUtils.h"
#include "SdifFile.h"
#include "Synthesizer.h"
#include "RealTimeSynthesizer.h"

#include "Channelizer.h"

#define PAD
#ifdef PAD
  #define FUNDAMENTAL_FREQUENCY 440 //pad
#else
  #define FUNDAMENTAL_FREQUENCY 109 //pno
#endif

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
    LorisVoice() :
        tailOff(0.0), sampleIndex(0), synth(buffer)
    {
        secPerSample = 1.0 / 44100;

        lastFreqMultiplyer = 1.0;
        play = false;
    }

    bool canPlaySound(SynthesiserSound* sound)
    {
        return dynamic_cast <LorisSound*>(sound) != 0;
    }

    void startNote(int midiNoteNumber, float velocity,
                   SynthesiserSound* /*sound*/, int /*currentPitchWheelPosition*/)
    {
        level = velocity * 0.15;
        sampleIndex = 0;
        tailOff = 0.0;
        
        double freqMultiplyer = MidiMessage::getMidiNoteInHertz (midiNoteNumber) / FUNDAMENTAL_FREQUENCY;
    
        synth.resetSynth(freqMultiplyer / lastFreqMultiplyer);//scale back to original and scale to desired pitch
        
        lastFreqMultiplyer = freqMultiplyer;
        play = true;
    }

    void stopNote(bool allowTailOff)
    {
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

    void pitchWheelMoved(int /*newValue*/)
    {
        // can't be bothered implementing this for the demo!
    }

    void controllerMoved(int /*controllerNumber*/, int /*newValue*/)
    {
        // not interested in controllers in this case.
    }

    void renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
    {
        if ( !play ) return;
        
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
                    outputBuffer.addSample(i, startSample, currentSample);

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
                    outputBuffer.addSample(i, startSample, currentSample);
                
                ++startSample;
                ++sampleIndex;
            }
        }
    }
    
    void stop()
    {
        play = false;
        tailOff = 0.;
        sampleIndex = 0;
        clearCurrentNote();
    }
    
    void setup(Loris::PartialList &partials)
    {
        synth.setupRealtime(partials);
    }

private:
    std::vector<double> buffer;
    double secPerSample;
    double level, tailOff;
    int sampleIndex;
    double lastFreqMultiplyer;
    bool play;
    
    Loris::RealTimeSynthesizer synth;
};


//==============================================================================
ParaphrasisAudioProcessor::ParaphrasisAudioProcessor()
    : TeragonPluginBase(),
      ParameterObserver(),
      analyzer(formatManager, analyzerSync)
{
    parameters.add(new teragon::FrequencyParameter(kParameterSamplePitch_name, kParameterSamplePitch_minValue,
                                                   kParameterSamplePitch_maxValue, kParameterSamplePitch_defaultValue));
    parameters.add(new teragon::FrequencyParameter(kParameterFrequencyResolution_name, kParameterFrequencyResolution_minValue,
                                                   kParameterFrequencyResolution_maxValue, kParameterFrequencyResolution_defaultValue));
    parameters.add(new teragon::StringParameter(kParameterLastSamplePath_name));
    
    parameters.pause();

    for (int i = 10; --i >= 0;)
        synth.addVoice(new LorisVoice());

    synth.addSound(new LorisSound());
    
    formatManager.registerBasicFormats();
}

//==============================================================================
ParaphrasisAudioProcessor::~ParaphrasisAudioProcessor()
{

}

//==============================================================================
void ParaphrasisAudioProcessor::loadSample()
{
    analyzer.setSamplePath(parameters[kParameterLastSamplePath_name]->getDisplayText());
    analyzer.setFrequencyResolution(parameters[kParameterFrequencyResolution_name]->getValue());
    analyzer.setPitch(parameters[kParameterSamplePitch_name]->getValue());
    //        analyzer.startThread();
    analyzer.runThread();
    
    analyzerSync.wait();
    
    int numVoices = synth.getNumVoices();
    Loris::PartialList partials = analyzer.partials();
    LorisVoice* voice;
    for (int i = 0; i < numVoices; i++)
    {
        voice = dynamic_cast<LorisVoice *>(synth.getVoice(i));
        if (voice)
            voice->setup(partials);
    }
}

//==============================================================================
void ParaphrasisAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    TeragonPluginBase::prepareToPlay(sampleRate, samplesPerBlock);
    synth.setCurrentPlaybackSampleRate(sampleRate);
}
//==============================================================================
void ParaphrasisAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    TeragonPluginBase::releaseResources();
}

//==============================================================================
void ParaphrasisAudioProcessor::onParameterUpdated(const Parameter *parameter)
{

}

//==============================================================================
void ParaphrasisAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    //for (int channel = 0; channel < getNumInputChannels(); ++channel)
    //{
    //    float* channelData = buffer.getWritePointer (channel);
    // ..do something to the data...
    //}
    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    //for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    //{
    //    buffer.clear (i, 0, buffer.getNumSamples() );
    //}

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    TeragonPluginBase::processBlock(buffer, midiMessages);
    
    const int numSamples = buffer.getNumSamples();

    synth.renderNextBlock(buffer, midiMessages, 0, numSamples);
}
//==============================================================================
bool ParaphrasisAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}
//==============================================================================
AudioProcessorEditor* ParaphrasisAudioProcessor::createEditor()
{
    return new ParaphrasisAudioProcessorEditor(this, parameters, Resources::getCache(), formatManager);
}
//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ParaphrasisAudioProcessor();
}