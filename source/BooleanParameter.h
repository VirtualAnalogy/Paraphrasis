/*
 *  BooleanParameter.h
 *  PluginParameters
 *
 *  Created by Nik Reiman on 2010-04-17.
 *  Copyright 2010 Teragon Audio. All rights reserved.
 *
 */

#ifndef __BooleanParameter_h__
#define __BooleanParameter_h__

#ifndef __NamedParameter_h__
#include "NamedParameter.h"
#endif

namespace teragon {
  namespace pluginParameters {
    class BooleanParameter : public NamedParameter {
    public:
      BooleanParameter(ParameterString name);
      ~BooleanParameter();
            
      const ParameterString getDisplayText() const;
      const ParameterValue getDisplayValue() const;
      void setDisplayValue(const ParameterValue value);
      
      const ParameterValue getValue() const { return this->value; }
      void setValue(const ParameterValue value) { this->value = value; }
      
    private:
      ParameterString name;
      bool value;
    };
  }
}

#endif
