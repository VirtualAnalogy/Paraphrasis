/*
  ==============================================================================

    EllipsizedLabel.h
    Created: 20 Dec 2013 9:30:17am
    Author:  Nik Reiman

  ==============================================================================
*/

#ifndef ELLIPSIZEDLABEL_H_INCLUDED
#define ELLIPSIZEDLABEL_H_INCLUDED

#include "JuceHeader.h"

namespace teragon {

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
        while(renderedTextWidth >= maxWidth && truncateAtIndex > 0) {
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
