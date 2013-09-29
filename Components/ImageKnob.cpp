/*
  ==============================================================================

    ImageKnob.cpp
    Created: 29 May 2013 8:45:14pm
    Author:  Nik Reiman

  ==============================================================================
 */

#include "ImageKnob.h"

namespace teragon {

ImageKnob::ImageKnob(PluginParameter *parameter, const ResourceCache::ImageStates *imageStates) :
Slider(juce::Slider::RotaryVerticalDrag, juce::Slider::NoTextBox),
PluginParameterObserver(),
parameter(parameter), knobImage(imageStates->normal) {
    parameter->addObserver(this);
    setRange(0.0, 1.0);
    setValue(parameter->getScaledValue());
}

ImageKnob::~ImageKnob() {
    parameter->removeObserver(this);
}

void ImageKnob::onParameterUpdated(const PluginParameter* parameter) {
    setValue(parameter->getScaledValue());
}

void ImageKnob::valueChanged() {
    parameter->setScaledValue(getValue());
}

void ImageKnob::paint(Graphics &g) {
    const int knobWidth = knobImage.getWidth();
    double filmstripImageCount = knobImage.getHeight() / knobWidth - 1;
    int imageIndex = (int) (filmstripImageCount * getValue()) * knobWidth;

    Rectangle<int> knobArea(0, imageIndex, knobWidth, knobWidth);
    Image knobFrame = knobImage.getClippedImage(knobArea);
    Image resizedKnobFrame = knobFrame.rescaled(knobWidth, knobWidth, Graphics::highResamplingQuality);

    g.drawImageAt(resizedKnobFrame, 0, 0);
}

} // namespace teragon
