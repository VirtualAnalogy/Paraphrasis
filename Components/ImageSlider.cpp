/*
  ==============================================================================

    ImageSlider.cpp
    Created: 28 May 2013 10:07:08pm
    Author:  Nik Reiman

  ==============================================================================
*/

#include "ImageSlider.h"

namespace teragon {

ImageSlider::ImageSlider(const char* handleImage, const int handleImageSize,
                         const char* wellImage, const int wellImageSize) :
    Slider(juce::Slider::LinearVertical, juce::Slider::NoTextBox), handleImage(), wellImage() {
    setImages(ImageCache::getFromMemory(handleImage, handleImageSize),
              ImageCache::getFromMemory(wellImage, wellImageSize));
    setRange(0, 100, 1);
}

ImageSlider::~ImageSlider() {
}

void ImageSlider::setImages(const Image& handleImage, const Image& wellImage) {
  this->handleImage = handleImage;
  this->wellImage = wellImage;
}

void ImageSlider::paint(Graphics &g) {
  int handleX = (getWidth() - handleImage.getWidth()) / 2;
  int wellX = (getWidth() - wellImage.getWidth()) / 2;
  int yRange = getHeight() - handleImage.getHeight() - 1;
  int position = yRange - (yRange * (getValue() / getMaximum() - getMinimum())) + 1;

  // g.fillCheckerBoard(getLocalBounds(), 10, 10, juce::Colours::white, juce::Colours::grey);

  g.drawImage(wellImage, wellX, 0, wellImage.getWidth(), getHeight(),
              0, 0, wellImage.getWidth(), wellImage.getHeight());
  g.drawImage(handleImage, handleX, position, handleImage.getWidth(), handleImage.getHeight(),
              0, 0, handleImage.getWidth(), handleImage.getHeight());
}

}
