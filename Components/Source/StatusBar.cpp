/*
Copyright (c) 2013 Teragon Audio. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/

#include "StatusBar.h"
#include "PluginParameterComponent.h"
#include "AnimationConstants.h"

namespace teragon {

StatusBar::StatusBar(ConcurrentParameterSet &parameters, const ResourceCache*) :
juce::Component(), juce::Timer(), ParameterObserver(),
parameters(parameters), labelOpacity(1.0), clearTimeout(0) {
    addAndMakeVisible(&parameterNameLabel);
    addAndMakeVisible(&parameterValueLabel);
}

void StatusBar::subscribeToParameters() {
    for(size_t i = 0; i < parameters.size(); ++i) {
        Parameter *parameter = parameters[i];
        // Only update the parameter if it has at least one other component listening to it. Otherwise
        // we risk showing a bunch of internal parameters which we may not want to expose.
        for(size_t j = 0; j < parameter->getNumObservers(); ++j) {
            ParameterObserver *observer = parameter->getObserver(j);
            PluginParameterComponent *component = dynamic_cast<PluginParameterComponent*>(observer);
            if(observer != this && component != nullptr) {
                parameter->addObserver(this);
                component->setStatusObserver(this);
            }
        }
    }
}

void StatusBar::ignoreParameter(const ParameterString &name) {
    Parameter *parameter = parameters[name];
    if(parameter != nullptr) {
        parameter->removeObserver(this);
    }
}

void StatusBar::resized() {
    Component::resized();
    const int labelHeight = (getHeight() - kPadding) / 2;
    parameterNameLabel.setBounds(0, 0, getWidth(), labelHeight);
    parameterValueLabel.setBounds(0, labelHeight + kPadding, getWidth(), labelHeight);
    configureLabelProperties(parameterNameLabel);
    configureLabelProperties(parameterValueLabel);
}

const Font StatusBar::getFont() {
    return Font(Font::getDefaultMonospacedFontName(), (float)kFontSize, Font::plain);
}

void StatusBar::configureLabelProperties(Label &label) {
    label.setColour(Label::textColourId, Colours::black);
    label.setFont(getFont());
}

StatusBar::~StatusBar() {
    for(size_t i = 0; i < parameters.size(); ++i) {
        parameters[i]->removeObserver(this);
    }
}

void StatusBar::onParameterUpdated(const Parameter *parameter) {
    juce::MessageManagerLock lock;
    displayParameter(parameter);
}

void StatusBar::displayParameter(const Parameter *parameter) {
    parameterNameLabel.setText(parameter->getName());
    parameterValueLabel.setText(parameter->getDisplayText());

    labelOpacity = 1.0f;
    clearTimeout = kClearTimeoutInMs / kAnimationFrameRate;
    if (!isTimerRunning()) {
        startTimer(kAnimationTimerRateInMs);
    }
}

void StatusBar::timerCallback() {
    // Displaying text at full opacity
    if(clearTimeout > 0) {
        --clearTimeout;
        parameterNameLabel.setAlpha(1.0f);
        parameterValueLabel.setAlpha(1.0f);
    }
    // Fadeout has started
    else if(labelOpacity > 0.0f) {
        labelOpacity -= kFadeDurationStepRate;
        parameterNameLabel.setAlpha(labelOpacity);
        parameterValueLabel.setAlpha(labelOpacity);
    }
    // Fadeout finished, hide the text and stop the timer
    else {
        parameterNameLabel.setText(String::empty);
        parameterValueLabel.setText(String::empty);
        stopTimer();
    }
}
} // namespace teragon
