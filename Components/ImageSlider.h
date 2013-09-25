/*
  ==============================================================================

    ImageSlider.h
    Created: 28 May 2013 10:07:08pm
    Author:  Nik Reiman

  ==============================================================================
*/

#ifndef __IMAGESLIDER_H_B0B8D694__
#define __IMAGESLIDER_H_B0B8D694__

#include "JuceHeader.h"

namespace teragon {

class ImageSlider : public juce::Slider {
public:
    ImageSlider(const char* handleImage, const int handleImageSize,
        const char* wellImage, const int wellImageSize);
    ImageSlider(const String &componentName);
    virtual ~ImageSlider();

    void paint(Graphics &g);
    void setImages(const Image& handleImage, const Image& wellImage);

private:
    Image handleImage;
    Image wellImage;
};

} // namespace teragon

#endif  // __IMAGESLIDER_H_B0B8D694__
