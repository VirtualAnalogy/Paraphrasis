/*
Copyright (c) 2013 Teragon Audio. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
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
