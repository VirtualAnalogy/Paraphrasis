/*
  ==============================================================================

    ImageKnob.cpp
    Created: 29 May 2013 8:45:14pm
    Author:  Nik Reiman

  ==============================================================================
 */

#include "ImageKnob.h"

namespace teragon {

ImageKnob::ImageKnob(ThreadsafePluginParameterSet &parameters, const ParameterString &name,
                     const ResourceCache *resources, const String &imageName) :
Slider(juce::Slider::RotaryVerticalDrag, juce::Slider::NoTextBox),
PluginParameterComponent(parameters, name, resources, imageName) {
    knobWidth = imageStates->normal.getWidth();
    filmstripImageCount = imageStates->normal.getHeight() / knobWidth - 1;
    knobArea.setX(0);
    knobArea.setY(0);
    knobArea.setWidth(knobWidth);
    knobArea.setHeight(knobWidth);

    setRange(0.0, 1.0);
    setValue(parameter->getScaledValue());
}

void ImageKnob::onParameterUpdated(const PluginParameter* parameter) {
    juce::MessageManagerLock lock;
    setValue(parameter->getScaledValue());
}

void ImageKnob::valueChanged() {
    onValueChanged(getValue());
}

void ImageKnob::paint(Graphics &g) {
    if(isMouseOver() && !isMouseButtonDown()) {
        onMouseOver();
    }

    const int y = (int)(filmstripImageCount * getValue()) * knobWidth;
    knobArea.setY(y);
    const Image knobFrame = imageStates->normal.getClippedImage(knobArea);
    const Image resizedKnobFrame = knobFrame.rescaled(knobWidth, knobWidth, Graphics::highResamplingQuality);
    g.drawImageAt(resizedKnobFrame, 0, 0);
}

} // namespace teragon
