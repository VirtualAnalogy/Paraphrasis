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

#ifndef __JUCE_HEADER_CA663DA5FEBB7F21__
#define __JUCE_HEADER_CA663DA5FEBB7F21__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "TeragonGuiComponents.h"
#include "Resources.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ParaphrasisAudioProcessorEditor  : public AudioProcessorEditor,
                                         public ParameterObserver,
                                         public ButtonListener,
                                         public LabelListener
{
public:
    //==============================================================================
    ParaphrasisAudioProcessorEditor (ParaphrasisAudioProcessor* ownerFilter, teragon::ConcurrentParameterSet& p, teragon::ResourceCache *r);
    ~ParaphrasisAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    virtual bool isRealtimePriority() const
    {
        return false;
    }

    virtual void onParameterUpdated(const Parameter *parameter) ;
    static double checkParameterBoundaries(const Parameter *parameter, double value);

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void labelTextChanged (Label* labelThatHasChanged);

    // Binary resources:
    static const char* background2_png;
    static const int background2_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    teragon::ConcurrentParameterSet &parameters;
    teragon::ResourceCache *resources;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<teragon::ImageKnobLarge> knob;
    ScopedPointer<teragon::ImageKnobLarge> knob2;
    ScopedPointer<Label> sampleLbl;
    ScopedPointer<ImageButton> selectBtn;
    ScopedPointer<ImageButton> analyzeBtn;
    ScopedPointer<Label> pitchLbl;
    ScopedPointer<Label> resolutionLbl;
    Image cachedImage_background2_png;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParaphrasisAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_CA663DA5FEBB7F21__
