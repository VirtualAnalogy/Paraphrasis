/*
  ==============================================================================

    ImageKnob.cpp
    Created: 29 May 2013 8:45:14pm
    Author:  Nik Reiman

  ==============================================================================
*/

#include "ImageKnob.h"

namespace teragon {

ImageKnob::ImageKnob(const char* knobImage, const int knobImageSize) :
    Slider(juce::Slider::RotaryVerticalDrag, juce::Slider::NoTextBox), knobImage() {
  setRange(0, 100, 1);
  setImages(ImageCache::getFromMemory(knobImage, knobImageSize));
}

ImageKnob::~ImageKnob() {
}

void ImageKnob::setImages(const Image& knobImage) {
  this->knobImage = knobImage;
}

void ImageKnob::paint(Graphics &g) {
  double valueScaled = getValue() / (getMaximum() - getMinimum()) + getMinimum();
  const int knobWidth = knobImage.getWidth();
  double filmstripImageCount = knobImage.getHeight() / knobWidth - 1;
  int imageIndex = (int)(filmstripImageCount * valueScaled) * knobWidth;

  // Useful for debugging to see background area
  // g.fillCheckerBoard(getLocalBounds(), 10, 10, juce::Colours::white, juce::Colours::grey);

  Rectangle<int> knobArea(0, imageIndex, knobWidth, knobWidth);
  Image knobFrame = knobImage.getClippedImage(knobArea);
  Image resizedKnobFrame = knobFrame.rescaled(knobWidth, knobWidth, Graphics::highResamplingQuality);

  g.drawImageAt(resizedKnobFrame, 0, 0);
}

} // namespace teragon
