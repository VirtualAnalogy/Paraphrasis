/*
  ==============================================================================
    This file was auto-generated!
    It contains the basic startup code for a Juce application.
  ==============================================================================
*/
#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
// teragon
#include "TeragonPluginBase.h"
#include "PluginParameters.h"
// Loris
#include "PartialList.h"

using namespace teragon;

static const char* kParameterSamplePitch_name = "Sample Pitch";
static const  int kParameterSamplePitch_minValue = 50;
static const  int kParameterSamplePitch_maxValue = 10000;
static const  int kParameterSamplePitch_defaultValue = 440;


static const char* kParameterFrequencyResolution_name = "Frequency Resolution";
static const  int kParameterFrequencyResolution_minValue = 30;
static const  int kParameterFrequencyResolution_maxValue = 10000;
static const  int kParameterFrequencyResolution_defaultValue = 40;

//==============================================================================
/**
*/
class ParaphrasisAudioProcessor  : public TeragonPluginBase, ParameterObserver
{

public:
    //==============================================================================
    ParaphrasisAudioProcessor();
    ~ParaphrasisAudioProcessor();
    
    const String getName() const override { return JucePlugin_Name; }
    
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages) override;
    
    // PluginParameterObserver methods
    virtual bool isRealtimePriority() const override { return true; }
    virtual void onParameterUpdated(const Parameter *parameter) override;

private:
    Loris::PartialList partials;

    // the synth!
    Synthesiser synth;

    void initLoris();
    void initLogging();
    void deleteLogger();
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParaphrasisAudioProcessor)
};
#endif  // PLUGINPROCESSOR_H_INCLUDED
