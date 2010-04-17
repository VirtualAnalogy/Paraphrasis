/*
 *  BooleanParameter.cpp
 *  PluginParameters
 *
 *  Created by Nik Reiman on 2010-04-17.
 *  Copyright 2010 Teragon Audio. All rights reserved.
 *
 */

#ifndef __BooleanParameter_h__
#include "BooleanParameter.h"
#endif

namespace teragon {
  namespace pluginParameters {
    BooleanParameter::BooleanParameter(ParameterString name) : PluginParameter() {
      this->name = name;
      this->value = false;
    }
    
    BooleanParameter::~BooleanParameter() {
    }
    
    const ParameterString BooleanParameter::getDisplayText() const {
      return this->value ? "true" : "false";
    }
    
    const ParameterValue BooleanParameter::getDisplayValue() const {
      return this->value ? 1.0 : 0.0;
    }
  }
}
