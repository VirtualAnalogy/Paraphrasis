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

#include "PushButton.h"
#include "AnimationConstants.h"

namespace teragon {

PushButton::PushButton(ConcurrentParameterSet &parameters, const ParameterString &name,
                       const ResourceCache *resources) :
ThinButton(parameters, name, resources, "push_button"),
enabledOpacity(0.0f), stepRate(0.0f) {
    enabledImage = imageStates->normal;
    disabledImage = imageStates->alternate;
    setClickingTogglesState(true);
    // Set initial button state
    setToggleState(isParameterEnabled(), NotificationType::dontSendNotification);
    enabledOpacity = isParameterEnabled() ? 0.0f : 1.0f;
}

void PushButton::onParameterUpdated(const Parameter *parameter) {
    ThinButton::onParameterUpdated(parameter);
    postClicked();
}

void PushButton::clicked() {
    ThinButton::clicked();
    postClicked();
}

void PushButton::postClicked() {
    enabledOpacity = getToggleState() ? 1.0f : 0.0f;
    stepRate = (getToggleState() ? -1.0f : 1.0f) * kFadeDurationStepRate;
    startTimer(kAnimationTimerRateInMs);
}

void PushButton::paint(Graphics &g) {
    int buttonY = 0;
    const int buttonHeight = enabledImage.getHeight();
    const int buttonWidth = enabledImage.getWidth();

    if(gravity == kGravityBottom) {
        buttonY = getHeight() - buttonHeight;
    }

    // Draw disabled image as background
    g.drawImage(disabledImage, 0, buttonY, buttonWidth, buttonHeight,
                0, 0, buttonWidth, buttonHeight);

    if(enabledOpacity > 0.0f) {
        if(enabledOpacity > 1.0f) {
            enabledOpacity = 1.0f;
        }
        else if(enabledOpacity < 0.0f) {
            enabledOpacity = 0.0f;
        }
        g.setOpacity(enabledOpacity);
        g.drawImage(enabledImage, 0, buttonY, buttonWidth, buttonHeight,
                    0, 0, buttonWidth, buttonHeight);
    }
}

void PushButton::timerCallback() {
    enabledOpacity += stepRate;
    if(enabledOpacity >= 1.0f) {
        stopTimer();
    }
    else if (enabledOpacity <= 0.0f) {
        stopTimer();
    }
    repaint();
}

} // namespace teragon
