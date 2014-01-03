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
