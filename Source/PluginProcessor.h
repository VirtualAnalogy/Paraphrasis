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
#include "LorisSynthesiser.h"

using namespace teragon;

//==============================================================================
/**
 Paraphrasis processor class. 
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
    
    virtual void setStateInformation(const void *data, int sizeInBytes) override;

    // PluginParameterObserver methods
    virtual bool isRealtimePriority() const override { return true; }
    virtual void onParameterUpdated(const Parameter *parameter) override;

    // my methods
    void analyzeSample();

    /** Is processor (analysis data) ready for synthesis? */
    bool isReady()
    {
        return m_isReady;
    }

private:
    String loadedSamplePath;    // Path to actual data
    bool m_isReady = false;     // Is processor (analysis data) ready for synthesis?

    // the synth!
    LorisSynthesiser synth;     // Loris wrapper
    SampleAnalyzer analyzer;    // Data analyzer and loader
    WaitableEvent analyzerSync; // Wait for analyzer to finish

    AudioFormatManager  formatManager; // For loading input data (audio files)
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParaphrasisAudioProcessor)
};
#endif  // PLUGINPROCESSOR_H_INCLUDED
