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

#ifndef __PluginParameter_h__
#define __PluginParameter_h__

#include <string>

namespace teragon {
typedef std::string ParameterString;
typedef double ParameterValue;

class PluginParameter {
public:
  PluginParameter(ParameterString inName) :
    name(inName), minValue(0.0), maxValue(1.0), value(0.0) {}
  PluginParameter(ParameterString inName, ParameterValue inMinValue,
  ParameterValue inMaxValue, ParameterValue inDefaultValue) :
    name(inName), minValue(inMinValue), maxValue(inMaxValue), value(inDefaultValue) {}
  virtual ~PluginParameter() {}

  const ParameterString& getName() const { return name; }
  const ParameterString getSafeName() const { return makeSafeName(name); }
  static const ParameterString makeSafeName(const ParameterString& string) {
    ParameterString result;
    for(size_t i = 0; i < string.length(); ++i) {
      if(((string[i] >= 'a' && string[i] <= 'z') ||
          (string[i] >= '0' && string[i] <= '9') ||
          (string[i] >= 'A' && string[i] <= 'Z'))) {
        result += string[i];
      }
    }
    return result;
  }

  virtual const ParameterString getDisplayText() const = 0;
  virtual const ParameterValue getScaledValue() const = 0;
  virtual void setScaledValue(const ParameterValue value) = 0;

  virtual const ParameterValue getValue() const { return value; }
  virtual void setValue(const ParameterValue inValue) { value = inValue; }

protected:
  const ParameterValue getMinValue() const { return minValue; }
  const ParameterValue getMaxValue() const { return maxValue; }

private:
  ParameterString name;
  const ParameterValue minValue;
  const ParameterValue maxValue;
  ParameterValue value;
};
}

#endif
