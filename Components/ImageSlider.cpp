/*
  ==============================================================================

    ImageSlider.cpp
    Created: 28 May 2013 10:07:08pm
    Author:  Nik Reiman

  ==============================================================================
 */

#include "ImageSlider.h"
#include "PluginParameter.h"

namespace teragon {

ImageSlider::ImageSlider(PluginParameter *parameter,
                         const ResourceCache::ImageStates *imageStates) :
Slider(juce::Slider::LinearVertical, juce::Slider::NoTextBox),
PluginParameterObserver(),
parameter(parameter), handleImage(imageStates->normal), wellImage(imageStates->background) {
    parameter->addObserver(this);
    setRange(parameter->getMinValue(), parameter->getMaxValue());
    setValue(parameter->getValue());
}

ImageSlider::~ImageSlider() {
    parameter->removeObserver(this);
}

void ImageSlider::valueChanged() {
    parameter->setValue(getValue());
}

void ImageSlider::onParameterUpdated(const PluginParameter* parameter) {
    setValue(parameter->getValue());
}

void ImageSlider::paint(Graphics &g) {
    int handleX = (getWidth() - handleImage.getWidth()) / 2;
    int yRange = getHeight() - handleImage.getHeight() / 2;
    // Mysterious logic... o_O Not sure why this handle is so tough to position, even
    // at position == 0, it is ~20px below the top of the well. Not sure why this is,
    // but this arithmetic seems to put it in the right position.
    int position = yRange - (yRange * (getValue() / getMaximum() - getMinimum())) + 1;
    int offset = handleImage.getHeight() / 4 + 1;

    g.drawImageAt(wellImage, 0, 0);
    g.drawImageAt(handleImage, handleX, position - offset);
}
}
