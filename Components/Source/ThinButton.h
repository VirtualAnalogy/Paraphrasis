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
#include "PluginParameters.h"
#include "ResourceCache.h"

namespace teragon {

class ThinButton : public juce::ImageButton, public PluginParameterObserver {
public:
    typedef enum {
        kGravityTop,
        kGravityBottom,
        kGravityCentered,
        kGravityDefault = kGravityTop
    } Gravity;

public:
    ThinButton(PluginParameter *parameter, const ResourceCache::ImageStates *imageStates,
               const ThinButton::Gravity gravity = kGravityDefault);
    virtual ~ThinButton();

    void clicked();
    bool isRealtimePriority() const { return false; }
    void onParameterUpdated(const PluginParameter* parameter);

    void paint(Graphics &g);

    virtual const Image getImageForButtonState() = 0;

private:
    void setImages(Image downImage, Image upImage);

    PluginParameter *parameter;
    Gravity gravity;
};

} // namespace teragon

#endif  // __THINBUTTON_H_2C648127__
