/*
  ==============================================================================

    ImageKnob.cpp
    Created: 29 May 2013 8:45:14pm
    Author:  Nik Reiman

  ==============================================================================
*/

#include "ImageKnob.h"
#include "Sizes.h"

namespace teragon {

ImageKnob::ImageKnob() : Slider(), knobImage(), useSmallKnobs(false) {
  initialize();
}

ImageKnob::ImageKnob(const String &componentName) : Slider(componentName), knobImage(), useSmallKnobs(false) {
  initialize();
}

ImageKnob::~ImageKnob() {
}

void ImageKnob::initialize() {
  setSliderStyle(juce::Slider::RotaryVerticalDrag);
}

void ImageKnob::setUseSmallKnobs(bool useSmallKnobs) {
    this->useSmallKnobs = useSmallKnobs;
}

void ImageKnob::setImages(const Image& knobImage) {
  this->knobImage = knobImage;
}

void ImageKnob::paint(Graphics &g) {
  double valueScaled = getValue() / (getMaximum() - getMinimum()) + getMinimum();
  double filmstripImageCount = knobImage.getHeight() / knobImage.getWidth() - 1;
  int imageIndex = (int)(filmstripImageCount * valueScaled) * knobImage.getWidth();
  // Useful for debugging to see background area
  // g.fillCheckerBoard(getLocalBounds(), 10, 10, juce::Colours::white, juce::Colours::grey);

  Rectangle<int> knobArea(0, imageIndex, knobImage.getWidth(), knobImage.getWidth());
  const int knobSize = useSmallKnobs ? kImageKnobSmallSize : kImageKnobLargeSize;
  Image knobFrame = knobImage.getClippedImage(knobArea);
  Image resizedKnobFrame = knobFrame.rescaled(knobSize, knobSize, Graphics::highResamplingQuality);

  g.drawImageAt(resizedKnobFrame, 0, 0);
}

} // namespace teragon
