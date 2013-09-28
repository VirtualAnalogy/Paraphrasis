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
MainContentComponent::MainContentComponent (teragon::PluginParameterSet &parameters)
    : parameters(parameters)
{
    addAndMakeVisible (newLabel = new Label ("new label",
                                             "Toggle Button"));
    newLabel->setFont (Font (15.00f, Font::plain));
    newLabel->setJustificationType (Justification::centredLeft);
    newLabel->setEditable (false, false, false);
    newLabel->setColour (Label::textColourId, Colours::white);
    newLabel->setColour (TextEditor::textColourId, Colours::black);
    newLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

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

    addAndMakeVisible (label3 = new Label ("new label",
                                           "Indicator Light"));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (Label::textColourId, Colours::white);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label4 = new Label ("new label",
                                           "Large Knob"));
    label4->setFont (Font (15.00f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (Label::textColourId, Colours::white);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label5 = new Label ("new label",
                                           "Small knob"));
    label5->setFont (Font (15.00f, Font::plain));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (Label::textColourId, Colours::white);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (toggleButton = new teragon::ToggleButton (parameters["button"],
                                                                 Resources::toggle_button_normal_png,
                                                                 Resources::toggle_button_normal_pngSize,
                                                                 Resources::toggle_button_pressed_png,
                                                                 Resources::toggle_button_pressed_pngSize));
    toggleButton->setName ("toggle button");

    addAndMakeVisible (pushButton = new teragon::PushButton (parameters["indicator"],
                                                             Resources::push_button_normal_png,
                                                             Resources::push_button_normal_pngSize,
                                                             Resources::push_button_pressed_png,
                                                             Resources::push_button_pressed_pngSize));
    pushButton->setName ("push button");

    addAndMakeVisible (smallKnob = new teragon::ImageKnob (parameters["knob"],
                                                           Resources::smallknob270frames_png,
                                                           Resources::smallknob270frames_pngSize));
    smallKnob->setName ("small knob");

    addAndMakeVisible (largeKnob = new teragon::ImageKnob (parameters["knob"],
                                                           Resources::largeknob270frames_png,
                                                           Resources::largeknob270frames_pngSize));
    largeKnob->setName ("large knob");

    addAndMakeVisible (fader = new teragon::ImageSlider (parameters["knob"],
                                                         Resources::slider_thumb_png,
                                                         Resources::slider_thumb_pngSize,
                                                         Resources::slider_well_png,
                                                         Resources::slider_well_pngSize));
    fader->setName ("fader");

    addAndMakeVisible (indicatorLight = new teragon::IndicatorLight (parameters["indicator"],
                                                                     Resources::indicator_light_active_png,
                                                                     Resources::indicator_light_active_pngSize,
                                                                     Resources::indicator_light_inactive_png,
                                                                     Resources::indicator_light_inactive_pngSize));
    indicatorLight->setName ("indicator light");

    drawable1 = Drawable::createFromImageData (Resources::texture_png, Resources::texture_pngSize);

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

    newLabel = nullptr;
    pushButtonLabel = nullptr;
    faderLabel = nullptr;
    label3 = nullptr;
    label4 = nullptr;
    label5 = nullptr;
    toggleButton = nullptr;
    pushButton = nullptr;
    smallKnob = nullptr;
    largeKnob = nullptr;
    fader = nullptr;
    indicatorLight = nullptr;
    drawable1 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainContentComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    jassert (drawable1 != 0);
    if (drawable1 != 0)
        drawable1->drawWithin (g, Rectangle<float> (-3, -4, 512, 512),
                               RectanglePlacement::stretchToFit, 1.000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainContentComponent::resized()
{
    newLabel->setBounds (14, 32, 96, 24);
    pushButtonLabel->setBounds (16, 88, 94, 24);
    faderLabel->setBounds (32, 282, 48, 24);
    label3->setBounds (136, 40, 96, 24);
    label4->setBounds (136, 285, 80, 24);
    label5->setBounds (144, 136, 80, 24);
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
                 parentClasses="public Component, public ButtonListener" constructorParams="teragon::PluginParameterSet &amp;parameters"
                 variableInitialisers="parameters(parameters)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.660" fixedSize="1"
                 initialWidth="250" initialHeight="320">
  <BACKGROUND backgroundColour="ffffffff">
    <IMAGE pos="-3 -4 512 512" resource="texture_png" opacity="1" mode="0"/>
  </BACKGROUND>
  <LABEL name="new label" id="38208308bb309b1a" memberName="newLabel"
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
  <LABEL name="new label" id="75da6a91515ddd5d" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="136 40 96 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Indicator Light"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="ef0fde9d17b48a9b" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="136 285 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Large Knob" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="4730cafd631f5fb9" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="144 136 80 24" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="Small knob" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="toggle button" id="ca1a005aea565e73" memberName="toggleButton"
                    virtualName="teragon::ToggleButton" explicitFocusOrder="0" pos="24 16 72 40"
                    class="Component" params="toggle_button_normal_png,&#10;toggle_button_normal_pngSize,&#10;toggle_button_pressed_png,&#10;toggle_button_pressed_pngSize"/>
  <GENERICCOMPONENT name="push button" id="95812891ea323314" memberName="pushButton"
                    virtualName="teragon::PushButton" explicitFocusOrder="0" pos="24 72 70 40"
                    class="Component" params="push_button_normal_png,&#10;push_button_normal_pngSize,&#10;push_button_pressed_png,&#10;push_button_pressed_pngSize"/>
  <GENERICCOMPONENT name="small knob" id="cbdd78d09251ea34" memberName="smallKnob"
                    virtualName="teragon::ImageKnob" explicitFocusOrder="0" pos="152 72 66 66"
                    class="Component" params="smallknob270frames_png,&#10;smallknob270frames_pngSize"/>
  <GENERICCOMPONENT name="large knob" id="1ebc5ac437f1ae39" memberName="largeKnob"
                    virtualName="teragon::ImageKnob" explicitFocusOrder="0" pos="120 170 113 113"
                    class="Component" params="largeknob270frames_png,&#10;largeknob270frames_pngSize"/>
  <GENERICCOMPONENT name="fader" id="8f5f5e73140aff67" memberName="fader" virtualName="teragon::ImageSlider"
                    explicitFocusOrder="0" pos="24 144 62 134" class="Component"
                    params="slider_thumb_png,&#10;slider_thumb_pngSize,&#10;slider_well_png,&#10;slider_well_pngSize"/>
  <GENERICCOMPONENT name="indicator light" id="fca1b7e8ed89a244" memberName="indicatorLight"
                    virtualName="teragon::IndicatorLight" explicitFocusOrder="0"
                    pos="168 16 24 24" class="Component" params="indicator_light_active_png,&#10;indicator_light_active_pngSize,&#10;indicator_light_inactive_png,&#10;indicator_light_inactive_pngSize"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
