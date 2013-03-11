/*
 * Copyright (c) 2013 Teragon Audio. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __FrequencyParameter_h__
#define __FrequencyParameter_h__

#include <sstream>
#include <math.h>
#include "PluginParameter.h"

namespace teragon {
class FrequencyParameter : public PluginParameter {
public:
  explicit FrequencyParameter(ParameterString inName, ParameterValue inMinValue,
  ParameterValue inMaxValue, ParameterValue inDefaultValue) :
  PluginParameter(inName, inMinValue, inMaxValue, inDefaultValue) {
    logMinValue = log(inMinValue);
    range = log(inMaxValue) - log(inMinValue);
  }
  virtual ~FrequencyParameter() {}

  virtual const ParameterString getDisplayText() const {
    std::stringstream numberFormatter;
    numberFormatter.precision(1);
    numberFormatter << std::fixed << getValue();
    return numberFormatter.str() + " Hz";
  }
  virtual const ParameterValue getScaledValue() const {
    return (log(getValue()) - logMinValue) / range;
  }
  virtual void setScaledValue(const ParameterValue inValue) {
    setValue(exp(inValue * range + logMinValue));
  }

private:
  double logMinValue;
  double range;
};
}

#endif
