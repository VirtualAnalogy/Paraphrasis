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

#ifndef __IMAGEKNOB_H_4804529__
#define __IMAGEKNOB_H_4804529__

#include "JuceHeader.h"
#include "PluginParameterComponent.h"
#include "ResourceCache.h"

namespace teragon {

/**
* Implementation of a filmstrip knob widget, similar to those popularized
* by the VSTGUI framework. This class requires a filmstrip knob image, which
* is a very tall image of with each knob rotation frame appended vertically
* after each other. See the "scripts" directory of the TeragonGuiComponents
* project for a script capable of generating filmstrips from a directory of
* knob animation frames.
*
* Juce does not have built-in support for filmstrip knobs, instead it opts
* for primitively-drawn rotated knobs (the word "primitive" here refers to
* graphics primitives, this is not a jab ot Juce's code sophistication).
* However, many plugin designers prefer filmstrip knobs because realistic
* shading can be done, giving the knob a more natural look. Even if shading
* is not desired, rotating a simple graphic will often result in "wiggle",
* which yields a poor-looking animation. Furthermore, filmstrip knobs are
* often very high-performance, since it is often quicker to paint a single
* pre-rendered image than it is to rotate an image on the fly.
*
* Other classes in the TeragonGuiComponents frameworks do not require the
* caller to pass in the image name, so for that reason subclasses of this
* base class exist simply to fill in the knob image name. This seems like
* overkill, but it greatly simplifies doing layout in Introjucer.
*/
class ImageKnob : public juce::Slider, public PluginParameterComponent {
public:
    ImageKnob(ConcurrentParameterSet &parameters, const ParameterString &name,
              const ResourceCache *resources, const String &imageName);
    virtual ~ImageKnob() {}

    virtual void onParameterUpdated(const Parameter* parameter);
    virtual void valueChanged();
    virtual void paint(Graphics &g);

private:
    juce::Rectangle<int> knobArea;
    int knobWidth;
    double filmstripImageCount;
};

} // namespace teragon

#endif  // __IMAGEKNOB_H_4804529__
