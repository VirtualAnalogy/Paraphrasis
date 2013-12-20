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

#include "AnimationConstants.h"
#include "IndicatorLight.h"

namespace teragon {

IndicatorLight::IndicatorLight(ThreadsafePluginParameterSet &parameters, const ParameterString &name,
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

void IndicatorLight::onParameterUpdated(const PluginParameter* parameter) {
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
