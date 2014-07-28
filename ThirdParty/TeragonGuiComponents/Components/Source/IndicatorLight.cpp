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

#include "IndicatorLight.h"
#include "AnimationConstants.h"

namespace teragon {

IndicatorLight::IndicatorLight(ConcurrentParameterSet &parameters, const ParameterString &name,
                               const ResourceCache *resources) :
Component(String::empty),
PluginParameterComponent(parameters, name, resources, "indicator_light"),
lightOn(false), pulse(false) {
    enabledImage = imageStates->normal;
    enabledImageWidth = enabledImage.getWidth();
    enabledImageHeight = enabledImage.getHeight();
    disabledImage = imageStates->alternate;
    disabledImageWidth = disabledImage.getWidth();
    disabledImageHeight = disabledImage.getHeight();

    setLightOn(parameter->getScaledValue() > 0.5);
}

void IndicatorLight::onParameterUpdated(const Parameter* parameter) {
    juce::MessageManagerLock lock;

    // For VoidParameter, we simply pulse the light
    if(dynamic_cast<const VoidParameter*>(parameter) != nullptr) {
        setLightOn(true, true);
    }
    else {
        setLightOn(parameter->getScaledValue() > 0.5);
    }
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
        if(pulse) {
            if(pulseHoldFrames-- <= 0) {
                setLightOn(false);
            }
        }
        else {
            stopTimer();
        }
    }
    else if (enabledOpacity <= 0.0f) {
        stopTimer();
    }
    repaint();
}

void IndicatorLight::setLightOn(bool lightOn, bool pulse) {
    if (this->lightOn != lightOn) {
        this->lightOn = lightOn;
        this->enabledOpacity = lightOn ? 0.0f : 1.0f;
        this->stepRate = (lightOn ? 1.0f : -1.0f) * kFadeDurationStepRate;
        this->pulse = pulse;
        if(pulse) {
            pulseHoldFrames = (int)(kFadeDurationInMs / kAnimationFrameRate);
        }
        startTimer(kAnimationTimerRateInMs);
    }
}

} // namespace teragon
