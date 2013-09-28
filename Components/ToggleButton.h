/*
  ==============================================================================

    ToggleButton.h
    Created: 30 May 2013 8:59:23pm
    Author:  Nik Reiman

  ==============================================================================
*/

#ifndef __TOGGLEBUTTON_H_CCE55A62__
#define __TOGGLEBUTTON_H_CCE55A62__

#include "ThinButton.h"

namespace teragon {

class ToggleButton : public ThinButton {
public:
    ToggleButton(PluginParameter* parameter,
                 const char* normalImage, const int normalImageSize,
                 const char* pressedImage, const int pressedImageSize,
                 const ThinButton::Gravity gravity = kGravityDefault) :
    ThinButton(parameter, normalImage, normalImageSize, pressedImage, pressedImageSize, gravity)
    {
        setClickingTogglesState(false);
    }
    virtual ~ToggleButton() {}

    const Image getImageForButtonState() {
        return isDown() ? getDownImage() : getNormalImage();
    }
};

}

#endif  // __TOGGLEBUTTON_H_CCE55A62__
