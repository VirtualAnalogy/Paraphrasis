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
  int yRange = getHeight() - handleImage.getHeight() / 2;
  // Mysterious logic... o_O Not sure why this handle is so tough to position, even
  // at position == 0, it is ~20px below the top of the well. Not sure why this is,
  // but this arithmetic seems to put it in the right position.
  int position = yRange - (yRange * (getValue() / getMaximum() - getMinimum())) + 1;
  int offset = handleImage.getHeight() / 4 + 1;

  // g.fillCheckerBoard(getLocalBounds(), 10, 10, juce::Colours::white, juce::Colours::grey);

  g.drawImageAt(wellImage, 0, 0);
  g.drawImageAt(handleImage, handleX, position - offset);
}

}
