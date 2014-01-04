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

#include "TeragonPluginBase.h"
#include "arduino-base64/Base64.h"

namespace teragon {

// Constructor /////////////////////////////////////////////////////////////////

TeragonPluginBase::TeragonPluginBase() {
    // Start with the parameter set paused, in case the plugin is created before
    // playback starts.
    parameters.pause();
}

// Playback ////////////////////////////////////////////////////////////////////

void TeragonPluginBase::prepareToPlay(double, int) {
    parameters.resume();
}

void TeragonPluginBase::processBlock(AudioSampleBuffer &buffer, MidiBuffer &) {
    parameters.processRealtimeEvents();

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for(int i = getNumInputChannels(); i < getNumOutputChannels(); ++i) {
        buffer.clear(i, 0, buffer.getNumSamples());
    }
}

void TeragonPluginBase::releaseResources() {
    parameters.pause();
}

// Plugin properties ///////////////////////////////////////////////////////////

bool TeragonPluginBase::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool TeragonPluginBase::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

// Parameter handling //////////////////////////////////////////////////////////

int TeragonPluginBase::getNumParameters() {
    return parameters.size();
}

float TeragonPluginBase::getParameter(int index) {
    return (float)parameters[index]->getScaledValue();
}

void TeragonPluginBase::setParameter(int index, float newValue) {
    parameters.setScaled((const size_t)index, newValue);
}

const String TeragonPluginBase::getParameterName(int index) {
    return parameters[index]->getName();
}

const String TeragonPluginBase::getParameterText(int index) {
    return parameters[index]->getDisplayText();
}

bool TeragonPluginBase::isMetaParameter(int index) const {
    return (dynamic_cast<VoidParameter *>(parameters[index]) == nullptr);
}

// State save/restore //////////////////////////////////////////////////////////

void TeragonPluginBase::getStateInformation(MemoryBlock &destData) {
    // Save all parameters in the set, handling string/blob/numeric types with
    // correct serialization to XML.
    XmlElement xml(getName());
    for(size_t i = 0; i < parameters.size(); ++i) {
        Parameter *parameter = parameters[i];
        const String attributeName = parameter->getSafeName();
        // Do not serialize the version parameter, it must be set by the plugin
        // and not overridden
        if(attributeName == "Version") {
            continue;
        }

        if(dynamic_cast<StringParameter *>(parameter) != nullptr) {
            // Convert parameter strings to juce strings
            const String value = parameter->getDisplayText();
            xml.setAttribute(attributeName, value);
        }
        else if(dynamic_cast<BlobParameter *>(parameter) != nullptr) {
            // Use base64 encoding for binary blob data
            BlobParameter *blobParameter = dynamic_cast<BlobParameter *>(parameter);
            size_t blobSize = blobParameter->getDataSize();
            char *encodedBlob = new char[base64_enc_len(blobSize)];
            base64_encode(encodedBlob, (char*)blobParameter->getData(), blobSize);
            xml.setAttribute(attributeName, encodedBlob);
            delete [] encodedBlob;
        }
        else if(dynamic_cast<IntegerParameter *>(parameter) != nullptr) {
            // Serialize integer parameters with the proper call
            xml.setAttribute(attributeName, (int)parameter->getValue());
        }
        else if(dynamic_cast<VoidParameter *>(parameter) != nullptr) {
            // Skip void parameters, these don't contain any interesting values
            continue;
        }
        else {
            // All other parameters can be serialized as doubles
            xml.setAttribute(attributeName, (double)parameter->getValue());
        }
    }

    // Save XML data to disk (via the host, that is)
    copyXmlToBinary(xml, destData);
}

void TeragonPluginBase::setStateInformation(const void *data, int sizeInBytes) {
    // Restore parameter values from serialized XML state
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if(xmlState != 0 && xmlState->hasTagName(getName())) {
        for(size_t i = 0; i < parameters.size(); i++) {
            Parameter *parameter = parameters[i];
            const String attributeName = parameter->getSafeName();
            // Check to make sure that this parameter exists in the saved XML state. We
            // could run into problems when a newer version of this plugin introduces new
            // parameters which may not necessarily exist in saved documents from older
            // versions. In such cases, new parameters will retain their default values.
            if(xmlState->hasAttribute(attributeName)) {
                if(dynamic_cast<StringParameter *>(parameter) != nullptr) {
                    // Convert juce strings to binary data events
                    juce::String value = xmlState->getStringAttribute(attributeName);
                    parameters.setData(parameter, value.toStdString().c_str(),
                                       (const size_t)value.length());
                }
                else if(dynamic_cast<BlobParameter *>(parameter) != nullptr) {
                    // Base64 decode the serialized string to binary blob data
                    juce::String value = xmlState->getStringAttribute(attributeName);
                    char *rawValue = const_cast<char *>(value.toRawUTF8());
                    char *blob = new char[base64_dec_len(rawValue, value.length())];
                    int blobSize = base64_decode(blob, rawValue, value.length());
                    parameters.setData(parameter, blob, (const size_t)blobSize);
                    delete [] blob;
                }
                else if(dynamic_cast<IntegerParameter *>(parameter) != nullptr) {
                    // Treat integer parameters as real integers
                    parameters.set(parameter, xmlState->getIntAttribute(attributeName));
                }
                else {
                    // Everything else can be handled as a double
                    parameters.set(parameter, xmlState->getDoubleAttribute(attributeName));
                }
            }
        }

        // Force parameters to be applied immediately
        parameters.processRealtimeEvents();
    }
}

} // namespace teragon
