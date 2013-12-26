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

#ifndef __PluginParameters_IntegerParameter_h__
#define __PluginParameters_IntegerParameter_h__

#include <sstream>
#include "FloatParameter.h"

namespace teragon {

class IntegerParameter : public FloatParameter {
public:
    IntegerParameter(const ParameterString &inName,
                     int inMinValue,
                     int inMaxValue,
                     int inDefaultValue) :
    FloatParameter(inName, (ParameterValue)inMinValue,
                   (ParameterValue)inMaxValue,
                   (ParameterValue)inDefaultValue) {}

    virtual ~IntegerParameter() {}

    virtual const ParameterString getDisplayText() const {
        std::stringstream numberFormatter;
        numberFormatter << (int)getValue();
        std::string result = numberFormatter.str();
        if(getUnit().length() > 0) {
            result.append(" ").append(getUnit());
        }
        return result;
    }
};

} // namespace teragon

#endif // __PluginParameters_IntegerParameter_h__
