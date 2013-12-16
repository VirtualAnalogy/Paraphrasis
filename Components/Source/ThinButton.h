/*
  ==============================================================================

    ThinButton.h
    Created: 30 May 2013 8:47:07pm
    Author:  Nik Reiman

  ==============================================================================
*/

#ifndef __THINBUTTON_H_2C648127__
#define __THINBUTTON_H_2C648127__

#include "JuceHeader.h"
#include "PluginParameterComponent.h"
#include "ResourceCache.h"

namespace teragon {

class ThinButton : public juce::ImageButton, public PluginParameterComponent {
public:
    typedef enum {
        kGravityTop,
        kGravityBottom,
        kGravityCentered,
        kGravityDefault = kGravityTop
    } Gravity;

public:
    ThinButton(ThreadsafePluginParameterSet &parameters, const ParameterString &name,
               const ResourceCache *resources, const String &imageName);

    void clicked();
    void onParameterUpdated(const PluginParameter* parameter);
    void paint(Graphics &g);

    virtual const Image getImageForButtonState() = 0;

private:
    // For now, always set this to be kGravityDefault (ie, kGravityTop), but
    // in the future there could be an option to control the gravity.
    Gravity gravity;
};

} // namespace teragon

#endif  // __THINBUTTON_H_2C648127__
