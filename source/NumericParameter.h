/*
 *  NumericParameter.h
 *  PluginParameters
 *
 *  Created by Nik Reiman on 2010-04-18.
 *  Copyright 2010 Teragon Audio. All rights reserved.
 *
 */

#ifndef __NumericParameter_h__
#define __NumericParameter_h__

#ifndef __NamedParameter_h__
#include "NamedParameter.h"
#endif

#include <sstream>

namespace teragon {
  namespace pluginParameters {
    class NumericParameter : public NamedParameter {
    public:
      NumericParameter(ParameterString name, ParameterValue minValue, ParameterValue maxValue) : NamedParameter(name) {
        this->minValue = minValue;
        this->maxValue = maxValue;
        this->value = minValue;
      }
      ~NumericParameter() {}
      
      const ParameterString getDisplayText() const {
        std::stringstream numberFormatter;
        numberFormatter << this->value;
        return numberFormatter.str();
      }
      
      const ParameterValue getMinValue() const { return this->maxValue; }
      const ParameterValue getMaxValue() const { return this->maxValue; }
      const ParameterValue getValue() const { return this->value; }
      void setValue(const ParameterValue value) { this->value = value; }
      
    private:
      ParameterValue minValue;
      ParameterValue maxValue;
      ParameterValue value;
    };
  }
}

#endif
