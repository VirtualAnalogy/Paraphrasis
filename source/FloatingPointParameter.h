#ifndef __FloatingPointParameter_h__
#define __FloatingPointParameter_h__

#ifndef __PluginParameter_h__
#include "PluginParameter.h"
#endif

#include <sstream>

namespace teragon {
  namespace pluginParameters {
    class FloatingPointParameter : public PluginParameter {
    public:
      FloatingPointParameter(ParameterString name, ParameterValue minValue, ParameterValue maxValue);
      ~FloatingPointParameter();

      const ParameterString getName() const { return this->name; }
      
      const ParameterString getDisplayText() const;
      const ParameterValue getDisplayValue() const;
      
      const ParameterValue getValue() const { return this->value; }
      void setValue(const ParameterValue value) { this->value = value; }

    private:
      ParameterString name;
      ParameterValue value;
      ParameterValue minValue;
      ParameterValue maxValue;
    };
  }
}

#endif
