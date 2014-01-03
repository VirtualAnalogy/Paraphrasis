/*
 * Copyright (c) 2013 - Teragon Audio LLC
 *
 * Permission is granted to use this software under the terms of either:
 * a) the GPL v2 (or any later version)
 * b) the Affero GPL v3
 *
 * Details of these licenses can be found at: www.gnu.org/licenses
 *
 * This software is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * ------------------------------------------------------------------------------
 *
 * This software uses the JUCE library.
 *
 * To release a closed-source product which uses JUCE, commercial licenses are
 * available: visit www.juce.com for more information.
 */

#ifndef __TOGGLEBUTTON_H_CCE55A62__
#define __TOGGLEBUTTON_H_CCE55A62__

#include "ThinButton.h"

namespace teragon {

/**
* A toggle button widget which does not show a current state. This is mostly
* useful for triggering actions, such as save, open, etc. Although this
* component does not require a given parameter type, it is most useful when
* bound to a VoidParameter, which can act as a basic message passing system
* between the GUI and core of an application.
*/
class ToggleButton : public ThinButton {
public:
    ToggleButton(ConcurrentParameterSet &parameters, const ParameterString &name,
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
