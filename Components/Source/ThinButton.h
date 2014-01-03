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

#ifndef __THINBUTTON_H_2C648127__
#define __THINBUTTON_H_2C648127__

#include "JuceHeader.h"
#include "PluginParameterComponent.h"
#include "ResourceCache.h"

namespace teragon {

/**
* Base class for buttons. See the ToggleButton and PushButton subclasses
* for further information.
*/
class ThinButton : public juce::ImageButton, public PluginParameterComponent {
public:
    typedef enum {
        kGravityTop,
        kGravityBottom,
        kGravityCentered,
        kGravityDefault = kGravityTop
    } Gravity;

public:
    ThinButton(ConcurrentParameterSet &parameters, const ParameterString &name,
               const ResourceCache *resources, const String &imageName);

    virtual void clicked();
    virtual bool isParameterEnabled() const;
    virtual void onParameterUpdated(const Parameter* parameter);

    virtual void paint(Graphics &g);

    virtual const Image getImageForButtonState() = 0;

protected:
    // For now, always set this to be kGravityDefault (ie, kGravityTop), but
    // in the future there could be an option to control the gravity.
    Gravity gravity;
};

} // namespace teragon

#endif  // __THINBUTTON_H_2C648127__
