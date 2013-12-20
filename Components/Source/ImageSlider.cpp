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

#include "ImageSlider.h"
#include "PluginParameterComponent.h"

namespace teragon {

ImageSlider::ImageSlider(ThreadsafePluginParameterSet &parameters, const ParameterString &name,
                         const ResourceCache *resources) :
Slider(juce::Slider::LinearVertical, juce::Slider::NoTextBox),
PluginParameterComponent(parameters, name, resources, "slider") {
    handleImage = imageStates->normal;
    wellImage = imageStates->background;
    offset = handleImage.getHeight() / 4 + 1;

    setRange(0.0, 1.0);
    setValue(parameter->getValue());
}

void ImageSlider::valueChanged() {
    onValueChanged(getValue());
}

void ImageSlider::onParameterUpdated(const PluginParameter* parameter) {
    juce::MessageManagerLock lock;
    setValue(parameter->getScaledValue());
}

void ImageSlider::paint(Graphics &g) {
    if(isMouseOver() && !isMouseButtonDown()) {
        onMouseOver();
    }

    const int handleX = (getWidth() - handleImage.getWidth()) / 2;
    const int yRange = getHeight() - handleImage.getHeight() / 2;
    // Mysterious logic... o_O Not sure why this handle is so tough to position, even
    // at position == 0, it is ~20px below the top of the well. Not sure why this is,
    // but this arithmetic seems to put it in the right position.
    const int position = (int)(yRange - (yRange * (getValue() / getMaximum() - getMinimum())) + 1);
    g.drawImageAt(wellImage, 0, 0);
    g.drawImageAt(handleImage, handleX, position - offset);
}

} // namespace teragon
