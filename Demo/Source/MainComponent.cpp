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
#include "Resources.h"
//[/Headers]

#include "MainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainContentComponent::MainContentComponent (teragon::ThreadsafePluginParameterSet &parameters, teragon::ResourceCache *resourceCache)
    : parameters(parameters),
      resourceCache(resourceCache)
{
    addAndMakeVisible (toggleButtonLabel = new Label ("toggle button label",
                                                      "Toggle Button"));
    toggleButtonLabel->setFont (Font (15.00f, Font::plain));
    toggleButtonLabel->setJustificationType (Justification::centredLeft);
    toggleButtonLabel->setEditable (false, false, false);
    toggleButtonLabel->setColour (Label::textColourId, Colours::white);
    toggleButtonLabel->setColour (TextEditor::textColourId, Colours::black);
    toggleButtonLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (pushButtonLabel = new Label ("push button label",
                                                    "Push Button"));
    pushButtonLabel->setFont (Font (15.00f, Font::plain));
    pushButtonLabel->setJustificationType (Justification::centredLeft);
    pushButtonLabel->setEditable (false, false, false);
    pushButtonLabel->setColour (Label::textColourId, Colours::white);
    pushButtonLabel->setColour (TextEditor::textColourId, Colours::black);
    pushButtonLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (faderLabel = new Label ("fader label",
                                               "Fader"));
    faderLabel->setFont (Font (15.00f, Font::plain));
    faderLabel->setJustificationType (Justification::centred);
    faderLabel->setEditable (false, false, false);
    faderLabel->setColour (Label::textColourId, Colours::white);
    faderLabel->setColour (TextEditor::textColourId, Colours::black);
    faderLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (indicatorLightLabel = new Label ("indicator light label",
                                                        "Indicator Light"));
    indicatorLightLabel->setFont (Font (15.00f, Font::plain));
    indicatorLightLabel->setJustificationType (Justification::centredLeft);
    indicatorLightLabel->setEditable (false, false, false);
    indicatorLightLabel->setColour (Label::textColourId, Colours::white);
    indicatorLightLabel->setColour (TextEditor::textColourId, Colours::black);
    indicatorLightLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (largeKnobLabel = new Label ("large knob label",
                                                   "Large Knob"));
    largeKnobLabel->setFont (Font (15.00f, Font::plain));
    largeKnobLabel->setJustificationType (Justification::centredLeft);
    largeKnobLabel->setEditable (false, false, false);
    largeKnobLabel->setColour (Label::textColourId, Colours::white);
    largeKnobLabel->setColour (TextEditor::textColourId, Colours::black);
    largeKnobLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (smallKnobLabel = new Label ("small knob label",
                                                   "Small knob"));
    smallKnobLabel->setFont (Font (15.00f, Font::plain));
    smallKnobLabel->setJustificationType (Justification::centredLeft);
    smallKnobLabel->setEditable (false, false, false);
    smallKnobLabel->setColour (Label::textColourId, Colours::white);
    smallKnobLabel->setColour (TextEditor::textColourId, Colours::black);
    smallKnobLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (toggleButton = new teragon::ToggleButton (parameters, "button",
                                                                 resourceCache));
    toggleButton->setName ("toggle button");

    addAndMakeVisible (pushButton = new teragon::PushButton (parameters, "indicator",
                                                             resourceCache));
    pushButton->setName ("push button");

    addAndMakeVisible (smallKnob = new teragon::ImageKnobSmall (parameters, "knob", resourceCache));
    smallKnob->setName ("small knob");

    addAndMakeVisible (largeKnob = new teragon::ImageKnobLarge (parameters, "knob", resourceCache));
    largeKnob->setName ("large knob");

    addAndMakeVisible (fader = new teragon::ImageSlider (parameters, "knob", resourceCache));
    fader->setName ("fader");

    addAndMakeVisible (indicatorLight = new teragon::IndicatorLight (parameters, "indicator",
                                                                     resourceCache));
    indicatorLight->setName ("indicator light");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (250, 320);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MainContentComponent::~MainContentComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    toggleButtonLabel = nullptr;
    pushButtonLabel = nullptr;
    faderLabel = nullptr;
    indicatorLightLabel = nullptr;
    largeKnobLabel = nullptr;
    smallKnobLabel = nullptr;
    toggleButton = nullptr;
    pushButton = nullptr;
    smallKnob = nullptr;
    largeKnob = nullptr;
    fader = nullptr;
    indicatorLight = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    delete resourceCache;
    resourceCache = nullptr;
    //[/Destructor]
}

