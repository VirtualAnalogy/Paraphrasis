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

class IndicatorLight : public Component, public Timer, public PluginParameterObserver {
public:
    IndicatorLight(PluginParameter *parameter, const ResourceCache::ImageStates *imageStates);
    virtual ~IndicatorLight();

    bool isRealtimePriority() const { return false; }
    void onParameterUpdated(const PluginParameter* parameter);

    void paint(Graphics &g);
    void timerCallback();

    void setEnabled(bool enabled);

private:
    PluginParameter *parameter;
    Image enabledImage;
    Image disabledImage;

    bool enabled;
    float enabledOpacity;
    float stepRate;
};

}

#endif  // __INDICATORLIGHT_H_DAF02643__
