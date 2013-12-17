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
    ToggleButton(ThreadsafePluginParameterSet &parameters, const ParameterString &name,
                 const ResourceCache *resources) :
    ThinButton(parameters, name, resources, "toggle_button") {
        setClickingTogglesState(false);
    }

    virtual ~ToggleButton() {}

    const Image getImageForButtonState() {
        return isDown() ? getDownImage() : getNormalImage();
    }
};

} // namespace teragon

#endif  // __TOGGLEBUTTON_H_CCE55A62__
