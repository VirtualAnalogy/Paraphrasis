/*
  ==============================================================================

    StatusBar.h
    Created: 18 Dec 2013 6:48:02pm
    Author:  Nik Reiman

  ==============================================================================
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
