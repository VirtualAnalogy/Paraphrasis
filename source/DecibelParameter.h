/*
 *  DecibelParameter.h
 *  PluginParameters
 *
 *  Created by Nik Reiman on 2010-04-18.
 *  Copyright 2010 Teragon Audio. All rights reserved.
 *
 */

#ifndef __DecibelParameter_h__
#define __DecibelParameter_h__

#ifndef __NumericParameter_h__
#include "NumericParameter.h"
#endif

namespace teragon {
  namespace pluginParameters {
    const ParameterValue kDcOffset = 1E-25f;
    
    class DecibelParameter : public NumericParameter {
    public:
      DecibelParameter(ParameterString name, ParameterValue minValue, ParameterValue maxValue);
      ~DecibelParameter();
      
      const ParameterValue getDisplayValue() const;
      void setDisplayValue(const ParameterValue value);
      
    private:
      ParameterString name;
    };
  }
}

#endif
