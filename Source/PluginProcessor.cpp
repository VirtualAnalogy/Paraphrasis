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
#include "Resampler.h"
#include "SdifFile.h"


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
    
    parameters.add(new teragon::BooleanParameter(kParameterReverse_name, kParameterReverse_defaultValue));
    
    parameters.pause();

    for (int i = 16; --i >= 0;)
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
    analyzer.setReverse(parameters[kParameterReverse_name]->getValue());

    analyzer.runThread();
    analyzerSync.wait();
    
    double samplePitch = parameters[kParameterSamplePitch_name]->getValue();

    m_isReady = analyzer.partials().empty() == false;
    synth.setup(analyzer.partials(), samplePitch);// partials will be moved from analyzer to synth
    
    ParaphrasisAudioProcessorEditor* editor = dynamic_cast<ParaphrasisAudioProcessorEditor *>(getActiveEditor());
    if (editor)
        editor->lightOn( m_isReady );
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
void ParaphrasisAudioProcessor::setStateInformation(const void *data, int sizeInBytes)
{
    TeragonPluginBase::setStateInformation(data, sizeInBytes);
    loadSample();
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

	// In case we have more outputs than inputs, we'll clear any output
	// channels that didn't contain input data, (because these aren't
	// guaranteed to be empty - they may contain garbage).
	for (int i = 0; i < getNumInputChannels(); ++i) {
		buffer.clear(i, 0, buffer.getNumSamples());
	}
    
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