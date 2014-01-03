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

#ifndef __PLUGINPARAMETERCOMPONENT_H__
#define __PLUGINPARAMETERCOMPONENT_H__

#include "../PluginParameters/include/PluginParameters.h"
#if !PLUGINPARAMETERS_MULTITHREADED
#error PluginParameters must be built in multi-threaded mode
#endif

#include "ResourceCache.h"

namespace teragon {

/**
* Base class for all TeragonGuiComponents widgets. Basically handles the
* process of observing a parameter and sending updates to that parameter
* on an associated ConcurrentParameterSet.
*/
class PluginParameterComponent : public ParameterObserver {
public:
    PluginParameterComponent(ConcurrentParameterSet &parameters, const ParameterString &name,
                             const ResourceCache *resources, const String &imageName) :
    ParameterObserver(),
    parameters(parameters), parameter(nullptr), imageStates(nullptr), observer(nullptr) {
        parameter = parameters[name];
        if(parameter == nullptr) {
            String message = "Could not bind component to parameter: ";
            message += name.c_str();
            Logger::getCurrentLogger()->writeToLog(message);
            return;
        }
        parameter->addObserver(this);

        if(resources == nullptr && imageName != String::empty) {
          String message = "Could not initialize component with NULL ResourceCache";
          Logger::getCurrentLogger()->writeToLog(message);
            return;
        }
        else if(resources != nullptr) {
            imageStates = resources->get(imageName);
            if(imageStates == nullptr) {
                String message = "Could not find image resource for component: ";
                message += imageName;
                Logger::getCurrentLogger()->writeToLog(message);
                return;
            }
        }
    }

    virtual ~PluginParameterComponent() {
        if(parameter != nullptr) {
            parameter->removeObserver(this);
            if(observer != nullptr) {
                parameter->removeObserver(observer);
            }
        }
    }

    virtual bool isRealtimePriority() const {
        return false;
    }

    virtual void onValueChanged(ParameterValue value) {
        parameters.setScaled(parameter, value, this);
    }

    virtual void setStatusObserver(ParameterObserver *observer) {
        this->observer = observer;
    }

    virtual void onMouseOver() {
        if(observer != nullptr) {
            observer->onParameterUpdated(parameter);
        }
    }

private:
    // Disallow assignment operator
    PluginParameterComponent& operator=(const PluginParameterComponent&) { return *this; }

protected:
    ConcurrentParameterSet &parameters;
    Parameter *parameter;
    ResourceCache::ImageStates *imageStates;
    ParameterObserver *observer;
};

} // namespace teragon

#endif
