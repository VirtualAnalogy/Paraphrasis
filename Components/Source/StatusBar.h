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

#ifndef STATUSBAR_H_INCLUDED
#define STATUSBAR_H_INCLUDED

#include "JuceHeader.h"
#include "EllipsizedLabel.h"
#include "ResourceCache.h"
#include "../PluginParameters/include/ThreadsafePluginParameterSet.h"

namespace teragon {

static const float kFadeStepRate = 0.325f;

class StatusBar : public juce::Component, public juce::Timer, public PluginParameterObserver {
public:
    StatusBar(ThreadsafePluginParameterSet &parameters, const ResourceCache *resources);
    virtual ~StatusBar();

    virtual void resized() override;

    virtual void subscribeToParameters();
    virtual bool isRealtimePriority() const;
    virtual void onParameterUpdated(const PluginParameter *parameter);

    virtual void displayParameter(const PluginParameter *parameter);
    virtual void timerCallback();

protected:
    static const int kClearTimeoutInMs = 1500;
    // Number of pixels between top and bottom label
    static const int kPadding = 4;

private:
    void configureLabelProperties(Label &label);

    EllipsizedLabel parameterNameLabel;
    EllipsizedLabel parameterValueLabel;

    ThreadsafePluginParameterSet &parameters;

    float labelOpacity;
    float clearTimeout;
};

} // namespace teragon

#endif  // STATUSBAR_H_INCLUDED
