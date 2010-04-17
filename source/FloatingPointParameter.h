#ifndef __FloatingPointParameter_h__
#define __FloatingPointParameter_h__

#ifndef __NumericParameter_h__
#include "NumericParameter.h"
#endif

namespace teragon {
  namespace pluginParameters {
    class FloatingPointParameter : public NumericParameter {
    public:
      FloatingPointParameter(ParameterString name, ParameterValue minValue, ParameterValue maxValue);
      ~FloatingPointParameter();

      const ParameterValue getDisplayValue() const;
      void setDisplayValue(const ParameterValue value);
    };
  }
}

#endif
