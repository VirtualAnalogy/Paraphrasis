/*
  ==============================================================================

    IndicatorLight.cpp
    Created: 29 May 2013 9:35:45pm
    Author:  Nik Reiman

  ==============================================================================
 */

#include "IndicatorLight.h"

namespace teragon {

IndicatorLight::IndicatorLight(PluginParameter *parameter,
                               const ResourceCache::ImageStates *imageStates) :
Component(String::empty),
PluginParameterObserver(),
parameter(parameter), enabledImage(imageStates->alternate),
disabledImage(imageStates->normal), enabled(false) {
    parameter->addObserver(this);
    setEnabled(parameter->getValue());
}

IndicatorLight::~IndicatorLight() {
    parameter->removeObserver(this);
}

void IndicatorLight::onParameterUpdated(const PluginParameter* parameter) {
    setEnabled(parameter->getValue());
    repaint();
}

void IndicatorLight::paint(juce::Graphics &g) {
    g.drawImage(disabledImage, 0, 0, getWidth(), getHeight(),
                0, 0, disabledImage.getWidth(), disabledImage.getHeight());

    if (enabledOpacity > 0.0f) {
        if (enabledOpacity >= 1.0f) {
            enabledOpacity = 1.0f;
        }
        else if (enabledOpacity <= 0.0f) {
            enabledOpacity = 0.0f;
        }
        g.setOpacity(enabledOpacity);
        g.drawImage(enabledImage, 0, 0, getWidth(), getHeight(),
                    0, 0, enabledImage.getWidth(), enabledImage.getHeight());
    }
}

void IndicatorLight::timerCallback() {
    enabledOpacity += stepRate;
    if (enabledOpacity >= 1.0f) {
        stopTimer();
    }
    else if (enabledOpacity <= 0.0f) {
        stopTimer();
    }
    repaint();
}

void IndicatorLight::setEnabled(bool enabled) {
    if (this->enabled != enabled) {
        this->enabled = enabled;
        this->enabledOpacity = enabled ? 0.0f : 1.0f;
        this->stepRate = (enabled ? 1.0f : -1.0f) * 0.325f;
        startTimer(33); // ~30fps
    }
}
}