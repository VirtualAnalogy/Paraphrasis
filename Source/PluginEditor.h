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
/**
 This is Paraphrasis synthesiser.

 Copyright (c) 2014 by Tomas Medek

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY, without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

 tom@virtualanalogy.com
 */
#include "JuceHeader.h"
#include "PluginProcessor.h"

#include "TeragonGuiComponents.h"

#include "Resources.h"

#include "dRowAudio_PitchDetector.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
 Paraphrasis editor.
                                                                    //[/Comments]
*/
class ParaphrasisAudioProcessorEditor  : public AudioProcessorEditor,
                                         public ParameterObserver,
                                         public ButtonListener,
                                         public LabelListener
{
public:
    //==============================================================================
    ParaphrasisAudioProcessorEditor (ParaphrasisAudioProcessor* ownerFilter, teragon::ConcurrentParameterSet& p, teragon::ResourceCache *r, AudioFormatManager &formatManager);
    ~ParaphrasisAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    ParaphrasisAudioProcessor* getProcessor() const
    {
        return static_cast <ParaphrasisAudioProcessor*>(getAudioProcessor());
    }

    /** Set LED light on
        @param on true = on, off otherwise. */
    void lightOn(bool on) { ledBtn->setToggleState(on, false); }

    /** teragon::ParameterObserver method
        @param parameter Parameter to be updated.
     */
    virtual void onParameterUpdated(const Parameter *parameter) ;

    /** teragon::ParameterObserver method.
     */
    virtual bool isRealtimePriority() const { return false; }


    /** Check if value is in interval defined by parameter.
        @parameter parameter Parameter object with interval definition.
        @parameter value Value to be checked.
     */
    static double checkParameterBoundaries(const Parameter *parameter, double value);

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void labelTextChanged (Label* labelThatHasChanged);

    // Binary resources:
    static const char* background2_png;
    static const int background2_pngSize;
    static const char* led_off_png;
    static const int led_off_pngSize;
    static const char* led_on_png;
    static const int led_on_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    teragon::ConcurrentParameterSet& parameters; // parameters
    teragon::ResourceCache *resources;  // pictures, etc.
    AudioFormatManager& formatManager;  // loads audio files
    std::string path;                   // path of actual sample (it is class variable - we want it to have live long, string data are send and processed later, it is done so to prevent memory issues if it was local variable)
    drow::PitchDetector detector;       // to auto-detect sample pitch
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<teragon::ImageKnobLarge> knob;
    ScopedPointer<teragon::ImageKnobLarge> knob2;
    ScopedPointer<Label> sampleLbl;
    ScopedPointer<ImageButton> selectBtn;
    ScopedPointer<ImageButton> analyzeBtn;
    ScopedPointer<Label> pitchLbl;
    ScopedPointer<Label> resolutionLbl;
    ScopedPointer<ImageButton> resolutionBtn;
    ScopedPointer<ImageButton> ledBtn;
    ScopedPointer<ImageButton> reverseBtn;
    Image cachedImage_background2_png;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParaphrasisAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_CA663DA5FEBB7F21__
