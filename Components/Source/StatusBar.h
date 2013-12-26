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
#include "../PluginParameters/include/PluginParameters.h"

namespace teragon {

/**
* Provides a two-line status window for displaying parameter information.
* To use this widget, you must call subscribeToParameters() after all other
* GUI widgets have been constructed. That method will iterate over all
* parameters in the ThreadsafePluginParameterSet, finding those which have
* at least one TeragonGuiComponent registered as an observer. Any updates
* on those parameters will be automatically displayed in this component.
*
* This widget is necessary because of the minimalist style of the other GUI
* widgets. Rather than cluttering up the entire UI with unit labels, or
* using tooltips to display plugin values, this component is used instead.
*
* For components which can receive mouse-over events, this widget will
* register itself as an observer there as well so that the current parameter
* value can be shown without having to alter the value.
*/
class StatusBar : public juce::Component, public juce::Timer, public ParameterObserver {
public:
    StatusBar(ConcurrentParameterSet &parameters, const ResourceCache *resources);
    virtual ~StatusBar();

    static const Font getFont();

    virtual void resized() override;

    /**
      * Iterate over the parameter set and subscribe to all parameters which have at least
      * one PluginParameterComponent as an observer.
      */
    virtual void subscribeToParameters();

    /**
      * Tell the status bar to ignore updates from the given parameters. This should be
      * called after calling subscribeToParameters().
      */
    virtual void ignoreParameter(const ParameterString &name);

    virtual bool isRealtimePriority() const { return false; }
    virtual void onParameterUpdated(const Parameter *parameter);

    virtual void displayParameter(const Parameter *parameter);
    virtual void timerCallback();

protected:
    static const int kClearTimeoutInMs = 1500;
    // Number of pixels between top and bottom label
    static const int kPadding = 4;
    static const int kFontSize = 13;

private:
    void configureLabelProperties(Label &label);

    EllipsizedLabel parameterNameLabel;
    EllipsizedLabel parameterValueLabel;

    ConcurrentParameterSet &parameters;

    float labelOpacity;
    float clearTimeout;
};

} // namespace teragon

#endif  // STATUSBAR_H_INCLUDED
