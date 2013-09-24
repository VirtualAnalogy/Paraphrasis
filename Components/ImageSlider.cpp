/*
  ==============================================================================

    ImageSlider.cpp
    Created: 28 May 2013 10:07:08pm
    Author:  Nik Reiman

  ==============================================================================
*/

#include "ImageSlider.h"
#include "Sizes.h"

namespace teragon {

ImageSlider::ImageSlider() : Slider(),
  handleImage(), backgroundImage() {
  initialize();
}

ImageSlider::ImageSlider(const String &componentName) : Slider(componentName),
  handleImage(), backgroundImage() {
  initialize();
}

ImageSlider::~ImageSlider() {
}

void ImageSlider::initialize() {
  setSliderStyle(juce::Slider::LinearVertical);
}

void ImageSlider::setImages(const Image& handleImage, const Image& backgroundImage) {
  this->handleImage = handleImage;
  this->backgroundImage = backgroundImage;
}

void ImageSlider::paint(Graphics &g) {
  int handleX = (getWidth() - kImageSliderHandleWidth) / 2;
  int backgroundX = (getWidth() - backgroundImage.getWidth()) / 2;
  int yRange = getHeight() - kImageSliderHandleHeight - 1;
  int position = yRange - (yRange * (getValue() / getMaximum() - getMinimum())) + 1;
  // g.fillCheckerBoard(getLocalBounds(), 10, 10, juce::Colours::white, juce::Colours::grey);
  g.drawImage(backgroundImage, backgroundX, 0, backgroundImage.getWidth(), getHeight(),
              0, 0, backgroundImage.getWidth(), backgroundImage.getHeight());
  g.drawImage(handleImage, handleX, position, kImageSliderHandleWidth, kImageSliderHandleHeight,
              0, 0, handleImage.getWidth(), handleImage.getHeight());
}

}
