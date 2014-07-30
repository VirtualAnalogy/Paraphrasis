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
// My
#include "SampleAnalyzer.h"

using namespace teragon;

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

    void loadSample();

private:
    Loris::PartialList partials;

    // the synth!
    Synthesiser synth;

    SampleAnalyzer analyzer;
    WaitableEvent analyzerSync;
    AudioFormatManager  formatManager;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParaphrasisAudioProcessor)
};
#endif  // PLUGINPROCESSOR_H_INCLUDED
