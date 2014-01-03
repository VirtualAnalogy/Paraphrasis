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

#ifndef ELLIPSIZEDLABEL_H_INCLUDED
#define ELLIPSIZEDLABEL_H_INCLUDED

#include "JuceHeader.h"

namespace teragon {

/**
* This class is a simple subclass of the Juce Label class, with the only
* difference being that it ellipsizes long text (ie, adding "…" to the end
* of long strings which must be truncated. Juce also ellipsizes, but it
* first tries to compact the text by decreasing the width, which looks
* quite bad. Also, Juce does not use the UTF-8 ellipsis character, instead
* using "...", which takes up much more space.
*/
class EllipsizedLabel : public juce::Label {
public:
    EllipsizedLabel() : Label() {}
    EllipsizedLabel(const String &componentName, const String &labelText) :
    Label(componentName, labelText) {}

    virtual ~EllipsizedLabel() {}

    virtual void setText(const String &newText) {
        // Minor optimization to save a lot of trouble below
        if(newText == String::empty) {
            Label::setText(newText, NotificationType::dontSendNotification);
            return;
        }

        const Font font = getFont();
        const int maxWidth = getWidth();
        float renderedTextWidth = font.getStringWidthFloat(newText);
        int truncateAtIndex = newText.length();
        String truncatedText = newText;

        // Yeah, this is kind of stupid, but there's not really a more efficient way to do
        // this. Basically we keep subtracting characters from the string, appending the
        // ellipsis character, and then measuring how large the resulting string would be.
        // If it can fit in the Label's bounds, then that's the string we want to set.
        while(maxWidth > 0 && renderedTextWidth >= maxWidth && truncateAtIndex > 0) {
            --truncateAtIndex;
            // If the last character is a space, then skip it. Otherwise the result will be
            // a string that looks like "long example string …", which should instead look
            // like "long example string…".
            if(newText[truncateAtIndex - 1] == ' ') {
                continue;
            }
            truncatedText = newText.substring(0, truncateAtIndex);
            truncatedText += "…";
            renderedTextWidth = font.getStringWidthFloat(truncatedText);
            if(renderedTextWidth < maxWidth) {
                break;
            }
        }

        Label::setText(truncatedText, NotificationType::dontSendNotification);
    }
};

} // namespace teragon

#endif  // ELLIPSIZEDLABEL_H_INCLUDED
