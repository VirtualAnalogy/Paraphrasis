/*
  ==============================================================================

    ImageKnob.h
    Created: 29 May 2013 8:45:14pm
    Author:  Nik Reiman

  ==============================================================================
 */

#ifndef __IMAGEKNOB_H_4804529__
#define __IMAGEKNOB_H_4804529__

#include "JuceHeader.h"
#include "PluginParameterComponent.h"
#include "ResourceCache.h"

namespace teragon {

class ImageKnob : public juce::Slider, public PluginParameterComponent {
public:
    ImageKnob(ThreadsafePluginParameterSet &parameters, const char *name);
    virtual ~ImageKnob();

    bool isRealtimePriority() const { return false; }
    void onParameterUpdated(const PluginParameter* parameter);
    void valueChanged();

    void paint(Graphics &g);

private:
    Image knobImage;
};

} // namespace teragon

#endif  // __IMAGEKNOB_H_4804529__
