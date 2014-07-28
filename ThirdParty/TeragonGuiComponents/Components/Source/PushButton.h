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

#ifndef __PUSHBUTTON_H_AE7ED0A8__
#define __PUSHBUTTON_H_AE7ED0A8__

#include "ThinButton.h"

namespace teragon {

/**
* Widget for a state button, which can be either turned on or off. This
* widget makes most sense to associate with BooleanParameters, but it can
* be used for any numerical parameter.
*/
class PushButton : public ThinButton, public Timer {
public:
    PushButton(ConcurrentParameterSet &parameters, const ParameterString &name,
               const ResourceCache *resources);

    virtual ~PushButton() {}

    const Image getImageForButtonState() {
        return getToggleState() ? getDownImage() : getNormalImage();
    }

    virtual void onParameterUpdated(const Parameter *parameter);

    virtual void clicked();
    virtual void postClicked();
    virtual void paint(Graphics &g);

    virtual void timerCallback();

private:
    Image enabledImage;
    Image disabledImage;
    float enabledOpacity;
    float stepRate;
};

} // namespace teragon

#endif  // __PUSHBUTTON_H_AE7ED0A8__
