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
