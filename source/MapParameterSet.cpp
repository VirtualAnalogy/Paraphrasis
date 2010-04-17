#ifndef __MapParameterSet_h__
#include "MapParameterSet.h"
#endif

namespace teragon {
  namespace pluginParameters {
    MapParameterSet::MapParameterSet() : PluginParameterSet() {
    }

    MapParameterSet::~MapParameterSet() {
    }

    void MapParameterSet::addParameter(PluginParameter* parameter) {
      parameterStorage.insert(make_pair(parameter->getName(), parameter));
    }

    PluginParameter* MapParameterSet::getParameter(const ParameterIndex index) const {
      MapParameterSetStorage::const_iterator iterator = parameterStorage.begin();
      if(iterator != parameterStorage.end()) {
        // TODO: This is very inefficient...
        for(int i = 0; i < index; ++i) {
          iterator++;
        }
        return iterator->second;
      }
      else {
        return NULL;
      }
    }

    PluginParameter* MapParameterSet::getParameter(const ParameterString name) const {
      MapParameterSetStorage::const_iterator iterator = parameterStorage.find(name);
      return (iterator != parameterStorage.end()) ? iterator->second : NULL;
    }
    
    const int MapParameterSet::size() const {
      return parameterStorage.size();
    }
  }
}
