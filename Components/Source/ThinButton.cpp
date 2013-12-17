/*
  ==============================================================================

    ThinButton.cpp
    Created: 30 May 2013 8:47:07pm
    Author:  Nik Reiman

  ==============================================================================
*/

#include "ThinButton.h"

namespace teragon {

ThinButton::ThinButton(ThreadsafePluginParameterSet &parameters, const ParameterString &name,
                       const ResourceCache *resources, const String &imageName) :
ImageButton(String::empty),
PluginParameterComponent(parameters, name, resources, imageName),
gravity(kGravityDefault) {
    juce::ImageButton::setImages(false, false, true,
                                 imageStates->normal, 1.0f, Colour(0x0),
                                 Image::null, 1.0f, Colour(0x0),
                                 imageStates->alternate, 1.0, Colour(0x0));
}

void ThinButton::clicked() {
    onValueChanged(getToggleState());
}

bool ThinButton::isParameterEnabled() const {
    return parameter->getScaledValue() > 0.5;
}

void ThinButton::onParameterUpdated(const PluginParameter* parameter) {
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
