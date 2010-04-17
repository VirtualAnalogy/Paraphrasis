/*
 *  FloatingPointParameter.cpp
 *  PluginParameters
 *
 *  Created by Nik Reiman on 2010-04-17.
 *  Copyright 2010 Teragon Audio. All rights reserved.
 *
 */

#ifndef __FloatingPointParameter_h__
#include "FloatingPointParameter.h"
#endif

namespace teragon {
  namespace pluginParameters {
    FloatingPointParameter::FloatingPointParameter(ParameterString name, ParameterValue minValue, ParameterValue maxValue) : PluginParameter() {
      this->name = name;
      this->minValue = minValue;
      this->maxValue = maxValue;
      this->value = minValue;
    }
    
    FloatingPointParameter::~FloatingPointParameter() {
    }
    
    const ParameterString FloatingPointParameter::getDisplayText() const {
      std::stringstream numberFormatter;
      numberFormatter << this->value;
      return numberFormatter.str();
    }
    
    const ParameterValue FloatingPointParameter::getDisplayValue() const {
      return (this->value - this->minValue) / (this->maxValue - this->minValue);
    }
  }
}
