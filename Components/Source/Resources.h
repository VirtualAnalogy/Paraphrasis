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

#ifndef __JUCE_HEADER_334E74D91B2532D2__
#define __JUCE_HEADER_334E74D91B2532D2__

//[Headers]     -- You can add your own extra header files here --
/*
Copyright (c) 2013 Teragon Audio. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/

#include "JuceHeader.h"
#include "ResourceCache.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class Resources  : public Component
{
public:
    //==============================================================================
    Resources ();
    ~Resources();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    /**
      * @return A new ResourceCache instance which can be used to fetch graphics for
      * drawing all components. This object is generally passed to the component
      * window upon creation, which then assumes ownership of the cache. This means
      * that this object is responsible for deleting the cache upon destruction, or
      * else resources will be leaked!
      */
    static teragon::ResourceCache* getCache();
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
    static const char* toggle_button_normal_png;
    static const int toggle_button_normal_pngSize;
    static const char* toggle_button_pressed_png;
    static const int toggle_button_pressed_pngSize;
    static const char* large_knob_135frames_png;
    static const int large_knob_135frames_pngSize;
    static const char* small_knob_135frames_png;
    static const int small_knob_135frames_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Resources)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_334E74D91B2532D2__
