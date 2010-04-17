/*
 *  DecibelParameter.cpp
 *  PluginParameters
 *
 *  Created by Nik Reiman on 2010-04-18.
 *  Copyright 2010 Teragon Audio. All rights reserved.
 *
 */

#ifndef __DecibelParameter_h__
#include "DecibelParameter.h"
#endif

#include <math.h>

namespace teragon {
  namespace pluginParameters {
    DecibelParameter::DecibelParameter(ParameterString name, ParameterValue minValue, ParameterValue maxValue) :
    NumericParameter(name, minValue, maxValue) {
    }
    
    DecibelParameter::~DecibelParameter() {
    }
    
    const ParameterValue DecibelParameter::getDisplayValue() const {
      // XXX: Some of the values in this calculation could be cached
      return (log(getValue()) - log(getMinValue())) /
             (log(getMaxValue()) - log(getMinValue()));
    }
    
    void DecibelParameter::setDisplayValue(const ParameterValue value) {
      // XXX: Some of the values in this calculation could be cached
      setValue(exp(value * (log(getMaxValue()) - log(getMinValue())) + log(getMinValue())));
    }
  }
}
