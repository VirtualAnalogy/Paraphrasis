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
