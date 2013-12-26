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

#ifndef __THINBUTTON_H_2C648127__
#define __THINBUTTON_H_2C648127__

#include "JuceHeader.h"
#include "PluginParameterComponent.h"
#include "ResourceCache.h"

namespace teragon {

/**
* Base class for buttons. See the ToggleButton and PushButton subclasses
* for further information.
*/
class ThinButton : public juce::ImageButton, public PluginParameterComponent {
public:
    typedef enum {
        kGravityTop,
        kGravityBottom,
        kGravityCentered,
        kGravityDefault = kGravityTop
    } Gravity;

public:
    ThinButton(ConcurrentParameterSet &parameters, const ParameterString &name,
               const ResourceCache *resources, const String &imageName);

    virtual void clicked();
    virtual bool isParameterEnabled() const;
    virtual void onParameterUpdated(const Parameter* parameter);

    virtual void paint(Graphics &g);

    virtual const Image getImageForButtonState() = 0;

protected:
    // For now, always set this to be kGravityDefault (ie, kGravityTop), but
    // in the future there could be an option to control the gravity.
    Gravity gravity;
};

} // namespace teragon

#endif  // __THINBUTTON_H_2C648127__
