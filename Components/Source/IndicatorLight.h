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

#ifndef __INDICATORLIGHT_H_DAF02643__
#define __INDICATORLIGHT_H_DAF02643__

#include "JuceHeader.h"
#include "PluginParameterComponent.h"
#include "ResourceCache.h"

namespace teragon {

/**
* A small light which can be lit up when the associated parameter is enabled.
* If the parameter is a VoidParameter, then the light will pulse by briefly
* lighting up and then dimming out. This can be very useful for showing tempo
* or other timed events.
*/
class IndicatorLight : public Component, public Timer, public PluginParameterComponent {
public:
    IndicatorLight(ConcurrentParameterSet &parameters, const ParameterString &name,
                   const ResourceCache *resources);
    virtual ~IndicatorLight() {}

    void onParameterUpdated(const Parameter* parameter);
    void paint(Graphics &g);
    void timerCallback();
    void setLightOn(bool lightOn, bool pulse = false);

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
    bool pulse;
    int pulseHoldFrames;
};

} // namespace teragon

#endif  // __INDICATORLIGHT_H_DAF02643__
