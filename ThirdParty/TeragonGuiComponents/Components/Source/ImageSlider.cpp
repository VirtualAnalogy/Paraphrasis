/*
 * Copyright (c) 2013 - Teragon Audio LLC
 *
 * Permission is granted to use this software under the terms of either:
 * a) the GPL v2 (or any later version)
 * b) the Affero GPL v3
 *
 * Details of these licenses can be found at: www.gnu.org/licenses
 *
 * This software is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * ------------------------------------------------------------------------------
 *
 * This software uses the JUCE library.
 *
 * To release a closed-source product which uses JUCE, commercial licenses are
 * available: visit www.juce.com for more information.
 */

#include "ImageSlider.h"

namespace teragon {

ImageSlider::ImageSlider(ConcurrentParameterSet &parameters, const ParameterString &name,
                         const ResourceCache *resources) :
Slider(juce::Slider::LinearVertical, juce::Slider::NoTextBox),
PluginParameterComponent(parameters, name, resources, "slider") {
    handleImage = imageStates->normal;
    wellImage = imageStates->background;
    offset = handleImage.getHeight() / 4 + 1;

    setRange(0.0, 1.0);
    setValue(parameter->getScaledValue(), NotificationType::dontSendNotification);
}

void ImageSlider::valueChanged() {
    onValueChanged(getValue());
}

void ImageSlider::onParameterUpdated(const Parameter* parameter) {
    juce::MessageManagerLock lock;
    setValue(parameter->getScaledValue(), NotificationType::dontSendNotification);
}

void ImageSlider::paint(Graphics &g) {
    if(isMouseOver() && !isMouseButtonDown()) {
        onMouseOver();
    }

    const int handleX = (getWidth() - handleImage.getWidth()) / 2;
    const int yRange = getHeight() - handleImage.getHeight() / 2;
    // Mysterious logic... o_O Not sure why this handle is so tough to position, even
    // at position == 0, it is ~20px below the top of the well. Not sure why this is,
    // but this arithmetic seems to put it in the right position.
    const int position = (int)(yRange - (yRange * (getValue() / getMaximum() - getMinimum())) + 1);
    g.drawImageAt(wellImage, 0, 0);
    g.drawImageAt(handleImage, handleX, position - offset);
}

} // namespace teragon
