/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_CB87035FA43504BB__
#define __JUCE_HEADER_CB87035FA43504BB__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "IndicatorLight.h"
#include "ImageKnob.h"
#include "ImageSlider.h"
#include "PushButton.h"
#include "ToggleButton.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainContentComponent  : public Component,
                              public ButtonListener
{
public:
    //==============================================================================
    MainContentComponent ();
    ~MainContentComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void buttonClicked(Button *button);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();

    // Binary resources:
    static const char* indicator_light_active_png;
    static const int indicator_light_active_pngSize;
    static const char* indicator_light_inactive_png;
    static const int indicator_light_inactive_pngSize;
    static const char* push_button_normal_png;
    static const int push_button_normal_pngSize;
    static const char* push_button_pressed_png;
    static const int push_button_pressed_pngSize;
    static const char* slider_thumb_png;
    static const int slider_thumb_pngSize;
    static const char* slider_well_png;
    static const int slider_well_pngSize;
    static const char* texture_png;
    static const int texture_pngSize;
    static const char* toggle_button_normal_png;
    static const int toggle_button_normal_pngSize;
    static const char* toggle_button_pressed_png;
    static const int toggle_button_pressed_pngSize;
    static const char* largeknob270frames_png;
    static const int largeknob270frames_pngSize;
    static const char* smallknob270frames_png;
    static const int smallknob270frames_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> newLabel;
    ScopedPointer<Label> label;
    ScopedPointer<Label> label2;
    ScopedPointer<Label> label3;
    ScopedPointer<Label> label4;
    ScopedPointer<Label> label5;
    ScopedPointer<teragon::PushButton> pushButton;
    ScopedPointer<teragon::ToggleButton> toggleButton;
    ScopedPointer<teragon::ImageKnob> smallKnob;
    ScopedPointer<teragon::ImageKnob> largeKnob;
    ScopedPointer<Component> component;
    Image cachedImage_texture_png;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_CB87035FA43504BB__
