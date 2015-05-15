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
    static const char* anitaSemiSquare_ttf;
    static const int anitaSemiSquare_ttfSize;
    static const char* large_knob_png;
    static const int large_knob_pngSize;
    static const char* button_select_down_png;
    static const int button_select_down_pngSize;
    static const char* button_select_normal_png;
    static const int button_select_normal_pngSize;
    static const char* button_analyze_down_png;
    static const int button_analyze_down_pngSize;
    static const char* button_analyze_normal_png;
    static const int button_analyze_normal_pngSize;


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
