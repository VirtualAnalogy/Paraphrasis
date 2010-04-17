#ifndef __PluginParameterSet_h__
#define __PluginParameterSet_h__

#ifndef __PluginParameter_h__
#include "PluginParameter.h"
#endif

namespace teragon {
  namespace pluginParameters {
    typedef int ParameterIndex;

    class PluginParameterSet {
    public:
      PluginParameterSet() {};
      virtual ~PluginParameterSet() {};

      virtual void addParameter(PluginParameter* parameter) = 0;
      
      virtual PluginParameter* getParameter(const ParameterIndex index) const = 0;
      virtual PluginParameter* getParameter(const ParameterString name) const = 0;
      
      virtual const int size() const = 0;
    };
  }
}

#endif
