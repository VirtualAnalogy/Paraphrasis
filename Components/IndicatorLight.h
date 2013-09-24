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

namespace teragon {

class IndicatorLight : public Component, public Timer {
public:
    IndicatorLight();
    virtual ~IndicatorLight() {}

    void paint(Graphics &g);
    void timerCallback();

    void setEnabled(bool enabled);
    void setImages(Image enabledImage, Image disabledImage);

private:
    bool enabled;
    float enabledOpacity;
    float stepRate;
    Image enabledImage;
    Image disabledImage;
};

}

#endif  // __INDICATORLIGHT_H_DAF02643__
