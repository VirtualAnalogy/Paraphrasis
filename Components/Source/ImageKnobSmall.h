/*
  ==============================================================================

    ImageKnobSmall.h
    Created: 16 Dec 2013 10:16:35pm
    Author:  Nik Reiman

  ==============================================================================
*/

#ifndef IMAGEKNOBSMALL_H_INCLUDED
#define IMAGEKNOBSMALL_H_INCLUDED

#include "ImageKnob.h"

namespace teragon {

class ImageKnobSmall : public ImageKnob {

public:
    ImageKnobSmall(ThreadsafePluginParameterSet &parameters, const ParameterString &name,
                   const ResourceCache *resources) :
    ImageKnob(parameters, name, resources, "small_knob") {}

    virtual ~ImageKnobSmall() {}
};

} // namespace teragon

#endif  // IMAGEKNOBSMALL_H_INCLUDED
