/*
  ==============================================================================

    PushButton.h
    Created: 29 May 2013 9:39:08pm
    Author:  Nik Reiman

  ==============================================================================
*/

#ifndef __PUSHBUTTON_H_AE7ED0A8__
#define __PUSHBUTTON_H_AE7ED0A8__

#include "ThinButton.h"

namespace teragon {

class PushButton : public ThinButton {
public:
    PushButton(PluginParameter* parameter, const ResourceCache::ImageStates *imageStates,
               const ThinButton::Gravity gravity = kGravityDefault) :
    ThinButton(parameter, imageStates, gravity) {
        setClickingTogglesState(true);
    }
    virtual ~PushButton() {}

    const Image getImageForButtonState() {
        return getToggleState() ? getDownImage() : getNormalImage();
    }
};

}

#endif  // __PUSHBUTTON_H_AE7ED0A8__
