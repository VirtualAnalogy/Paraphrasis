#ifndef __MapParameterSet_h__
#define __MapParameterSet_h__

#ifndef __PluginParameterSet_h__
#include "PluginParameterSet.h"
#endif

#include <map>

namespace teragon {
  namespace pluginParameters {
    typedef std::map<ParameterString, PluginParameter*> MapParameterSetStorage;

    class MapParameterSet : public PluginParameterSet {
    public:
      MapParameterSet();
      ~MapParameterSet();

      void addParameter(PluginParameter* parameter);

      PluginParameter* getParameter(const ParameterIndex index) const;
      PluginParameter* getParameter(const ParameterString name) const;
      
      const int size() const;

    private:
      MapParameterSetStorage parameterStorage;
    };
  }
}

#endif
