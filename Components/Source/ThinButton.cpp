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
