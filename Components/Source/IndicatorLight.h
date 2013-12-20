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
