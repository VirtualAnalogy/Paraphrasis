/*
  ==============================================================================

    ThinButton.h
    Created: 30 May 2013 8:47:07pm
    Author:  Nik Reiman

  ==============================================================================
*/

#ifndef __THINBUTTON_H_2C648127__
#define __THINBUTTON_H_2C648127__

#include "JuceHeader.h"

namespace teragon {

class ThinButton : public juce::ImageButton {
public:
    typedef enum {
        kGravityTop,
        kGravityBottom,
        kGravityCentered,
        kGravityDefault = kGravityTop
    } Gravity;

public:
    ThinButton(const char* pressedImage, const int pressedImageSize,
        const char* normalImage, const int normalImageSize,
        const ThinButton::Gravity gravity = kGravityDefault);
    virtual ~ThinButton() {}

    void paint(Graphics &g);
    virtual const Image getImageForButtonState() = 0;
    void setImages(const Image &buttonDown, const Image &buttonUp);

private:
      Gravity gravity;
      Image buttonDown;
      Image buttonUp;
};

} // namespace teragon

#endif  // __THINBUTTON_H_2C648127__
