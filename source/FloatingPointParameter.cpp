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
    FloatingPointParameter::FloatingPointParameter(ParameterString name, ParameterValue minValue, ParameterValue maxValue) :
    NumericParameter(name, minValue, maxValue) {
    }
    
    FloatingPointParameter::~FloatingPointParameter() {
    }
    
    const ParameterValue FloatingPointParameter::getDisplayValue() const {
      // XXX: Some of the values in this calculation could be cached
      return (getValue() - getMinValue()) / (getMaxValue() - getMinValue());
    }
    
    void FloatingPointParameter::setDisplayValue(const ParameterValue value) {
      // XXX: Some of the values in this calculation could be cached
      setValue(value * (getMaxValue() - getMinValue()) + getMinValue());
    }
  }
}
