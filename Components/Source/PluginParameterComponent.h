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
