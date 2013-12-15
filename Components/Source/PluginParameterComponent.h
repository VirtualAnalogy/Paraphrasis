#ifndef __PLUGINPARAMETERCOMPONENT_H__
#define __PLUGINPARAMETERCOMPONENT_H__

#define ENABLE_MULTITHREADED 1
#include "../PluginParameters/include/PluginParameters.h"

namespace teragon {

class PluginParameterComponent : public PluginParameterObserver {
public:
    PluginParameterComponent(ThreadsafePluginParameterSet &parameters, const char *name) :
    PluginParameterObserver(),
    parameters(parameters) {
        parameter = parameters[name];
        parameter->addObserver(this);
    }

    virtual ~PluginParameterComponent() {}

    virtual void onValueChanged(ParameterValue value) {
        parameters.set(parameter, value, this);
    }

protected:
    ThreadsafePluginParameterSet &parameters;
    PluginParameter *parameter;
};
} // namespace teragon

#endif
