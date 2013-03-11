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

#ifndef __DecibelParameter_h__
#define __DecibelParameter_h__

#include <sstream>
#include <math.h>
#include "FloatParameter.h"

namespace teragon {
class DecibelParameter : public FloatParameter {
public:
  /**
   * Create a new parameter for a volume in decibels. Note that this parameter
   * represents its value internally as a *linear* value. If you actually need
   * this value in decibels, see the convertLinearToDecibels() method.
   */
  explicit DecibelParameter(ParameterString inName, ParameterValue inMinValue,
  ParameterValue inMaxValue, ParameterValue inDefaultValue) :
  FloatParameter(inName, convertDecibelsToLinear(inMinValue),
   convertDecibelsToLinear(inMaxValue), convertDecibelsToLinear(inDefaultValue)) {
    range = getMaxValue() - getMinValue();
  }
  virtual ~DecibelParameter() {}

  virtual const ParameterString getDisplayText() const {
    std::stringstream numberFormatter;
    numberFormatter.precision(1);
    numberFormatter << std::fixed << convertLinearToDecibels(getValue());
    return numberFormatter.str() + " dB";
  }

  static const ParameterValue convertDecibelsToLinear(const ParameterValue decibels) {
    return exp10(decibels / 20.0);
  }

  static const ParameterValue convertLinearToDecibels(const ParameterValue linear) {
    return 20.0 * log10(linear);
  }

private:
  double range;
};
}

#endif
