/*
  ==============================================================================

    ImageKnob.cpp
    Created: 29 May 2013 8:45:14pm
    Author:  Nik Reiman

  ==============================================================================
 */

#include "ImageKnob.h"

namespace teragon {

ImageKnob::ImageKnob(PluginParameter *parameter, const char* knobImage, const int knobImageSize) :
Slider(juce::Slider::RotaryVerticalDrag, juce::Slider::NoTextBox),
PluginParameterObserver(),
parameter(parameter), knobImage() {
    parameter->addObserver(this);
    setRange(parameter->getMinValue(), parameter->getMaxValue());
    setImages(ImageCache::getFromMemory(knobImage, knobImageSize));
    setValue(parameter->getValue());
}

ImageKnob::~ImageKnob() {
    parameter->removeObserver(this);
}

void ImageKnob::setImages(const Image& knobImage) {
    this->knobImage = knobImage;
}

void ImageKnob::onParameterUpdated(const PluginParameter* parameter) {
    setValue(parameter->getValue());
}

void ImageKnob::valueChanged() {
    parameter->setValue(getValue());
}

void ImageKnob::paint(Graphics &g) {
    double valueScaled = getValue() / (getMaximum() - getMinimum()) + getMinimum();
    const int knobWidth = knobImage.getWidth();
    double filmstripImageCount = knobImage.getHeight() / knobWidth - 1;
    int imageIndex = (int) (filmstripImageCount * valueScaled) * knobWidth;

    // Useful for debugging to see background area
    // g.fillCheckerBoard(getLocalBounds(), 10, 10, juce::Colours::white, juce::Colours::grey);

    Rectangle<int> knobArea(0, imageIndex, knobWidth, knobWidth);
    Image knobFrame = knobImage.getClippedImage(knobArea);
    Image resizedKnobFrame = knobFrame.rescaled(knobWidth, knobWidth, Graphics::highResamplingQuality);

    g.drawImageAt(resizedKnobFrame, 0, 0);
}

} // namespace teragon
