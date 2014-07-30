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

#ifndef __PluginParameters_BlobParameter_h__
#define __PluginParameters_BlobParameter_h__

#include <stdlib.h>
#include "DataParameter.h"

namespace teragon {

class BlobParameter : public DataParameter {
public:
    BlobParameter(const ParameterString &inName, void *inData = NULL, size_t inDataSize = 0) :
    DataParameter(inName),
    data(NULL), dataSize(inDataSize) {
        if(inData != NULL && inDataSize > 0) {
            data = malloc(inDataSize);
            memcpy(data, inData, inDataSize);
        }
    }

    virtual ~BlobParameter() {
        if(data != NULL) {
            free(data);
        }
    }

    virtual const ParameterString getDisplayText() const {
        return (data != NULL && dataSize > 0) ? "(Data)" : "(Null)";
    }

    virtual void *getData() const {
        return data;
    }

    virtual size_t getDataSize() const {
        return dataSize;
    }


#if PLUGINPARAMETERS_MULTITHREADED
protected:
#endif

    virtual void setValue(const void *inData, const size_t inDataSize) {
        if(inData == NULL || inDataSize == 0) {
            return;
        }
        if(data != NULL) {
            free(data);
        }

        data = malloc(inDataSize);
        dataSize = inDataSize;
        memcpy(data, inData, inDataSize);

        notifyObservers();
    }

private:
    void *data;
    size_t dataSize;
};

} // namespace teragon

#endif  // __PluginParameters_BlobParameter_h__
