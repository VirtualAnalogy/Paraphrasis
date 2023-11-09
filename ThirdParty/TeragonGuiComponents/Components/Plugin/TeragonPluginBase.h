/*
 * Copyright (c) 2013 - Teragon Audio LLC
 *
 * Permission is granted to use this software under the terms of either:
 * a) the GPL v2 (or any later version)
 * b) the Affero GPL v3
 *
 * Details of these licenses can be found at: www.gnu.org/licenses
 *
 * This software is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * ------------------------------------------------------------------------------
 *
 * This software uses the JUCE library.
 *
 * To release a closed-source product which uses JUCE, commercial licenses are
 * available: visit www.juce.com for more information.
 */

#ifndef TERAGONPLUGINBASE_H_INCLUDED
#define TERAGONPLUGINBASE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginParameters.h"

namespace teragon {

class TeragonPluginBase : public AudioProcessor {
public:
    // Constructor /////////////////////////////////////////////////////////////////
    TeragonPluginBase();
    virtual ~TeragonPluginBase() {}

    // Playback ////////////////////////////////////////////////////////////////////
    virtual void prepareToPlay(double sampleRate, int samplesPerBlock);
    virtual void processBlock(AudioSampleBuffer &buffer, MidiBuffer &midiMessages);
    virtual void releaseResources();

    // Plugin properties ///////////////////////////////////////////////////////////
    virtual const String getName() const = 0;
    virtual bool acceptsMidi() const;
    virtual bool producesMidi() const;
    virtual bool isInputChannelStereoPair(int index) const { return true; }
    virtual bool isOutputChannelStereoPair(int index) const { return true; }
    virtual bool silenceInProducesSilenceOut() const { return true; }
    virtual double getTailLengthSeconds() const { return 0.0; }
    virtual const String getInputChannelName(int i) const { return String(i + 1); }
    virtual const String getOutputChannelName(int i) const { return String(i + 1); }

    // Editor //////////////////////////////////////////////////////////////////////
    virtual AudioProcessorEditor *createEditor() = 0;
    virtual bool hasEditor() const { return true; }

    // Parameter handling //////////////////////////////////////////////////////////
    virtual int getNumParameters();
    virtual float getParameter(int index);
    virtual void setParameter(int index, float newValue);
    virtual const String getParameterName(int index);
    virtual const String getParameterText(int index);
    virtual bool isMetaParameter(int parameterIndex) const;

    // Program handling ////////////////////////////////////////////////////////////
    virtual int getNumPrograms() { return 0; }
    virtual int getCurrentProgram() { return 0; }
    virtual void setCurrentProgram(int index) {}
    virtual const String getProgramName(int index) { return String(); }
    virtual void changeProgramName(int index, const String &newName) {}

    // State save/restore //////////////////////////////////////////////////////////
    virtual void getStateInformation(MemoryBlock &destData);
    virtual void setStateInformation(const void *data, int sizeInBytes);

protected:
    ConcurrentParameterSet parameters;
};

} // namespace teragon

#endif  // TERAGONPLUGINBASE_H_INCLUDED

