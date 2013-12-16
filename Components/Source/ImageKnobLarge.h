/*
  ==============================================================================

    ImageKnobLarge.h
    Created: 16 Dec 2013 10:16:45pm
    Author:  Nik Reiman

  ==============================================================================
*/

#ifndef IMAGEKNOBLARGE_H_INCLUDED
#define IMAGEKNOBLARGE_H_INCLUDED

#include "ImageKnob.h"

namespace teragon {

class ImageKnobLarge : public ImageKnob {
public:
    ImageKnobLarge(ThreadsafePluginParameterSet &parameters, const ParameterString &name,
                   const ResourceCache *resources) :
    ImageKnob(parameters, name, resources, "large_knob") {}

    virtual ~ImageKnobLarge() {}
};
} // namespace teragon

#endif  // IMAGEKNOBLARGE_H_INCLUDED
