/*
  ==============================================================================

    ImageSlider.h
    Created: 28 May 2013 10:07:08pm
    Author:  Nik Reiman

  ==============================================================================
*/

#ifndef __IMAGESLIDER_H_B0B8D694__
#define __IMAGESLIDER_H_B0B8D694__

#include "JuceHeader.h"
#include "PluginParameterComponent.h"
#include "ResourceCache.h"

namespace teragon {

class ImageSlider : public juce::Slider, public PluginParameterComponent {
public:
    ImageSlider(ThreadsafePluginParameterSet &parameters, const ParameterString &name,
                const ResourceCache *resources);
    virtual ~ImageSlider() {}

    void valueChanged();
    void onParameterUpdated(const PluginParameter* parameter);
    void paint(Graphics &g);

private:
    Image handleImage;
    Image wellImage;
    int offset;
};

} // namespace teragon

#endif  // __IMAGESLIDER_H_B0B8D694__
