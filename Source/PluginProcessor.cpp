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
    // setup parameters
    parameters.add(new teragon::FrequencyParameter(kParameterSamplePitch_name, kParameterSamplePitch_minValue,
                                                   kParameterSamplePitch_maxValue, kParameterSamplePitch_defaultValue));
    parameters.add(new teragon::FrequencyParameter(kParameterFrequencyResolution_name, kParameterFrequencyResolution_minValue,
                                                   kParameterFrequencyResolution_maxValue, kParameterFrequencyResolution_defaultValue));
    parameters.add(new teragon::StringParameter(kParameterLastSamplePath_name));
    parameters.add(new teragon::BooleanParameter(kParameterReverse_name, kParameterReverse_defaultValue));

    // setup synth
    for (int i = kDefaultSynthesiserVoiceNumbers; --i >= 0;)
        synth.addVoice(new LorisVoice());

    synth.addSound(new LorisSound());
    
    // setup format manager
    formatManager.registerBasicFormats();
}

//==============================================================================
ParaphrasisAudioProcessor::~ParaphrasisAudioProcessor()
{

}

//==============================================================================
void ParaphrasisAudioProcessor::analyzeSample()
{
    // upate analyzer parameters
    analyzer.setSamplePath(parameters[kParameterLastSamplePath_name]->getDisplayText());
    analyzer.setFrequencyResolution(parameters[kParameterFrequencyResolution_name]->getValue());
    analyzer.setPitch(parameters[kParameterSamplePitch_name]->getValue());
    analyzer.setReverse(parameters[kParameterReverse_name]->getValue());

    // analyze
    analyzer.runThread();
    analyzerSync.wait();
    
    // setup synth
    double samplePitch = parameters[kParameterSamplePitch_name]->getValue();
    
    m_isReady = analyzer.partials().empty() == false;
    
    synth.setup(analyzer.partials(), samplePitch);// partials will be moved from analyzer to synth
    
    // indicate analysis state
    ParaphrasisAudioProcessorEditor* editor = dynamic_cast<ParaphrasisAudioProcessorEditor *>(getActiveEditor());
    if (editor)
        editor->lightOn( m_isReady );
}

//==============================================================================
void ParaphrasisAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    // From JUCE doc:
    // The number of samples in these buffers is NOT guaranteed to be the same for
    // every callback, and may be more or less than the estimated value given to
    // prepareToPlay(). Your code must be able to cope with variable-sized blocks,
    // or you're going to get clicks and crashes!
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
    analyzeSample();// reload sample when state information changes (possible path change)
}

//==============================================================================
void ParaphrasisAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    TeragonPluginBase::processBlock(buffer, midiMessages);

	// Clear input channels.
	for (int i = 0; i < getNumInputChannels(); ++i)
    {
		buffer.clear(i, 0, buffer.getNumSamples());
	}
    
    // synthesise
    const int numSamples = buffer.getNumSamples();
    synth.renderNextBlock(buffer, midiMessages, 0, numSamples);
    
    // copy first channel to other(s) (synth is mono)
    auto synthetisedChannel = buffer.getReadPointer(0);
    for (int i = buffer.getNumChannels(); --i > 0;)
        buffer.copyFrom(i, 0, synthetisedChannel, numSamples);
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