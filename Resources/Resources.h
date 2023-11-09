/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

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
class GraphicsResources  : public Component
{
public:
    //==============================================================================
    GraphicsResources ();
    ~GraphicsResources() override;

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

    void paint (juce::Graphics& g) override;
    void resized() override;

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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GraphicsResources)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

