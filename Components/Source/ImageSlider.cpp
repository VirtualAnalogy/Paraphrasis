/*
  ==============================================================================

    ImageSlider.cpp
    Created: 28 May 2013 10:07:08pm
    Author:  Nik Reiman

  ==============================================================================
 */

#include "ImageSlider.h"
#include "PluginParameterComponent.h"

namespace teragon {

ImageSlider::ImageSlider(ThreadsafePluginParameterSet &parameters, const ParameterString &name,
                         const ResourceCache *resources) :
Slider(juce::Slider::LinearVertical, juce::Slider::NoTextBox),
PluginParameterComponent(parameters, name, resources, "slider") {
    setRange(0.0, 1.0);
    setValue(parameter->getValue());
}

void ImageSlider::valueChanged() {
    onValueChanged(getValue());
}

void ImageSlider::onParameterUpdated(const PluginParameter* parameter) {
    setValue(parameter->getScaledValue());
}

void ImageSlider::paint(Graphics &g) {
    Image handleImage = imageStates->normal;
    Image wellImage = imageStates->background;
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
