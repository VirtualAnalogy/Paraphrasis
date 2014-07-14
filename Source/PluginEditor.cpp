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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ParaphrasisAudioProcessorEditor::ParaphrasisAudioProcessorEditor (ParaphrasisAudioProcessor* ownerFilter)
    : AudioProcessorEditor(ownerFilter)
{
    addAndMakeVisible (bypassBtn = new TextButton ("Bypass Button"));
    bypassBtn->setButtonText (TRANS("Bypass"));
    bypassBtn->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    getProcessor()->requestUIUpdate();//UI update must be done each time a new editor is constructed
    bypassBtn->setClickingTogglesState(true);
    startTimer (200); //starts timer with interval of 200mS
    //[/Constructor]
}

ParaphrasisAudioProcessorEditor::~ParaphrasisAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    bypassBtn = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ParaphrasisAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ParaphrasisAudioProcessorEditor::resized()
{
    bypassBtn->setBounds (80, 96, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ParaphrasisAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    ParaphrasisAudioProcessor* ourProcessor = getProcessor();
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == bypassBtn)
    {
        //[UserButtonCode_bypassBtn] -- add your button handler code here..
        ourProcessor->setParameter(ParaphrasisAudioProcessor::masterBypass, (float) bypassBtn->getToggleState());
        ourProcessor->setParameterNotifyingHost(ParaphrasisAudioProcessor::masterBypass, (float) bypassBtn->getToggleState());
        //[/UserButtonCode_bypassBtn]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ParaphrasisAudioProcessorEditor::timerCallback()
{
    ParaphrasisAudioProcessor* ourProcessor = getProcessor();
    if (ourProcessor->needsUIUpdate() )
    {
        //load your UI components with internal state information from plug-in - example:
        /*YourButtonName->setToggleState(1.0f == ourProcessor->getParameter(YourProjectNameAudioProcessor::MasterBypass), false);*/
        //repeat for "OtherParams"...
        bypassBtn->setToggleState(1.0f == ourProcessor->getParameter(ParaphrasisAudioProcessor::masterBypass), juce::dontSendNotification);
        ourProcessor->clearUIUpdateFlag();
    }
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ParaphrasisAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="ParaphrasisAudioProcessor* ownerFilter" variableInitialisers="AudioProcessorEditor(ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <TEXTBUTTON name="Bypass Button" id="e1e14ac0134f5ff1" memberName="bypassBtn"
              virtualName="" explicitFocusOrder="0" pos="80 96 150 24" buttonText="Bypass"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
