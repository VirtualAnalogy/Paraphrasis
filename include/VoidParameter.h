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

#ifndef __VOIDPARAMETER_H_
#define __VOIDPARAMETER_H_

namespace teragon {
/**
 * Parameter which does not hold a real value. This parameter's value is
 * always 0, regardless of whether setValue() is called.
 * This parameter type is mostly useful to send events between observers.
 */
class VoidParameter : public PluginParameter {
public:
  explicit VoidParameter(ParameterString inName) : PluginParameter(inName) {}
  virtual ~VoidParameter() {}

  virtual const ParameterString getDisplayText() const { return getName(); }
  virtual const ParameterValue getDisplayValue() const { return getValue(); }
  virtual void setDisplayValue(const ParameterValue inValue) { setValue(inValue); }

  virtual const ParameterValue getScaledValue() const { return getValue(); }
  virtual void setScaledValue(const ParameterValue inValue) { setValue(inValue); }
  virtual const ParameterValue getValue() const { return 0.0; }
  virtual void setValue(const ParameterValue inValue = 0.0) {
    notifyObservers();
  }

private:
  bool value;
};
}
#endif

