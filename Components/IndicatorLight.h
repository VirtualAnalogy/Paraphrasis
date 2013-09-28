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
#include "PluginParameters.h"

namespace teragon {

class IndicatorLight : public Component, public Timer, public PluginParameterObserver {
public:
    IndicatorLight(PluginParameter *parameter,
                   const char* enabledImage, const int enabledImageSize,
                   const char* disabledImage, const int disabledImageSize);
    virtual ~IndicatorLight();

    void onParameterUpdated(const PluginParameter* parameter);

    void paint(Graphics &g);
    void timerCallback();

    void setEnabled(bool enabled);
    void setImages(Image enabledImage, Image disabledImage);

private:
    Image enabledImage;
    Image disabledImage;
    PluginParameter *parameter;

    bool enabled;
    float enabledOpacity;
    float stepRate;
};

}

#endif  // __INDICATORLIGHT_H_DAF02643__
