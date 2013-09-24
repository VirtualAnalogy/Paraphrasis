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
    ToggleButton(const char* pressedImage, const int pressedImageSize,
        const char* normalImage, const int normalImageSize,
        const ThinButton::Gravity gravity = kGravityDefault) :
        ThinButton(pressedImage, pressedImageSize, normalImage, normalImageSize, gravity) {
        setClickingTogglesState(true);
    }
    virtual ~ToggleButton() {}

    const Image getImageForButtonState() {
        return getToggleState() ? getDownImage() : getNormalImage();
    }
};

}

#endif  // __TOGGLEBUTTON_H_CCE55A62__
