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

#ifndef __PLUGINPARAMETERCOMPONENT_H__
#define __PLUGINPARAMETERCOMPONENT_H__

#if ! ENABLE_MULTITHREADED
#error PluginParameters must be built in multi-threaded mode
#endif

#include "../PluginParameters/include/PluginParameters.h"
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
