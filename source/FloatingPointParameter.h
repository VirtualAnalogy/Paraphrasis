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
      FloatingPointParameter(ParameterString name) : PluginParameter() {
        this->name = name;
        this->value = 0.0;
      }
      ~FloatingPointParameter() {}

      const ParameterString getName() const { return this->name; }
      const ParameterString getDisplayValue() const {
        std::stringstream numberFormatter;
        numberFormatter << this->value;
        return numberFormatter.str();
      }

      const ParameterValue getValue() const { return this->value; }
      void setValue(const ParameterValue value) { this->value = value; }

    private:
      ParameterString name;
      ParameterValue value;
    };
  }
}

#endif
