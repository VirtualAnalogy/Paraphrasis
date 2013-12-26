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

#ifndef __PluginParameters_DataParameter_h__
#define __PluginParameters_DataParameter_h__

#include "Parameter.h"

namespace teragon {

/**
* This class is intended for non-calculation data holders, such as strings or blobs.
*/
class DataParameter : public Parameter {
public:
    DataParameter(const ParameterString &inName) : Parameter(inName, 0.0, 1.0, 0.0) {}
    virtual ~DataParameter() {}

    virtual const ParameterValue getScaledValue() const {
        return 0.0;
    }

    virtual void setScaledValue(const ParameterValue value) {}

    virtual void setValue(const ParameterValue inValue) {}

#if PLUGINPARAMETERS_MULTITHREADED
    friend class Event;
    friend class DataEvent;

protected:
#endif

    virtual void setValue(const void *inData, const size_t inDataSize) = 0;
};

} // namespace teragon

#endif // __PluginParameters_DataParameter_h__
