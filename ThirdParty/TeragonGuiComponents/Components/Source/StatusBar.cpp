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
