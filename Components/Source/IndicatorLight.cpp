/*
  ==============================================================================

    IndicatorLight.cpp
    Created: 29 May 2013 9:35:45pm
    Author:  Nik Reiman

  ==============================================================================
 */

#include "IndicatorLight.h"

namespace teragon {

IndicatorLight::IndicatorLight(ThreadsafePluginParameterSet &parameters, const ParameterString &name,
                               const ResourceCache *resources) :
Component(String::empty),
PluginParameterComponent(parameters, name, resources, "indicator_light"),
lightOn(false) {
    setLightOn(parameter->getValue());
}

void IndicatorLight::onParameterUpdated(const PluginParameter* parameter) {
    setLightOn(parameter->getValue());
    repaint();
}

void IndicatorLight::paint(juce::Graphics &g) {
    Image enabledImage = imageStates->normal;
    Image disabledImage = imageStates->alternate;

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

void IndicatorLight::setLightOn(bool lightOn) {
    if (this->lightOn != lightOn) {
        this->lightOn = lightOn;
        this->enabledOpacity = lightOn ? 0.0f : 1.0f;
        this->stepRate = (lightOn ? 1.0f : -1.0f) * 0.325f;
        startTimer(33); // ~30fps
    }
}
}