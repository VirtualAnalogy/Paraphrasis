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
    PushButton(ThreadsafePluginParameterSet &parameters, const ParameterString &name,
               const ResourceCache *resources) :
    ThinButton(parameters, name, resources, "push_button") {
        setClickingTogglesState(true);
        setToggleState(parameter->getScaledValue() > 0.5, NotificationType::dontSendNotification);
    }

    virtual ~PushButton() {}

    const Image getImageForButtonState() {
        return getToggleState() ? getDownImage() : getNormalImage();
    }
};

} // namespace teragon

#endif  // __PUSHBUTTON_H_AE7ED0A8__
