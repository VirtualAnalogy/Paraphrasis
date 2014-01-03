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

#ifndef __IMAGESLIDER_H_B0B8D694__
#define __IMAGESLIDER_H_B0B8D694__

#include "JuceHeader.h"
#include "PluginParameterComponent.h"
#include "ResourceCache.h"

namespace teragon {

/**
* A vertical fader widget, which contains a background well and a handle
* image. A horizontal variant of this widget is not provided, because this
* control type is rarely used (with crossfaders being the notable exception).
*/
class ImageSlider : public juce::Slider, public PluginParameterComponent {
public:
    ImageSlider(ConcurrentParameterSet &parameters, const ParameterString &name,
                const ResourceCache *resources);
    virtual ~ImageSlider() {}

    void valueChanged();
    void onParameterUpdated(const Parameter* parameter);
    void paint(Graphics &g);

private:
    Image handleImage;
    Image wellImage;
    int offset;
};

} // namespace teragon

#endif  // __IMAGESLIDER_H_B0B8D694__
