/*
 *  NamedParameter.h
 *  PluginParameters
 *
 *  Created by Nik Reiman on 2010-04-18.
 *  Copyright 2010 Teragon Audio. All rights reserved.
 *
 */

#ifndef __NamedParameter_h__
#define __NamedParameter_h__

#ifndef __PluginParameter_h__
#include "PluginParameter.h"
#endif

namespace teragon {
  namespace pluginParameters {
    class NamedParameter : public PluginParameter {
    public:
      NamedParameter(ParameterString name) : PluginParameter() { this->name = name; }
      ~NamedParameter() {}
      
      const ParameterString getName() const { return this->name; }
      
    private:
      ParameterString name;
    };
  }
}

#endif
