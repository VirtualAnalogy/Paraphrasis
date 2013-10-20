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

#ifndef __BooleanParameter_h__
#define __BooleanParameter_h__

#include "PluginParameter.h"

namespace teragon {
class BooleanParameter : public PluginParameter {
public:
  explicit BooleanParameter(ParameterString inName, bool inDefaultValue = false) :
  PluginParameter(inName), value(inDefaultValue) {}
  virtual ~BooleanParameter() {}

  virtual const ParameterString getDisplayText() const { return value ? "true" : "false"; }
  virtual const ParameterValue getDisplayValue() const { return getValue(); }
  virtual void setDisplayValue(const ParameterValue inValue) { setValue(inValue); }

  virtual const ParameterValue getScaledValue() const { return getValue(); }
  virtual const ParameterValue getValue() const { return value ? 1.0 : 0.0; }

#if ENABLE_MULTITHREADED
#if HAVE_TESTRUNNER
  friend class _Tests;
#endif
protected:
#endif
  virtual void setScaledValue(const ParameterValue inValue) { setValue(inValue); }
  virtual void setValue(const ParameterValue inValue) {
    value = inValue > 0.5 ? true : false;
    PluginParameter::setValue(inValue);
  }

private:
  bool value;
};
}

#endif
