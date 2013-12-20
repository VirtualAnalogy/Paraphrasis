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
#include "StatusBar.h"

namespace teragon {

class PluginParameterComponent : public PluginParameterObserver {
public:
    PluginParameterComponent(ThreadsafePluginParameterSet &parameters, const ParameterString &name,
                             const ResourceCache *resources, const String &imageName) :
    PluginParameterObserver(),
    parameters(parameters), parameter(NULL), imageStates(NULL), statusBar(NULL) {
        Logger *logger = Logger::getCurrentLogger();

        parameter = parameters[name];
        if (parameter == NULL) {
            String message = "Could not bind component to parameter: ";
            message += name.c_str();
            logger->writeToLog(message);
            return;
        }
        parameter->addObserver(this);

        if (resources == NULL) {
            logger->writeToLog("Could not initialize component with NULL ResourceCache");
            return;
        }
        imageStates = resources->get(imageName);
        if (imageStates == NULL) {
            String message = "Could not find image resource for component: ";
            message += imageName;
            logger->writeToLog(message);
            return;
        }
    }

    virtual ~PluginParameterComponent() {
        if (parameter != NULL) {
            parameter->removeObserver(this);
        }
    }

    virtual bool isRealtimePriority() const {
        return false;
    }

    virtual void onValueChanged(ParameterValue value) {
        parameters.setScaled(parameter, value, this);
    }

    virtual void setStatusBar(StatusBar *statusBar) {
        this->statusBar = statusBar;
    }

    virtual void onMouseOver() {
        if(statusBar != NULL && parameter != NULL) {
            statusBar->displayParameter(parameter);
        }
    }

protected:
    ThreadsafePluginParameterSet &parameters;
    PluginParameter *parameter;
    ResourceCache::ImageStates *imageStates;
    StatusBar *statusBar;
};

} // namespace teragon

#endif
