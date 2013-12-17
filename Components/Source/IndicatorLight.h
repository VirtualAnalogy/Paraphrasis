/*
  ==============================================================================

    IndicatorLight.h
    Created: 29 May 2013 9:35:45pm
    Author:  Nik Reiman

  ==============================================================================
*/

#ifndef __INDICATORLIGHT_H_DAF02643__
#define __INDICATORLIGHT_H_DAF02643__

#include "JuceHeader.h"
#include "PluginParameterComponent.h"
#include "ResourceCache.h"

namespace teragon {

class IndicatorLight : public Component, public Timer, public PluginParameterComponent {
public:
    IndicatorLight(ThreadsafePluginParameterSet &parameters, const ParameterString &name,
                   const ResourceCache *resources);
    virtual ~IndicatorLight() {}

    void onParameterUpdated(const PluginParameter* parameter);
    void paint(Graphics &g);
    void timerCallback();
    void setLightOn(bool lightOn);

private:
    Image enabledImage;
    Image disabledImage;
    int enabledImageWidth;
    int enabledImageHeight;
    int disabledImageWidth;
    int disabledImageHeight;

    bool lightOn;
    float enabledOpacity;
    float stepRate;
};

} // namespace teragon

#endif  // __INDICATORLIGHT_H_DAF02643__
