/*
Copyright (c) 2013 Teragon Audio. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
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
