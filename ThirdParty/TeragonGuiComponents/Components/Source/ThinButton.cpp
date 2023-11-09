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

#include "ThinButton.h"

namespace teragon {

ThinButton::ThinButton(ConcurrentParameterSet &parameters, const ParameterString &name,
                       const ResourceCache *resources, const String &imageName) :
ImageButton(String()),
PluginParameterComponent(parameters, name, resources, imageName),
gravity(kGravityDefault) {
    juce::ImageButton::setImages(false, false, true,
                                 imageStates->normal, 1.0f, Colour(0x0),
                                 Image(), 1.0f, Colour(0x0),
                                 imageStates->alternate, 1.0, Colour(0x0));
}

void ThinButton::clicked() {
    onValueChanged(getToggleState());
}

bool ThinButton::isParameterEnabled() const {
    return parameter->getScaledValue() > 0.5;
}

void ThinButton::onParameterUpdated(const Parameter*) {
    juce::MessageManagerLock lock;
    setToggleState(isParameterEnabled(), NotificationType::dontSendNotification);
}

void ThinButton::paint(Graphics &g) {
    const Image buttonStateImage = getImageForButtonState();
    int buttonY = 0;
    const int buttonHeight = buttonStateImage.getHeight();
    const int buttonWidth = buttonStateImage.getWidth();

    if(gravity == kGravityBottom) {
        buttonY = getHeight() - buttonHeight;
    }

    g.drawImage(buttonStateImage, 0, buttonY, buttonWidth, buttonHeight,
                0, 0, buttonWidth, buttonHeight);
}

} // namespace teragon
