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
    ToggleButton(const ThinButton::Gravity gravity = kGravityDefault) : ThinButton(gravity) {
        setClickingTogglesState(true);
    }
    virtual ~ToggleButton() {}

    const Image getImageForButtonState() {
        return getToggleState() ? getDownImage() : getNormalImage();
    }
};

}

#endif  // __TOGGLEBUTTON_H_CCE55A62__