//==============================================================================
void MainContentComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::black);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainContentComponent::resized()
{
    toggleButtonLabel->setBounds (14, 32, 96, 24);
    pushButtonLabel->setBounds (16, 88, 94, 24);
    faderLabel->setBounds (32, 282, 48, 24);
    indicatorLightLabel->setBounds (136, 40, 96, 24);
    largeKnobLabel->setBounds (136, 285, 80, 24);
    smallKnobLabel->setBounds (144, 136, 80, 24);
    toggleButton->setBounds (24, 16, 72, 40);
    pushButton->setBounds (24, 72, 70, 40);
    smallKnob->setBounds (152, 72, 66, 66);
    largeKnob->setBounds (120, 170, 113, 113);
    fader->setBounds (24, 144, 62, 134);
    indicatorLight->setBounds (168, 16, 24, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainContentComponent" componentName=""
                 parentClasses="public Component" constructorParams="teragon::ThreadsafePluginParameterSet &amp;parameters, teragon::ResourceCache *resourceCache"
                 variableInitialisers="parameters(parameters),&#10;resourceCache(resourceCache)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.660"
                 fixedSize="1" initialWidth="250" initialHeight="320">
  <BACKGROUND backgroundColour="ff000000">
    <IMAGE pos="0 0 250 320" resource="" opacity="1" mode="0"/>
  </BACKGROUND>
  <LABEL name="toggle button label" id="38208308bb309b1a" memberName="toggleButtonLabel"
         virtualName="" explicitFocusOrder="0" pos="14 32 96 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Toggle Button" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="push button label" id="ad30ab13d0bd72a3" memberName="pushButtonLabel"
         virtualName="" explicitFocusOrder="0" pos="16 88 94 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Push Button" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="fader label" id="97f421fd7cf519bb" memberName="faderLabel"
         virtualName="" explicitFocusOrder="0" pos="32 282 48 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Fader" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="36"/>
  <LABEL name="indicator light label" id="75da6a91515ddd5d" memberName="indicatorLightLabel"
         virtualName="" explicitFocusOrder="0" pos="136 40 96 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Indicator Light"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="large knob label" id="ef0fde9d17b48a9b" memberName="largeKnobLabel"
         virtualName="" explicitFocusOrder="0" pos="136 285 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Large Knob" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="small knob label" id="4730cafd631f5fb9" memberName="smallKnobLabel"
         virtualName="" explicitFocusOrder="0" pos="144 136 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Small knob" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="toggle button" id="ca1a005aea565e73" memberName="toggleButton"
                    virtualName="teragon::ToggleButton" explicitFocusOrder="0" pos="24 16 72 40"
                    class="Component" params="parameters, &quot;button&quot;,&#10;resourceCache"/>
  <GENERICCOMPONENT name="push button" id="95812891ea323314" memberName="pushButton"
                    virtualName="teragon::PushButton" explicitFocusOrder="0" pos="24 72 70 40"
                    class="Component" params="parameters, &quot;indicator&quot;,&#10;resourceCache"/>
  <GENERICCOMPONENT name="small knob" id="cbdd78d09251ea34" memberName="smallKnob"
                    virtualName="teragon::ImageKnobSmall" explicitFocusOrder="0"
                    pos="152 72 66 66" class="Component" params="parameters, &quot;knob&quot;, resourceCache"/>
  <GENERICCOMPONENT name="large knob" id="1ebc5ac437f1ae39" memberName="largeKnob"
                    virtualName="teragon::ImageKnobLarge" explicitFocusOrder="0"
                    pos="120 170 113 113" class="Component" params="parameters, &quot;knob&quot;, resourceCache"/>
  <GENERICCOMPONENT name="fader" id="8f5f5e73140aff67" memberName="fader" virtualName="teragon::ImageSlider"
                    explicitFocusOrder="0" pos="24 144 62 134" class="Component"
                    params="parameters, &quot;knob&quot;, resourceCache"/>
  <GENERICCOMPONENT name="indicator light" id="fca1b7e8ed89a244" memberName="indicatorLight"
                    virtualName="teragon::IndicatorLight" explicitFocusOrder="0"
                    pos="168 16 24 24" class="Component" params="parameters, &quot;indicator&quot;,&#10;resourceCache"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
