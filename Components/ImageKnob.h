/*
  ==============================================================================

    ImageKnob.h
    Created: 29 May 2013 8:45:14pm
    Author:  Nik Reiman

  ==============================================================================
*/

#ifndef __IMAGEKNOB_H_4804529__
#define __IMAGEKNOB_H_4804529__

#include "JuceHeader.h"

namespace teragon {

class ImageKnob : public juce::Slider {
public:
  ImageKnob(const char* knobImage, const int knobImageSize);
  virtual ~ImageKnob();

  void paint(Graphics &g);
  void setImages(const Image& knobImage);

private:
  Image knobImage;
};

} // namespace teragon

#endif  // __IMAGEKNOB_H_4804529__
