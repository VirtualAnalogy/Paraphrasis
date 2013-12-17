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
    enabledImage = imageStates->normal;
    enabledImageWidth = enabledImage.getWidth();
    enabledImageHeight = enabledImage.getHeight();
    disabledImage = imageStates->alternate;
    disabledImageWidth = disabledImage.getWidth();
    disabledImageHeight = disabledImage.getHeight();

    setLightOn(parameter->getScaledValue() > 0.5);
}

void IndicatorLight::onParameterUpdated(const PluginParameter* parameter) {
    juce::MessageManagerLock lock;
    setLightOn(parameter->getScaledValue() > 0.5);
}

void IndicatorLight::paint(juce::Graphics &g) {
    // Always draw the disabled image, since it will serve as the background. The
    // enabled image will be drawn on top of this with some degree of opacity, so
    // the light has a subtle fade effect.
    g.drawImage(disabledImage, 0, 0, getWidth(), getHeight(),
                0, 0, disabledImageWidth, disabledImageHeight);

    if (enabledOpacity > 0.0f) {
        if (enabledOpacity >= 1.0f) {
            enabledOpacity = 1.0f;
        }
        else if (enabledOpacity <= 0.0f) {
            enabledOpacity = 0.0f;
        }
        g.setOpacity(enabledOpacity);
        g.drawImage(enabledImage, 0, 0, getWidth(), getHeight(),
                    0, 0, enabledImageWidth, enabledImageHeight);
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

} // namespace teragon
