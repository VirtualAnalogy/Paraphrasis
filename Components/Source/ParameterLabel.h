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

#ifndef PARAMETERLABEL_H_INCLUDED
#define PARAMETERLABEL_H_INCLUDED

#include "JuceHeader.h"
#include "EllipsizedLabel.h"
#include "PluginParameterComponent.h"

namespace teragon {

/**
* A simple  component to display a parameter value. A ResourceCache is not
* necessary for this constructor, since it is just using the built-in font
* rendering.
*/
class ParameterLabel : public EllipsizedLabel, public PluginParameterComponent {
public:
    ParameterLabel(ConcurrentParameterSet &parameters, const ParameterString &name) :
    EllipsizedLabel(), PluginParameterComponent(parameters, name, nullptr, String::empty) {
        setText(parameter->getDisplayText());
    }

    virtual ~ParameterLabel() {}

    virtual void onParameterUpdated(const Parameter *parameter) {
        juce::MessageManagerLock lock;
        setText(parameter->getDisplayText());
    }
};

}

#endif  // PARAMETERLABEL_H_INCLUDED
