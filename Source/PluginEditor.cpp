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

//[Headers] You can add your own extra header files here...
/*
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

#include "../Resources/Resources.h"
#include "SampleAnalyzer.h"
#include "ParameterDefitions.h"
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...

//[/MiscUserDefs]

//==============================================================================
ParaphrasisAudioProcessorEditor::ParaphrasisAudioProcessorEditor (ParaphrasisAudioProcessor* ownerFilter, teragon::ConcurrentParameterSet& p, teragon::ResourceCache *r, AudioFormatManager &formatManager)
    : AudioProcessorEditor(ownerFilter),
      parameters(p),
      resources(r),
      formatManager(formatManager)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    knob.reset (new teragon::ImageKnobLarge (parameters, "Sample Pitch", r));
    addAndMakeVisible (knob.get());
    knob->setName ("knob");

    knob->setBounds (60, 129, 64, 64);

    knob2.reset (new teragon::ImageKnobLarge (parameters, "Frequency Resolution", r));
    addAndMakeVisible (knob2.get());
    knob2->setName ("knob");

    knob2->setBounds (176, 129, 64, 64);

    sampleLbl.reset (new juce::Label ("sampleLbl",
                                      juce::String()));
    addAndMakeVisible (sampleLbl.get());
    sampleLbl->setFont (juce::Font (juce::Font::getDefaultMonospacedFontName(), 13.50f, juce::Font::plain).withTypefaceStyle ("Regular"));
    sampleLbl->setJustificationType (juce::Justification::centredLeft);
    sampleLbl->setEditable (false, false, false);
    sampleLbl->setColour (juce::Label::backgroundColourId, juce::Colour (0x009f9d9d));
    sampleLbl->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    sampleLbl->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    sampleLbl->setBounds (24, 45, 176, 20);

    selectBtn.reset (new juce::ImageButton ("selectBtn"));
    addAndMakeVisible (selectBtn.get());
    selectBtn->setButtonText (TRANS("new button"));
    selectBtn->addListener (this);

    selectBtn->setImages (false, true, true,
                          juce::Image(), 1.000f, juce::Colour (0x00000000),
                          juce::Image(), 1.000f, juce::Colour (0x00000000),
                          juce::Image(), 1.000f, juce::Colour (0x00000000));
    selectBtn->setBounds (194, 41, 88, 30);

    analyzeBtn.reset (new juce::ImageButton ("analyzeBtn"));
    addAndMakeVisible (analyzeBtn.get());
    analyzeBtn->setButtonText (TRANS("new button"));
    analyzeBtn->addListener (this);

    analyzeBtn->setImages (false, true, true,
                           juce::Image(), 1.000f, juce::Colour (0x00000000),
                           juce::Image(), 1.000f, juce::Colour (0x00000000),
                           juce::Image(), 1.000f, juce::Colour (0x00000000));
    analyzeBtn->setBounds (105, 230, 92, 48);

    pitchLbl.reset (new juce::Label ("pitchLbl",
                                     TRANS("20k")));
    addAndMakeVisible (pitchLbl.get());
    pitchLbl->setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    pitchLbl->setJustificationType (juce::Justification::centred);
    pitchLbl->setEditable (true, true, false);
    pitchLbl->setColour (juce::Label::textColourId, juce::Colour (0xf2c3c3c3));
    pitchLbl->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    pitchLbl->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    pitchLbl->setColour (juce::TextEditor::highlightColourId, juce::Colour (0x40ffffff));
    pitchLbl->addListener (this);

    pitchLbl->setBounds (57, 192, 70, 24);

    resolutionLbl.reset (new juce::Label ("resolutionLbl",
                                          TRANS("20k")));
    addAndMakeVisible (resolutionLbl.get());
    resolutionLbl->setFont (juce::Font (12.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    resolutionLbl->setJustificationType (juce::Justification::centred);
    resolutionLbl->setEditable (true, true, false);
    resolutionLbl->setColour (juce::Label::textColourId, juce::Colour (0xffc3c3c3));
    resolutionLbl->setColour (juce::Label::outlineColourId, juce::Colour (0x00ffffff));
    resolutionLbl->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    resolutionLbl->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));
    resolutionLbl->setColour (juce::TextEditor::highlightColourId, juce::Colour (0x40ffffff));
    resolutionLbl->addListener (this);

    resolutionLbl->setBounds (173, 192, 70, 24);

    resolutionBtn.reset (new juce::ImageButton ("analyzeBtn"));
    addAndMakeVisible (resolutionBtn.get());
    resolutionBtn->setButtonText (TRANS("new button"));
    resolutionBtn->addListener (this);

    resolutionBtn->setImages (false, true, true,
                              juce::Image(), 1.000f, juce::Colour (0x00000000),
                              juce::Image(), 1.000f, juce::Colour (0x00000000),
                              juce::Image(), 1.000f, juce::Colour (0x00000000));
    resolutionBtn->setBounds (128, 155, 44, 32);

    ledBtn.reset (new juce::ImageButton ("ledBtn"));
    addAndMakeVisible (ledBtn.get());
    ledBtn->setButtonText (TRANS("new button"));
    ledBtn->addListener (this);

    ledBtn->setImages (false, true, true,
                       juce::ImageCache::getFromMemory (led_off_png, led_off_pngSize), 1.000f, juce::Colour (0x00000000),
                       juce::Image(), 1.000f, juce::Colour (0x00000000),
                       juce::ImageCache::getFromMemory (led_on_png, led_on_pngSize), 1.000f, juce::Colour (0x00000000));
    ledBtn->setBounds (240, 240, 24, 24);

    reverseBtn.reset (new juce::ImageButton ("reverseBtn"));
    addAndMakeVisible (reverseBtn.get());
    reverseBtn->setButtonText (TRANS("new button"));
    reverseBtn->addListener (this);

    reverseBtn->setImages (false, true, true,
                           juce::Image(), 1.000f, juce::Colour (0x00000000),
                           juce::Image(), 1.000f, juce::Colour (0x00000000),
                           juce::Image(), 1.000f, juce::Colour (0x00000000));
    reverseBtn->setBounds (23, 238, 88, 30);

    cachedImage_background2_png_1 = juce::ImageCache::getFromMemory (background2_png, background2_pngSize);

    //[UserPreSize]

    // remove the ugly purple border from label's text edit
    LookAndFeel& laf = LookAndFeel::getDefaultLookAndFeel();
    laf.setColour(TextEditor::focusedOutlineColourId, Colour (0x00ffffff));
    laf.setColour(TextEditor::outlineColourId, Colour (0x00ffffff));
    laf.setColour(TextEditor::highlightColourId, Colour (0x40ffffff));
    LookAndFeel::setDefaultLookAndFeel(&laf);

    // load images for the image buttons
	selectBtn->setImages (false, true, true,
                          ImageCache::getFromMemory (GraphicsResources::button_select_normal_png, GraphicsResources::button_select_normal_pngSize), 1.000f, Colour (0x00000000),
                          Image(), 1.000f, Colour (0x00000000),
                          ImageCache::getFromMemory (GraphicsResources::button_select_down_png, GraphicsResources::button_select_down_pngSize), 1.000f, Colour (0x00000000));
    analyzeBtn->setImages (false, true, true,
                          ImageCache::getFromMemory (GraphicsResources::button_analyze_normal_png, GraphicsResources::button_analyze_normal_pngSize), 1.000f, Colour (0x00000000),
                          Image(), 1.000f, Colour (0x00000000),
                          ImageCache::getFromMemory (GraphicsResources::button_analyze_down_png, GraphicsResources::button_analyze_down_pngSize), 1.000f, Colour (0x00000000));
    resolutionBtn->setImages (false, true, true,
                           ImageCache::getFromMemory (GraphicsResources::button_analyze_normal_png, GraphicsResources::button_analyze_normal_pngSize), 1.000f, Colour (0x00000000),
                           Image(), 1.000f, Colour (0x00000000),
                           ImageCache::getFromMemory (GraphicsResources::button_analyze_down_png, GraphicsResources::button_analyze_down_pngSize), 1.000f, Colour (0x00000000));

    reverseBtn->setImages (false, true, true,
                              ImageCache::getFromMemory (GraphicsResources::button_analyze_normal_png, GraphicsResources::button_analyze_normal_pngSize), 1.000f, Colour (0x00000000),
                              Image(), 1.000f, Colour (0x00000000),
                              ImageCache::getFromMemory (GraphicsResources::button_analyze_down_png, GraphicsResources::button_analyze_down_pngSize), 1.000f, Colour (0x00000000));
	reverseBtn->setClickingTogglesState(true);
    reverseBtn->setToggleState(parameters[kParameterReverse_name]->getValue(), juce::dontSendNotification);

    // register this as parameter observer
    parameters.get(kParameterSamplePitch_name)->addObserver(this);
    parameters.get(kParameterFrequencyResolution_name)->addObserver(this);
    parameters.get(kParameterReverse_name)->addObserver(this);

    // set last values
    onParameterUpdated(parameters.get(kParameterFrequencyResolution_name));
    onParameterUpdated(parameters.get(kParameterSamplePitch_name));
    onParameterUpdated(parameters.get(kParameterLastSamplePath_name));

    // set default LED state
    ledBtn->setClickingTogglesState(false);
    ParaphrasisAudioProcessor *processor = dynamic_cast<ParaphrasisAudioProcessor *>(getProcessor());
    if (processor)
        lightOn(processor->isReady());
    //[/UserPreSize]

    setSize (300, 300);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ParaphrasisAudioProcessorEditor::~ParaphrasisAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    // unregister observers
    parameters.get(kParameterSamplePitch_name)->removeObserver(this);
    parameters.get(kParameterFrequencyResolution_name)->removeObserver(this);
    parameters.get(kParameterReverse_name)->removeObserver(this);
    //[/Destructor_pre]

    knob = nullptr;
    knob2 = nullptr;
    sampleLbl = nullptr;
    selectBtn = nullptr;
    analyzeBtn = nullptr;
    pitchLbl = nullptr;
    resolutionLbl = nullptr;
    resolutionBtn = nullptr;
    ledBtn = nullptr;
    reverseBtn = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ParaphrasisAudioProcessorEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xffbdbdbd));

    {
        int x = 0, y = 0, width = 300, height = 300;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (juce::Colours::black);
        g.drawImage (cachedImage_background2_png_1,
                     x, y, width, height,
                     0, 0, cachedImage_background2_png_1.getWidth(), cachedImage_background2_png_1.getHeight());
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ParaphrasisAudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
	knob->setBounds (60, 129, 64, 64);
	knob2->setBounds (176, 129, 64, 64);
	sampleLbl->setBounds (24, 45, 176, 20);
	selectBtn->setBounds (194, 41, 88, 30);
	analyzeBtn->setBounds (105, 230, 92, 48);
	pitchLbl->setBounds (57, 192, 70, 24);
	resolutionLbl->setBounds (173, 192, 70, 24);
	resolutionBtn->setBounds (128, 155, 44, 32);
	ledBtn->setBounds (240, 240, 24, 24);
	reverseBtn->setBounds (23, 238, 88, 30);
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ParaphrasisAudioProcessorEditor::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == selectBtn.get())
    {
        //[UserButtonCode_selectBtn] -- add your button handler code here..
        // select sample file
        File lastFile;

        // load last location
        String filePath = parameters.get(kParameterLastSamplePath_name)->getDisplayText();
        if ( filePath.isEmpty() )
            lastFile = File::getSpecialLocation (File::userHomeDirectory);
        else
            lastFile = File(filePath);

        String formats = formatManager.getWildcardForAllFormats();
#ifdef ENABLE_SDIF_FILES
        formats += ";*.sdif";
#endif
        FileChooser myChooser ("Please select the sample file you want to load...", lastFile, formats);
        if (myChooser.browseForFileToOpen())
        {
            File sampleFile (myChooser.getResult());
            if ( sampleFile.exists() )
            {
                // set parameter
                sampleLbl->setText(sampleFile.getFileName(), juce::dontSendNotification);
                path = sampleFile.getFullPathName().toRawUTF8();
                parameters.setData(kParameterLastSamplePath_name, path.c_str(), path.length());

                // dectect pitch
                AudioFormatReader* reader = formatManager.createReaderFor(sampleFile);
                if (reader)
                {
                    detector.setSampleRate(reader->sampleRate);
                    AudioSampleBuffer buffer(reader->numChannels, reader->lengthInSamples);
                    reader->read(&buffer, 0, reader->lengthInSamples, 0, true, true);
                    double pitch = detector.detectPitch(buffer.getWritePointer(0), reader->lengthInSamples);

                    parameters.set(kParameterSamplePitch_name, pitch);
                    parameters.set(kParameterFrequencyResolution_name, kDefaultPitchResolutionRation * pitch);

                    delete reader;
                }

            }

        }
        //[/UserButtonCode_selectBtn]
    }
    else if (buttonThatWasClicked == analyzeBtn.get())
    {
        //[UserButtonCode_analyzeBtn] -- add your button handler code here..
        getProcessor()->analyzeSample();
        //[/UserButtonCode_analyzeBtn]
    }
    else if (buttonThatWasClicked == resolutionBtn.get())
    {
        //[UserButtonCode_resolutionBtn] -- add your button handler code here..
        // set default resolution freq defined by actual pitch frequency
        parameters.set(kParameterFrequencyResolution_name, kDefaultPitchResolutionRation * parameters.get(kParameterSamplePitch_name)->getValue());
        //[/UserButtonCode_resolutionBtn]
    }
    else if (buttonThatWasClicked == ledBtn.get())
    {
        //[UserButtonCode_ledBtn] -- add your button handler code here..
        //[/UserButtonCode_ledBtn]
    }
    else if (buttonThatWasClicked == reverseBtn.get())
    {
        //[UserButtonCode_reverseBtn] -- add your button handler code here..
        // change reverse name.
        parameters.set(kParameterReverse_name, reverseBtn->getToggleState());
        //[/UserButtonCode_reverseBtn]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void ParaphrasisAudioProcessorEditor::labelTextChanged (juce::Label* labelThatHasChanged)
{
    //[UserlabelTextChanged_Pre]
    //[/UserlabelTextChanged_Pre]

    if (labelThatHasChanged == pitchLbl.get())
    {
        //[UserLabelCode_pitchLbl] -- add your label text handling code here..
        if ( ! pitchLbl->isBeingEdited() )
        {
            float newValue = pitchLbl->getText().getFloatValue();
            teragon::Parameter* par = parameters.get(kParameterSamplePitch_name);
            parameters.set(kParameterSamplePitch_name, checkParameterBoundaries(par, newValue));
        }
        //[/UserLabelCode_pitchLbl]
    }
    else if (labelThatHasChanged == resolutionLbl.get())
    {
        //[UserLabelCode_resolutionLbl] -- add your label text handling code here..
        if ( ! resolutionLbl->isBeingEdited() )
        {
            float newValue = resolutionLbl->getText().getFloatValue();
            teragon::Parameter* par = parameters.get(kParameterFrequencyResolution_name);
            parameters.set(kParameterFrequencyResolution_name, checkParameterBoundaries(par, newValue));
        }
        //[/UserLabelCode_resolutionLbl]
    }

    //[UserlabelTextChanged_Post]
    //[/UserlabelTextChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ParaphrasisAudioProcessorEditor::onParameterUpdated(const Parameter *parameter)
{
    // update editor due to parameter changes
    if ( parameter->getName() == kParameterFrequencyResolution_name )
    {
        resolutionLbl->setText( String( parameter->getValue(), 2 ), juce::dontSendNotification );
    }
    else if ( parameter->getName() == kParameterSamplePitch_name )
    {
        pitchLbl->setText( String( parameter->getValue() , 2) , juce::dontSendNotification );
    }
    else if ( parameter->getName() == kParameterLastSamplePath_name )
    {
        File file( parameter->getDisplayText() );
        sampleLbl->setText( String( file.getFileName() ), juce::dontSendNotification );
    }
    else if (parameter->getName() == kParameterReverse_name )
    {
        reverseBtn->setToggleState(parameters[kParameterReverse_name]->getValue(), juce::dontSendNotification);
    }

    lightOn(false);// when any parameter changes - set light off
}

double ParaphrasisAudioProcessorEditor::checkParameterBoundaries(const Parameter *parameter, double value)
{
    if (value < parameter->getMinValue())
        value = parameter->getMinValue();
    else if (value > parameter->getMaxValue())
        value = parameter->getMaxValue();

    return value;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ParaphrasisAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public ParameterObserver"
                 constructorParams="ParaphrasisAudioProcessor* ownerFilter, teragon::ConcurrentParameterSet&amp; p, teragon::ResourceCache *r, AudioFormatManager &amp;formatManager"
                 variableInitialisers="AudioProcessorEditor(ownerFilter),&#10;    parameters(p),&#10;    resources(r),&#10;    formatManager(formatManager)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="300" initialHeight="300">
  <BACKGROUND backgroundColour="ffbdbdbd">
    <IMAGE pos="0 0 300 300" resource="background2_png" opacity="1.0" mode="0"/>
  </BACKGROUND>
  <GENERICCOMPONENT name="knob" id="52cfbedef63fe00b" memberName="knob" virtualName="teragon::ImageKnobLarge"
                    explicitFocusOrder="0" pos="60 129 64 64" class="Component" params="parameters, &quot;Sample Pitch&quot;, r"/>
  <GENERICCOMPONENT name="knob" id="675ee145463a99df" memberName="knob2" virtualName="teragon::ImageKnobLarge"
                    explicitFocusOrder="0" pos="176 129 64 64" class="Component"
                    params="parameters, &quot;Frequency Resolution&quot;, r"/>
  <LABEL name="sampleLbl" id="f5aa6f6cb476ff84" memberName="sampleLbl"
         virtualName="" explicitFocusOrder="0" pos="24 45 176 20" bkgCol="9f9d9d"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default monospaced font"
         fontsize="13.5" kerning="0.0" bold="0" italic="0" justification="33"/>
  <IMAGEBUTTON name="selectBtn" id="63e2e3bfd7cbefd5" memberName="selectBtn"
               virtualName="" explicitFocusOrder="0" pos="194 41 88 30" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1.0" colourNormal="0" resourceOver=""
               opacityOver="1.0" colourOver="0" resourceDown="" opacityDown="1.0"
               colourDown="0"/>
  <IMAGEBUTTON name="analyzeBtn" id="56836504f0a08694" memberName="analyzeBtn"
               virtualName="" explicitFocusOrder="0" pos="105 230 92 48" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1.0" colourNormal="0" resourceOver=""
               opacityOver="1.0" colourOver="0" resourceDown="" opacityDown="1.0"
               colourDown="0"/>
  <LABEL name="pitchLbl" id="400eaffd0e2f9582" memberName="pitchLbl" virtualName=""
         explicitFocusOrder="0" pos="57 192 70 24" textCol="f2c3c3c3"
         edTextCol="ff000000" edBkgCol="0" hiliteCol="40ffffff" labelText="20k"
         editableSingleClick="1" editableDoubleClick="1" focusDiscardsChanges="0"
         fontname="Default font" fontsize="12.0" kerning="0.0" bold="0"
         italic="0" justification="36"/>
  <LABEL name="resolutionLbl" id="c17f4e0142be49bf" memberName="resolutionLbl"
         virtualName="" explicitFocusOrder="0" pos="173 192 70 24" textCol="ffc3c3c3"
         outlineCol="ffffff" edTextCol="ff000000" edBkgCol="0" hiliteCol="40ffffff"
         labelText="20k" editableSingleClick="1" editableDoubleClick="1"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <IMAGEBUTTON name="analyzeBtn" id="5822ed37b120e159" memberName="resolutionBtn"
               virtualName="" explicitFocusOrder="0" pos="128 155 44 32" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1.0" colourNormal="0" resourceOver=""
               opacityOver="1.0" colourOver="0" resourceDown="" opacityDown="1.0"
               colourDown="0"/>
  <IMAGEBUTTON name="ledBtn" id="53d3b450ed60b4e0" memberName="ledBtn" virtualName=""
               explicitFocusOrder="0" pos="240 240 24 24" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="led_off_png" opacityNormal="1.0" colourNormal="0"
               resourceOver="" opacityOver="1.0" colourOver="0" resourceDown="led_on_png"
               opacityDown="1.0" colourDown="0"/>
  <IMAGEBUTTON name="reverseBtn" id="22e0e6c1d2a68619" memberName="reverseBtn"
               virtualName="" explicitFocusOrder="0" pos="23 238 88 30" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1.0" colourNormal="0" resourceOver=""
               opacityOver="1.0" colourOver="0" resourceDown="" opacityDown="1.0"
               colourDown="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: background2_png, 51421, "../Resources/Graphics/background2.png"
static const unsigned char resource_ParaphrasisAudioProcessorEditor_background2_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,1,44,0,0,1,44,8,6,0,0,0,121,125,142,117,0,0,0,4,115,66,73,84,
8,8,8,8,124,8,100,136,0,0,0,9,112,72,89,115,0,0,13,215,0,0,13,215,1,66,40,155,120,0,0,0,25,116,69,88,116,83,111,102,116,119,97,114,101,0,119,119,119,46,105,110,107,115,99,97,112,101,46,111,114,103,155,
238,60,26,0,0,32,0,73,68,65,84,120,156,188,189,91,140,38,201,117,38,246,69,254,151,170,191,254,170,234,170,234,174,234,238,233,235,76,207,141,164,68,114,200,229,146,180,46,148,137,21,13,241,65,134,1,95,
225,53,12,203,126,48,108,232,205,15,134,13,24,126,177,33,192,134,31,252,96,24,208,10,2,246,197,55,64,171,213,174,86,128,109,192,187,146,232,33,197,225,232,194,25,206,12,217,61,221,61,51,221,61,125,171,
234,234,174,235,95,255,159,225,135,204,19,121,226,196,57,145,249,247,80,142,153,234,204,63,46,39,78,68,198,249,226,59,145,145,153,238,247,127,255,247,61,234,224,156,139,143,133,131,131,11,191,225,28,28,
59,38,249,41,95,75,154,149,238,189,71,81,20,73,30,58,167,63,171,46,75,118,87,221,230,105,79,81,20,181,62,128,175,123,144,116,151,109,226,114,138,194,1,72,219,65,121,101,91,231,233,219,160,155,43,0,215,
228,117,112,209,239,174,114,194,185,247,128,210,126,25,228,117,0,16,218,196,207,229,145,206,233,119,89,150,122,126,212,121,188,72,115,8,241,85,28,66,126,0,240,66,94,78,151,159,87,158,92,90,89,242,60,165,
153,31,161,73,190,83,223,253,255,209,38,45,207,243,200,152,75,143,186,23,250,189,62,250,52,200,184,188,48,112,33,6,32,13,220,250,72,198,200,143,84,94,75,211,6,52,15,109,233,92,126,124,20,122,59,9,28,117,
107,196,49,105,239,115,30,123,189,24,100,61,124,108,216,190,123,61,93,64,164,77,111,223,140,244,232,183,188,14,214,53,146,215,179,106,67,21,87,150,37,156,115,152,205,102,201,53,103,157,93,87,60,159,161,
152,64,213,38,71,0,88,174,174,168,143,248,113,46,192,105,64,198,202,107,149,215,140,223,10,92,183,46,125,146,11,150,109,105,182,217,229,90,105,178,217,188,86,95,122,62,169,176,153,189,67,59,180,244,94,
175,135,190,156,41,101,3,186,204,240,93,66,50,176,141,116,171,140,5,124,241,140,79,105,179,36,79,167,54,185,154,157,100,218,168,201,152,205,102,225,220,57,74,211,217,81,81,20,193,232,179,186,212,71,45,
111,148,134,249,89,46,55,90,139,233,113,57,100,160,109,58,87,108,174,9,243,206,236,243,6,205,144,159,151,229,125,86,166,97,165,203,80,20,133,201,54,172,48,143,157,89,50,117,240,102,24,194,179,203,56,143,
134,221,6,121,241,177,1,39,163,47,91,88,46,159,252,52,125,129,170,31,250,124,182,232,202,140,218,192,67,158,211,111,203,248,249,121,155,188,172,97,74,70,104,212,175,49,3,139,221,180,129,93,163,135,71,
220,60,62,2,92,163,155,167,95,46,204,160,57,157,185,30,150,222,213,145,3,118,90,94,61,194,33,101,163,110,110,57,116,110,177,232,46,236,250,121,2,213,249,183,97,240,93,234,6,116,163,203,233,35,211,181,
188,161,47,235,37,153,54,6,204,227,74,95,79,112,245,56,243,222,195,249,28,163,38,6,212,210,94,54,49,242,114,77,155,237,178,217,201,160,165,95,100,255,244,155,34,18,76,244,74,35,74,237,171,98,212,152,210,
151,145,251,83,101,117,8,25,149,134,84,204,38,7,53,122,240,158,15,196,198,29,105,24,142,13,120,222,195,92,43,147,121,155,182,180,25,173,200,227,217,69,238,0,78,122,27,227,11,152,55,188,178,99,62,189,92,
212,135,224,253,154,55,62,190,110,167,77,74,243,177,44,26,248,62,154,169,187,200,225,110,48,13,254,182,124,81,104,230,157,72,78,174,237,242,40,89,66,215,160,129,16,233,226,157,143,221,87,133,193,200,50,
85,115,92,154,214,162,127,23,249,159,133,153,118,206,195,38,3,199,210,202,178,68,159,27,26,117,30,53,153,255,86,243,48,176,10,157,164,0,70,226,138,200,78,244,121,115,214,25,159,79,226,202,178,12,148,91,
99,35,81,149,240,209,69,37,32,35,57,57,198,240,243,10,146,53,37,58,10,58,156,150,111,3,103,40,71,229,154,184,216,21,38,99,239,210,244,46,238,141,28,168,26,152,240,243,231,55,6,201,122,144,28,169,189,66,
193,200,253,161,131,222,231,182,235,34,1,59,2,3,3,64,219,234,104,234,114,112,174,98,66,106,219,61,162,73,145,226,248,13,151,38,17,65,14,31,231,148,151,110,10,56,199,251,81,182,185,153,204,158,7,164,245,
80,203,100,23,204,139,118,246,101,35,228,49,103,252,212,200,48,248,11,189,243,101,57,237,110,154,42,59,195,108,232,156,95,116,146,43,229,91,117,105,238,94,91,125,154,60,29,80,219,153,94,91,208,6,63,15,
101,233,195,160,74,251,142,152,29,191,51,233,131,209,38,147,136,33,135,183,145,79,56,60,206,234,35,233,178,132,115,145,78,235,27,112,174,25,164,101,9,192,129,238,162,181,129,89,12,34,177,145,53,122,211,
68,199,61,8,7,184,102,38,15,68,203,115,182,167,215,209,48,66,214,30,195,118,231,5,63,121,3,66,211,163,19,160,195,195,151,153,116,1,166,20,167,129,102,140,1,246,100,106,50,198,76,30,58,22,69,79,232,143,
0,96,189,94,175,2,172,160,72,237,186,4,23,198,235,149,36,198,89,231,35,95,153,55,162,171,209,90,134,156,3,19,171,30,185,46,215,198,248,186,230,9,125,192,126,23,134,177,230,3,185,203,177,142,114,38,179,
218,72,215,139,182,86,128,244,175,203,71,237,226,186,22,69,168,35,223,23,218,93,214,52,104,147,89,202,184,226,252,22,8,72,3,210,210,72,158,115,141,44,9,104,150,204,112,172,251,196,71,192,168,215,213,38,
143,247,13,35,66,77,90,189,134,36,200,91,48,194,178,65,214,136,33,86,114,63,59,179,231,215,197,2,8,7,135,18,101,84,159,133,7,193,35,225,24,145,212,25,131,236,243,233,172,131,101,81,244,170,69,119,57,115,
74,150,224,203,18,80,6,166,204,59,175,98,124,134,110,99,114,243,132,121,192,39,119,148,250,82,154,171,34,170,248,185,52,11,210,80,150,172,127,69,31,74,61,184,155,43,117,226,121,120,144,224,65,64,222,214,
151,85,153,198,29,148,12,74,6,109,252,196,178,100,155,98,16,147,193,98,104,84,48,6,122,192,251,34,232,145,232,32,209,132,49,58,186,142,158,245,155,13,122,196,40,170,99,220,183,49,219,208,128,23,154,141,
56,135,2,0,234,155,37,77,57,189,79,114,128,170,133,96,87,214,154,93,200,8,20,190,136,228,135,250,234,166,185,162,154,12,3,64,241,46,73,234,109,206,115,170,202,246,164,140,82,203,51,107,246,97,81,35,213,
163,178,64,61,15,131,210,242,52,6,150,203,67,174,204,243,215,51,15,40,201,144,3,77,203,72,121,92,27,45,150,101,184,43,107,93,56,75,239,198,184,1,154,161,52,215,152,126,219,253,81,1,86,51,73,122,128,95,
127,150,43,167,135,12,124,107,68,23,22,147,164,9,215,101,30,247,72,171,67,7,36,153,167,106,233,92,46,152,209,14,70,166,196,145,250,123,126,3,182,244,177,0,78,43,103,217,131,44,167,93,151,28,217,240,136,
239,78,194,123,120,54,91,121,102,63,222,123,244,122,189,42,143,81,191,115,14,69,81,112,192,74,55,86,18,80,208,58,21,137,235,4,20,180,0,207,22,253,66,190,150,197,121,222,25,90,30,201,194,52,166,86,53,161,
131,171,215,81,23,171,77,86,25,83,134,194,158,0,125,240,200,99,12,88,237,64,174,5,94,158,31,189,167,52,199,116,75,235,135,81,79,151,9,128,238,64,73,32,208,100,88,224,44,25,169,101,188,1,130,124,237,122,
73,57,149,176,22,102,83,229,212,128,142,234,207,109,34,141,127,243,27,25,250,93,208,54,208,235,26,52,89,154,92,202,199,39,59,202,206,207,115,245,116,145,43,55,231,242,217,174,41,195,1,58,94,214,161,60,
245,198,209,230,238,88,165,168,48,0,215,40,16,205,216,194,192,114,179,184,220,140,25,206,93,58,0,231,97,71,185,50,30,8,212,159,199,75,215,137,252,113,233,46,153,198,200,193,176,163,158,185,52,205,109,
226,191,61,244,117,178,170,223,186,213,197,219,220,12,132,178,181,28,185,173,150,172,46,64,29,197,213,40,34,129,0,176,103,113,85,142,17,52,195,179,92,23,90,63,178,24,77,27,83,203,179,29,250,75,117,37,
166,69,125,144,182,173,42,71,134,27,235,145,3,233,24,120,57,163,147,186,55,117,105,161,251,226,62,253,113,18,33,55,25,215,34,101,13,74,189,185,49,84,245,139,115,14,125,254,92,147,22,248,182,133,100,64,
177,223,114,71,118,52,11,138,59,80,21,224,25,236,171,5,52,230,1,52,210,217,185,248,145,18,107,77,232,121,235,202,165,105,108,112,222,242,52,144,179,19,11,244,231,20,227,201,164,49,162,46,109,156,71,79,
89,78,254,214,92,66,58,111,51,34,94,134,135,28,67,147,6,204,203,116,98,46,206,37,112,147,43,167,179,154,28,3,17,140,149,220,33,118,140,203,84,242,172,35,207,91,217,180,205,178,200,30,186,180,43,215,126,
115,98,250,57,4,194,6,14,198,0,208,151,254,172,117,228,10,231,216,130,85,214,44,31,40,168,216,102,192,141,6,141,169,241,121,75,139,139,91,237,2,59,145,235,67,154,113,133,56,1,162,109,109,254,44,161,75,
121,122,132,166,234,150,186,126,1,60,149,172,42,183,236,243,152,193,166,245,91,131,76,119,109,50,236,179,173,29,138,225,0,80,141,71,206,220,50,77,147,167,29,187,176,63,160,114,55,114,178,53,99,149,158,
129,197,188,172,177,18,229,165,242,64,96,240,113,221,85,10,177,71,231,104,91,11,168,68,208,161,215,75,221,88,57,73,88,125,155,235,75,83,119,35,207,103,9,252,102,1,215,185,175,230,118,136,247,87,137,1,
154,155,89,173,217,253,121,101,116,205,67,23,179,11,67,107,101,6,104,6,203,103,1,38,186,187,26,71,134,74,234,159,93,30,251,81,244,15,19,115,90,190,203,76,104,5,155,157,117,235,91,21,0,131,155,66,35,48,
214,145,235,61,175,1,88,192,34,13,150,206,185,161,90,121,120,94,192,102,44,93,140,220,202,99,177,70,45,175,4,76,11,248,172,250,163,53,87,89,182,62,90,108,73,35,33,185,240,115,1,46,5,96,73,182,126,151,
80,231,43,145,82,90,35,180,184,240,187,108,242,240,125,31,28,112,168,251,52,176,251,172,128,102,201,226,33,199,186,114,229,77,131,85,203,23,2,88,229,205,14,110,192,116,222,109,51,42,18,214,149,103,79,
50,205,98,18,109,231,250,239,70,31,100,12,46,1,28,35,61,23,103,77,60,90,123,52,131,210,12,145,131,104,212,150,191,133,48,47,187,153,91,190,184,193,193,251,248,179,128,111,14,140,187,183,161,25,223,1,43,
208,172,219,114,121,69,81,84,46,161,6,64,93,1,137,226,249,57,253,73,57,92,129,84,78,60,248,180,129,102,201,85,103,245,76,176,58,80,202,209,216,11,239,188,182,60,70,237,225,209,135,112,81,178,229,227,190,
213,6,70,147,110,212,200,175,21,95,147,172,105,55,173,49,106,58,88,125,155,235,171,234,119,85,3,13,64,212,64,205,18,213,115,135,188,97,204,19,114,96,109,229,237,106,200,57,48,204,177,162,231,97,96,129,
37,1,201,29,183,80,158,171,226,145,198,41,237,13,215,204,3,174,80,236,92,108,28,141,202,195,85,227,198,35,217,92,42,119,19,68,237,243,109,224,88,183,82,201,51,155,205,42,151,176,141,177,228,152,11,103,
6,156,45,208,239,248,152,198,117,97,12,154,187,87,181,4,81,71,182,1,99,14,124,35,217,190,170,58,7,60,185,77,152,93,13,44,208,241,78,185,43,185,69,213,17,0,242,235,114,218,36,66,149,21,172,207,171,166,
54,131,205,21,153,107,14,133,233,106,202,115,12,34,150,167,176,39,217,54,25,248,157,187,28,80,119,1,21,141,69,69,101,234,36,211,187,16,209,214,228,157,2,137,7,156,190,200,221,21,20,163,113,11,109,220,
250,90,63,23,198,110,176,141,14,67,49,76,92,53,88,164,119,76,73,100,35,47,148,49,142,148,39,215,214,212,213,102,26,41,229,156,115,241,78,119,158,0,216,96,146,116,22,91,6,167,215,156,0,14,69,65,249,192,
202,199,71,25,164,27,38,25,141,212,75,211,87,230,137,12,86,105,87,99,184,200,230,1,0,87,20,241,118,6,199,134,120,109,152,86,131,93,70,71,94,62,71,171,61,43,111,189,167,202,108,35,51,94,153,63,128,95,230,
241,42,121,206,203,241,208,6,228,93,216,155,166,187,6,14,17,19,105,44,37,164,75,0,224,242,163,58,153,101,19,235,144,178,114,158,133,213,134,10,12,107,240,169,34,226,115,202,207,1,77,145,17,152,167,218,
95,148,183,157,141,230,189,145,202,10,232,6,4,215,33,105,147,162,3,105,206,193,218,231,142,104,38,203,192,190,184,12,65,72,122,189,94,179,134,37,129,65,115,205,164,241,91,179,184,102,108,109,46,27,31,
16,218,128,77,140,147,189,190,89,101,79,68,79,51,128,198,211,138,162,168,46,87,200,91,117,167,162,104,60,105,121,31,158,4,112,117,193,182,126,145,109,139,219,213,0,64,161,228,241,162,60,77,75,92,119,77,
46,181,81,198,201,252,161,30,5,24,228,57,160,51,77,121,253,100,92,27,179,176,130,6,58,86,156,86,87,156,151,218,162,51,158,28,51,176,116,110,27,231,14,213,245,85,101,179,187,148,146,89,201,109,56,124,35,
172,166,87,85,206,38,5,113,27,244,235,96,181,207,202,35,211,219,174,173,60,15,101,106,197,173,50,173,46,33,159,253,99,134,32,143,205,5,59,158,76,112,120,112,128,201,100,146,92,64,77,182,150,199,154,213,
187,176,41,43,111,23,32,1,244,231,242,68,68,42,55,195,76,109,134,82,49,212,182,126,104,235,11,210,201,137,120,45,175,198,136,130,42,0,224,187,49,182,200,101,238,224,118,80,224,239,76,171,24,67,92,190,
11,136,181,26,128,204,219,194,174,178,178,230,52,86,181,140,112,205,98,195,38,247,139,165,177,107,193,203,204,3,168,9,251,148,249,196,196,219,5,144,165,46,164,102,41,242,13,6,3,44,45,45,97,56,28,70,122,
200,137,144,7,142,43,180,140,32,39,128,240,104,78,22,168,96,27,160,150,231,248,248,24,79,158,60,49,103,113,203,56,101,135,240,50,185,89,87,94,148,156,27,209,6,124,244,59,247,90,226,168,94,118,236,42,159,
91,104,142,253,241,115,121,61,172,120,77,30,229,153,183,15,114,245,216,0,172,135,224,6,180,0,143,100,22,90,94,173,92,46,254,121,202,181,165,107,12,116,158,122,187,48,151,46,241,207,163,127,23,189,57,155,
230,113,242,119,105,200,59,58,58,194,225,225,33,214,215,215,177,176,176,48,23,83,51,111,42,160,126,129,159,166,160,166,120,219,238,112,10,135,135,135,102,154,85,94,2,148,12,93,140,66,2,85,45,185,153,185,
208,220,105,209,22,86,171,242,116,1,28,43,83,4,102,25,13,4,105,228,72,7,74,174,142,28,16,180,177,79,153,135,126,135,215,205,40,229,228,187,194,114,178,225,28,123,28,200,201,166,38,229,120,223,90,65,50,
32,47,215,78,121,30,133,65,72,96,214,142,124,188,90,160,162,157,7,64,165,56,177,64,206,153,36,173,183,208,227,102,161,46,214,7,141,209,81,203,244,190,161,241,32,117,178,66,197,106,92,18,167,182,205,35,
188,46,89,99,100,90,95,88,50,1,132,239,22,116,237,83,0,216,219,219,195,96,48,48,211,137,77,230,218,68,121,168,15,59,189,173,65,107,144,53,107,31,31,31,171,121,181,134,201,122,43,165,132,143,32,202,228,
116,74,3,51,252,204,93,73,53,191,107,214,200,140,10,85,157,218,250,80,2,85,14,144,194,145,203,87,234,108,84,210,39,28,30,248,215,110,114,76,169,204,164,105,140,79,203,107,25,161,201,160,21,166,236,89,
188,166,183,21,114,70,170,61,176,204,235,151,33,232,200,134,102,0,37,126,151,26,186,1,135,66,154,218,21,77,175,250,52,176,12,230,21,106,224,44,212,76,174,93,89,2,14,232,161,122,3,2,200,11,176,152,141,
197,24,75,31,20,225,219,120,210,246,33,236,179,228,119,6,167,211,105,253,22,6,193,242,92,227,82,146,20,137,39,225,206,181,136,215,119,186,51,197,117,198,211,94,70,3,51,158,174,191,71,201,215,253,107,239,
247,226,241,90,122,78,143,231,101,111,60,36,111,75,101,91,1,164,60,141,245,217,64,197,229,10,224,137,51,170,122,105,64,166,209,120,138,215,250,195,2,48,107,221,203,4,46,186,38,26,168,66,7,86,115,98,19,
192,195,95,95,45,219,72,65,123,53,11,253,214,216,131,101,132,188,12,215,213,10,210,35,145,253,223,184,61,77,254,152,73,184,232,122,231,39,247,72,201,164,95,67,146,114,78,121,93,13,100,190,6,56,206,206,
248,29,215,102,219,67,119,166,70,229,179,219,57,82,110,146,148,151,99,37,185,75,40,103,118,199,226,224,92,61,24,243,179,175,140,239,66,119,121,121,203,112,114,238,144,85,255,188,128,212,22,212,11,51,179,
245,224,33,7,102,206,181,191,45,194,2,104,231,28,102,100,192,116,36,118,232,98,67,146,6,155,211,153,250,185,203,139,255,114,224,71,65,246,93,120,100,196,167,3,179,201,35,116,164,153,222,208,163,204,48,
122,106,143,230,74,230,140,177,43,171,215,216,144,233,10,117,72,143,243,52,27,142,41,158,95,87,41,47,145,235,17,231,133,143,88,17,125,139,36,74,111,209,77,182,93,35,17,109,237,175,234,66,194,254,226,99,
195,182,163,69,247,182,119,161,119,49,168,102,102,137,39,88,62,139,202,250,228,204,53,15,51,249,219,8,57,151,39,178,20,103,27,234,60,224,37,215,149,114,160,219,21,8,73,63,0,81,191,207,3,232,109,245,90,
44,154,215,41,243,242,115,50,26,107,128,91,229,114,242,121,30,109,118,215,0,75,230,181,218,105,129,65,23,112,206,165,107,242,83,230,216,172,37,18,131,235,82,79,88,35,34,6,69,172,134,112,192,161,218,123,
231,56,235,170,0,206,57,199,232,32,234,184,234,135,212,153,127,111,81,179,219,22,21,3,187,12,113,53,55,226,178,10,39,92,66,185,253,94,134,138,174,198,168,46,59,86,187,240,212,72,174,4,192,214,83,248,173,
125,204,179,190,67,122,53,0,152,187,128,154,251,32,65,148,183,77,211,129,239,230,200,129,135,149,102,129,97,27,56,117,97,145,93,1,46,202,11,229,177,11,165,76,23,150,165,149,213,140,92,187,174,217,93,217,
181,209,117,1,35,30,167,185,178,165,111,62,62,203,3,207,219,198,38,180,58,172,73,87,43,67,71,11,180,52,134,103,49,42,206,26,181,244,74,64,12,130,114,109,136,79,108,213,79,229,206,124,248,217,141,73,91,
164,163,209,163,122,29,146,116,223,155,252,132,172,177,220,104,167,123,151,143,72,228,192,164,43,11,179,26,106,165,183,13,4,186,99,163,5,109,182,74,126,203,124,13,178,70,241,214,192,224,237,214,6,185,
53,144,180,139,170,133,28,208,106,114,178,119,2,155,132,74,14,59,231,178,181,242,22,155,72,202,210,172,14,68,64,20,151,245,233,53,64,243,84,68,176,165,122,146,183,220,157,184,81,25,157,120,86,215,200,
231,250,196,121,227,118,91,76,47,247,42,99,235,188,137,75,221,188,250,164,6,22,155,25,106,227,65,139,183,235,214,226,82,144,168,213,233,84,62,0,34,139,47,203,50,177,65,58,82,219,219,216,38,29,139,162,
200,47,186,67,85,63,53,112,174,140,54,19,167,131,188,221,8,230,137,39,134,160,177,179,220,69,12,249,130,60,186,61,141,200,175,214,52,175,216,102,170,87,232,96,133,73,181,1,19,207,231,16,219,97,92,86,3,
175,102,0,52,79,5,0,128,0,47,210,73,76,2,82,215,152,157,196,238,72,23,166,197,203,240,56,169,183,108,67,10,28,85,40,189,111,238,162,9,227,36,70,80,122,251,165,116,150,33,80,141,225,103,73,106,218,227,
38,114,177,62,83,208,250,168,246,214,234,49,32,191,0,197,203,114,29,57,211,2,108,48,201,7,171,205,250,243,155,57,210,33,211,37,216,230,174,135,252,205,243,152,139,238,90,156,69,247,249,239,104,32,101,
100,1,213,109,207,157,157,29,245,245,196,27,245,166,179,202,93,0,160,24,21,239,28,174,131,164,161,33,175,82,54,42,87,63,238,211,165,253,18,28,125,227,224,127,166,16,128,95,92,240,88,135,6,140,155,60,241,
224,183,6,147,101,0,1,224,235,243,89,89,38,128,137,204,239,78,193,55,147,75,110,64,243,56,215,20,77,242,70,249,44,119,72,147,105,177,78,0,228,100,56,39,83,152,44,165,159,157,115,88,94,94,86,95,4,120,124,
124,140,131,131,3,150,55,214,165,97,147,113,27,134,195,33,134,195,33,158,62,125,26,245,2,35,98,0,28,251,157,247,6,232,29,253,149,141,198,253,50,30,143,49,153,76,48,153,28,71,242,234,17,33,236,169,97,100,
150,189,209,177,122,158,56,29,175,22,99,214,128,140,123,14,253,116,214,75,63,62,160,161,179,99,61,207,243,209,204,192,1,70,27,220,187,187,187,248,209,143,126,20,63,35,232,201,45,112,120,227,141,55,176,
185,184,24,213,145,115,19,179,179,7,211,73,198,211,81,62,183,39,219,149,214,43,182,51,84,139,90,21,51,42,10,192,0,156,84,110,51,0,186,184,205,173,108,177,195,121,44,191,26,144,154,17,135,201,194,208,165,
13,180,170,186,72,111,91,127,95,89,15,21,74,6,191,28,208,185,129,158,24,42,4,32,197,214,158,158,215,63,155,175,31,43,186,138,223,206,57,124,225,11,95,64,191,223,143,242,208,241,193,131,7,216,223,223,87,
101,228,218,178,178,178,130,51,103,206,96,119,119,55,11,192,93,100,17,72,89,121,95,120,225,5,108,111,111,227,225,195,135,34,29,74,200,51,101,126,44,75,219,149,207,178,94,229,58,151,101,137,126,89,210,
70,194,90,21,231,48,155,233,198,19,13,10,7,20,202,12,4,52,131,132,22,56,181,89,237,222,189,123,232,245,122,248,198,55,190,129,241,120,220,58,131,155,244,92,128,149,102,168,133,5,104,194,45,104,3,62,233,
150,209,55,241,42,87,171,142,3,0,246,188,156,166,163,80,34,207,10,21,240,178,216,137,117,167,43,228,117,76,158,178,120,106,129,92,78,151,121,152,150,188,78,90,191,240,93,230,109,235,67,213,239,38,158,
171,226,137,240,50,195,75,229,232,215,132,62,204,194,243,54,140,33,190,59,231,156,195,202,202,10,250,253,62,110,221,186,133,39,79,158,36,186,18,59,32,35,228,64,220,101,156,219,121,236,181,181,231,1,9,
43,158,215,87,107,164,234,39,219,227,156,51,219,77,233,154,237,74,123,160,242,201,179,132,65,72,117,66,17,42,204,106,119,90,164,194,218,215,114,40,204,102,51,12,135,67,44,46,46,166,236,141,41,59,155,205,
112,255,254,125,60,126,252,56,12,224,94,175,135,245,141,13,156,63,127,30,253,126,31,55,63,252,16,195,225,16,151,46,93,138,58,227,111,254,230,111,112,225,194,5,156,62,125,26,39,39,39,184,115,231,78,152,
173,70,163,17,62,247,185,207,97,50,153,224,206,157,59,209,243,143,206,185,144,14,0,159,126,250,41,30,62,124,136,233,116,26,12,237,212,169,83,184,112,225,2,70,163,81,53,136,189,52,228,238,198,44,89,143,
54,0,44,64,79,25,83,19,114,223,37,148,231,146,137,4,86,170,232,154,236,238,22,46,141,12,22,171,42,235,87,72,59,145,143,231,15,160,165,220,69,76,93,12,41,199,150,107,197,63,15,0,144,14,7,7,7,201,164,161,
1,196,96,48,192,218,218,26,150,150,150,162,190,216,223,219,195,246,206,78,237,165,136,255,234,87,53,45,44,44,96,109,109,45,122,228,101,54,155,97,119,119,23,123,123,123,17,176,174,174,174,98,52,26,69,186,
120,239,113,231,206,157,160,207,185,115,231,208,239,247,209,239,247,131,78,79,158,60,97,110,168,13,114,249,137,196,55,215,88,148,33,29,219,190,84,84,77,254,77,90,89,150,250,162,187,19,25,181,217,95,155,
29,120,165,18,33,101,222,211,167,79,227,238,221,187,248,225,15,127,136,197,197,197,96,120,253,126,31,103,207,158,197,214,214,22,0,224,254,253,251,120,247,221,119,177,186,186,138,241,120,12,160,122,184,
242,189,159,252,4,240,30,87,174,92,193,246,246,14,150,150,70,137,129,62,124,248,16,103,206,156,65,175,215,195,251,239,191,143,91,183,110,225,204,230,25,12,7,195,128,254,31,126,248,33,110,222,188,137,173,
173,45,44,44,44,4,253,122,189,30,138,162,192,246,246,54,222,126,251,109,44,45,45,97,125,125,61,180,231,131,15,62,192,193,193,1,190,244,165,47,69,117,82,168,62,16,144,174,23,197,253,18,86,120,217,250,66,
102,15,152,82,143,54,171,201,16,174,33,124,96,188,164,67,180,184,238,244,186,83,119,209,197,0,103,168,155,99,171,33,205,251,8,135,228,56,211,182,27,80,200,237,157,210,228,229,244,201,233,235,133,142,50,
255,179,103,207,224,189,199,43,175,188,130,253,253,253,104,220,63,123,246,44,154,108,1,96,107,107,11,155,155,155,120,246,236,25,166,211,41,128,106,189,106,253,210,37,28,79,38,1,44,124,253,223,172,156,
5,153,23,47,94,196,104,52,194,147,39,79,66,220,210,210,18,214,214,214,240,222,123,239,5,121,167,78,157,194,249,243,231,177,191,191,143,227,227,227,24,12,232,230,140,47,195,88,224,0,211,198,194,168,63,
121,191,74,246,212,235,245,224,189,15,71,217,103,148,198,159,92,136,113,166,249,34,54,31,171,125,46,44,231,138,88,235,9,50,104,108,137,226,185,98,91,91,91,248,197,95,252,69,236,236,236,68,101,182,183,
183,113,239,222,61,252,234,175,254,42,22,23,23,241,248,241,99,172,172,172,224,27,223,248,70,52,120,223,122,235,45,60,126,252,24,87,175,94,77,214,25,52,70,177,189,189,141,203,151,47,227,75,95,250,82,148,
190,179,179,131,139,23,47,226,43,95,249,74,124,17,80,217,225,246,246,54,70,163,17,190,250,213,175,98,54,155,5,212,47,138,2,187,187,187,17,72,90,76,71,242,151,38,61,112,11,70,98,249,245,136,251,181,185,
160,46,42,163,129,161,212,35,184,96,136,247,157,105,131,77,246,93,23,55,69,187,35,158,99,92,93,216,167,47,203,32,178,19,248,101,242,37,179,119,135,50,60,52,87,42,13,39,39,39,184,126,253,58,78,157,58,21,
185,140,11,11,11,184,116,233,18,202,178,196,163,71,143,66,254,149,149,21,60,121,242,4,15,31,62,140,250,247,242,229,203,24,141,70,17,187,225,161,215,235,97,52,26,225,238,221,187,225,37,3,100,248,151,47,
95,198,112,56,196,100,50,1,80,129,216,193,193,1,174,95,191,158,97,135,192,157,59,119,0,0,175,189,246,90,208,137,242,106,203,14,178,223,154,37,6,132,101,21,26,238,52,206,76,194,3,23,237,157,164,56,245,
153,76,239,209,235,247,105,209,157,132,168,253,4,253,50,229,131,53,32,249,204,121,238,220,57,156,63,127,62,138,63,60,60,196,159,253,217,159,97,103,103,7,231,206,157,67,89,150,129,249,240,5,250,133,133,
5,28,29,29,137,217,161,234,64,218,144,58,155,205,80,150,37,102,179,25,166,211,41,134,195,97,120,234,156,234,155,78,167,88,92,92,76,226,233,120,114,114,130,193,96,128,71,143,30,225,189,247,222,139,218,
181,186,186,106,190,245,51,5,175,120,166,143,211,149,69,239,162,121,75,132,213,175,196,202,164,219,174,1,103,142,57,105,117,104,235,13,50,120,31,239,249,242,176,243,230,100,89,32,11,246,118,87,13,96,164,
142,26,248,106,19,166,22,47,239,96,90,122,90,109,219,219,219,195,222,222,94,12,10,30,120,245,181,87,49,30,143,35,192,114,206,225,224,224,0,47,188,240,2,150,150,150,178,76,134,7,110,35,47,189,244,82,210,
118,202,67,231,4,94,22,233,160,97,99,93,143,164,207,57,128,213,199,106,187,9,48,83,182,148,56,184,86,198,166,166,41,215,194,123,143,190,247,232,19,237,226,141,213,40,26,239,52,43,15,143,203,237,140,230,
233,114,112,12,6,195,170,35,102,13,93,133,87,6,139,111,252,218,114,54,171,0,199,251,122,59,64,156,158,206,44,241,239,217,108,150,29,140,211,233,20,87,174,92,193,197,139,23,163,139,159,51,60,222,166,250,
7,169,173,122,80,201,80,245,62,233,27,186,251,24,149,33,189,93,186,230,36,13,216,50,192,210,251,176,183,14,72,159,24,200,185,83,218,151,126,219,250,91,11,185,250,186,178,161,46,110,31,192,22,206,225,195,
102,105,26,103,181,160,120,191,157,139,215,92,100,188,6,112,222,215,238,156,152,8,169,28,45,71,240,64,227,181,97,208,205,6,82,89,207,187,239,190,155,244,11,141,227,182,137,33,199,54,101,136,242,26,15,
149,151,70,121,254,60,226,92,160,149,128,21,170,107,227,129,126,161,184,50,193,37,210,102,222,234,36,217,186,64,233,252,125,208,178,44,63,238,239,239,99,127,127,63,169,227,238,221,187,112,206,97,101,117,
5,69,81,96,113,113,17,31,125,244,81,160,220,206,57,156,156,156,96,123,103,27,27,27,27,40,138,2,167,214,214,112,251,246,109,172,173,173,97,113,113,49,170,147,191,35,42,106,71,61,187,172,172,172,224,222,
189,123,24,143,199,24,14,135,12,56,7,216,220,220,196,234,234,42,110,220,184,129,247,222,123,15,155,155,155,116,37,224,225,113,106,245,20,22,23,170,250,248,91,27,228,57,109,70,141,216,17,237,206,39,146,
4,133,153,49,207,81,155,37,9,168,154,54,165,140,42,138,19,116,59,164,49,160,210,242,118,113,225,186,0,69,154,183,130,111,13,224,44,144,106,3,51,190,56,223,5,244,184,177,248,38,82,93,87,179,128,120,48,
24,132,245,85,30,63,26,141,176,188,188,156,184,120,135,135,71,216,218,218,194,201,201,20,211,233,73,40,227,224,240,244,217,211,112,151,146,250,188,199,38,144,233,116,138,139,23,47,226,211,79,63,141,117,
247,62,90,162,56,62,62,198,153,51,103,176,185,185,137,233,116,26,229,125,186,251,180,105,75,17,3,161,246,140,162,217,95,10,171,211,38,73,30,151,76,42,30,225,134,130,115,46,188,210,38,30,115,53,187,115,
64,31,108,208,243,35,57,138,205,164,35,242,176,6,180,185,127,218,249,167,159,126,138,143,62,250,40,233,136,193,96,128,75,151,46,97,117,117,21,206,57,92,186,116,9,79,159,62,197,237,219,183,195,12,71,119,
64,174,94,189,10,160,90,136,124,246,236,25,62,248,224,3,115,118,225,254,116,19,7,188,244,210,75,248,201,79,126,130,119,222,121,39,202,191,188,188,140,95,251,181,95,195,230,230,38,182,182,182,112,251,246,
109,220,188,121,51,202,243,218,107,175,225,181,215,94,211,93,43,101,107,8,215,99,134,153,170,99,238,72,109,15,249,235,29,215,114,166,215,234,212,234,160,107,71,113,242,217,59,235,145,167,54,151,175,45,
174,169,91,151,175,177,23,203,64,18,217,12,104,185,12,203,16,53,150,212,198,68,100,222,209,104,132,23,95,124,81,205,255,236,217,51,60,121,242,36,234,219,237,237,199,24,12,250,184,120,241,66,34,243,167,
63,253,105,88,234,144,125,232,189,199,167,159,126,138,205,205,205,232,142,56,80,121,9,124,33,126,103,103,7,163,209,8,231,206,157,139,218,84,150,37,222,121,210,140,117,95,166,58,231,174,163,5,222,86,232,
194,176,200,27,170,78,243,64,233,126,239,247,126,207,119,49,20,233,10,89,51,250,131,7,15,162,56,9,32,243,214,37,131,149,102,150,17,174,82,23,67,214,211,105,192,233,91,13,186,232,111,1,67,91,60,245,163,
156,169,180,188,243,164,37,249,192,88,157,146,78,113,109,108,203,170,27,176,221,230,54,22,147,4,15,243,81,28,213,56,132,107,213,198,212,72,183,54,208,234,162,123,99,140,77,247,118,97,48,90,92,27,224,230,
222,63,69,12,100,158,58,212,118,180,76,76,188,189,231,206,157,107,250,190,181,255,168,148,94,87,175,215,67,63,44,220,34,54,154,136,142,49,119,133,15,88,141,93,209,102,209,234,98,55,183,237,165,114,121,
86,144,186,10,218,192,215,12,39,97,88,222,71,172,176,43,171,73,211,67,76,118,15,26,253,89,204,66,139,107,117,183,74,38,187,72,251,69,130,153,212,137,180,14,71,215,148,173,50,50,125,232,6,76,180,161,149,
242,55,174,75,219,2,59,215,161,107,186,5,14,207,19,146,235,80,41,159,176,74,77,159,164,31,185,110,181,156,156,13,68,128,87,69,132,99,217,100,138,65,130,215,207,229,80,27,12,67,143,246,50,213,147,179,9,
160,226,97,227,46,147,67,60,214,154,79,248,161,235,250,20,173,101,203,52,223,176,169,78,114,188,167,109,13,164,12,212,204,213,197,104,191,245,29,206,163,89,90,185,213,79,131,197,96,94,84,142,58,223,57,
23,148,107,140,15,106,217,185,216,83,179,120,164,182,37,172,61,25,178,37,227,164,190,225,108,105,62,6,167,231,173,6,98,190,126,77,134,246,91,134,160,175,99,192,71,219,30,162,109,24,113,57,98,54,206,197,
31,8,125,110,240,170,103,254,112,142,122,48,115,113,52,192,105,188,183,24,155,101,148,185,73,46,171,115,98,252,101,12,100,74,189,77,146,182,169,149,237,33,243,76,62,7,175,138,70,38,58,70,155,104,163,99,
252,134,135,121,216,210,124,108,50,255,32,190,252,109,2,18,144,244,171,22,184,204,100,227,168,197,92,120,154,204,147,52,136,161,103,206,104,185,44,237,1,104,173,156,86,191,245,145,85,237,216,166,83,104,
163,114,33,82,23,170,190,32,18,96,120,126,146,199,116,151,178,186,128,142,204,163,177,79,30,159,3,47,141,97,164,174,70,51,150,170,57,195,90,207,226,178,109,192,178,198,21,177,182,250,46,142,170,79,19,
217,46,187,19,248,176,223,109,76,206,100,79,245,150,139,28,43,177,192,162,2,249,244,99,165,109,229,210,107,148,62,190,162,181,85,59,151,64,226,234,254,247,4,124,225,253,197,186,235,220,181,46,243,85,209,
108,146,210,202,135,93,4,168,222,55,18,24,22,221,213,139,93,31,157,49,200,160,61,250,161,173,195,200,181,145,170,134,122,102,23,174,40,223,161,215,176,50,136,25,191,46,19,49,166,160,124,235,76,175,5,57,
0,72,142,6,12,148,95,144,130,36,95,52,240,188,143,64,185,113,199,124,120,51,3,111,3,188,111,220,1,196,215,34,55,161,80,186,212,65,26,181,6,90,242,119,81,228,211,245,214,235,33,175,179,139,192,200,123,
31,185,166,188,38,141,213,64,137,235,10,2,161,5,202,53,107,59,207,78,218,201,185,55,31,4,158,7,124,120,160,45,19,86,62,173,15,164,238,13,64,104,250,84,122,231,88,83,151,122,57,11,15,46,172,225,158,230,
142,206,177,79,213,75,37,115,126,57,175,92,50,30,105,148,149,97,55,3,48,116,20,210,93,173,117,66,18,162,124,158,203,160,116,164,126,75,75,232,226,234,181,229,205,165,75,189,105,171,67,146,167,200,127,
70,76,190,122,182,45,36,119,250,140,55,98,82,28,111,131,6,218,220,115,142,101,164,109,206,49,21,45,104,245,52,108,139,50,177,115,231,18,120,164,153,55,146,71,24,24,38,2,7,239,116,224,82,89,113,128,70,
57,113,231,21,132,21,229,0,0,32,0,73,68,65,84,217,113,156,87,130,82,236,33,80,122,155,161,202,160,3,158,85,142,187,162,241,99,76,205,218,23,162,249,34,240,133,142,122,205,115,205,181,49,40,131,54,209,
210,49,60,154,35,7,170,28,188,133,50,152,157,194,184,232,130,100,141,185,102,75,93,65,160,235,239,182,206,208,58,218,98,80,109,175,90,238,18,18,183,210,80,77,99,78,188,175,194,250,149,215,250,167,225,
213,9,208,112,249,53,45,119,96,117,192,69,175,199,169,242,74,23,79,63,239,50,240,82,69,248,105,170,103,112,13,133,238,82,72,46,206,186,100,94,45,103,213,209,40,219,144,93,154,116,120,106,92,182,203,67,
207,50,104,99,152,198,30,121,62,214,102,85,169,175,36,14,196,92,169,95,157,139,65,189,201,175,179,111,174,163,218,71,190,219,94,181,182,231,61,45,198,169,29,195,135,84,121,144,96,229,156,67,122,175,15,
241,232,96,110,140,54,107,71,51,163,215,7,44,87,86,187,40,210,176,155,249,47,109,60,85,228,156,206,78,36,106,107,117,37,109,48,130,156,49,219,228,201,178,185,116,234,43,27,28,210,114,218,90,96,216,161,
12,54,203,195,71,123,197,26,93,237,201,65,14,118,158,38,207,147,54,41,128,20,235,221,238,206,200,208,54,169,84,206,130,189,240,12,196,91,35,164,91,42,25,157,181,163,27,208,251,200,212,203,51,239,130,218,
199,116,245,200,183,91,107,71,23,38,164,169,164,141,239,78,44,170,66,58,3,40,21,249,117,126,173,126,94,79,219,53,13,111,28,237,178,112,109,185,21,228,46,104,51,15,80,1,75,41,46,164,247,244,222,33,123,
230,203,185,48,68,7,180,129,209,176,15,187,61,118,57,253,188,43,227,178,102,82,57,9,104,229,114,175,131,225,76,88,211,63,199,78,121,156,54,160,52,93,120,126,237,241,155,174,161,75,191,53,121,156,98,84,
108,146,242,30,220,121,225,121,227,122,92,0,5,56,199,202,160,62,39,153,128,243,233,54,20,105,244,186,139,151,122,37,86,89,158,55,244,45,169,69,118,71,70,13,36,110,89,91,221,50,112,29,120,157,190,110,179,
47,245,231,95,43,54,238,0,131,20,89,109,14,117,81,167,34,94,66,8,184,80,183,211,2,215,92,127,83,8,119,9,249,160,148,198,101,205,166,26,125,148,71,109,177,156,223,166,143,210,181,188,150,220,22,183,69,
230,231,198,110,181,33,55,8,114,96,99,229,151,191,19,151,207,200,155,147,103,77,30,26,173,183,250,130,231,179,88,161,165,159,115,78,35,118,157,202,202,16,250,154,185,94,241,156,36,199,29,55,68,97,85,222,
222,72,42,127,91,105,105,30,9,118,121,16,225,231,57,0,236,42,79,62,30,149,150,139,245,179,218,17,250,47,244,119,134,49,139,109,73,222,167,107,210,22,227,38,38,197,227,157,115,232,133,56,135,18,101,141,
11,141,58,161,141,165,143,220,119,114,143,73,126,47,247,122,25,43,144,0,235,11,188,222,199,244,147,111,111,8,141,245,141,28,45,221,65,7,7,237,226,106,58,228,232,185,86,78,182,45,202,235,116,42,107,149,
161,80,150,101,2,4,214,76,210,38,51,199,202,40,228,210,181,182,242,56,205,141,180,38,129,54,221,67,62,118,179,65,77,247,62,76,92,60,143,197,0,219,0,193,123,95,125,154,93,228,149,236,48,103,112,186,158,
172,69,28,20,201,216,90,216,130,85,71,23,64,211,55,86,54,235,82,26,88,233,109,208,117,2,210,53,38,235,165,122,54,168,231,219,192,191,154,83,210,235,130,90,0,221,74,155,149,37,250,69,81,93,100,254,30,119,
201,58,40,104,76,135,142,116,222,235,21,145,28,45,127,78,110,206,16,114,3,43,14,116,97,155,25,200,205,81,158,116,224,119,159,56,218,231,218,32,207,131,70,6,0,115,157,44,96,210,242,208,95,118,134,54,216,
152,16,94,245,77,11,203,210,218,67,186,169,98,115,64,213,33,94,3,73,237,119,4,8,2,36,229,120,50,129,33,99,192,188,140,247,30,5,236,135,131,37,144,230,244,85,207,125,189,126,197,183,1,180,76,220,90,187,
76,208,204,48,54,77,255,110,182,38,67,195,134,171,226,52,6,105,114,66,88,75,165,58,18,50,227,210,231,70,93,45,169,143,208,0,170,70,248,159,10,123,225,199,74,145,138,137,20,53,138,22,69,17,187,152,108,
91,67,91,80,23,141,131,114,49,165,149,93,20,98,61,255,97,63,74,196,169,172,198,104,170,142,170,25,128,79,13,128,100,240,99,151,115,107,66,176,228,229,228,200,55,114,230,202,171,128,70,70,34,246,244,0,
233,251,203,53,253,172,180,48,108,201,104,40,79,149,33,164,181,25,121,44,63,38,187,149,24,214,78,95,255,83,199,123,95,194,251,118,38,144,51,84,158,214,6,70,90,217,220,185,9,60,134,236,182,160,77,180,20,
130,61,66,247,66,248,68,168,177,194,212,238,233,206,163,76,167,250,128,194,197,166,42,155,67,46,32,191,17,151,101,89,16,159,170,239,106,68,57,35,165,206,178,62,230,153,99,108,188,92,100,124,52,99,178,
207,20,69,58,186,10,127,61,228,32,142,143,84,164,11,107,108,50,136,163,17,104,6,73,227,99,38,98,25,104,220,22,132,89,133,202,250,170,130,38,77,1,12,158,166,213,171,233,150,3,70,237,183,156,44,120,8,119,
209,106,182,96,213,161,233,226,148,248,240,219,53,107,30,177,17,230,0,36,127,119,176,105,78,234,89,120,223,148,143,251,175,97,236,60,15,151,79,175,4,214,24,174,117,77,52,80,168,218,215,190,165,65,202,
214,202,229,206,219,216,154,21,154,54,164,178,171,244,116,66,74,142,4,205,77,183,134,194,124,194,227,215,168,175,237,190,214,88,8,63,106,111,217,164,63,45,173,13,177,131,222,132,222,98,95,9,95,148,147,
250,241,14,105,6,91,115,46,227,248,38,66,173,141,90,188,188,32,118,219,226,116,162,122,22,179,163,192,239,14,122,254,41,117,9,80,202,32,10,187,228,35,160,142,40,102,162,55,15,185,39,24,172,32,245,15,241,
113,38,51,175,6,121,89,3,241,213,211,0,109,12,167,107,186,85,23,31,191,148,47,46,111,124,197,135,137,171,38,22,187,41,154,30,57,125,40,93,155,120,158,135,129,69,160,201,152,13,111,75,18,87,135,182,189,
102,218,121,23,29,155,60,53,114,41,32,71,231,245,27,71,121,163,168,131,138,200,48,249,209,122,13,202,124,129,237,194,69,58,3,165,136,29,131,148,42,81,1,67,9,22,109,238,169,5,92,9,43,115,16,119,84,236,
175,4,133,223,142,245,37,20,153,236,156,67,78,248,205,102,30,109,198,214,234,228,237,213,250,98,86,206,146,247,94,205,102,179,120,214,11,234,107,245,80,93,28,44,211,60,161,78,233,22,40,19,129,166,171,
150,30,226,156,144,229,145,244,205,243,26,189,124,210,32,233,195,12,72,90,140,202,218,38,34,245,202,213,151,59,118,97,216,4,172,133,139,63,195,101,217,135,247,62,217,80,221,166,151,115,213,50,81,69,70,
217,214,138,122,45,77,182,175,97,177,105,32,185,125,39,140,108,158,7,137,115,134,146,51,70,10,242,131,173,209,57,25,130,96,45,86,221,109,241,185,119,77,181,201,139,47,190,48,36,175,51,62,94,94,174,231,
117,209,89,3,163,54,38,172,201,34,37,115,102,89,122,229,117,214,188,93,108,98,145,117,248,0,14,10,139,18,72,37,117,104,115,75,44,99,147,249,172,60,109,238,144,166,199,243,184,72,1,136,56,59,78,234,226,
114,218,239,24,230,244,146,160,52,143,206,154,44,171,92,27,19,180,64,50,170,43,180,190,153,1,147,245,42,52,44,213,100,239,206,53,143,230,240,1,200,93,68,137,242,22,122,75,227,126,62,198,37,2,103,125,72,
13,49,212,227,125,108,24,136,25,145,60,151,249,100,124,155,219,196,223,90,96,151,39,144,180,229,202,62,147,125,220,164,75,160,109,49,158,186,246,104,230,234,208,70,189,29,58,104,60,215,245,117,54,175,
37,121,252,141,178,109,193,98,76,60,189,237,92,202,225,186,200,252,205,236,175,201,170,226,11,244,204,235,227,153,65,230,218,161,157,83,185,152,233,1,201,228,169,180,161,97,157,236,97,125,146,229,125,
179,46,92,122,56,177,239,41,199,72,53,230,167,129,77,115,119,189,153,220,18,44,241,72,234,177,66,63,55,248,200,112,180,142,11,3,26,169,210,188,114,173,17,93,141,160,161,169,104,118,231,50,58,25,202,66,
14,172,88,166,212,223,2,88,139,141,81,144,91,27,52,22,196,65,138,190,226,195,90,84,227,171,14,254,93,192,21,0,122,69,47,102,59,12,180,187,128,145,21,180,182,145,43,240,115,153,132,20,157,100,61,57,157,
184,94,86,255,116,249,40,134,86,135,204,167,179,137,204,66,126,61,233,248,112,109,67,180,42,115,30,118,164,145,128,234,167,197,230,186,181,203,135,127,16,217,88,87,70,101,231,141,235,139,243,232,236,73,
218,67,225,200,206,99,55,180,47,51,114,133,52,99,150,21,132,181,28,209,168,220,0,183,228,230,66,148,191,5,136,115,110,173,5,158,82,63,45,93,187,96,178,239,170,107,238,147,53,40,46,175,13,84,181,50,252,
188,100,207,78,228,242,85,154,216,122,104,65,155,217,57,8,228,175,87,251,12,41,131,197,202,57,235,228,113,154,238,185,182,112,32,108,155,108,44,25,64,51,81,194,251,236,51,133,22,72,180,130,135,172,199,
72,231,178,114,100,64,115,79,165,158,218,184,212,108,159,231,79,240,130,38,204,72,182,89,45,164,59,108,233,22,92,73,118,163,195,57,167,127,249,89,107,144,54,168,18,85,156,139,244,207,185,24,93,229,90,
84,147,203,211,12,169,250,221,204,116,100,186,90,155,44,80,206,157,91,70,211,48,207,156,49,56,113,174,0,152,150,59,151,38,130,156,73,53,154,223,5,180,44,215,160,145,109,223,196,176,6,102,44,59,175,191,
38,67,62,70,150,148,97,107,34,109,0,209,45,173,172,235,237,86,70,3,23,249,187,139,46,109,241,93,219,96,145,18,43,77,75,183,235,211,153,149,12,26,35,180,243,54,139,255,92,143,250,157,238,237,139,236,217,
52,202,18,116,173,64,75,3,38,169,84,46,93,230,137,58,182,182,113,106,152,236,167,42,190,210,197,251,198,109,10,42,231,234,22,125,154,188,179,75,185,38,210,181,137,0,212,41,101,92,170,179,28,56,4,50,60,
141,205,4,186,238,36,131,157,7,89,62,222,146,194,117,151,178,52,215,108,30,151,48,55,142,128,150,253,69,213,5,83,245,162,80,185,221,202,108,95,215,21,189,135,204,0,232,28,32,166,245,82,59,82,121,154,17,
71,237,225,54,84,231,149,155,163,165,46,93,24,142,212,93,234,163,233,169,165,119,9,22,171,75,219,158,182,133,174,117,153,121,159,124,50,246,217,196,195,227,202,178,180,25,22,21,168,79,90,27,206,41,37,
87,130,231,145,157,208,181,211,146,65,229,133,110,240,137,30,188,94,201,48,120,186,100,103,97,147,170,216,65,45,215,175,114,110,73,108,128,105,31,1,64,209,227,160,96,61,168,220,164,243,223,26,157,151,
231,181,221,71,237,204,1,146,214,38,169,51,111,19,83,221,190,142,204,222,213,190,99,212,223,50,132,174,204,190,141,9,242,52,205,104,229,184,232,50,129,106,33,153,152,69,157,109,249,41,78,182,197,210,41,
23,186,144,4,43,206,106,171,6,164,57,6,71,239,245,202,177,195,174,12,179,215,235,85,27,71,169,49,9,40,41,27,53,219,194,60,64,164,41,73,33,48,10,167,187,123,21,195,116,145,187,228,120,217,76,60,213,164,
129,171,22,36,51,209,102,64,171,77,26,3,208,207,161,158,167,105,237,110,43,16,191,186,71,26,204,108,166,127,19,49,26,68,236,132,152,133,106,48,243,217,208,115,135,238,238,79,165,84,206,32,242,229,249,
190,68,219,133,235,198,204,230,179,135,92,62,141,229,132,35,219,15,72,163,93,110,85,145,99,54,247,98,189,46,160,2,31,175,229,89,159,23,147,95,94,79,100,123,132,9,141,226,173,117,60,231,140,53,44,15,209,
209,252,216,1,229,85,186,236,92,152,109,212,153,156,118,123,35,111,148,13,93,140,189,45,2,176,144,166,33,0,205,240,45,117,240,163,70,177,173,246,74,29,165,60,139,161,89,231,222,251,228,6,66,27,176,74,
29,121,254,121,152,21,15,52,120,194,142,252,142,107,17,93,24,65,23,32,210,242,84,42,107,140,48,141,215,216,130,229,146,197,125,168,151,155,7,0,173,118,180,157,127,86,25,133,79,159,39,148,237,224,237,209,
24,82,214,253,101,68,32,174,35,101,82,18,224,19,182,85,102,210,132,254,42,96,185,220,81,161,206,186,187,197,165,121,250,95,205,219,208,80,212,27,204,88,243,141,186,168,115,210,129,167,13,214,42,62,6,75,
57,43,199,65,230,45,203,88,143,182,96,13,0,173,172,246,42,154,70,247,84,47,126,174,61,232,154,228,119,77,61,154,124,173,108,12,248,162,110,62,83,40,58,101,131,215,55,177,230,244,215,251,172,27,227,202,
165,107,238,80,174,12,93,63,139,105,242,190,182,12,78,147,223,6,82,93,242,180,29,233,188,45,93,202,238,10,148,93,108,66,134,198,50,217,154,163,92,51,22,65,121,248,153,46,166,189,51,92,190,25,83,174,143,
228,214,119,100,57,45,143,197,194,100,136,129,221,215,40,169,205,22,136,226,171,35,215,167,209,65,103,39,241,219,45,219,244,183,242,229,250,33,219,23,244,104,141,178,81,144,83,235,18,101,245,152,141,19,
125,24,178,116,187,243,75,203,1,185,129,67,110,136,212,187,147,155,172,232,111,129,179,181,150,162,253,230,241,188,95,0,68,207,143,230,12,49,55,201,180,149,17,56,30,79,200,20,87,69,196,114,248,184,11,
227,88,111,175,131,161,71,93,214,27,229,120,208,214,160,52,157,121,222,152,140,232,164,37,210,147,197,91,215,176,43,96,211,177,215,235,197,31,161,104,214,179,10,0,51,85,89,250,109,25,45,111,72,22,168,
136,82,250,186,156,88,56,151,65,147,149,203,223,230,254,228,216,5,5,201,0,101,27,115,6,223,22,44,227,158,199,101,172,134,105,181,185,142,246,195,181,129,168,140,231,236,54,98,167,174,155,235,231,125,243,
138,16,89,174,107,63,144,28,25,172,87,231,0,233,157,182,180,61,236,142,50,16,221,34,151,117,122,15,120,175,223,185,211,152,178,117,46,1,37,212,67,108,208,33,0,146,53,118,52,192,9,117,121,186,226,0,239,
114,62,30,77,198,228,145,172,11,81,255,228,38,38,121,23,190,43,184,168,231,81,93,237,19,91,104,19,60,124,89,127,53,71,127,115,168,252,244,151,125,55,129,167,81,135,73,3,167,80,157,59,56,215,220,126,79,
101,84,221,148,51,216,102,50,74,245,202,25,169,198,100,114,160,167,235,111,159,207,43,63,11,78,204,208,232,183,115,46,12,30,19,152,8,48,68,117,161,174,236,64,105,118,226,107,161,29,128,26,0,32,89,77,217,
68,90,157,183,253,14,154,182,64,204,25,148,101,112,109,174,139,118,174,141,243,156,219,211,102,192,149,138,117,30,229,214,62,141,127,158,223,90,16,207,213,79,129,219,98,99,43,181,209,87,9,162,109,136,
64,214,170,167,45,88,248,16,71,210,95,204,222,53,166,21,217,134,71,248,68,94,191,223,111,150,177,44,35,212,46,166,230,107,70,6,138,152,30,55,242,226,6,233,29,101,111,114,12,231,190,17,22,40,183,115,17,
221,118,202,30,51,141,166,74,125,52,6,34,243,114,185,17,72,215,6,148,99,151,17,11,101,157,18,247,47,35,45,202,53,176,128,80,107,27,119,211,185,238,214,3,225,109,3,54,215,31,86,72,179,228,141,143,64,55,
63,89,2,112,204,101,110,49,58,222,55,114,76,201,47,20,183,201,147,32,35,199,129,118,205,76,121,162,222,30,155,248,121,93,252,109,9,89,54,21,107,218,232,80,219,132,102,207,109,147,134,108,183,213,38,57,
206,229,123,217,249,209,65,124,219,180,40,224,3,115,174,44,128,216,36,77,216,125,237,97,103,121,46,3,197,23,198,131,192,28,180,52,16,172,100,23,1,188,178,76,67,169,183,254,17,235,217,8,107,58,146,93,24,
62,107,201,78,108,171,179,109,134,141,244,46,108,22,100,129,142,26,2,152,213,63,51,238,158,100,88,50,78,51,46,32,254,114,240,60,76,243,121,102,224,185,131,211,217,131,156,112,114,204,166,137,68,232,23,
90,155,139,175,71,243,230,76,62,85,228,220,158,78,245,178,234,145,97,106,252,25,190,144,162,0,146,86,191,247,62,162,175,109,87,70,190,179,93,182,65,3,160,92,63,240,163,102,43,124,140,89,229,218,210,128,
234,186,149,174,222,214,160,129,147,28,16,26,66,122,31,95,124,73,111,165,145,198,10,206,204,153,72,27,152,82,175,6,52,27,176,226,121,181,79,102,169,231,222,48,86,167,199,39,250,40,235,53,225,206,93,139,
107,75,229,147,122,181,69,118,167,179,167,54,144,207,165,89,76,83,11,218,172,220,86,103,155,220,156,145,243,253,59,57,240,125,158,186,108,166,131,104,173,43,203,176,16,27,151,156,156,121,32,8,180,64,86,
206,55,222,167,249,219,136,4,135,91,254,187,145,159,218,22,5,235,129,113,181,30,131,185,242,243,56,79,205,148,124,115,222,232,80,4,247,48,197,23,62,137,52,178,251,82,89,9,34,214,109,115,14,40,124,119,
248,96,48,192,116,58,85,25,151,213,97,178,126,171,28,63,146,140,178,102,82,218,76,208,137,145,8,189,180,186,114,250,88,249,115,191,163,129,129,198,165,1,16,223,226,77,64,62,5,64,173,205,106,61,153,1,152,
128,162,2,194,201,35,80,6,78,69,15,194,179,2,106,159,7,218,19,203,244,201,91,46,26,38,65,156,158,88,139,246,22,76,231,92,204,84,42,5,218,84,111,234,233,18,8,85,170,253,12,9,128,193,55,95,216,225,111,24,
209,217,161,212,136,237,191,243,128,119,0,61,207,168,129,158,201,74,106,253,194,184,102,122,240,178,180,27,93,147,21,185,108,14,240,190,97,160,0,17,148,166,108,83,23,208,31,12,88,94,77,95,227,13,174,70,
90,89,150,232,147,178,93,216,132,181,137,145,231,27,143,199,120,250,244,105,80,154,245,92,60,149,180,4,11,32,77,132,103,117,68,122,113,154,173,180,171,43,48,106,105,214,172,215,118,110,181,77,158,91,119,
194,52,217,82,158,166,123,252,27,224,134,210,6,102,218,66,126,170,143,20,208,241,122,19,80,153,108,188,110,15,125,38,202,8,145,219,203,148,114,50,79,13,104,178,223,245,186,117,249,22,72,112,5,228,68,4,
216,159,209,10,231,245,207,210,151,209,36,161,214,77,233,162,255,228,245,247,245,164,206,221,199,32,79,48,214,0,47,62,5,58,46,211,236,131,160,27,48,26,141,178,108,53,102,168,108,124,101,38,141,62,34,228,
171,187,193,107,3,188,65,86,142,168,146,202,45,46,46,194,123,143,131,131,131,234,17,16,106,60,16,206,185,226,154,17,91,0,34,243,72,16,227,192,149,48,145,154,201,56,71,223,71,107,152,77,196,48,164,139,
38,116,136,242,209,187,175,82,6,108,130,153,42,15,48,251,33,176,5,5,132,178,95,24,170,131,6,244,213,26,94,165,120,194,72,160,227,82,14,56,181,144,14,234,170,62,58,39,113,60,94,11,17,75,208,192,135,74,
43,6,1,232,160,159,115,15,165,135,161,49,111,173,125,252,92,243,34,184,241,215,39,85,92,97,219,65,212,70,229,250,107,105,218,49,215,238,92,153,202,110,235,5,127,240,87,244,84,221,109,201,235,247,251,88,
28,45,98,105,180,68,70,15,32,126,175,149,6,198,86,219,232,60,188,113,148,168,157,197,96,40,52,187,189,229,162,53,201,168,242,45,46,46,98,52,26,169,31,164,224,71,58,215,88,76,46,127,151,163,140,243,74,
156,155,163,62,53,253,57,101,104,32,102,229,213,0,59,199,130,219,210,204,137,65,178,45,69,61,201,70,45,253,45,227,179,244,224,65,139,151,113,22,48,243,48,207,226,242,60,95,153,177,206,231,73,151,58,116,
97,33,93,234,210,218,54,175,204,46,249,121,255,91,128,29,116,9,91,57,116,247,175,249,29,111,131,209,228,207,102,51,244,227,217,206,179,193,218,12,188,174,175,160,145,239,104,231,183,211,187,2,146,76,179,
226,115,32,32,63,28,0,212,139,243,138,236,46,250,217,237,109,95,216,159,7,204,104,151,186,42,167,166,204,159,5,172,248,158,165,46,224,35,101,229,38,179,92,185,46,105,124,22,229,191,53,112,207,25,13,253,
230,125,41,141,132,234,224,175,100,142,13,199,54,120,250,217,213,208,181,53,96,147,205,24,96,51,79,156,197,190,172,56,114,125,158,23,204,120,80,217,96,81,45,172,115,27,229,182,217,228,5,138,34,95,127,
81,20,205,43,146,115,179,173,28,52,109,134,215,54,179,102,1,131,92,173,186,35,41,208,0,140,88,7,243,123,201,168,163,29,243,98,221,37,138,111,26,155,232,175,125,253,166,58,103,232,46,218,148,235,15,217,
39,218,192,114,206,97,230,103,173,253,172,213,99,213,159,43,39,203,90,121,186,166,181,133,121,199,138,246,165,109,30,180,54,183,49,15,121,46,191,2,83,167,2,136,159,85,204,49,48,114,109,114,204,70,202,
105,55,94,27,200,120,123,187,200,211,198,7,175,71,91,132,159,39,228,38,150,58,33,201,151,212,227,171,127,188,111,1,71,239,155,135,159,173,10,121,102,180,0,14,117,236,7,31,124,128,233,116,26,229,161,124,
151,46,93,194,250,250,122,136,83,101,249,52,142,246,234,118,5,78,203,120,53,70,195,117,159,193,225,207,38,67,92,27,76,113,165,152,134,29,182,114,153,133,100,230,140,74,171,95,139,139,62,179,197,102,59,
174,215,255,240,127,252,19,92,186,240,2,254,205,95,250,59,137,172,132,1,187,6,148,121,255,241,181,53,173,172,212,79,246,151,150,174,197,121,239,67,127,105,187,208,163,199,100,164,239,89,103,207,238,110,
103,129,191,46,154,242,36,131,190,102,150,182,59,98,179,72,77,15,235,5,132,109,76,228,179,166,147,158,188,127,187,6,117,114,162,9,221,199,249,100,187,34,240,67,115,221,188,242,33,91,45,228,64,176,59,203,
4,102,174,164,53,44,158,216,60,58,67,44,167,82,20,114,104,169,225,228,228,4,127,252,199,127,140,253,253,125,53,221,57,135,175,125,237,107,248,205,223,252,205,231,158,177,155,193,142,152,241,120,246,164,
82,139,27,225,156,11,239,189,166,193,236,189,199,246,193,49,126,103,122,30,127,191,191,141,127,119,60,9,139,141,109,172,38,74,47,92,3,186,14,65,6,207,23,109,216,117,233,5,165,58,202,178,196,201,201,9,
254,252,127,251,135,56,245,198,55,241,175,127,243,43,102,189,161,157,236,174,142,214,119,114,70,181,38,42,109,144,243,116,174,107,146,55,52,63,5,2,15,31,13,38,210,153,131,117,130,99,222,235,113,202,239,
164,61,14,201,86,9,126,211,37,24,138,216,186,161,177,31,85,190,162,75,84,189,50,177,241,220,14,250,117,176,226,128,106,140,209,43,100,172,27,11,182,125,85,40,21,238,252,41,99,197,43,253,64,90,87,253,21,
231,139,243,203,99,187,155,153,99,96,190,246,108,156,171,55,142,202,245,17,126,148,40,107,173,103,121,239,49,155,205,176,183,183,135,217,108,134,139,23,47,226,139,95,252,98,132,216,211,233,20,223,255,
254,247,241,87,127,245,87,248,141,223,248,13,44,46,46,198,134,78,235,102,154,27,167,24,89,195,30,226,11,20,177,6,231,106,31,58,221,89,223,228,115,128,243,56,58,60,194,147,39,187,192,114,5,188,57,22,24,
201,161,47,123,56,145,142,234,162,105,251,145,156,139,223,122,97,185,118,222,123,236,239,239,227,239,255,231,255,21,206,111,172,133,118,90,15,6,75,125,187,24,130,6,190,213,169,222,247,212,173,205,133,
234,250,152,72,19,130,204,186,207,136,117,181,49,58,203,5,145,0,107,49,19,15,175,190,127,169,110,134,26,82,151,144,116,73,191,18,173,49,53,126,3,128,179,230,144,222,226,6,113,213,34,119,46,83,46,119,204,
129,67,146,151,197,57,163,140,37,135,119,104,23,29,181,224,133,87,16,127,170,222,183,63,99,103,249,205,196,6,38,147,9,0,96,56,28,226,236,217,179,209,162,227,209,209,17,62,247,185,207,225,7,63,248,1,238,
220,185,131,43,87,174,224,193,131,7,120,244,232,81,236,170,21,5,46,95,190,140,149,149,149,40,126,119,119,23,119,238,220,9,191,95,126,229,21,44,44,44,224,222,189,123,216,217,222,142,244,46,138,2,87,175,
94,197,242,242,50,156,115,216,47,61,254,234,100,24,177,50,146,253,106,127,138,51,197,12,165,47,113,116,116,8,44,3,31,205,250,248,211,67,135,126,175,31,92,172,171,253,41,46,246,227,246,31,160,135,31,79,
6,152,214,160,255,114,111,138,23,250,37,30,150,5,222,159,14,195,69,115,174,128,3,240,98,127,138,75,125,122,207,117,9,192,225,41,28,126,50,29,224,132,200,5,27,244,175,21,37,22,139,2,179,139,47,195,143,
250,161,220,73,89,226,39,179,5,60,241,233,62,186,141,158,199,151,135,211,208,15,209,245,172,185,178,163,54,48,166,193,229,200,243,92,92,197,202,89,191,202,100,139,165,213,105,242,109,174,236,71,195,154,
197,128,231,128,41,217,143,5,102,26,163,109,115,207,226,102,200,187,139,113,94,57,233,112,79,64,2,78,174,158,168,188,54,145,213,2,249,56,145,128,25,201,169,175,113,96,223,42,48,234,125,16,218,172,76,24,
116,204,77,20,50,228,193,73,75,139,111,116,244,171,185,173,113,255,200,223,207,185,9,50,104,131,124,56,28,162,223,239,227,240,240,48,52,232,233,211,167,120,231,157,119,208,235,245,176,186,186,138,233,
116,138,31,254,240,135,248,193,15,126,144,200,44,138,2,223,250,214,183,240,157,239,124,7,101,89,226,15,254,224,15,240,246,219,111,71,121,126,251,183,127,27,231,206,157,195,247,223,124,19,127,241,23,127,
145,232,228,156,195,119,190,243,29,124,251,219,223,198,173,131,18,255,237,244,28,115,33,217,12,15,135,239,14,159,225,183,220,97,232,180,55,251,167,241,230,132,183,181,2,164,191,91,28,224,191,57,181,139,
178,44,241,71,251,67,252,207,211,77,76,105,13,202,57,252,167,195,71,248,87,23,142,241,195,195,1,254,187,217,6,43,219,200,250,102,255,0,191,179,250,4,179,217,12,255,203,254,34,254,65,121,182,26,47,78,214,
231,240,95,14,239,227,151,138,2,255,112,120,5,111,224,16,127,183,220,193,167,147,18,255,254,209,101,28,160,23,234,229,109,122,163,56,192,255,116,234,49,122,189,158,1,64,62,98,165,114,125,103,30,208,138,
210,59,48,171,72,78,173,187,124,239,183,168,140,166,217,168,78,13,164,180,16,27,96,195,138,36,248,88,134,40,227,114,233,109,245,83,83,0,31,53,139,178,240,243,44,96,250,20,36,219,218,35,227,249,163,79,
109,224,156,99,96,185,35,63,215,174,145,36,61,188,63,181,137,167,186,75,88,52,133,185,160,220,185,60,242,14,227,74,189,245,214,91,248,203,191,252,203,68,201,215,95,127,29,253,126,31,199,199,199,120,245,
213,87,113,230,204,25,204,102,37,8,230,203,178,196,219,111,191,141,31,252,224,7,248,149,95,249,21,236,237,237,225,175,255,250,175,49,30,143,241,205,111,126,19,163,209,8,75,75,75,24,143,199,56,60,60,196,
235,175,191,142,115,231,206,177,7,45,29,166,211,19,188,245,214,91,120,243,205,55,241,181,175,125,13,219,187,71,192,234,37,252,43,15,223,193,75,135,219,1,175,142,139,1,254,159,179,95,192,255,141,21,252,
91,197,52,220,29,250,198,163,15,240,149,131,123,213,214,12,0,222,21,120,115,227,101,252,197,248,5,220,60,120,140,51,179,67,252,147,227,23,224,122,37,254,237,79,127,132,179,211,3,140,199,75,120,125,115,
29,199,0,174,108,127,138,255,108,255,6,166,211,89,227,18,22,5,254,197,153,207,225,251,75,231,241,201,225,99,156,154,30,224,143,39,103,112,10,135,248,247,238,253,0,75,126,86,107,15,184,162,192,210,210,
18,94,222,88,197,211,195,61,148,163,18,211,242,4,7,7,7,248,167,7,75,56,88,40,240,175,61,252,43,188,190,127,191,126,43,69,213,160,133,197,5,92,56,189,142,147,147,229,196,109,236,50,225,116,137,183,242,
201,236,124,124,114,99,36,125,172,144,48,10,165,76,60,184,181,60,41,152,88,160,44,219,34,61,7,153,110,2,100,32,43,250,243,180,13,24,53,69,228,215,100,248,121,27,251,171,244,139,43,183,243,229,65,167,45,
62,196,101,134,4,95,54,106,101,142,70,208,198,40,247,224,250,85,135,53,157,43,105,173,4,172,248,130,86,3,81,2,23,80,129,206,165,75,151,176,186,186,26,165,109,108,108,224,252,249,243,160,215,218,28,30,
30,226,214,173,91,56,58,58,10,178,41,207,143,127,252,99,60,123,246,12,15,31,62,196,116,58,197,23,191,248,69,92,185,114,5,195,225,16,163,209,18,22,22,22,224,189,199,193,193,33,110,220,184,129,201,100,18,
100,108,110,110,226,252,249,243,120,247,221,119,113,120,120,136,163,227,202,85,61,83,30,227,149,133,234,149,196,101,89,226,240,240,9,30,60,250,16,55,207,127,5,247,78,154,199,24,78,187,25,94,29,150,232,
245,92,173,231,30,246,30,95,199,143,198,47,224,214,49,176,52,57,192,131,254,34,190,242,228,22,190,49,219,198,194,226,2,70,11,30,235,253,234,205,136,199,195,69,252,164,216,196,67,55,4,93,229,241,244,16,
95,124,116,29,127,117,233,28,110,30,205,240,242,209,30,60,78,112,176,176,140,251,227,51,88,41,26,247,236,12,78,240,226,112,138,149,190,195,206,201,9,252,162,199,172,156,225,240,240,16,135,251,37,176,0,
124,178,184,142,51,253,202,221,4,128,5,231,241,98,113,136,11,195,138,181,52,3,35,166,213,28,96,188,215,7,73,149,102,48,109,99,113,154,151,141,7,92,156,168,58,149,154,235,163,200,215,214,211,116,86,162,
111,5,208,100,230,140,171,145,159,186,74,210,248,232,78,118,91,224,96,216,117,82,224,117,199,54,73,241,249,124,20,247,153,67,52,9,217,186,231,88,19,247,145,53,150,197,159,74,161,252,206,187,244,187,132,
82,145,244,118,185,189,179,155,206,57,251,218,220,220,196,233,211,167,131,34,189,126,31,139,11,11,88,94,94,198,96,48,192,222,222,30,254,240,15,255,16,211,233,20,195,225,48,212,215,239,247,177,176,176,
0,0,56,62,62,14,235,98,43,43,43,56,119,238,28,250,253,126,69,15,251,125,236,238,238,226,31,253,163,63,192,108,54,195,194,194,66,144,177,184,184,24,206,167,211,105,184,88,171,171,171,184,176,178,26,0,235,
233,211,167,24,236,85,58,207,102,51,244,234,205,175,75,75,75,184,176,124,1,253,126,31,101,89,98,127,127,31,55,118,142,1,0,147,201,4,7,7,7,192,42,176,184,176,128,23,214,94,192,104,113,132,162,87,96,48,
24,96,50,153,224,127,28,190,140,219,139,99,44,248,41,134,190,4,28,176,57,59,196,139,123,247,1,0,39,39,83,76,167,83,124,115,247,3,252,211,23,190,138,255,125,227,23,168,19,67,127,158,198,20,191,135,27,21,
125,47,155,59,89,95,122,114,27,255,215,242,85,252,112,229,50,126,232,174,240,11,135,2,30,255,245,240,1,254,158,155,132,235,81,221,112,136,25,135,197,180,194,160,118,53,204,178,129,165,93,115,43,78,157,
161,171,132,52,62,98,35,85,78,9,66,141,97,42,12,64,210,55,164,128,148,3,168,54,38,147,59,151,193,90,3,182,242,106,76,44,90,51,174,39,208,54,102,34,101,106,196,35,199,166,180,186,115,113,113,121,173,95,
50,140,175,3,171,44,125,250,204,165,115,174,217,214,160,45,82,38,29,84,83,42,74,183,22,56,129,10,236,214,215,215,163,221,238,69,81,160,215,239,163,223,235,97,54,43,113,227,198,13,156,156,156,224,202,149,
43,248,250,215,191,142,126,191,143,225,112,1,195,225,32,90,147,34,153,195,225,16,75,75,75,1,136,78,78,78,240,254,251,239,99,54,155,225,218,181,107,248,250,215,191,142,94,175,135,133,133,5,12,135,67,124,
239,123,223,11,50,104,94,31,12,135,88,90,234,7,157,78,78,78,224,14,137,21,206,80,212,117,13,6,125,140,199,125,20,69,15,222,87,254,126,239,217,12,240,192,172,156,5,42,223,239,247,48,30,143,3,192,206,102,
51,220,123,118,128,219,195,37,92,60,120,132,255,224,238,255,139,177,159,97,113,113,17,131,193,0,111,187,165,112,65,71,163,17,126,245,209,199,248,242,123,127,128,71,227,13,148,69,175,238,207,2,111,158,
126,21,63,90,190,128,239,151,99,124,129,221,77,28,14,134,184,176,186,132,255,226,198,63,195,163,193,24,7,131,81,176,215,251,139,107,248,199,231,222,192,63,62,30,227,215,151,78,90,63,108,97,129,76,20,175,
108,185,168,180,231,20,203,48,98,215,244,123,253,51,60,15,109,179,154,42,103,150,225,121,159,184,187,72,198,175,101,72,169,172,231,13,220,208,117,87,42,222,12,169,214,199,127,51,251,162,120,199,228,18,
89,8,215,41,227,122,113,185,116,22,136,141,239,194,3,155,252,26,176,241,107,83,111,102,23,152,161,187,135,222,123,20,189,94,208,79,5,45,133,193,59,87,51,44,192,94,155,202,166,137,181,107,109,199,248,112,
97,136,193,96,16,149,37,170,55,153,76,194,221,161,237,237,109,236,237,237,97,113,113,49,196,211,62,46,237,187,102,244,155,203,120,240,224,1,246,246,246,176,176,176,144,200,144,23,245,131,233,0,19,84,123,
203,158,96,140,183,87,78,97,88,78,177,225,39,120,138,56,144,1,1,205,224,105,226,171,11,210,235,245,130,1,77,38,19,156,28,236,163,215,47,241,112,241,20,238,109,93,195,230,176,192,94,81,96,86,150,184,127,
84,201,234,245,122,24,47,141,177,127,241,85,60,59,56,68,111,58,69,207,87,95,231,57,158,28,227,113,125,247,239,100,50,137,94,130,182,176,176,128,114,243,5,60,93,218,66,121,124,132,133,178,132,247,192,116,
122,130,39,190,135,137,47,48,157,77,113,114,114,162,190,54,68,6,11,16,194,53,107,98,3,40,84,6,101,151,231,69,170,131,102,204,113,125,105,253,113,237,50,47,159,84,231,97,63,154,155,226,88,217,136,137,138,
124,116,206,239,124,83,188,188,123,94,255,8,120,175,221,93,215,218,195,148,173,226,51,223,15,36,121,178,127,200,27,98,136,221,200,172,219,229,88,221,241,58,155,232,31,64,237,223,248,200,124,60,43,136,
241,34,115,71,128,167,76,52,179,217,12,133,83,30,205,105,163,254,161,65,92,79,67,223,112,247,49,210,187,222,81,62,155,225,244,233,211,216,216,216,192,206,206,14,254,228,79,254,68,109,167,230,114,242,14,
222,218,218,194,169,83,167,176,187,187,139,63,250,163,63,82,203,86,101,170,252,211,233,20,191,179,119,10,143,138,5,202,132,98,88,226,87,246,63,198,210,176,192,94,65,70,238,80,20,46,170,179,168,1,32,122,
116,71,180,207,57,135,254,236,4,95,222,249,16,111,159,126,25,255,96,245,11,36,174,250,103,212,244,163,247,30,255,125,255,69,236,172,14,130,46,76,16,149,253,180,6,0,0,32,0,73,68,65,84,206,30,63,195,151,
103,143,48,171,123,142,202,253,159,229,58,254,215,165,179,192,18,162,252,0,48,156,77,241,247,142,62,193,108,182,24,109,40,212,174,175,213,199,86,90,156,16,255,212,128,162,1,189,180,110,158,189,177,47,
143,6,39,20,247,165,54,160,8,56,1,243,185,65,250,29,27,96,186,169,150,88,68,206,5,148,94,132,198,174,184,68,239,97,238,247,242,222,43,123,187,242,192,192,229,218,233,118,59,218,65,71,215,115,158,178,90,
158,102,98,169,244,207,201,73,219,214,180,187,2,97,196,59,221,67,102,231,80,240,153,192,161,217,175,99,48,43,56,192,21,21,109,251,214,183,190,133,205,205,205,234,153,64,135,32,131,239,44,38,247,238,215,
127,253,215,241,244,233,46,38,147,147,74,140,171,246,122,149,101,25,92,173,181,181,53,124,247,187,223,197,149,43,87,34,93,251,253,62,198,227,49,190,251,221,239,98,119,119,55,108,246,164,58,102,179,25,
198,227,49,122,189,30,202,250,14,220,225,193,1,254,157,233,223,96,255,100,90,15,170,18,231,167,123,184,124,122,13,195,225,41,140,123,135,248,143,31,254,16,159,223,88,65,89,174,68,134,126,197,31,226,63,
121,244,67,188,188,186,128,126,191,143,255,240,209,95,226,202,169,49,188,95,9,224,224,156,195,120,60,198,191,241,241,59,248,151,31,253,4,187,163,181,234,46,158,115,240,101,137,233,116,138,209,210,18,46,
111,46,227,217,179,25,126,107,247,109,236,31,79,162,139,228,125,137,213,201,62,94,94,30,98,124,246,44,14,103,51,252,71,143,222,198,11,171,99,28,22,14,95,217,125,140,211,135,63,197,108,70,143,63,85,215,
170,55,157,224,154,59,194,213,139,23,208,235,141,213,55,73,106,191,181,240,60,101,218,228,228,118,223,215,25,178,233,65,150,48,202,68,78,135,223,86,154,149,167,237,141,14,156,137,72,118,102,213,105,197,
89,65,26,116,23,89,218,114,141,45,255,249,192,45,138,171,21,165,35,128,176,14,199,227,186,202,230,231,179,217,44,118,9,89,142,120,236,208,15,87,47,105,20,108,101,162,102,88,14,14,189,162,192,104,52,194,
203,47,191,140,209,104,148,221,223,69,123,177,138,162,192,234,234,106,164,32,55,252,165,165,37,244,251,125,172,174,174,70,27,73,157,115,24,14,135,88,95,95,71,175,215,195,250,250,122,242,9,246,126,191,
143,165,165,37,244,250,125,184,103,39,128,247,232,245,123,120,165,60,198,73,81,1,228,96,113,128,165,165,77,172,174,174,98,56,28,194,123,143,175,79,38,88,29,245,163,15,19,12,6,3,188,176,182,138,173,233,
20,203,227,69,76,23,250,248,218,224,8,43,227,65,228,122,245,251,125,172,173,173,1,0,214,247,246,112,114,50,105,250,177,0,138,97,129,229,101,135,181,133,1,102,179,2,159,47,158,97,210,107,0,203,57,87,189,
79,104,99,3,171,171,171,24,143,199,24,12,6,248,122,255,0,163,81,15,253,126,31,151,134,135,216,56,57,66,89,196,27,46,7,203,67,172,174,158,193,250,250,122,184,49,193,211,101,255,106,97,30,96,146,110,141,
45,171,102,78,130,150,37,64,164,84,221,201,125,82,226,218,126,107,101,101,59,228,91,63,186,158,255,60,243,206,83,134,130,186,254,44,202,231,226,101,63,203,163,149,6,232,78,151,67,5,90,133,115,230,6,90,
158,191,153,192,154,253,130,20,31,238,18,90,235,86,164,144,60,111,124,209,166,227,122,189,138,241,44,46,46,6,131,209,228,211,64,88,90,170,182,38,204,102,179,10,121,35,23,174,122,252,100,48,24,96,52,170,
252,40,41,19,168,238,230,45,46,46,134,59,129,178,158,162,40,48,153,76,208,235,85,101,150,70,75,184,176,217,188,9,177,215,171,64,96,48,168,220,178,193,96,128,217,108,22,238,90,146,60,126,7,178,223,239,
195,151,37,150,150,150,48,24,12,66,62,158,119,115,115,19,107,107,107,97,13,142,247,233,96,48,168,100,248,106,225,157,175,81,145,78,189,94,15,195,225,48,0,216,104,52,66,191,95,221,44,88,88,88,136,30,46,
39,185,212,142,46,31,179,245,222,39,139,242,218,128,206,205,202,114,108,104,233,185,223,185,32,217,161,23,51,244,60,204,69,78,134,109,0,75,199,231,125,79,86,202,24,242,238,102,104,159,194,160,230,97,61,
49,211,241,17,99,165,107,37,223,19,38,251,99,94,70,37,211,180,73,204,154,44,228,120,227,57,136,165,242,184,228,187,132,26,122,106,33,137,119,241,224,37,195,146,121,37,40,122,239,3,96,104,233,141,162,61,
194,50,120,239,107,3,175,48,153,234,28,14,135,73,89,186,64,222,123,108,250,19,252,214,227,191,196,171,167,199,24,12,150,35,128,161,45,14,4,146,252,194,242,118,240,157,227,174,40,48,20,59,180,67,31,58,
68,58,57,7,240,47,105,115,160,224,236,140,235,77,114,122,53,232,242,207,177,209,157,208,180,159,138,8,136,248,53,44,203,50,102,92,176,7,89,101,60,218,32,115,224,81,241,235,123,226,133,204,4,172,168,35,
36,171,226,210,153,190,180,143,44,210,145,77,106,188,158,166,223,42,61,44,208,229,242,116,61,105,177,159,218,79,121,18,85,227,4,161,87,85,55,1,68,197,55,186,48,41,64,79,215,116,45,125,9,231,117,102,20,
206,153,205,240,177,158,182,59,205,167,5,201,168,52,219,238,2,84,93,66,218,71,85,124,244,213,156,92,5,26,136,181,209,114,171,1,218,197,176,202,107,232,91,231,142,242,200,114,116,97,138,162,192,112,56,
196,185,181,21,108,76,38,88,91,232,7,96,178,130,38,207,98,160,86,27,101,30,77,174,101,180,33,222,3,179,89,12,52,69,70,47,212,180,155,12,72,99,81,154,254,92,119,237,119,147,143,239,172,174,102,113,237,
21,35,109,236,39,153,213,129,248,110,24,195,62,173,143,185,6,124,100,120,15,240,7,146,237,114,77,249,24,16,236,124,82,255,128,189,181,10,101,217,108,165,200,217,72,34,185,197,168,205,190,204,52,43,7,202,
18,224,100,90,87,118,103,157,183,225,195,124,161,25,119,212,224,126,148,236,154,109,7,33,163,97,120,154,34,81,158,220,30,254,57,66,0,57,164,172,32,186,126,62,190,35,198,233,124,191,223,199,242,242,50,
188,247,193,205,82,235,80,102,61,11,92,121,185,234,77,171,241,44,207,207,115,147,64,110,157,73,11,165,194,30,114,224,154,155,73,67,26,29,51,122,230,116,10,245,54,10,196,249,53,29,144,26,72,36,159,177,
3,75,167,174,128,107,253,230,79,121,168,238,142,71,180,37,35,241,58,60,251,50,78,96,83,80,243,39,198,45,100,119,213,185,178,1,201,110,235,250,228,26,97,45,191,112,69,227,34,242,46,110,97,185,150,29,116,
1,30,203,125,140,227,27,27,174,110,234,37,82,68,25,1,88,68,35,37,13,207,53,66,27,52,179,89,245,8,9,255,220,151,22,180,52,235,107,196,57,134,163,201,227,121,56,235,217,223,223,87,153,142,86,86,99,40,109,
122,88,131,64,205,231,226,33,214,212,11,200,217,223,210,1,96,125,22,77,24,149,219,154,56,117,81,89,23,14,154,30,185,48,15,213,167,246,52,191,99,166,86,199,102,13,193,2,222,182,56,170,91,130,110,201,242,
57,81,78,190,43,203,116,185,148,186,115,121,187,48,149,92,25,10,242,165,130,214,151,120,230,97,70,109,229,101,189,81,57,241,53,163,94,175,135,209,104,148,110,238,77,234,139,245,46,91,116,41,138,146,238,
18,34,202,216,133,198,202,115,2,134,233,116,138,157,157,29,115,86,230,198,59,143,161,231,242,202,124,86,222,112,238,32,152,228,124,32,216,53,95,43,35,113,46,204,180,234,251,220,235,52,205,5,205,185,180,
109,117,231,250,175,171,12,210,195,202,155,99,70,93,100,203,50,109,198,52,15,75,161,32,95,107,211,6,128,169,107,69,231,128,4,228,90,106,39,189,18,23,249,51,180,49,151,71,251,134,99,174,190,174,58,104,
199,195,195,195,112,7,159,183,81,235,231,174,30,141,115,174,218,56,170,26,91,189,193,142,220,196,176,159,10,13,197,212,6,248,211,167,79,107,122,138,250,45,2,76,174,247,49,11,96,238,147,84,146,235,197,
93,141,54,99,227,157,198,59,128,191,35,156,57,76,36,37,42,203,101,219,3,192,133,242,161,110,165,13,60,119,14,240,232,237,167,92,119,89,39,191,152,205,190,175,180,47,154,182,117,3,95,46,159,215,219,234,
158,48,25,93,220,4,158,55,151,159,235,16,54,157,178,205,167,222,251,230,19,107,243,214,239,125,152,201,249,182,5,171,207,53,35,74,39,117,114,111,58,184,74,140,189,105,99,86,182,39,5,73,125,161,61,7,8,
109,237,107,43,75,45,132,162,31,15,114,60,236,239,239,227,212,169,83,157,250,37,55,30,185,238,125,62,120,34,197,193,238,6,212,157,204,211,172,202,102,179,153,189,46,163,108,113,224,191,173,89,151,128,
160,13,153,57,195,50,101,249,102,55,53,137,107,102,202,246,217,191,109,27,136,214,110,250,157,107,103,27,147,203,13,166,156,60,173,77,242,154,55,129,226,93,82,30,176,223,255,14,160,217,129,46,59,53,58,
181,174,73,105,166,145,14,114,114,227,186,105,94,129,201,82,144,130,208,60,229,91,229,103,24,89,213,130,110,238,165,165,87,215,122,186,2,120,23,57,109,121,172,122,39,39,147,128,31,242,49,45,75,143,28,
115,244,222,199,107,88,154,144,121,168,123,151,15,7,104,32,19,43,91,177,6,109,80,73,157,98,126,164,113,138,166,206,182,243,168,173,190,137,147,139,148,214,219,49,115,110,85,21,71,235,54,121,183,75,213,
79,147,201,206,115,215,41,167,99,10,90,121,32,213,226,195,117,169,126,52,113,98,22,175,226,245,111,5,54,253,195,100,241,244,250,152,130,143,143,50,183,49,194,46,249,44,118,210,38,243,231,25,186,0,80,151,
201,181,77,182,140,159,167,31,58,86,6,160,241,214,192,129,75,180,203,58,202,184,254,188,160,212,154,159,13,58,105,32,93,234,145,108,39,196,243,149,225,26,153,156,175,6,109,152,53,203,18,16,76,36,55,155,
242,120,135,230,14,92,244,24,146,113,141,36,227,33,8,41,217,221,74,217,87,1,188,124,51,211,180,129,41,151,145,212,169,181,163,3,112,89,245,229,174,207,220,134,81,95,36,135,246,129,222,76,2,60,31,181,57,
194,62,89,73,232,75,205,160,187,244,133,247,249,245,192,156,1,241,223,33,174,30,51,218,2,117,155,123,41,243,117,1,23,58,159,151,241,89,109,83,219,212,177,108,122,94,4,57,85,155,212,230,68,65,155,128,121,
92,178,211,189,205,29,161,56,205,53,2,16,30,16,118,138,12,77,174,140,211,26,144,203,235,224,162,61,87,90,89,77,78,210,137,174,1,157,168,1,74,89,179,143,0,240,251,114,154,107,236,189,111,190,187,168,232,
44,243,91,253,220,229,183,206,100,244,252,93,227,231,157,224,186,4,205,253,204,5,218,255,21,77,46,85,130,93,134,177,229,138,1,54,117,207,13,74,202,239,46,250,203,122,180,118,119,233,3,109,226,162,185,
85,243,26,40,175,181,102,103,213,107,129,150,6,178,86,30,237,205,22,26,161,224,19,185,118,77,104,66,237,39,159,147,175,126,168,46,27,143,211,62,67,239,125,243,20,58,201,201,201,208,58,213,154,233,115,
134,194,119,235,215,213,214,58,166,44,70,171,155,213,194,206,211,139,105,181,37,234,124,126,110,228,227,85,240,197,118,174,171,85,167,89,111,2,78,41,248,120,223,14,14,150,171,209,102,84,57,134,214,230,
190,104,110,182,247,241,218,71,174,110,53,157,85,21,54,183,42,69,53,198,10,185,65,214,208,223,98,70,50,173,107,190,54,25,89,192,200,82,209,184,29,93,1,26,62,126,150,207,42,155,147,53,239,91,41,114,105,
69,81,164,15,63,251,42,71,43,208,104,33,162,166,181,28,115,166,119,233,214,82,78,133,173,11,217,6,110,77,57,27,168,114,161,11,195,212,153,139,188,219,26,206,148,56,82,170,142,47,82,189,154,71,121,188,
218,78,32,207,40,83,121,250,108,218,214,39,85,186,182,111,42,149,45,39,14,25,186,48,9,11,12,187,132,168,93,188,223,139,180,237,121,224,163,205,192,85,176,220,187,46,186,168,227,37,169,174,97,72,237,186,
197,253,45,235,99,26,36,227,173,193,54,105,203,94,228,169,119,237,87,155,50,85,16,141,229,234,121,186,246,81,151,60,132,11,125,254,70,2,105,160,57,151,74,59,215,102,202,156,235,34,243,116,1,21,141,202,
106,96,166,213,97,181,193,170,211,202,39,203,116,105,99,151,118,70,236,66,124,243,78,171,131,63,52,157,202,107,76,192,106,99,14,92,100,221,185,246,82,208,220,91,21,128,42,33,217,60,185,25,156,215,207,
199,156,124,78,78,2,228,243,0,105,27,27,105,211,93,45,175,232,94,253,246,33,53,199,156,186,25,58,191,190,13,48,105,30,14,77,182,85,60,128,176,69,35,221,3,72,101,114,100,134,199,107,207,46,90,228,35,250,
184,48,27,119,252,188,159,3,153,156,235,163,53,132,191,37,32,49,176,112,167,64,119,115,210,14,143,59,43,7,10,214,172,204,7,105,14,32,180,248,4,172,162,93,225,113,154,182,128,94,101,77,103,249,28,152,229,
152,143,5,90,148,150,166,167,70,211,69,166,22,188,207,124,59,176,99,176,102,230,182,122,101,249,28,64,168,174,82,75,157,109,191,181,250,181,201,161,194,149,84,86,174,221,210,152,123,61,195,195,96,134,
219,22,194,181,134,190,112,47,119,197,107,109,214,192,37,73,243,158,80,49,228,227,109,182,38,186,156,199,196,63,156,162,233,212,235,245,208,39,252,205,49,168,231,61,202,56,190,97,78,230,125,252,248,49,
246,247,247,113,233,210,37,85,150,197,172,146,250,24,48,242,224,156,195,245,235,55,176,186,186,138,179,103,183,32,25,8,207,87,117,34,0,218,129,142,212,109,115,112,56,58,62,194,141,27,55,240,234,171,175,
98,97,97,161,149,89,117,97,94,50,77,203,175,245,75,219,195,220,60,36,134,36,64,120,158,208,21,188,114,204,248,121,101,87,54,83,237,225,114,46,63,86,52,153,82,135,156,161,90,109,170,207,162,231,8,173,124,
52,166,100,93,82,95,250,146,56,223,156,157,155,148,121,187,66,54,71,55,35,170,113,222,16,54,205,29,108,108,65,202,53,251,128,234,171,43,213,64,141,222,148,34,101,181,50,80,35,174,44,75,244,219,192,138,
135,54,247,75,86,164,95,116,57,72,170,243,247,222,123,15,71,71,71,56,125,122,3,227,241,184,158,177,210,126,226,200,109,25,113,207,213,111,248,20,3,225,254,253,79,1,120,156,61,187,85,247,183,206,40,99,
250,94,199,149,169,145,211,99,72,252,253,233,57,96,145,65,222,65,105,51,80,153,110,129,212,188,111,162,80,229,27,32,198,39,3,153,222,14,48,221,88,79,91,26,55,182,220,181,211,100,117,117,231,114,134,164,
229,55,153,136,82,206,50,206,112,46,64,141,247,106,27,83,37,224,110,0,170,33,66,41,184,145,59,72,182,38,1,48,6,179,212,141,43,2,61,176,216,147,252,157,202,176,251,77,139,75,94,145,28,133,44,13,70,130,
40,26,5,229,74,241,230,147,180,162,112,248,244,211,79,113,124,124,140,133,133,5,220,188,121,11,191,240,11,191,0,234,72,46,163,202,159,110,195,72,104,175,247,234,163,48,18,232,44,112,33,189,98,253,83,23,
108,60,94,194,47,253,210,191,20,90,67,197,121,222,106,0,229,129,169,168,50,197,29,195,245,130,139,24,158,166,183,198,206,186,128,96,162,120,91,86,182,83,219,27,179,50,165,91,33,218,138,144,9,150,12,109,
131,178,86,78,99,89,109,44,140,199,105,239,68,123,30,54,44,117,179,210,45,131,7,16,94,191,163,1,169,188,217,65,227,83,3,202,54,32,206,1,182,21,111,157,59,215,172,179,62,47,171,226,199,138,97,101,216,149,
83,20,118,108,112,91,134,47,67,48,212,38,34,160,242,108,86,226,230,205,155,216,218,218,194,218,218,26,222,127,255,125,188,244,210,75,88,90,106,190,176,240,193,7,31,224,193,131,7,145,204,162,40,176,177,
177,129,107,215,174,97,105,105,9,179,217,12,127,254,231,127,30,233,233,156,195,198,233,211,120,253,181,215,48,24,14,195,187,226,203,178,196,159,254,233,159,226,213,215,94,197,249,243,231,209,60,8,237,
241,207,255,249,191,192,107,175,189,134,243,231,207,227,211,79,63,197,237,219,183,171,111,16,10,185,111,188,241,6,122,189,30,222,124,243,77,252,242,47,255,50,150,151,151,113,227,198,13,220,189,123,23,
199,199,199,73,127,125,251,219,223,142,62,201,30,13,198,186,79,232,7,7,59,138,228,151,129,47,78,242,254,32,217,150,49,201,122,231,101,116,185,32,141,164,117,76,192,7,112,78,94,139,50,39,227,178,210,19,
35,112,113,60,93,119,107,86,151,147,34,245,113,0,76,225,6,104,108,90,158,91,128,199,229,167,32,209,236,161,210,152,137,100,212,22,24,243,114,18,132,53,22,164,245,163,229,49,104,128,227,156,67,175,232,
69,19,91,59,131,141,221,83,158,175,90,195,138,148,4,43,144,223,120,168,5,173,97,86,160,244,135,15,31,224,224,224,0,95,252,226,23,177,180,180,132,219,183,111,227,230,205,155,248,252,231,63,31,242,77,167,
83,244,122,61,92,186,116,41,148,59,60,60,196,237,219,183,49,28,14,241,202,43,175,0,0,174,94,189,26,213,251,228,201,19,124,252,209,71,88,89,94,198,229,203,151,35,192,58,60,60,196,201,228,4,229,172,249,
120,4,0,28,29,29,97,58,157,162,44,75,252,228,39,63,193,112,56,196,181,107,215,18,189,233,115,98,39,39,39,240,190,122,208,243,189,247,222,195,249,243,231,113,249,242,229,164,173,185,65,21,245,151,103,91,
74,34,67,166,205,117,122,31,243,55,138,90,125,111,189,204,111,30,96,202,133,121,229,116,101,100,36,183,43,179,146,113,210,248,10,198,120,173,55,54,88,6,159,164,101,53,202,47,9,200,124,210,216,155,114,
233,182,146,54,121,0,129,92,227,14,58,167,1,1,224,125,186,167,178,107,29,93,39,71,237,137,4,21,188,8,148,93,58,62,102,179,89,183,207,124,73,87,202,202,111,189,195,61,39,247,246,237,219,56,127,254,124,
248,192,196,181,107,215,240,254,123,239,53,31,178,112,213,151,120,150,151,151,113,245,234,213,168,252,100,50,193,254,254,62,138,162,8,239,97,167,111,17,2,192,165,75,151,176,191,191,143,131,131,131,240,
158,116,254,71,223,20,212,58,152,232,44,189,83,158,218,53,28,14,113,234,212,41,56,231,112,114,114,18,189,82,217,185,234,125,235,164,55,0,140,199,99,44,47,47,103,251,129,215,239,12,80,9,231,244,213,74,
204,15,54,124,22,151,241,207,205,182,2,123,177,93,244,92,121,199,202,66,12,96,32,6,4,249,81,206,56,3,115,145,12,166,39,93,242,28,19,209,152,12,143,239,226,18,105,113,22,232,202,114,214,171,96,178,245,
249,134,203,164,253,148,222,138,210,152,23,15,146,109,133,60,181,23,16,94,138,64,55,175,224,224,93,60,161,22,61,154,28,0,180,0,22,63,143,247,152,85,101,251,253,190,100,88,249,93,232,242,34,202,25,137,
207,88,18,236,162,124,245,51,127,15,30,60,192,254,254,62,190,240,133,47,224,214,173,91,225,174,66,233,61,110,222,188,137,207,125,238,115,129,6,115,58,28,58,163,40,170,143,49,212,249,111,222,188,25,190,
250,12,32,250,34,115,116,225,106,36,87,47,44,139,187,118,237,26,62,252,240,67,188,245,214,91,81,250,104,52,194,183,190,245,173,160,83,89,150,88,94,94,198,133,11,23,240,241,199,31,227,214,173,91,209,69,
63,119,238,28,190,250,213,175,170,253,101,213,205,251,48,103,60,26,104,229,192,71,26,66,4,24,153,96,205,182,156,25,90,109,146,229,187,204,220,92,63,103,184,74,33,3,59,209,64,41,210,149,25,174,214,79,212,
31,124,188,105,47,162,155,7,200,156,144,167,185,83,82,95,126,139,95,202,211,234,243,13,149,82,245,3,217,157,17,180,15,22,91,186,90,186,104,237,158,78,79,234,56,160,97,138,158,197,205,87,71,120,31,86,142,
89,241,32,1,172,203,12,111,13,208,15,63,252,16,167,207,156,193,172,44,241,240,225,195,32,127,121,121,25,119,239,222,197,213,171,87,177,184,184,24,220,56,217,128,0,24,222,99,103,103,7,11,11,11,248,230,
55,191,89,127,176,161,90,180,255,228,147,79,34,87,144,102,95,143,202,173,204,1,200,139,47,190,136,23,95,124,49,44,28,58,231,112,239,222,61,188,251,206,187,216,222,222,198,226,226,98,96,128,69,81,224,203,
95,254,50,190,244,165,47,69,123,93,222,127,255,125,124,252,241,199,129,1,74,131,50,153,135,193,196,120,156,198,14,172,153,50,39,95,134,132,109,2,201,157,32,77,134,198,30,62,171,187,233,129,196,208,74,
95,6,66,149,115,221,114,192,232,171,194,113,222,192,32,218,23,167,187,62,114,98,233,19,202,84,63,90,243,229,218,213,117,2,40,138,30,160,172,15,209,121,110,18,237,2,80,154,188,94,175,31,197,229,250,138,
191,198,74,3,228,176,134,21,6,40,31,4,78,14,182,234,113,5,13,164,10,246,69,24,185,15,202,2,181,71,15,31,98,239,217,30,62,255,249,207,99,117,117,21,127,231,171,95,141,140,226,123,223,251,30,62,186,125,
27,175,189,254,122,216,77,194,229,73,131,30,143,199,216,222,222,198,59,239,188,19,189,183,253,224,224,0,227,241,56,169,127,125,125,29,215,175,95,199,225,225,97,248,34,13,95,123,34,176,225,193,57,135,135,
15,31,162,244,101,248,60,151,247,149,111,125,112,112,128,27,55,110,36,122,221,189,123,55,124,158,140,190,155,104,25,189,198,12,114,172,69,6,139,105,105,0,214,197,16,44,157,40,228,214,148,180,118,180,129,
87,110,166,174,142,180,27,92,175,163,173,45,90,154,99,32,85,141,251,188,183,145,11,242,225,226,72,62,98,131,141,116,23,12,76,171,83,101,84,162,61,109,172,104,158,60,106,31,101,228,105,50,105,169,164,139,
206,93,116,243,222,139,103,9,19,144,106,42,150,2,120,92,201,222,115,164,221,17,224,114,40,110,103,103,7,23,46,94,192,242,242,114,114,215,203,57,135,151,94,122,9,15,30,60,192,108,54,195,210,120,140,97,
237,218,113,122,190,178,178,18,190,246,252,226,139,47,162,40,10,236,237,237,133,187,122,4,100,180,134,180,182,182,134,165,165,37,56,231,240,250,235,175,227,227,143,63,198,179,103,207,66,221,156,73,57,
231,176,183,183,151,180,97,101,101,5,215,174,93,195,242,120,140,189,253,125,108,108,108,160,223,239,97,54,155,225,217,179,103,113,159,121,143,173,173,45,92,188,120,49,114,11,52,118,37,211,195,64,149,251,
191,128,128,222,124,247,125,84,47,186,93,71,10,242,75,60,90,160,94,200,49,172,108,121,97,4,60,94,202,109,11,159,101,91,67,155,140,46,198,222,53,191,85,70,147,155,130,111,197,107,125,228,66,229,251,72,
179,83,138,215,250,68,150,149,227,207,126,191,93,115,19,32,7,46,205,39,236,170,252,243,130,83,26,87,194,253,238,239,254,110,72,177,12,201,74,215,58,232,225,195,135,217,153,62,247,149,152,184,83,105,31,
86,51,187,58,231,146,245,7,39,127,139,60,17,71,172,103,80,121,201,168,236,227,199,143,241,214,91,111,225,141,55,222,192,217,179,103,99,29,235,114,57,87,141,51,1,64,103,20,93,202,231,102,115,187,78,165,
44,31,251,162,204,60,0,97,234,145,244,101,188,119,78,11,243,212,91,13,242,12,56,121,158,151,13,240,14,6,174,177,158,68,142,184,14,22,235,173,88,18,212,109,18,22,75,235,10,140,57,192,228,242,180,71,110,
218,100,89,191,219,226,219,116,226,186,109,109,109,101,101,183,199,53,96,23,22,221,129,230,34,72,42,76,161,237,183,22,47,141,41,186,131,232,155,189,88,20,215,6,148,64,101,123,109,183,239,45,96,145,249,
63,248,224,3,220,187,119,47,196,159,156,156,160,223,239,99,115,115,211,212,167,43,8,105,113,185,1,151,147,23,231,169,102,94,45,191,28,44,156,49,231,12,145,167,87,88,219,145,57,121,121,231,201,126,171,
195,60,108,140,235,67,155,106,85,35,97,34,249,103,208,93,253,150,1,222,142,4,188,136,81,40,122,89,70,154,109,131,71,116,219,158,219,21,103,42,214,226,182,170,35,242,70,221,69,198,60,172,198,210,129,130,
133,13,188,156,180,103,250,203,246,167,7,180,109,12,205,177,26,243,253,126,191,89,116,231,236,39,215,113,218,236,220,54,11,209,12,84,237,21,204,177,42,61,94,118,18,173,5,145,129,52,187,210,237,53,32,41,
211,57,135,51,103,206,68,27,84,7,131,65,0,43,62,104,101,155,231,1,235,174,233,146,49,134,122,129,132,85,90,50,187,164,89,224,201,235,51,81,39,1,168,231,11,86,221,213,9,139,131,139,62,253,212,69,78,18,
47,240,93,62,90,148,51,94,174,14,103,238,222,251,32,54,103,43,240,205,114,73,36,211,24,247,252,55,255,222,97,216,70,144,148,241,245,7,92,243,0,162,129,137,28,207,57,251,14,50,81,127,168,151,45,140,91,
19,95,234,6,250,72,146,148,11,47,251,146,3,86,117,30,239,116,23,174,90,27,163,144,233,18,244,230,49,94,77,102,55,183,40,126,111,145,76,215,88,5,239,232,141,141,13,108,108,108,168,250,88,23,77,202,144,
241,178,62,9,230,145,123,64,111,112,80,30,10,143,218,226,189,57,64,100,222,28,19,86,7,54,226,141,148,109,178,115,121,88,230,236,131,55,82,134,181,86,146,131,71,107,2,73,100,249,52,127,200,219,241,43,209,
57,6,98,77,214,213,73,60,65,183,201,143,198,6,210,49,156,150,75,199,186,102,59,114,194,238,18,104,226,146,204,72,251,118,160,252,29,216,113,244,30,50,36,231,150,54,65,142,82,143,249,122,25,141,149,240,
52,173,83,52,42,221,21,124,218,104,169,101,248,86,30,231,156,185,94,214,86,142,159,71,131,136,165,181,201,206,201,180,2,239,63,77,86,110,18,233,82,94,134,240,168,137,79,199,0,201,211,206,91,221,187,12,
19,211,174,119,182,255,104,12,102,128,130,203,107,251,94,99,27,163,226,241,57,150,34,203,102,153,22,82,99,230,231,146,209,231,100,207,227,206,241,223,93,215,184,44,157,165,199,228,155,76,166,172,240,182,
134,154,65,133,52,246,36,141,51,218,96,49,64,245,171,57,22,88,133,52,164,232,215,116,186,246,168,67,234,142,201,206,144,231,154,236,220,108,166,233,107,13,56,211,224,156,109,140,173,70,218,82,198,50,202,
156,107,96,25,181,54,99,182,1,161,150,174,61,147,152,99,150,60,79,151,124,150,46,162,64,46,115,2,84,109,192,144,139,235,170,147,213,190,54,112,72,220,87,9,220,6,232,106,227,84,221,213,159,209,57,23,218,
152,179,101,155,210,238,218,200,69,56,175,215,163,10,87,160,232,165,91,61,224,93,180,65,55,169,19,30,206,167,227,61,188,34,153,43,19,27,89,85,123,50,166,92,238,142,153,182,198,101,207,44,92,33,121,46,
59,141,27,152,236,60,237,162,167,237,201,187,161,0,80,162,2,220,182,15,90,228,193,194,1,208,159,207,138,203,240,180,212,0,84,23,142,93,96,155,113,165,215,76,191,190,121,112,105,3,193,121,202,85,249,237,
69,121,75,110,14,28,173,252,22,11,210,126,91,113,243,228,9,32,35,235,173,237,164,49,100,251,177,37,75,79,154,240,161,44,232,203,252,63,15,86,150,203,111,29,233,92,182,195,23,30,126,22,127,198,158,62,107,
79,253,99,233,163,213,81,150,101,203,119,9,65,29,94,255,82,102,227,92,92,133,150,105,28,29,187,24,145,229,134,73,89,93,202,91,46,174,149,63,109,151,214,110,45,127,251,91,17,200,128,171,115,221,21,141,
103,157,202,32,114,32,198,235,151,50,57,211,229,237,104,74,216,173,201,178,82,180,15,240,208,134,57,88,1,16,191,222,197,98,130,50,62,121,244,136,61,123,169,234,14,165,159,196,4,42,235,177,38,19,158,159,
100,71,245,88,249,90,193,80,7,170,148,24,116,99,183,188,109,22,147,171,174,87,201,206,9,144,226,122,180,71,241,72,182,115,213,179,177,17,104,211,245,96,99,60,1,58,239,225,92,1,239,211,111,4,36,239,195,
138,192,5,108,32,179,130,26,101,36,132,231,72,159,31,228,64,243,244,120,243,198,72,107,144,91,46,147,222,88,151,228,225,229,114,71,75,239,241,120,140,193,96,144,212,127,114,114,130,253,253,125,56,87,61,
162,179,178,178,130,189,189,189,112,33,41,110,119,119,215,24,96,241,219,50,225,28,150,70,35,244,122,61,236,237,237,53,237,243,62,124,55,81,239,207,102,22,175,122,52,158,197,170,56,95,207,242,117,125,218,
236,202,219,87,9,54,217,107,151,96,229,207,201,146,241,212,151,235,235,235,106,254,163,163,35,28,30,30,6,185,36,67,115,45,186,232,150,99,43,252,247,226,226,34,134,195,33,158,62,125,10,14,79,161,191,248,
82,8,139,31,143,199,225,141,33,165,47,195,24,121,246,236,89,120,122,66,214,219,214,143,57,247,178,141,169,107,237,110,211,65,59,151,24,33,241,64,202,205,63,222,164,49,74,185,211,29,177,17,53,46,75,187,
97,147,178,109,119,9,163,115,218,104,215,194,72,186,176,161,121,88,150,12,212,169,185,124,91,91,91,245,155,80,211,60,135,135,135,184,113,227,6,134,195,33,174,92,185,130,159,253,236,103,56,58,58,2,80,61,
40,125,249,242,101,188,255,254,251,97,87,62,47,207,47,10,129,200,250,250,58,22,23,23,241,236,217,51,213,88,180,54,132,56,146,71,113,114,198,151,192,150,233,15,41,59,199,44,52,25,84,214,114,209,186,178,
38,10,87,174,92,97,187,167,99,89,143,30,61,194,71,31,125,148,26,8,210,69,95,173,78,235,119,46,255,169,83,167,176,190,190,142,221,221,93,163,188,126,35,106,107,107,11,199,199,199,225,205,34,189,94,15,151,
47,95,198,79,127,250,83,156,156,156,152,117,118,117,157,114,128,27,93,67,79,19,152,126,77,36,3,179,8,69,226,13,36,182,84,64,94,0,109,194,138,219,210,208,37,138,47,138,94,179,15,139,132,116,5,7,139,70,
182,1,135,38,159,63,139,104,213,151,164,249,184,243,85,99,170,219,29,190,75,199,41,99,37,136,117,52,43,166,48,33,239,171,7,172,239,220,185,19,233,180,185,185,137,115,231,206,97,48,24,224,240,240,16,63,
254,241,143,163,242,218,107,66,186,0,64,174,255,181,160,201,202,201,215,216,178,149,47,7,50,82,222,223,118,184,125,251,54,30,63,126,28,197,93,185,114,5,235,235,235,248,228,147,79,186,233,227,196,218,146,
18,186,48,44,234,11,122,179,2,245,183,101,140,188,28,189,218,200,123,143,233,116,138,119,223,125,23,101,89,38,31,98,224,128,144,235,123,107,188,104,128,18,218,96,76,86,60,228,62,90,161,29,37,211,171,142,
105,190,86,230,230,161,62,147,108,186,132,109,3,89,3,185,88,86,190,51,228,197,229,141,205,185,11,81,154,67,10,66,92,182,242,165,154,228,119,96,143,141,43,149,117,33,107,159,156,126,211,115,139,131,193,
0,206,57,92,184,112,1,119,239,222,69,81,20,56,123,238,44,250,245,211,234,23,47,94,132,247,30,159,124,242,9,122,189,30,78,157,58,133,209,104,4,190,87,231,248,248,24,247,239,223,7,128,192,214,120,155,247,
246,246,240,228,201,147,100,221,32,105,151,211,39,1,173,76,151,16,247,87,234,74,202,7,222,219,66,110,240,203,58,173,175,245,240,252,251,251,251,88,95,95,15,110,198,96,48,192,198,198,70,213,191,117,152,
205,102,216,219,219,11,96,183,184,184,136,245,245,245,232,245,67,36,243,254,253,251,56,60,60,196,202,202,10,214,214,214,194,59,207,188,247,56,56,56,192,147,39,79,48,153,76,66,185,178,44,113,250,244,105,
20,69,17,189,25,215,123,143,115,231,206,225,224,224,0,187,187,187,56,123,246,44,22,23,23,177,184,184,136,193,96,128,203,151,47,227,217,179,103,120,250,244,105,24,55,147,201,4,163,209,8,167,78,157,10,15,
229,123,239,49,153,76,176,187,187,139,227,227,99,44,46,46,226,204,153,51,201,196,56,153,76,176,179,179,131,201,100,146,216,175,197,142,212,52,32,89,10,170,94,124,16,95,67,237,26,73,102,173,49,180,28,187,
162,115,239,155,55,55,208,123,182,194,93,66,75,72,136,163,138,170,200,230,188,42,28,238,142,208,128,105,202,54,114,18,101,50,76,206,98,115,73,94,216,157,14,4,130,149,103,50,65,70,227,42,105,50,73,239,
51,167,79,135,221,241,206,85,15,87,207,102,51,28,30,30,98,56,28,98,121,121,25,69,81,84,123,80,74,15,95,84,229,249,35,25,155,155,155,216,216,216,192,211,167,79,171,120,196,179,40,255,163,150,12,135,67,
92,186,116,9,131,65,31,15,31,62,76,250,182,43,187,202,245,151,76,15,113,101,105,194,145,197,180,115,33,55,25,81,122,78,183,203,151,47,71,31,253,88,93,93,197,222,222,30,128,234,198,204,197,139,23,177,182,
182,134,189,189,61,76,167,83,120,239,49,26,141,112,250,244,105,76,38,19,28,28,28,224,242,229,203,24,141,70,245,250,83,220,95,189,94,15,11,11,11,184,118,237,90,200,79,238,209,249,243,231,195,155,113,185,
142,163,165,37,244,123,189,198,136,189,7,188,199,202,234,106,244,94,115,185,70,69,114,151,151,151,67,155,174,94,189,10,0,161,77,0,112,250,244,105,156,58,117,10,63,251,217,207,48,24,12,176,178,178,146,
232,78,79,110,240,247,177,89,125,173,245,49,35,55,73,58,237,168,247,222,199,236,135,157,107,248,145,123,167,187,252,109,178,46,38,63,124,72,149,42,224,149,241,243,40,15,13,234,176,94,85,69,249,232,53,
189,161,180,41,179,233,30,189,126,77,70,142,254,242,243,192,220,16,27,103,39,246,230,98,48,228,117,151,101,137,233,116,26,234,121,252,248,49,118,119,119,147,129,120,124,124,140,219,183,111,99,121,121,
25,203,203,203,184,115,231,78,88,159,88,94,94,198,227,199,219,145,11,195,219,80,150,30,71,71,199,184,121,243,38,235,139,234,109,172,227,241,50,238,223,143,103,113,231,210,39,235,157,51,118,155,103,250,
206,26,48,57,0,138,234,137,242,53,215,85,6,107,115,103,27,171,167,176,188,188,140,225,112,24,250,253,222,189,123,216,217,217,9,101,151,151,151,177,189,189,141,157,157,157,72,214,149,43,87,176,180,180,
132,131,131,131,0,86,31,127,252,113,72,231,147,202,198,198,6,202,178,196,245,235,215,35,54,117,246,236,89,156,57,115,38,52,55,76,50,66,111,122,6,146,226,157,115,245,68,227,241,226,139,47,226,248,248,24,
119,239,222,5,224,49,24,12,131,238,163,250,134,203,237,219,183,35,192,90,89,89,193,133,11,23,194,203,41,1,224,206,157,59,209,117,218,216,216,192,214,214,86,152,48,229,4,64,234,85,101,172,59,175,233,120,
160,99,144,73,246,81,122,128,45,79,133,73,183,142,114,206,217,47,34,244,124,243,41,146,231,48,35,175,173,78,119,142,125,72,53,235,6,41,224,229,128,32,161,6,0,0,32,0,73,68,65,84,156,131,15,95,235,8,245,
134,70,55,12,128,245,65,205,214,194,250,65,157,40,95,111,66,46,154,230,38,74,6,198,59,84,163,189,86,208,92,209,112,206,58,72,182,93,174,159,200,58,85,134,194,210,105,130,56,57,153,36,143,21,85,101,104,
96,165,44,244,232,232,40,122,253,114,90,54,137,68,124,33,210,32,41,124,91,224,253,19,100,52,194,164,116,85,70,204,194,117,38,149,139,191,126,253,58,94,121,229,21,12,6,3,252,236,103,63,139,94,11,68,178,
15,14,14,112,225,226,69,44,48,3,167,186,189,175,214,35,137,181,112,217,79,159,62,13,12,165,244,30,19,113,163,132,223,56,145,42,154,58,139,54,5,0,240,30,190,44,209,239,87,191,167,211,105,0,243,131,131,
131,104,18,164,155,56,101,89,134,246,210,75,41,41,208,157,210,217,108,150,0,150,212,81,3,17,147,225,228,216,81,201,228,213,64,198,55,208,202,53,48,235,216,37,110,54,155,197,128,229,80,173,251,232,46,98,
141,155,30,225,189,205,154,235,150,126,26,137,165,179,35,47,55,99,231,82,110,83,55,217,156,131,227,245,123,150,69,76,234,26,27,147,29,62,207,142,226,112,81,197,140,194,84,140,242,69,233,94,200,80,244,
211,250,157,247,73,2,172,60,116,96,84,57,64,178,249,16,233,214,232,40,196,194,133,245,178,118,134,100,77,58,185,252,77,61,205,107,177,63,252,240,67,92,187,118,13,215,174,93,195,173,91,183,130,17,83,232,
245,122,184,126,253,122,130,42,148,239,147,79,62,193,195,135,15,163,53,172,241,120,140,51,103,206,96,60,30,55,44,64,184,195,52,190,57,27,155,177,243,96,160,113,35,162,116,178,19,249,233,174,174,231,109,
33,16,10,5,248,231,145,175,141,79,173,46,37,50,187,22,44,73,130,36,14,86,253,206,57,244,105,97,79,171,60,101,90,205,150,5,78,251,184,34,252,182,115,78,102,238,28,176,223,163,157,228,119,72,210,228,7,74,
235,12,17,61,239,162,131,140,15,101,43,65,106,58,128,202,85,102,0,93,197,185,208,127,71,71,71,88,95,95,199,116,58,67,89,54,236,128,22,134,181,65,194,47,172,108,27,167,216,185,54,88,131,55,200,81,75,234,
129,139,242,126,102,103,236,36,171,91,205,100,232,244,134,215,159,254,244,167,120,229,149,87,112,249,242,101,124,248,225,135,225,45,30,71,71,71,216,218,218,194,100,50,73,92,229,39,79,158,192,123,31,62,
122,34,217,47,5,250,82,211,213,171,87,241,228,201,147,16,127,230,244,233,192,178,168,223,138,186,206,243,231,207,227,220,185,115,129,233,72,153,64,236,161,104,125,64,107,110,151,47,95,14,46,36,80,109,
161,160,246,231,152,19,157,203,62,213,128,66,27,251,84,54,122,93,15,141,229,234,135,90,103,60,57,167,19,46,159,140,181,73,153,199,105,99,149,38,171,190,124,203,102,84,17,155,118,101,101,94,139,99,29,101,
2,21,117,148,168,203,193,153,83,124,14,100,226,14,3,0,221,157,32,131,166,206,147,29,99,117,18,229,151,64,225,203,116,23,112,168,170,44,195,69,11,229,224,225,235,199,117,30,60,124,128,243,231,206,227,194,
133,23,162,114,7,7,7,201,222,43,211,213,67,51,97,68,121,52,246,101,4,253,11,58,36,57,83,191,18,162,190,227,215,138,231,129,126,137,53,3,180,2,111,239,100,50,193,245,235,215,241,242,203,47,227,234,213,
171,184,117,235,22,188,247,184,127,255,62,206,157,59,23,94,121,205,229,238,237,237,225,228,228,4,87,175,94,77,216,245,108,54,195,206,206,78,88,59,122,242,228,9,86,86,86,130,219,8,84,147,205,253,251,247,
35,111,162,44,75,108,111,111,99,105,105,9,155,155,155,73,191,240,188,60,78,218,12,181,233,225,195,135,88,91,91,139,244,159,78,167,120,240,224,1,78,78,78,240,255,245,246,101,219,113,228,56,218,96,100,202,
218,44,111,146,170,167,108,215,218,85,53,23,243,38,115,230,161,230,126,230,126,94,173,207,153,174,197,75,121,43,203,182,36,91,123,6,255,11,6,72,0,4,64,70,218,243,179,219,165,8,18,4,193,237,227,7,38,35,
98,107,107,203,104,156,242,215,243,44,172,118,102,227,28,248,2,86,188,139,182,11,71,89,52,101,190,30,219,235,57,62,17,2,64,248,159,255,249,159,152,110,108,198,32,227,100,60,29,112,242,141,163,133,224,
4,160,195,53,76,238,93,73,43,190,29,79,227,229,83,29,222,163,58,30,179,163,191,219,122,64,168,129,17,181,137,219,207,243,33,19,147,239,255,194,108,249,149,46,147,155,45,39,173,218,7,83,225,30,136,84,182,
208,186,56,242,212,117,245,126,245,161,65,130,155,21,230,184,51,94,158,150,123,178,110,154,55,145,188,224,129,64,171,156,116,157,198,122,153,152,0,160,180,189,166,91,46,176,18,248,62,199,29,180,22,124,
180,206,146,151,58,67,40,111,28,181,202,100,186,8,169,208,100,54,150,75,88,210,159,135,233,95,45,78,78,96,249,87,115,9,165,78,171,12,0,65,149,5,187,147,242,159,51,9,242,249,142,6,123,176,100,74,209,250,
164,242,152,38,198,225,67,214,150,140,22,175,213,221,210,207,236,113,78,122,207,41,191,213,230,17,0,130,160,81,218,226,225,234,136,237,61,46,156,236,220,214,233,63,99,172,104,156,215,94,21,59,22,229,123,
117,150,12,221,211,9,80,239,151,214,11,66,25,91,150,110,154,207,26,107,180,14,149,103,224,140,75,205,219,80,129,69,220,123,117,210,206,104,201,251,22,144,225,245,24,35,127,31,22,6,201,84,170,9,96,84,158,
82,95,175,3,165,46,173,18,217,37,85,2,250,179,210,222,124,175,232,210,208,223,181,109,114,81,57,195,153,30,35,50,220,215,94,230,19,99,253,65,83,109,193,176,116,90,178,86,156,60,68,218,202,215,195,66,180,
64,136,177,201,24,173,208,35,151,217,106,160,44,87,200,44,202,195,181,57,78,25,103,233,215,44,50,246,167,60,133,105,146,241,2,246,164,172,218,77,234,33,50,230,139,10,13,80,144,113,61,110,157,21,90,0,213,
155,223,98,123,244,186,199,182,94,25,102,91,132,214,235,101,120,69,188,231,4,165,191,234,233,157,34,154,50,252,158,191,50,165,106,184,20,89,92,31,3,160,80,175,6,84,108,64,64,57,105,139,121,228,107,107,
165,173,57,127,168,127,37,145,204,212,90,133,173,21,95,107,23,107,128,247,176,8,169,167,197,178,186,88,82,168,127,169,156,149,191,17,178,203,100,140,117,6,44,49,102,146,78,219,182,98,14,104,39,40,99,170,
195,85,210,92,49,77,166,55,93,142,91,90,55,90,47,75,111,15,35,106,197,107,224,110,237,101,75,226,66,227,232,227,71,150,157,45,251,233,216,28,22,67,253,122,153,50,233,8,98,78,103,45,216,11,223,2,97,33,
80,6,62,5,45,205,101,212,38,31,3,147,33,240,125,31,60,171,20,185,172,156,252,218,117,175,59,34,193,132,254,229,215,168,175,177,58,24,171,172,58,104,130,96,110,32,87,240,114,202,88,179,151,169,114,218,
217,114,181,66,64,219,172,170,212,224,38,211,254,175,66,75,63,75,231,171,89,185,36,242,146,121,211,32,95,190,231,77,112,107,76,89,19,83,155,7,86,136,198,181,150,175,53,175,40,152,122,222,140,87,15,0,254,
225,218,22,64,203,197,129,158,116,247,129,139,250,195,58,176,229,119,186,91,140,41,55,134,242,76,158,198,22,226,232,127,198,203,251,235,229,1,32,192,5,53,200,121,249,72,100,197,122,82,60,254,113,216,150,
178,130,120,101,205,182,13,108,183,45,149,215,214,211,2,48,252,43,1,136,126,152,212,171,71,47,56,245,76,74,158,1,11,152,87,78,37,215,193,20,10,3,107,191,72,80,205,31,149,133,91,181,89,95,168,180,73,40,
175,103,183,95,35,120,224,106,213,129,141,61,172,67,138,72,215,76,39,101,173,101,221,136,17,159,37,12,83,124,96,109,159,188,148,152,117,69,177,200,23,98,192,219,99,41,207,117,180,92,67,43,29,39,131,165,
79,210,71,128,122,19,178,98,75,35,185,134,88,6,183,242,75,162,53,97,91,245,64,93,212,65,208,126,238,239,237,120,43,206,74,211,218,133,197,171,90,8,136,42,122,45,157,90,126,26,180,122,88,105,52,190,71,
23,75,155,24,165,136,108,230,99,233,17,42,29,61,238,141,21,167,165,73,128,241,38,56,151,229,191,254,81,153,185,139,159,44,223,186,150,229,104,139,85,43,13,232,207,231,50,29,248,152,99,204,40,31,24,166,
182,194,4,88,11,229,201,6,100,82,19,104,153,109,153,45,201,233,75,90,217,222,119,89,89,113,35,121,150,80,75,71,67,100,57,38,91,200,160,228,119,108,27,148,166,106,171,64,130,40,206,169,167,54,8,228,181,
44,199,146,177,64,138,202,106,131,53,70,123,115,222,10,26,251,84,20,235,58,91,249,148,178,164,77,61,204,64,123,179,67,143,251,215,51,161,231,234,244,229,201,216,67,6,136,147,83,60,115,23,128,247,39,125,
199,155,181,32,229,184,168,191,235,66,101,249,64,152,162,200,39,221,46,79,143,87,119,111,60,50,91,148,113,46,211,173,135,159,211,109,107,172,148,113,25,240,89,194,68,197,196,170,55,205,225,106,111,5,55,
162,141,78,51,139,37,29,215,156,76,85,222,84,146,198,32,104,217,30,171,211,66,75,78,75,183,116,105,31,115,72,182,207,7,214,22,200,22,230,21,89,127,83,91,89,95,4,225,236,166,165,175,42,3,160,118,139,81,
60,201,240,123,143,113,245,132,185,224,146,229,38,99,112,192,235,19,134,231,248,28,150,197,238,139,135,226,203,1,111,83,156,55,97,218,3,165,103,239,146,231,192,91,190,201,168,114,205,106,134,109,45,168,
222,34,171,49,189,54,152,215,99,173,117,205,117,248,233,12,138,99,41,107,201,106,78,88,94,110,66,214,42,192,0,140,110,142,105,21,232,173,56,202,106,247,248,215,123,230,111,14,11,244,202,208,100,188,244,
30,144,162,241,214,32,241,216,27,166,83,189,214,209,17,181,252,40,30,217,17,253,51,93,184,224,58,137,52,234,217,183,47,36,237,245,210,213,182,204,249,140,95,203,122,202,193,9,210,99,23,149,13,228,190,
99,92,107,199,24,180,242,44,214,227,233,247,242,244,50,160,124,205,29,12,181,204,204,26,41,73,129,122,81,167,101,211,127,218,194,91,242,165,87,62,176,56,24,0,66,100,186,135,97,97,189,34,185,54,220,66,
111,26,44,247,70,99,40,189,236,195,74,179,202,208,26,78,139,195,60,61,161,181,226,81,219,172,23,206,245,184,79,185,237,98,25,12,158,173,189,224,111,201,132,16,248,226,4,5,6,228,194,211,91,118,93,144,22,
69,247,32,117,160,203,94,152,81,76,64,86,226,48,237,30,91,43,80,145,253,42,153,171,49,249,180,54,210,158,135,165,215,133,181,242,177,161,130,83,8,38,88,86,178,162,110,116,172,170,118,24,63,188,84,236,
43,214,227,131,189,181,99,6,11,163,158,26,253,52,96,177,147,158,145,75,229,196,56,38,151,80,78,100,109,114,107,6,89,43,255,92,128,64,106,108,188,111,64,13,61,180,215,178,197,98,35,30,117,150,58,123,104,
180,103,7,213,93,217,33,142,118,180,236,233,117,195,164,61,114,53,164,105,84,239,214,214,22,220,187,119,15,198,113,100,15,228,202,176,185,185,9,247,238,221,131,24,99,145,83,68,55,183,54,153,62,143,137,
200,137,86,198,18,128,166,156,190,69,193,210,213,147,230,233,32,216,225,46,228,250,194,9,0,80,123,11,236,62,214,223,56,212,192,185,117,77,239,181,133,91,179,179,85,135,210,6,124,78,91,216,96,1,101,5,124,
14,19,196,191,250,103,190,200,234,110,85,64,94,83,183,205,218,184,151,135,207,122,116,247,178,176,57,108,205,178,93,115,207,84,125,16,166,55,47,248,192,103,149,103,45,4,214,61,78,14,166,147,110,98,84,
242,125,245,160,50,8,94,90,223,1,164,247,44,221,187,119,15,190,249,230,27,120,240,224,1,252,243,159,255,84,63,150,112,126,126,14,247,239,223,135,199,143,31,195,253,251,247,77,185,179,179,51,184,127,255,
62,124,243,205,55,174,92,15,171,236,1,154,22,27,244,38,185,29,215,118,13,181,114,211,49,146,249,128,138,101,23,153,218,143,243,38,127,111,25,49,162,234,140,200,229,90,177,195,243,200,122,242,244,120,69,
20,95,22,255,254,239,255,254,159,8,40,97,168,65,5,169,155,28,220,154,97,49,198,252,142,115,218,56,50,143,118,223,74,147,247,116,37,109,161,116,139,170,210,114,61,182,98,165,209,183,182,86,114,49,230,149,
49,64,237,219,91,255,188,114,3,144,111,20,18,249,94,64,183,66,254,49,69,89,56,62,126,252,8,231,231,231,112,112,112,0,251,251,251,112,114,114,2,55,55,55,149,142,211,211,211,252,122,23,124,13,244,245,36,
23,20,57,250,186,104,170,15,251,2,235,88,253,19,246,201,251,32,218,37,132,178,208,224,88,31,66,234,183,97,49,164,175,20,15,229,31,61,123,88,233,12,80,116,41,125,85,149,27,2,49,93,59,164,203,221,98,21,
112,98,20,46,33,186,100,80,210,209,6,64,204,177,193,41,8,89,180,151,166,73,91,208,86,215,78,113,191,187,187,203,238,173,249,108,225,1,141,11,67,128,197,127,252,199,127,252,39,186,100,204,104,182,162,219,
19,66,26,128,159,46,90,119,242,123,229,88,64,73,67,47,24,90,101,106,116,217,211,45,255,85,105,212,54,168,59,161,5,172,234,10,102,200,91,244,220,210,85,77,70,8,110,125,206,207,207,225,228,228,36,191,138,
247,236,236,44,191,9,19,229,66,8,112,126,126,14,167,167,167,176,191,191,159,229,174,174,174,24,208,0,36,70,246,241,227,71,216,223,223,135,195,195,67,56,63,63,135,203,203,75,2,46,3,3,121,8,33,79,48,15,
232,123,23,133,156,39,150,5,48,215,155,176,215,210,238,177,188,128,47,78,242,35,111,47,174,103,132,24,211,73,113,42,39,251,63,146,178,204,241,5,211,27,74,167,5,144,142,45,140,243,250,158,246,79,154,239,
144,193,63,95,43,99,67,94,83,136,179,101,210,253,48,12,25,176,212,69,85,148,87,165,231,184,116,63,12,3,255,106,142,188,150,136,219,2,33,25,52,6,166,85,204,250,75,41,98,143,60,149,81,129,87,185,183,244,
243,107,228,201,83,124,74,108,234,206,131,195,91,233,196,64,211,64,200,107,27,25,188,120,173,63,212,50,129,15,38,90,54,130,212,222,222,30,108,110,110,154,79,227,35,35,219,219,219,131,91,27,27,112,163,
184,124,0,0,39,39,39,89,110,185,92,170,172,77,179,131,150,167,130,186,211,230,86,186,26,167,28,139,160,247,8,242,186,125,68,70,109,85,244,184,136,43,196,11,170,198,163,85,103,111,30,83,125,99,143,156,
161,23,239,173,246,208,22,119,107,140,101,230,140,233,16,97,8,67,30,163,172,77,98,204,236,148,125,53,71,22,234,197,125,110,186,135,204,244,90,205,75,246,195,172,96,189,171,158,55,28,62,58,32,58,110,90,
201,185,108,105,35,237,11,204,86,29,42,153,0,121,245,110,129,178,166,159,14,130,220,153,164,61,232,0,145,143,73,185,118,57,118,99,88,44,22,240,243,207,63,195,237,219,183,225,201,147,39,240,215,95,127,
177,227,38,232,26,15,195,192,228,142,142,142,216,87,179,165,190,221,221,93,120,242,228,9,188,127,255,94,145,147,19,100,62,56,89,65,251,102,164,188,198,182,181,24,176,236,63,11,188,100,158,32,250,43,231,
193,184,40,243,0,84,145,24,35,198,171,54,174,42,182,111,212,71,179,9,131,215,94,244,190,245,215,210,133,139,131,182,40,97,93,236,135,159,149,56,108,8,11,224,164,33,222,36,236,5,72,4,21,188,70,164,149,
135,38,173,206,170,145,154,234,230,123,7,185,124,140,11,192,127,173,139,132,53,65,189,250,37,25,123,47,44,131,11,143,133,24,75,27,83,0,160,122,52,157,121,53,130,122,128,3,148,190,160,175,140,150,193,26,
28,50,32,184,224,103,164,222,190,125,171,214,111,177,88,192,47,191,252,2,59,59,59,240,251,239,191,103,57,217,23,203,229,18,126,254,249,103,216,222,222,134,95,127,253,21,222,189,123,199,218,68,11,61,172,
169,133,93,169,15,128,185,64,113,28,145,54,19,59,177,15,234,178,61,32,90,199,110,45,132,201,158,210,102,233,190,210,105,232,246,60,27,57,174,164,78,45,13,0,212,55,47,104,30,2,157,107,248,15,15,87,115,
54,201,199,45,213,97,129,92,245,2,63,122,61,103,69,70,163,112,149,181,88,130,4,187,236,94,73,57,81,22,64,234,174,64,89,195,148,87,218,229,217,216,100,131,202,175,153,172,46,22,152,73,185,108,160,158,230,
181,177,199,116,104,27,150,190,148,12,196,7,166,185,97,185,92,194,47,191,252,2,219,219,219,240,219,111,191,79,224,82,175,174,27,27,27,89,238,159,255,252,103,6,33,201,108,81,223,214,214,22,252,246,219,
111,2,172,234,208,15,180,1,88,87,89,238,15,112,158,22,196,121,41,207,5,236,137,247,130,5,16,218,4,213,174,91,110,92,203,214,57,174,159,150,87,202,181,88,151,182,101,176,78,29,176,236,244,240,51,20,106,
153,254,244,131,23,166,201,202,88,44,204,125,54,78,0,152,4,49,165,224,170,82,54,35,161,43,65,26,216,117,195,5,0,208,92,201,97,146,7,200,174,161,104,211,20,71,24,96,18,173,108,235,89,169,235,106,54,128,
145,197,57,236,206,92,128,0,52,87,11,99,150,203,37,60,127,254,12,110,110,86,112,121,121,9,203,101,253,86,89,128,244,181,234,231,207,159,195,106,117,3,23,23,151,149,123,135,117,95,46,151,240,244,233,83,
184,185,185,134,139,139,139,102,59,104,204,178,117,109,201,99,144,19,201,100,48,226,222,114,229,36,19,227,114,58,99,105,217,173,5,127,139,35,157,26,151,109,210,83,110,148,118,48,29,124,81,144,158,73,140,
213,84,52,93,59,254,215,102,121,86,191,166,131,163,196,20,45,104,238,20,117,13,233,95,218,64,217,125,18,43,9,213,179,162,52,20,211,196,164,102,148,54,214,46,87,147,53,57,19,222,186,230,54,175,116,144,
16,123,71,212,116,13,156,42,151,80,46,245,64,88,96,4,245,152,65,101,131,1,78,57,141,82,106,106,15,148,195,186,49,160,49,162,13,166,191,23,23,23,236,215,64,43,104,114,218,100,241,244,81,119,76,79,23,122,
167,241,43,203,177,220,26,189,188,178,24,229,184,169,253,123,0,81,6,100,191,69,190,205,34,44,96,153,15,206,237,199,129,76,59,28,160,243,64,37,121,87,117,58,253,197,84,215,161,129,152,95,30,115,9,53,151,
141,6,58,8,180,67,134,139,197,194,125,117,49,45,71,147,241,174,231,128,143,87,70,111,185,97,24,50,243,84,153,94,89,66,83,28,101,145,82,6,229,38,157,138,49,69,207,140,80,175,176,117,58,181,33,64,221,22,
189,19,58,235,107,200,90,192,209,163,159,228,106,218,55,228,186,241,99,1,149,166,70,125,45,251,186,221,66,39,239,0,122,155,104,139,191,92,220,169,125,5,24,200,103,150,65,159,232,246,162,107,47,244,189,
192,228,181,137,180,29,203,162,120,96,185,135,22,33,210,210,151,171,113,53,61,219,53,143,153,72,195,240,90,251,110,26,213,39,27,78,235,32,41,39,89,154,108,164,22,203,240,6,129,86,54,0,64,160,229,41,131,
11,164,126,162,111,37,116,230,208,241,48,172,180,67,198,91,129,15,22,168,190,42,221,83,166,11,94,33,228,54,153,101,23,121,228,42,106,211,27,177,189,241,40,146,109,91,113,239,181,1,79,239,231,128,179,5,
6,173,201,171,181,163,28,187,45,38,37,227,121,251,182,159,147,181,0,210,75,211,108,180,112,160,85,119,171,205,232,15,74,210,246,30,70,60,12,3,44,145,66,104,232,72,43,170,55,30,15,188,44,172,44,86,88,3,
68,126,47,175,11,58,7,53,95,186,78,171,78,101,87,208,221,71,46,66,227,185,43,130,175,37,246,58,82,211,151,210,89,108,179,108,13,140,229,125,47,128,97,220,72,94,126,216,195,220,100,95,183,202,233,9,249,
121,49,199,197,147,178,16,117,176,176,236,233,102,66,44,190,254,53,81,99,31,30,8,90,12,137,166,37,249,0,33,144,185,101,216,95,129,73,3,60,45,208,179,218,14,63,50,235,233,145,96,227,245,131,5,50,178,141,
180,239,13,74,61,94,144,237,210,117,14,203,42,168,110,120,90,225,105,127,4,234,14,45,128,168,83,73,205,80,254,115,63,29,20,229,67,176,204,102,103,176,91,236,10,179,201,85,71,214,87,235,44,46,223,112,55,
169,167,8,0,3,244,189,225,180,5,188,189,125,215,11,64,179,128,42,20,142,132,110,116,102,86,141,65,73,3,61,46,210,195,40,45,89,57,81,36,75,145,206,92,53,46,112,161,205,56,42,198,251,200,39,166,180,171,
220,251,159,163,215,238,61,121,77,182,231,53,54,224,48,25,107,193,44,89,91,174,170,50,47,166,255,133,33,181,97,15,187,179,254,82,249,165,58,161,166,10,202,74,200,21,88,178,161,24,167,239,18,98,65,14,24,
105,141,162,93,107,149,195,225,54,228,198,169,229,180,188,86,25,82,126,206,43,146,67,8,93,242,172,99,136,3,20,12,249,86,217,245,4,68,32,135,233,218,118,161,242,198,172,180,209,180,160,109,35,196,250,49,
164,222,48,11,208,102,76,100,0,123,44,13,97,96,21,214,94,194,200,216,130,60,194,50,232,178,114,98,74,166,102,45,208,244,90,91,28,53,253,154,171,69,117,69,28,16,36,109,196,51,103,20,179,113,204,52,158,
19,100,127,21,98,160,2,239,104,131,80,139,205,105,229,46,213,9,94,234,80,53,158,231,18,141,227,200,79,152,203,70,204,172,43,102,234,239,173,166,21,69,39,172,45,64,249,213,203,98,77,84,135,180,189,53,192,
100,249,9,40,133,203,20,74,189,211,109,200,43,179,28,124,124,240,215,19,218,106,87,119,117,11,101,119,8,255,75,223,131,175,7,82,142,108,51,209,54,61,64,50,135,133,245,2,211,186,114,30,211,145,97,132,17,
66,92,131,1,206,144,213,228,241,222,251,192,168,23,167,45,180,214,184,46,108,135,235,140,226,23,61,45,175,22,212,120,225,46,104,238,63,245,140,100,221,88,61,155,77,27,10,195,234,249,117,207,187,70,166,
193,124,249,178,163,202,238,181,50,123,202,232,13,150,251,70,211,189,188,185,76,101,66,71,172,195,244,95,62,73,70,0,176,1,112,82,49,49,161,210,22,148,209,242,226,106,150,22,138,130,90,30,128,29,130,44,
241,229,116,190,171,159,28,211,240,194,151,0,148,222,188,20,152,83,148,238,138,201,124,218,66,232,177,111,207,110,89,174,87,94,15,235,147,227,19,191,152,196,143,81,148,101,45,198,152,199,98,15,83,177,
192,46,150,202,48,57,188,238,153,23,150,13,154,108,8,33,31,109,144,237,147,254,138,254,35,43,121,78,39,67,50,4,242,17,138,30,134,130,247,102,131,136,138,151,149,60,253,65,234,170,13,18,139,42,107,114,
148,3,74,183,52,21,23,25,56,122,46,223,231,184,98,149,109,10,88,180,202,145,180,93,235,92,204,223,2,0,143,253,122,65,107,163,254,204,160,206,229,166,190,80,22,48,139,133,208,34,146,206,114,215,195,74,
180,73,152,93,191,108,247,244,104,148,241,152,72,79,232,157,192,166,141,202,83,3,149,238,70,58,117,61,53,166,153,211,149,199,180,184,77,5,48,83,188,254,184,147,117,194,189,148,151,116,164,99,83,168,35,
78,122,101,249,22,208,166,62,193,180,113,28,249,167,234,61,86,210,222,71,169,18,85,57,186,210,107,141,93,228,189,1,163,175,154,236,72,5,240,195,172,172,124,5,124,187,128,75,248,254,221,0,33,234,231,150,
97,220,203,248,58,61,192,48,16,16,48,78,188,83,61,129,71,8,109,122,92,107,26,123,172,199,138,159,195,128,49,221,27,143,222,226,90,47,6,211,211,9,192,25,168,156,244,89,94,184,61,21,88,9,226,32,199,158,
85,79,111,43,66,198,245,140,91,111,140,183,216,82,170,239,232,166,247,164,133,16,242,219,55,146,78,0,128,118,94,0,72,175,227,129,122,238,178,119,186,231,87,243,134,226,70,80,97,121,45,27,11,1,163,5,110,
72,129,243,75,210,148,95,213,196,153,112,119,66,183,88,98,43,88,131,1,27,61,119,120,195,221,99,160,91,132,0,226,228,72,34,155,18,65,99,157,242,94,163,212,60,29,50,83,232,105,143,106,16,59,191,52,121,250,
214,113,215,123,100,44,181,52,123,111,127,123,19,182,199,62,22,39,152,97,85,127,121,107,120,18,121,108,17,22,33,203,242,152,25,198,181,216,169,167,75,254,213,126,109,52,217,99,244,189,45,237,158,56,18,
140,164,168,242,1,4,2,16,192,202,25,39,84,163,44,72,130,19,253,171,189,194,133,27,104,79,64,172,116,18,132,74,126,80,38,171,118,95,129,167,172,40,161,5,158,59,167,234,90,35,148,129,40,234,175,232,101,
29,19,40,150,233,160,166,45,6,173,58,217,26,137,13,36,175,53,0,177,236,222,9,210,10,30,240,167,244,190,188,37,96,223,241,137,76,101,187,126,254,111,133,105,81,232,153,168,90,124,143,140,230,154,182,126,
193,179,116,243,47,123,251,178,45,15,203,98,109,204,6,40,139,95,8,161,250,5,83,91,112,93,48,77,55,0,128,7,71,137,160,69,169,229,170,32,43,72,243,201,65,225,201,107,0,145,113,135,53,88,61,221,202,163,25,
118,57,181,158,118,250,28,215,55,198,250,67,167,24,47,1,93,118,108,5,62,145,62,235,167,47,22,154,123,99,117,188,180,61,182,210,113,177,162,187,156,30,155,89,31,211,215,0,61,254,176,186,7,204,82,70,155,
132,115,192,166,207,190,47,7,86,85,219,56,251,91,0,144,231,128,108,145,152,39,185,126,62,48,101,245,199,85,21,2,127,239,150,7,52,90,240,250,189,165,107,140,233,4,66,254,106,142,28,252,82,113,107,144,172,
179,242,87,46,87,8,128,141,138,39,205,39,201,154,157,36,5,230,128,244,86,11,47,221,235,60,15,104,181,58,91,224,167,129,63,13,26,8,182,210,189,21,209,146,97,241,161,184,234,61,121,180,224,14,86,186,63,
20,237,241,224,5,173,159,98,137,32,101,85,138,205,50,90,160,175,125,6,76,210,63,107,178,206,153,208,30,80,89,159,225,98,118,102,95,11,114,3,48,29,228,71,133,22,224,164,166,48,206,139,137,49,174,185,165,
178,94,180,201,44,102,221,114,23,241,157,251,203,50,177,202,187,132,172,175,167,208,130,172,251,158,60,58,179,226,249,172,95,242,36,16,204,97,80,189,224,147,174,35,180,104,132,7,58,218,224,237,5,17,239,
75,210,49,198,252,249,111,79,135,150,230,49,12,47,223,151,144,163,193,99,122,24,172,237,6,69,89,146,35,204,48,47,115,206,36,179,202,150,233,248,114,0,150,71,97,203,40,195,226,167,83,222,0,80,206,16,118,
176,187,10,40,22,182,188,198,58,243,118,14,150,55,109,59,104,111,255,232,113,243,188,114,181,32,109,26,157,239,30,78,23,102,57,50,44,173,207,114,209,96,51,16,156,212,244,111,249,25,212,204,23,99,238,244,
4,230,33,199,1,106,210,26,111,146,203,4,55,132,178,134,116,128,152,180,39,47,70,90,26,113,165,66,176,30,205,157,7,234,218,234,130,171,153,12,218,64,244,246,12,173,182,238,117,25,173,242,165,204,124,119,
174,214,107,177,120,75,190,167,140,81,123,173,138,226,218,90,101,90,43,127,203,70,151,49,73,70,211,112,239,230,186,143,50,78,218,29,189,50,100,29,13,224,194,64,227,117,207,104,146,195,61,171,104,63,155,
74,117,160,157,0,56,239,185,27,203,60,18,0,88,102,168,49,6,18,45,212,99,73,168,120,185,220,168,100,88,165,167,242,16,124,60,214,35,57,78,43,94,179,93,11,185,174,10,72,85,171,111,74,100,67,205,2,55,86,
191,78,187,146,235,219,97,107,202,152,108,81,250,138,182,225,220,246,104,5,89,199,94,93,235,150,135,101,246,148,87,79,72,0,11,161,184,168,237,162,201,73,79,51,107,188,155,171,181,223,255,84,149,69,220,
55,26,122,63,113,47,175,45,192,83,203,54,242,104,139,27,99,105,25,240,168,46,252,19,1,228,163,56,16,179,44,234,129,234,247,63,90,190,30,31,99,132,17,0,150,244,107,38,61,174,151,23,23,99,44,159,105,114,
88,90,153,128,156,202,87,114,130,227,87,143,198,116,216,163,187,122,32,210,211,48,180,58,79,150,163,221,23,155,49,93,77,86,117,91,171,41,175,71,238,107,204,53,165,59,19,122,98,134,61,174,224,231,128,139,
21,84,183,41,37,52,229,101,156,203,178,98,155,189,180,116,104,11,86,61,201,129,79,62,67,207,156,50,45,59,52,25,203,13,149,253,139,94,3,5,207,252,107,93,4,128,160,123,65,52,120,250,1,160,218,87,51,219,
77,178,204,24,115,164,215,214,22,200,46,241,245,191,189,224,52,221,229,9,73,101,181,115,88,238,164,207,189,79,210,162,35,167,4,73,29,41,36,105,3,80,99,140,161,177,217,108,173,242,214,125,23,216,133,186,
94,189,160,161,49,65,141,158,35,51,196,65,162,213,211,205,111,200,172,19,56,83,20,171,245,20,52,214,88,213,147,236,207,200,56,42,229,47,24,117,156,202,174,133,27,52,169,102,246,73,123,245,2,185,141,115,
93,63,13,56,57,11,244,245,197,40,126,189,87,138,108,45,22,38,243,66,117,162,157,98,140,213,71,43,180,208,122,194,64,222,47,51,78,40,134,72,119,175,196,217,251,84,217,223,52,38,47,6,169,211,155,48,150,
62,207,77,241,0,163,21,167,53,154,117,124,161,186,15,229,167,95,4,38,250,168,80,150,29,249,35,25,218,19,247,45,55,104,206,234,72,105,172,6,12,116,193,160,155,179,235,128,20,213,69,139,86,87,77,197,102,
45,88,192,37,148,76,44,84,180,37,109,175,0,249,171,72,114,178,228,254,138,117,127,201,128,123,102,236,201,2,10,162,198,196,243,38,100,15,43,148,32,145,255,78,99,79,67,99,201,106,169,45,218,220,178,216,
78,4,101,174,10,146,128,65,243,118,64,205,15,185,205,123,234,173,62,154,99,85,160,5,44,147,150,105,117,35,44,204,248,133,66,222,235,44,14,109,42,241,84,38,217,201,251,74,154,166,129,102,15,213,166,113,
248,203,92,211,53,36,29,155,238,241,143,2,2,216,190,0,236,151,191,94,128,157,19,180,55,144,214,140,187,15,8,91,113,26,35,176,88,170,231,242,105,113,242,17,26,212,95,46,200,235,115,38,121,160,125,42,92,
148,170,76,220,131,105,176,22,140,167,114,116,227,95,78,124,143,21,83,32,247,0,157,233,203,181,5,94,63,197,70,122,29,48,47,241,54,40,209,80,221,62,9,40,29,224,18,99,249,48,106,138,228,11,132,124,60,207,
210,35,239,151,114,32,245,176,20,203,237,75,76,164,60,222,67,3,221,127,106,177,159,92,165,136,125,65,229,235,202,20,29,109,102,199,108,234,113,251,28,102,66,247,214,38,139,117,29,202,61,174,136,81,73,
247,0,118,14,139,108,213,173,149,87,246,243,156,96,179,197,194,206,53,230,218,98,116,146,209,107,121,53,118,36,219,212,90,152,0,228,171,95,176,29,108,155,228,164,99,11,252,164,196,98,151,26,25,240,202,
104,77,106,156,47,18,96,240,142,125,249,89,252,234,92,177,161,65,183,169,44,198,40,55,136,241,25,115,187,209,254,101,46,38,132,58,206,32,71,24,22,139,5,127,150,80,53,202,185,214,210,220,65,62,209,160,
10,245,133,142,218,232,210,0,90,133,44,6,232,85,190,197,28,179,77,129,116,36,24,32,40,128,171,213,78,90,57,60,153,158,65,131,170,238,90,61,180,182,192,224,14,186,142,80,77,234,105,121,159,13,102,202,34,
214,2,168,94,23,177,39,120,46,169,166,183,7,64,10,12,235,121,52,86,52,167,188,58,46,243,170,210,231,148,185,68,0,237,45,167,154,17,173,254,203,44,136,141,123,28,103,80,82,149,115,86,180,236,158,111,19,
82,94,34,101,240,239,56,142,245,43,146,153,146,153,43,50,230,179,92,11,153,203,91,249,233,215,138,123,89,160,103,83,111,94,100,62,72,239,98,140,236,131,20,185,161,169,30,101,149,150,98,90,123,114,208,
101,86,144,213,222,63,112,106,49,7,43,168,117,22,123,57,205,60,13,183,202,80,2,65,136,107,110,129,23,214,5,183,117,229,168,172,181,0,68,69,86,222,71,208,250,56,197,83,55,85,67,52,29,196,198,44,235,3,158,
36,7,149,42,147,60,72,112,87,207,185,9,157,149,219,24,66,19,172,138,165,80,189,88,16,160,94,168,151,218,67,198,153,202,130,62,193,61,22,163,53,128,53,185,116,183,142,183,68,96,81,58,109,108,177,62,43,
173,71,158,155,68,55,167,73,163,139,58,33,45,70,49,115,176,27,64,74,211,122,236,215,130,87,166,76,47,46,188,254,238,163,162,147,218,87,228,215,97,59,154,109,188,44,191,31,122,244,22,29,156,197,246,234,
214,218,95,142,65,203,38,186,16,153,236,88,28,219,1,32,32,102,232,206,215,6,80,120,115,138,247,159,237,93,20,29,26,39,244,65,178,2,45,160,109,81,231,227,76,12,237,208,89,89,122,31,150,50,249,37,210,174,
227,50,246,186,148,86,158,168,200,106,111,40,149,43,72,34,71,122,157,172,242,221,250,6,126,150,169,85,39,9,20,22,59,108,181,169,22,114,94,121,62,45,131,104,89,205,189,178,44,182,102,13,80,59,239,244,46,
169,106,160,215,110,139,85,118,95,57,243,242,74,249,244,213,26,254,177,79,125,221,145,32,159,242,21,182,171,63,204,238,186,129,10,72,74,80,209,64,210,146,241,202,5,168,127,109,214,136,68,111,64,71,67,
211,211,2,31,12,120,212,137,190,159,142,42,231,121,106,38,42,117,46,65,4,175,98,158,155,136,233,218,100,176,86,120,117,181,119,128,193,122,19,4,99,134,162,129,139,112,122,128,82,211,209,3,202,90,121,61,
54,171,118,66,128,17,250,95,117,210,195,0,123,153,215,100,0,3,57,77,143,250,147,63,23,52,93,252,57,118,160,13,230,168,51,198,163,55,73,52,89,141,45,1,112,151,157,199,7,98,96,219,59,240,152,77,107,78,105,
113,85,253,200,98,212,98,56,189,96,226,217,210,203,162,90,122,181,197,148,62,43,171,17,5,109,62,98,57,75,25,217,98,86,24,198,113,108,190,85,192,210,67,7,143,229,114,154,172,141,76,148,94,87,14,0,216,131,
168,158,125,61,46,152,215,54,150,60,205,167,177,32,202,74,82,2,84,39,251,231,176,50,186,24,100,25,166,94,57,30,0,60,93,126,25,134,214,193,42,175,39,204,157,60,235,202,201,137,213,26,211,189,250,44,224,
234,185,167,182,96,176,22,245,156,6,0,116,35,157,206,19,235,252,158,230,101,88,118,81,64,183,8,69,15,227,179,216,162,44,211,251,160,170,103,127,8,65,127,31,22,10,210,191,242,90,254,92,41,193,70,76,63,
179,177,122,226,89,122,212,15,176,217,110,206,148,46,190,38,99,173,184,52,143,6,160,200,226,122,201,68,63,200,180,221,183,49,70,222,166,200,217,181,1,155,50,207,98,103,61,174,99,15,235,156,203,180,122,
221,29,41,238,121,201,248,0,0,32,0,73,68,65,84,63,103,129,237,29,115,86,27,208,114,104,154,4,4,143,109,121,186,114,62,50,113,178,124,18,168,244,55,235,59,45,122,61,245,175,65,148,167,91,215,254,28,210,
221,74,181,30,211,164,106,1,225,178,133,106,125,134,241,193,106,13,222,94,38,83,174,177,147,218,19,66,103,106,50,62,95,129,227,132,76,121,253,83,192,82,55,201,200,227,5,186,181,166,178,231,158,170,48,
135,163,66,212,39,13,114,185,231,199,205,162,101,210,191,89,47,232,139,129,180,247,75,6,58,113,180,137,237,149,43,39,29,6,79,143,140,199,31,32,52,27,180,69,93,198,181,192,171,231,30,143,123,244,128,177,
214,119,200,188,180,114,52,192,205,247,213,241,8,29,204,165,109,90,91,164,248,32,244,116,184,156,4,100,165,157,33,4,250,93,194,154,19,89,134,73,37,180,66,218,10,229,185,142,88,81,173,131,90,11,181,139,
198,121,130,107,157,93,175,208,150,109,214,128,181,0,23,229,172,58,107,204,147,3,92,250,199,226,66,45,167,129,58,211,201,158,46,160,182,180,25,12,77,239,89,176,190,68,200,7,26,149,242,172,113,213,178,
41,217,46,31,35,227,191,132,106,128,108,185,80,45,6,138,247,230,187,209,35,119,194,173,252,22,192,90,128,172,77,254,22,51,242,116,88,233,30,104,90,95,209,201,155,238,13,219,185,39,49,185,191,41,33,167,
199,24,203,251,176,0,218,244,94,51,88,2,133,124,249,92,8,245,171,130,105,3,244,174,222,242,165,100,205,9,52,81,98,10,15,133,230,38,91,238,220,185,3,119,238,220,97,217,66,8,240,241,227,71,56,62,62,134,
173,173,45,184,119,239,30,44,151,203,156,118,118,246,9,142,142,222,185,43,37,0,239,40,111,240,203,213,79,29,172,211,229,221,187,119,225,228,228,4,0,0,182,183,183,97,119,119,55,139,92,95,95,195,199,143,
31,97,28,71,216,219,219,131,203,203,75,184,186,186,154,244,249,31,152,208,222,152,209,154,156,235,6,107,146,206,145,179,6,255,214,214,22,220,190,125,187,202,119,125,125,157,219,109,111,111,15,110,221,
186,149,211,46,47,47,225,244,244,180,203,134,86,154,198,182,48,132,16,84,78,31,194,0,183,111,223,134,147,147,99,0,0,216,221,221,133,205,205,205,156,126,117,117,5,159,62,125,130,113,28,225,206,157,59,112,
118,118,198,190,68,131,186,89,57,142,29,242,126,14,83,181,226,169,13,154,77,189,64,213,186,142,49,214,46,161,231,103,90,44,203,51,204,50,84,171,28,189,175,222,252,16,177,211,73,69,3,148,231,149,208,140,
72,245,165,136,82,47,96,117,217,220,220,132,24,35,27,176,33,4,184,186,186,130,24,35,28,28,28,64,8,1,142,143,211,96,90,44,22,240,183,191,253,13,206,207,47,224,252,236,156,212,157,180,145,168,175,124,65,
162,28,196,148,114,89,174,224,48,12,112,123,119,23,190,249,230,27,248,199,63,254,1,27,27,27,240,211,79,63,193,241,241,49,172,86,43,8,16,224,240,240,16,78,78,78,224,229,203,151,176,191,191,15,31,62,124,
128,235,235,235,186,109,149,199,166,90,15,238,178,131,141,212,54,40,63,87,171,129,83,25,94,71,36,84,242,52,169,162,223,210,37,205,219,221,221,133,131,131,3,248,244,233,19,123,184,28,65,249,240,171,67,
56,56,56,128,15,31,62,0,64,234,155,175,191,254,26,158,60,121,82,129,86,139,81,181,24,152,182,128,49,131,67,26,79,187,187,187,240,240,225,67,56,57,57,134,189,189,61,120,252,248,49,28,31,31,103,249,195,
195,67,120,243,230,13,28,29,29,193,254,254,62,92,93,93,193,213,213,149,218,94,214,130,55,247,141,8,180,126,61,32,98,201,226,252,45,241,200,112,251,23,63,90,78,140,145,190,34,185,143,89,149,47,188,20,151,
4,47,135,97,72,175,148,157,218,167,100,11,104,170,171,187,88,105,128,34,157,220,32,210,113,92,43,235,88,1,43,222,200,227,56,194,197,197,69,30,192,210,166,141,141,13,120,241,226,5,156,159,159,231,248,189,
189,189,244,218,12,208,247,90,100,231,105,76,82,5,17,165,61,240,106,107,115,19,54,54,54,0,98,218,116,223,217,217,129,211,147,19,120,254,236,89,150,221,251,120,7,14,15,14,82,59,139,129,179,179,179,3,183,
110,221,130,147,147,19,5,140,232,43,104,234,54,224,178,60,207,186,193,155,248,115,242,106,105,103,103,103,240,140,180,11,13,219,219,219,240,234,213,43,56,58,58,202,113,227,56,194,214,214,86,5,88,115,236,
138,147,124,84,94,36,128,118,177,251,169,245,182,183,183,217,43,88,182,182,182,224,195,135,15,240,242,229,203,105,17,14,112,121,121,9,219,219,219,121,242,227,2,54,198,17,118,119,118,97,24,6,102,187,198,
92,100,154,118,109,2,20,217,83,162,50,120,224,156,193,98,228,164,166,108,235,164,217,159,242,219,191,136,2,57,136,92,230,124,25,107,139,197,162,254,8,5,22,150,226,74,97,232,70,225,106,204,101,75,225,244,
173,6,140,209,64,185,134,106,184,139,253,160,193,152,192,29,123,22,150,155,137,135,7,121,28,192,131,7,251,112,239,222,189,28,119,115,115,3,175,94,189,130,203,203,203,172,19,101,67,240,87,150,16,2,44,151,
75,56,60,60,132,151,47,95,50,187,31,61,122,4,127,254,249,167,107,63,234,202,95,200,158,226,206,206,207,225,236,252,28,254,246,47,255,2,227,212,95,171,113,100,173,56,226,189,104,175,7,15,30,192,225,225,
33,60,123,246,76,31,152,161,245,34,21,165,221,83,67,176,69,160,39,159,198,214,229,95,153,71,46,6,154,43,77,101,119,118,118,224,219,111,191,205,121,174,175,175,225,253,251,247,153,149,200,227,56,168,215,
123,8,27,89,219,217,217,89,142,187,119,239,30,220,220,220,192,233,233,105,105,191,48,228,246,176,234,71,195,199,143,31,97,177,88,192,87,95,125,149,227,216,251,250,201,124,138,49,230,207,190,143,227,8,
95,125,245,21,220,185,115,7,158,62,125,234,186,112,218,181,22,167,157,44,79,55,245,99,57,158,94,185,24,173,86,218,7,89,3,155,75,158,78,90,183,16,148,99,13,116,184,76,32,159,193,74,11,18,13,45,25,126,95,
42,148,210,116,58,221,114,73,1,32,51,10,117,239,135,229,43,64,137,236,234,175,191,222,194,187,119,239,89,61,30,62,124,8,119,239,222,205,171,28,14,16,106,219,56,142,44,78,82,223,221,221,93,6,220,33,4,184,
123,247,46,60,125,250,180,182,95,97,95,222,71,38,180,107,203,205,254,250,235,175,97,119,119,23,126,251,237,183,60,97,231,208,113,218,86,115,131,156,68,22,171,106,185,39,45,55,132,134,211,211,211,202,214,
7,15,30,192,198,198,6,60,121,242,4,198,113,132,213,106,5,55,55,55,172,237,198,113,204,251,66,154,141,219,219,219,112,113,113,145,235,20,66,128,173,173,173,106,81,107,213,213,170,15,0,103,217,0,229,172,
18,230,31,134,1,66,72,159,126,255,230,155,111,96,185,92,194,211,167,79,97,181,90,229,15,101,200,54,34,145,98,89,137,217,11,210,236,239,177,183,7,180,208,94,47,79,143,30,252,155,223,214,128,202,167,170,
84,7,51,217,94,18,137,7,58,112,66,0,48,206,102,177,60,80,160,67,2,77,15,13,55,25,23,130,45,162,172,19,176,1,86,171,85,245,97,135,143,31,63,102,10,14,144,6,10,221,135,194,213,152,126,77,69,179,91,251,49,
99,24,210,6,235,221,187,119,171,180,215,175,95,231,73,99,237,101,89,245,160,171,47,198,225,253,106,181,130,235,235,235,10,96,123,130,197,86,91,122,180,54,105,214,41,224,226,163,203,107,139,149,180,237,
230,230,38,239,55,98,218,245,245,53,252,237,111,127,131,197,98,193,250,78,230,173,24,150,243,12,157,108,231,71,143,30,85,114,159,62,125,130,15,31,222,171,107,184,166,103,53,174,152,78,244,106,104,63,82,
15,102,181,90,229,189,214,207,101,87,115,100,229,152,176,198,135,71,34,122,22,205,210,70,60,190,122,52,135,22,70,255,182,20,203,189,19,205,240,28,26,110,136,4,37,111,240,203,244,24,250,159,253,219,217,
217,169,126,85,186,127,255,62,28,29,29,193,98,177,128,171,171,43,120,248,240,33,124,252,248,17,0,0,150,203,37,220,190,125,27,94,191,126,157,229,37,48,225,253,225,225,33,220,187,119,79,216,17,225,230,230,
38,239,137,13,195,0,251,251,251,106,135,106,19,22,255,93,95,95,195,238,238,46,236,237,237,101,32,218,223,223,207,192,132,250,94,188,120,1,95,127,253,47,240,227,143,63,194,147,39,79,92,22,225,197,105,97,
206,30,79,218,89,224,44,156,214,152,79,8,61,158,177,171,124,96,37,239,69,64,132,212,63,219,91,91,37,15,36,134,117,125,125,13,113,106,251,253,253,125,198,126,247,246,246,224,205,155,55,194,226,8,18,175,
150,203,37,252,242,203,47,249,126,177,88,192,155,55,111,32,132,144,251,19,0,114,191,156,157,157,65,80,92,68,44,23,251,24,199,203,48,12,176,90,173,96,127,127,31,206,206,206,178,231,113,255,254,125,56,63,
63,39,205,23,225,217,179,103,240,232,209,35,248,246,219,111,179,75,200,172,111,48,209,57,96,69,237,181,228,99,68,198,86,159,224,191,185,185,169,206,182,85,101,197,210,151,94,57,1,2,7,44,111,16,122,108,
136,50,49,169,199,251,50,50,13,222,89,45,143,114,210,107,202,18,165,109,178,1,48,94,50,143,87,175,94,229,77,204,87,175,94,193,157,59,119,242,234,124,125,125,13,79,159,62,85,127,165,161,128,2,0,240,238,
221,187,188,218,135,16,224,167,159,126,2,128,0,23,23,23,112,121,121,9,203,229,18,190,249,230,27,184,184,184,128,231,207,159,51,160,209,234,12,0,249,231,237,211,211,83,120,255,254,61,60,120,240,32,215,
227,250,250,26,222,190,125,11,0,0,23,23,23,105,146,198,8,47,94,188,132,195,195,67,56,60,60,132,23,47,94,168,122,181,151,172,201,246,171,210,228,26,36,30,43,74,25,52,157,211,147,10,205,157,179,58,228,193,
108,236,155,109,109,109,193,254,193,1,139,203,237,18,1,222,190,125,11,95,125,245,21,28,16,153,211,211,211,124,228,33,151,33,76,139,49,129,221,31,127,252,145,109,192,125,167,24,35,188,123,247,14,34,164,
95,149,119,118,118,210,175,142,31,201,38,62,182,67,185,200,247,171,113,5,159,206,62,65,132,8,31,142,63,192,173,205,91,176,191,191,159,179,94,93,93,37,253,49,245,43,238,93,62,255,243,79,248,219,84,151,
55,111,254,98,5,201,125,190,106,175,117,24,242,194,193,230,244,48,48,226,17,83,66,254,81,33,95,147,182,209,8,13,157,147,203,229,242,179,220,74,188,142,49,194,98,185,40,111,28,213,10,155,27,90,212,207,
211,169,157,223,66,29,61,182,72,187,173,85,134,166,127,252,248,49,179,39,77,102,28,71,56,58,58,50,203,199,253,29,154,142,0,120,125,125,157,143,21,80,125,33,4,216,221,221,133,199,143,31,195,209,209,17,
252,245,246,45,115,193,113,144,200,114,0,0,254,248,227,143,28,247,234,213,43,179,45,94,189,122,197,108,66,32,147,245,196,32,25,14,91,252,114,187,2,0,253,133,71,96,70,239,239,134,193,96,215,61,43,189,212,
35,243,159,158,158,186,103,170,46,47,47,211,47,136,156,198,149,203,164,152,199,145,113,68,247,1,233,62,230,98,177,128,135,15,31,194,198,198,6,252,250,235,175,112,141,172,2,117,138,51,132,84,239,234,102,
5,79,159,36,150,180,26,87,240,242,69,249,177,70,182,133,252,209,70,27,3,158,43,70,235,172,206,213,104,244,34,31,16,108,239,75,122,97,22,107,183,72,134,118,157,238,1,112,188,225,28,10,48,189,211,61,83,
118,204,32,220,193,64,227,200,117,122,79,56,78,72,254,234,91,58,81,57,24,0,232,95,169,73,6,150,235,82,89,108,179,162,143,202,26,123,90,78,156,150,230,238,185,144,101,69,158,87,74,43,79,73,199,120,45,196,
24,225,206,157,59,240,221,119,223,193,217,217,25,12,195,0,127,155,86,234,119,239,222,85,46,91,85,142,136,107,213,193,147,77,247,83,141,212,120,85,81,115,127,112,157,128,99,197,90,116,48,206,3,178,214,
126,154,229,98,211,123,45,111,190,6,96,139,73,36,109,241,227,143,63,194,114,185,132,119,239,222,193,131,7,15,0,0,224,236,236,44,51,183,214,162,155,203,9,88,136,110,83,90,208,98,57,255,166,156,157,147,
15,22,211,52,139,4,72,144,179,220,50,141,109,71,122,61,129,222,116,3,33,4,88,161,7,195,218,18,235,0,249,40,136,235,114,78,77,19,66,72,39,221,173,201,170,3,142,125,61,12,244,160,36,128,6,42,120,111,161,
114,13,86,20,28,177,18,29,157,15,53,130,91,193,5,171,82,141,164,159,252,162,137,135,86,241,24,6,150,247,254,253,123,144,237,250,250,245,107,88,46,151,48,142,99,222,251,160,149,206,155,193,169,18,182,45,
96,79,128,86,63,122,64,138,245,116,93,181,192,247,7,125,38,228,247,147,92,224,244,226,230,61,12,109,197,205,205,43,227,63,124,248,0,151,23,23,172,95,78,79,79,243,94,24,61,199,215,163,207,117,187,65,31,
191,57,14,219,52,114,153,246,194,69,31,81,226,164,73,99,51,18,196,106,157,197,177,87,231,216,164,39,191,32,52,144,199,115,34,176,253,46,189,255,72,221,136,204,114,181,90,85,204,165,148,235,63,43,40,243,
141,163,52,194,94,57,173,198,224,13,51,143,70,182,86,14,109,149,77,58,74,121,53,53,245,55,253,229,222,219,56,142,240,238,221,187,42,207,187,119,239,0,0,224,252,252,156,109,210,182,66,207,4,160,118,245,
186,208,37,143,212,203,245,245,41,161,151,180,189,251,178,107,85,108,185,174,90,249,252,124,160,46,104,141,23,174,155,219,126,124,124,92,149,141,91,9,0,0,127,253,245,151,238,98,145,186,200,251,102,157,
156,224,129,95,11,168,211,75,12,181,60,14,195,49,117,250,44,117,24,6,119,111,182,85,214,40,94,153,28,99,132,101,72,119,19,236,78,70,16,160,202,168,59,201,229,117,147,117,66,121,142,144,159,131,169,59,
73,155,252,22,24,201,202,104,178,45,87,137,203,115,187,138,190,2,210,249,209,149,188,10,0,132,192,235,145,117,66,200,143,150,88,110,140,204,163,181,129,215,70,61,249,164,14,11,180,101,208,86,250,26,192,
52,22,236,187,103,0,254,143,40,82,55,103,207,149,20,43,87,75,197,21,152,178,19,170,170,232,181,39,136,100,182,204,18,177,8,107,11,41,181,175,135,221,81,215,75,251,21,109,138,40,140,42,232,125,33,203,105,
245,245,98,49,84,246,201,241,98,233,154,3,54,185,22,98,14,240,178,70,160,204,174,232,72,237,60,198,81,98,43,44,11,228,144,52,5,181,243,0,156,192,141,126,34,72,107,0,9,46,42,75,137,58,11,210,89,156,198,
194,8,208,56,19,10,117,122,108,171,178,49,36,151,79,11,117,222,114,141,84,22,98,100,3,61,20,67,77,16,137,66,222,99,166,84,94,181,95,216,106,213,185,7,88,180,160,150,149,18,242,194,230,45,40,154,30,207,
173,161,19,169,42,83,145,87,235,77,199,169,28,35,104,59,230,161,246,42,139,128,86,142,106,123,224,78,118,239,130,140,121,125,183,169,159,93,89,237,55,135,81,121,158,141,22,47,93,250,42,79,0,48,30,9,159,
250,32,20,246,60,141,213,37,61,20,73,255,210,66,189,65,69,55,255,16,216,84,144,153,10,167,15,180,178,201,18,74,89,214,170,94,85,203,32,28,242,151,59,180,173,151,157,209,123,139,17,234,204,173,214,83,13,
104,3,140,100,25,218,163,18,94,62,107,64,106,54,208,188,235,156,98,159,19,60,187,122,210,231,150,181,78,90,150,49,228,226,180,248,104,192,163,5,171,77,107,38,225,216,162,180,139,5,6,150,140,117,141,235,
41,76,174,47,38,37,211,228,3,203,158,237,244,85,61,124,79,82,46,186,170,77,35,255,197,81,202,200,191,195,48,232,95,126,214,174,35,0,104,95,216,201,215,19,235,26,105,231,146,149,13,25,21,13,35,212,192,
210,178,67,94,231,191,164,60,10,42,236,87,19,108,16,209,48,90,195,74,240,204,114,116,48,34,240,1,175,154,231,146,209,206,164,54,88,118,104,50,189,193,147,237,117,47,231,150,91,152,164,63,41,169,171,83,
250,208,46,131,29,44,52,212,90,54,118,131,178,0,37,44,175,140,27,156,145,194,174,200,229,173,160,246,57,89,192,165,142,214,56,106,141,33,237,245,201,69,46,149,158,244,160,78,124,198,15,65,45,178,121,86,
235,162,35,191,94,76,165,87,35,245,120,192,104,121,19,236,67,170,82,144,102,112,193,138,152,174,82,244,25,0,196,154,131,197,233,238,159,44,131,217,44,221,157,142,9,216,156,152,164,19,56,131,36,127,59,
39,58,50,84,136,178,189,160,154,148,110,157,29,115,229,195,234,235,6,171,30,22,152,106,31,215,148,118,77,23,85,92,181,88,138,9,78,65,206,178,133,94,123,19,151,6,107,225,74,100,164,252,20,95,38,120,137,
155,140,75,223,168,36,11,25,202,33,163,169,38,168,178,217,109,217,70,235,102,187,192,120,173,212,163,217,6,229,109,9,45,91,60,0,234,97,121,22,139,2,48,62,188,10,202,235,101,0,244,206,237,5,25,171,81,91,
121,40,10,207,3,177,18,36,5,213,220,39,205,135,150,122,233,187,223,123,216,79,98,151,62,59,104,129,96,171,205,205,144,59,211,207,35,129,160,119,242,250,69,251,76,16,239,231,48,66,77,143,101,235,186,238,
95,203,38,109,85,7,58,14,148,50,248,186,90,192,138,143,235,148,91,235,107,207,38,173,45,232,88,196,191,99,28,205,133,73,5,10,193,12,165,45,174,43,231,0,15,218,135,127,229,7,145,45,246,168,233,149,245,
100,15,63,211,224,2,13,165,81,162,66,61,131,171,234,156,24,217,132,139,200,71,133,172,214,249,45,91,165,155,40,235,232,1,46,16,59,66,17,48,117,121,193,162,183,45,64,182,6,77,207,224,238,209,103,201,105,
178,115,235,140,50,214,98,196,11,195,63,134,125,218,196,234,60,89,207,242,40,19,67,222,123,99,88,178,231,94,112,152,110,234,67,150,78,94,43,88,250,37,88,225,85,84,220,225,12,6,70,27,74,27,231,108,31,104,
175,74,182,193,14,0,247,213,71,113,128,84,234,138,49,78,31,82,21,111,43,176,38,17,119,127,244,65,232,129,22,213,197,86,10,26,175,165,171,29,11,0,192,247,167,122,24,138,201,222,66,225,71,172,29,228,170,
65,202,178,38,48,107,143,233,239,128,84,25,153,142,209,126,50,206,2,217,117,24,146,234,66,165,2,167,235,232,178,196,57,46,165,53,38,116,64,101,205,172,234,10,1,216,34,6,208,102,180,26,131,208,24,102,112,
250,134,229,133,80,220,92,99,140,20,246,2,106,188,22,34,206,218,6,120,208,235,186,47,3,209,147,99,166,53,87,95,40,45,155,186,60,19,35,206,179,95,202,23,246,74,222,231,175,232,147,215,234,135,84,181,137,
93,226,125,95,154,198,225,53,221,7,48,8,26,239,108,168,187,48,175,112,196,174,113,28,109,176,153,6,147,85,23,26,130,114,197,108,55,192,80,5,1,10,56,34,109,58,39,206,106,166,81,101,143,41,89,109,46,229,
20,195,132,239,226,51,80,43,248,44,45,107,5,96,191,32,121,250,218,140,17,127,200,153,99,155,213,55,152,150,174,35,59,156,168,233,209,226,44,214,98,229,109,219,235,28,192,140,177,154,7,190,174,249,236,
173,229,238,105,249,91,32,6,80,14,142,150,237,150,169,221,204,33,170,151,65,255,46,165,143,9,80,51,145,22,235,162,147,73,251,156,124,182,209,98,56,100,67,189,78,243,239,85,240,192,107,100,109,90,30,193,
152,204,175,220,24,108,10,87,9,175,125,116,106,45,86,254,160,151,161,217,145,196,211,129,58,173,253,210,188,214,87,97,228,79,10,110,49,253,24,172,246,232,5,54,217,167,237,192,1,206,116,223,112,114,43,
243,79,30,177,97,105,51,128,132,149,47,11,82,203,229,227,208,99,251,26,187,163,233,227,24,233,107,229,72,59,148,194,181,186,73,93,218,216,51,221,73,146,166,125,228,148,214,65,243,162,172,197,161,26,215,
98,209,245,60,50,26,77,235,182,100,8,40,86,123,26,39,153,204,220,134,240,174,189,213,88,234,215,244,84,131,68,54,178,98,87,37,163,116,66,210,205,31,17,24,6,255,220,21,141,27,6,58,80,105,91,214,117,164,
127,181,54,96,247,198,18,165,217,70,44,34,105,109,36,145,123,17,214,164,251,236,208,242,9,69,153,121,129,8,194,142,80,218,37,31,21,144,131,158,158,154,135,50,54,192,155,132,18,68,167,114,216,120,82,236,
236,189,6,168,93,162,113,165,51,184,30,118,133,143,194,112,16,28,137,149,250,92,146,101,124,14,75,3,224,31,95,41,96,139,227,188,148,95,22,91,221,171,136,49,178,133,104,201,223,184,192,133,203,117,89,153,
241,77,11,124,146,37,99,52,198,65,175,83,37,106,223,58,9,78,50,234,155,28,44,102,166,79,242,22,11,240,93,94,200,247,212,176,34,87,26,92,93,69,0,242,79,239,227,232,187,204,178,44,186,202,181,242,84,245,
73,30,14,4,60,248,215,218,148,22,125,160,203,215,204,173,29,2,107,159,170,216,26,237,109,19,157,252,101,248,99,2,189,244,79,117,203,253,170,86,153,44,157,124,141,71,230,145,32,209,90,128,172,241,67,221,
116,141,225,200,178,189,45,2,105,151,181,48,123,215,45,89,89,54,173,151,182,153,94,1,246,168,167,97,60,142,191,97,24,97,137,15,67,202,73,204,13,203,41,0,248,252,143,120,190,14,128,191,192,78,26,224,51,
44,178,226,73,38,100,132,126,215,196,7,60,12,115,30,81,241,6,13,174,194,8,8,153,169,16,134,26,17,245,148,129,14,0,234,59,221,123,234,171,177,130,156,134,63,199,56,245,168,131,177,184,52,242,140,35,97,
55,70,86,169,179,222,75,50,216,4,221,255,211,210,201,66,195,153,143,76,183,64,90,31,131,124,108,135,156,155,246,169,197,86,178,173,14,227,106,2,101,7,248,123,0,226,121,66,94,156,101,175,151,78,61,31,111,
193,150,120,128,30,77,173,190,28,110,93,90,123,78,153,98,35,129,202,89,11,195,96,242,228,90,254,242,104,85,78,3,46,213,22,231,90,174,48,154,123,165,237,21,88,178,158,221,238,97,206,8,16,134,254,7,143,
33,70,40,239,5,107,131,180,234,250,138,60,214,128,203,140,107,77,79,238,179,92,64,35,235,58,19,52,128,192,63,209,214,62,19,181,199,153,156,108,90,123,98,60,3,45,3,216,52,29,129,216,27,99,76,158,132,195,
68,101,124,15,96,104,118,107,239,199,210,202,176,242,167,118,197,26,32,176,22,215,206,98,92,216,6,242,99,26,113,114,15,101,121,20,59,106,194,25,38,134,165,60,154,195,42,71,192,74,219,47,210,174,181,198,
105,49,156,57,178,178,130,45,32,147,114,212,102,171,147,52,251,60,48,208,236,170,236,15,0,33,12,6,225,80,98,189,54,113,6,160,101,27,218,215,10,115,220,139,57,129,78,88,45,124,110,57,45,215,222,74,247,
108,144,203,125,140,192,246,37,213,60,160,131,0,77,243,92,52,45,158,234,179,192,199,90,252,61,175,167,167,220,52,135,48,62,176,54,137,70,185,22,184,202,115,85,45,44,144,241,33,136,77,119,89,121,13,5,91,
96,101,201,245,12,24,237,228,185,52,216,10,30,208,89,32,69,101,187,89,86,99,95,167,212,31,64,50,167,8,43,118,239,150,37,221,9,34,43,23,135,202,66,131,33,208,184,158,73,219,106,243,185,114,70,238,73,71,
101,137,155,203,154,132,217,14,37,187,53,241,45,93,122,255,206,119,167,218,50,253,128,82,141,83,146,135,185,192,138,124,15,211,178,226,173,241,38,127,48,144,178,244,125,88,50,191,60,174,98,201,81,187,
151,178,66,45,80,146,215,86,229,122,128,174,86,0,42,77,214,92,58,205,229,195,107,151,53,10,221,210,62,207,198,148,159,239,235,88,171,104,85,53,103,229,159,203,46,90,147,3,87,67,170,70,3,175,222,160,254,
42,41,162,122,86,113,189,220,190,183,53,104,131,185,53,14,123,130,53,17,123,152,15,13,93,125,54,137,212,143,208,244,49,79,109,156,90,121,180,185,66,235,106,177,160,94,175,201,26,191,9,56,67,169,171,49,
79,1,0,66,4,136,121,190,23,23,83,91,92,49,126,217,90,113,123,66,158,244,32,0,32,132,234,0,168,87,202,92,215,208,202,239,185,139,82,83,110,28,163,44,143,162,2,148,65,144,92,53,94,128,71,121,101,187,180,
202,195,48,15,8,244,116,15,192,181,65,169,110,78,199,249,99,198,42,135,219,81,78,182,7,197,214,94,253,173,116,111,226,23,87,72,63,226,227,129,89,15,248,241,23,13,246,179,59,85,38,247,145,94,158,5,80,150,
91,202,202,141,197,94,245,97,117,163,111,34,212,158,150,183,160,121,139,128,44,195,220,116,111,177,25,205,13,24,0,216,251,176,180,202,128,56,66,81,46,237,151,241,121,246,228,184,161,236,15,149,116,9,62,
192,226,211,61,2,72,31,203,241,92,213,217,192,202,34,193,64,48,133,225,144,149,186,101,175,86,46,134,24,211,48,28,156,188,109,246,168,189,165,20,243,242,123,34,33,38,119,118,108,166,85,54,101,178,38,97,
250,253,32,98,233,77,182,87,149,222,3,42,29,128,209,91,150,213,134,94,153,26,43,82,131,210,200,218,68,215,152,19,77,83,127,205,166,109,44,187,74,209,163,49,59,236,79,139,53,229,107,192,7,198,189,87,226,
40,12,139,34,163,102,136,69,217,104,160,172,163,174,132,236,112,90,249,114,173,25,171,221,231,1,139,191,76,78,247,172,76,57,177,39,16,64,58,170,149,167,13,52,203,125,179,220,21,171,14,188,221,38,90,198,
24,75,61,145,25,162,77,11,107,132,118,95,88,43,105,78,175,98,120,104,79,110,251,208,111,143,103,150,116,245,3,0,149,211,86,125,46,212,83,118,127,185,94,91,104,7,109,53,70,54,23,76,123,92,96,76,211,202,
159,110,0,136,23,4,0,16,34,63,150,177,88,44,96,140,49,189,30,135,234,72,70,240,188,192,199,155,44,135,218,131,31,147,237,89,0,70,50,22,44,150,184,148,141,218,162,193,26,122,83,121,122,164,193,235,96,201,
208,60,164,206,113,211,9,102,150,111,250,185,222,99,58,244,245,42,249,53,28,36,31,186,175,0,165,3,53,176,165,171,157,7,20,106,221,3,84,239,136,170,1,138,24,80,129,183,158,215,115,115,90,238,139,180,91,
11,235,184,168,235,202,55,203,18,0,101,157,248,247,109,162,109,84,159,255,210,0,94,99,41,84,62,198,244,234,19,105,67,107,129,107,217,157,198,124,187,94,77,64,20,44,173,92,227,27,36,210,53,14,62,11,52,
209,246,209,168,155,37,79,175,189,57,174,227,76,128,64,190,155,80,189,34,89,94,167,116,251,229,121,100,174,195,56,142,226,72,190,206,56,154,238,157,35,171,13,82,21,220,60,29,218,196,64,20,7,222,184,22,
8,72,74,77,203,214,58,35,157,211,98,15,137,169,108,85,2,149,213,134,22,80,122,237,64,67,175,251,234,173,232,102,91,174,169,179,197,30,232,91,74,113,229,247,228,53,157,50,139,245,1,12,107,133,247,66,143,
91,233,129,139,42,223,105,139,85,150,85,94,11,148,122,242,120,229,99,217,171,213,138,185,150,137,28,0,91,127,221,182,135,145,29,42,95,122,207,140,181,174,75,92,61,64,122,87,240,86,89,38,42,83,181,232,
198,43,13,163,53,146,133,238,24,240,168,135,198,166,18,197,77,202,40,168,105,212,189,2,16,227,93,243,26,219,244,64,23,43,237,53,45,186,216,101,149,82,133,38,77,235,5,230,10,148,72,91,158,103,246,52,179,
228,185,64,65,227,44,119,223,211,53,55,143,155,46,198,29,75,34,159,140,159,140,45,11,167,177,80,209,56,58,215,180,57,163,177,160,74,54,69,2,249,51,93,219,111,164,208,174,243,98,44,108,146,47,44,44,30,
77,109,143,202,204,128,31,153,98,155,238,218,4,225,32,81,124,97,105,128,69,245,24,83,161,0,66,194,48,12,230,91,30,86,171,85,213,56,195,48,84,8,205,58,149,120,81,217,133,140,186,159,47,131,198,26,248,61,
150,165,203,120,121,203,165,22,199,114,153,147,134,186,136,114,142,212,54,196,74,22,235,183,88,44,242,151,166,179,84,44,174,141,124,60,136,134,197,98,193,247,108,228,68,156,202,240,222,165,142,54,212,
159,134,3,8,97,128,197,98,200,125,143,178,52,200,49,116,115,115,195,234,79,223,66,66,131,252,78,158,166,83,130,157,246,221,131,182,171,199,25,179,10,170,202,115,118,94,240,24,168,7,112,22,211,170,64,199,
168,27,13,90,159,198,24,1,198,52,191,181,246,246,234,49,151,113,46,113,96,54,221,52,8,249,11,199,90,160,40,200,242,73,180,132,122,5,187,123,247,46,124,53,125,178,93,150,127,126,126,14,47,94,188,0,250,
193,87,77,206,118,125,0,64,110,90,147,90,105,245,208,58,188,37,99,1,140,214,30,181,29,50,189,200,176,51,45,228,215,154,170,60,114,251,237,183,223,194,114,185,132,95,127,253,53,231,11,33,100,6,186,181,
181,5,63,252,240,3,188,121,243,6,222,190,125,203,202,254,234,171,175,96,123,123,27,158,60,121,162,218,183,88,44,224,167,159,126,130,163,163,35,150,23,235,11,0,112,120,120,8,123,123,123,240,219,111,191,
185,245,252,254,251,239,225,250,250,26,158,62,125,154,204,159,234,244,237,183,223,194,114,177,128,223,255,248,3,198,113,204,246,90,225,226,226,34,215,21,0,224,241,227,199,176,183,183,167,218,118,124,124,
12,47,94,188,48,117,105,19,140,46,166,90,159,82,253,45,55,144,6,236,19,213,133,21,89,242,67,196,116,92,84,186,241,186,102,44,154,171,231,17,15,171,14,146,49,229,60,153,211,4,38,107,202,147,107,203,29,
213,60,3,246,17,10,25,228,138,221,227,46,182,246,196,44,86,115,115,115,3,47,95,190,100,233,91,219,91,112,120,144,6,191,252,28,184,221,1,8,78,24,159,175,148,14,18,43,123,150,132,226,46,117,0,147,102,83,
8,189,128,42,217,22,103,115,49,70,182,119,67,82,42,157,67,8,176,181,181,5,187,187,187,0,0,112,231,206,29,56,57,57,97,231,126,40,131,60,60,60,132,243,243,115,56,59,59,235,90,25,67,8,176,191,191,15,195,
48,192,131,7,15,224,232,232,72,101,31,22,219,148,225,207,63,255,132,239,191,255,62,235,10,147,77,219,219,219,240,251,239,191,231,69,234,234,234,74,5,208,157,157,29,56,56,56,128,79,159,62,177,248,24,35,
124,250,244,73,253,34,243,106,181,234,250,138,78,207,222,77,15,35,104,5,186,39,219,243,121,176,234,213,54,108,30,40,192,199,116,36,25,188,214,204,237,5,222,86,251,72,2,211,147,87,187,150,111,114,88,122,
147,138,78,66,90,65,11,21,117,70,1,85,131,106,8,27,99,172,62,225,126,118,118,6,119,239,220,133,91,183,110,85,147,127,107,107,11,182,182,182,152,174,179,179,179,236,230,132,16,96,119,119,23,66,8,240,233,
211,71,214,57,247,238,221,131,243,243,115,184,186,190,202,3,102,123,103,27,54,111,109,230,188,171,213,10,206,206,206,152,107,20,66,128,229,114,9,187,187,187,25,152,41,144,134,16,96,103,103,167,178,23,
0,224,244,244,148,233,218,217,217,129,205,205,186,60,180,31,227,81,141,181,31,65,219,115,140,17,246,15,14,224,252,252,28,198,113,132,253,253,125,56,57,57,97,178,116,32,157,157,157,193,163,71,143,224,183,
223,126,75,229,82,253,49,86,254,234,48,12,112,239,222,61,56,58,58,130,251,247,239,167,235,183,71,73,156,238,31,142,17,226,24,213,247,58,81,217,179,179,51,120,249,242,37,60,124,248,16,62,126,252,8,195,
48,192,254,254,62,188,124,249,18,206,206,206,178,252,106,181,130,235,235,107,166,99,123,123,27,30,60,120,0,39,39,39,240,242,229,203,170,93,110,110,110,216,231,228,231,132,182,187,167,199,183,221,120,101,
114,19,151,145,130,87,207,155,36,84,125,78,30,249,153,250,226,249,112,66,55,135,37,90,65,91,232,229,120,85,25,214,68,56,134,80,111,53,13,195,224,127,132,130,95,43,191,20,102,212,247,243,90,12,77,86,106,
115,115,19,118,118,118,242,253,246,246,54,220,186,117,11,222,189,123,71,242,7,56,60,60,128,251,247,239,179,253,8,164,159,191,255,254,59,220,220,220,228,202,126,253,245,215,57,14,0,224,246,237,219,240,
213,87,95,37,119,101,218,227,122,248,240,33,220,185,115,135,1,10,2,210,63,255,249,207,188,9,191,189,189,13,223,125,247,29,219,87,59,57,57,201,43,227,183,223,126,11,91,91,91,234,219,42,206,207,206,224,
230,250,26,66,8,169,188,187,119,153,253,184,71,243,191,255,251,191,238,139,252,173,73,1,144,92,189,219,183,111,195,179,103,207,96,181,90,193,15,63,252,0,183,111,223,206,19,183,44,60,73,255,171,87,47,225,
209,163,199,240,232,209,35,248,227,143,63,0,72,57,218,107,137,15,15,15,33,198,8,175,95,191,134,24,35,28,28,28,20,150,21,203,20,195,147,209,163,178,113,43,195,187,119,239,224,246,237,219,240,248,241,99,
24,134,1,78,78,78,114,127,147,26,2,29,101,155,155,155,240,221,119,223,193,249,249,57,60,123,246,172,210,137,109,116,251,246,237,188,40,96,64,70,169,133,94,38,101,197,107,172,69,130,85,5,94,98,78,209,237,
19,170,67,155,236,50,77,150,203,101,64,125,147,105,182,171,67,167,93,239,218,61,181,220,75,143,153,149,69,117,84,127,29,29,199,145,31,28,53,125,109,252,85,140,201,165,29,41,0,128,72,192,140,163,98,97,
88,166,175,74,138,220,218,218,130,195,195,195,76,219,99,140,240,254,253,123,56,61,61,205,147,22,153,19,238,109,209,9,255,253,247,223,195,238,238,46,28,79,172,231,244,228,4,246,247,247,97,127,127,31,94,
189,122,149,93,154,227,227,99,160,123,119,183,111,223,134,211,211,83,120,245,234,85,214,119,235,214,45,248,225,135,31,96,103,103,39,187,28,119,238,220,201,123,46,116,197,15,33,109,242,110,111,111,195,
219,183,111,225,175,191,254,170,59,107,154,115,49,70,184,189,183,7,159,62,125,130,231,207,159,231,228,229,114,9,63,253,244,19,236,236,236,192,233,233,41,0,244,111,246,98,216,223,223,135,139,139,139,204,
170,62,126,252,152,89,22,237,147,220,244,17,224,249,243,231,240,195,15,63,192,87,95,125,5,111,222,188,201,101,200,31,65,22,139,5,236,239,239,195,209,209,17,196,24,51,203,194,56,177,108,1,0,192,48,44,120,
7,11,251,209,166,87,175,94,193,143,63,254,8,49,198,106,91,128,234,3,0,216,216,216,128,239,190,251,14,174,174,174,224,233,211,167,170,94,188,222,221,221,133,59,119,238,48,77,71,71,71,149,11,41,243,91,161,
197,60,188,247,195,91,253,71,227,138,7,163,151,167,187,121,58,123,211,93,177,121,174,158,44,199,4,110,98,60,46,45,214,62,176,197,174,104,154,108,43,148,131,76,111,129,0,0,32,0,73,68,65,84,29,134,161,254,
46,97,181,47,66,246,164,74,82,159,60,151,169,253,108,186,89,23,99,132,143,31,63,194,157,59,119,224,214,173,91,240,242,229,75,184,188,188,36,101,23,215,113,24,6,120,255,254,61,124,251,237,183,176,177,177,
81,85,146,62,65,126,116,116,4,95,127,253,53,252,245,215,95,176,181,181,5,155,155,155,240,231,159,127,86,13,117,124,124,12,63,253,244,147,187,42,132,16,224,226,226,2,174,174,174,170,244,113,28,225,242,
242,18,30,60,120,144,247,144,0,146,59,115,114,114,2,199,199,199,128,191,84,162,253,63,255,252,179,218,94,30,155,178,108,219,218,218,130,187,119,239,50,198,241,230,205,155,204,178,180,73,10,16,225,242,
242,18,94,189,122,9,15,31,62,130,179,179,34,35,7,231,253,251,247,33,198,8,239,222,29,1,64,132,155,155,107,120,255,254,125,6,172,113,92,49,189,0,32,226,108,219,175,174,174,224,211,167,79,48,142,35,115,
137,101,88,44,22,240,221,119,223,65,140,17,158,60,121,162,190,232,144,134,215,175,95,195,235,215,175,43,61,173,182,214,38,140,22,175,229,107,185,147,94,217,124,251,164,157,87,211,229,45,104,173,95,236,
0,34,208,38,76,73,81,216,69,127,157,38,219,0,88,86,140,89,70,214,71,47,211,142,215,228,204,61,44,13,9,203,43,127,107,166,68,1,69,43,44,249,167,83,3,200,248,73,246,250,250,26,158,63,127,14,143,30,61,130,
71,143,30,193,211,167,79,225,234,234,202,180,235,245,235,215,213,179,139,23,23,23,172,220,147,147,19,56,56,56,128,253,253,125,216,222,222,134,227,227,99,166,147,234,251,243,207,63,171,120,186,175,214,
90,133,159,61,123,6,123,123,123,176,177,177,193,220,146,135,15,31,170,251,97,47,20,54,113,62,217,95,173,80,201,0,53,13,0,224,224,224,0,46,46,46,224,242,242,18,254,237,223,254,141,167,29,30,192,233,199,
83,86,15,236,207,213,106,132,163,163,119,176,181,181,13,15,31,62,130,79,159,62,65,140,145,217,186,88,44,224,193,131,7,240,246,237,91,184,119,239,62,251,69,23,32,237,9,82,55,142,142,3,90,95,47,224,162,
100,201,33,88,13,195,0,191,253,246,27,59,164,140,101,106,58,115,250,244,100,67,139,77,200,248,117,101,52,32,180,93,32,27,164,188,124,158,77,245,125,251,216,130,22,77,227,236,58,227,2,53,178,167,17,70,
167,189,215,185,206,47,240,11,1,128,62,116,216,242,97,165,66,10,86,214,138,0,192,157,6,205,40,128,84,233,63,255,252,19,30,63,126,12,223,124,243,13,60,123,246,44,187,95,168,111,181,90,193,131,7,15,224,
249,243,231,85,165,228,241,135,24,35,188,125,251,22,30,62,124,8,49,198,252,147,54,5,98,212,247,242,229,75,110,79,8,176,34,231,123,180,32,87,176,227,227,227,124,63,12,233,44,209,225,225,33,220,186,117,
11,206,206,206,32,132,244,139,232,131,7,15,42,166,135,117,43,123,132,101,47,35,0,240,147,242,132,180,110,220,218,128,187,119,239,194,139,23,47,96,140,99,218,143,154,84,220,186,117,11,30,126,253,16,246,
110,239,229,189,27,202,234,112,239,236,205,155,55,176,179,179,3,119,239,222,133,243,243,115,118,238,233,224,224,0,66,8,240,225,195,7,216,216,216,72,250,167,112,239,222,61,56,60,60,132,15,31,62,176,241,
48,12,67,102,191,50,104,44,202,90,232,240,215,208,199,143,31,195,198,173,13,120,250,228,105,6,43,100,0,216,246,84,23,218,160,149,131,103,182,248,56,41,186,104,200,231,185,140,71,120,232,57,63,109,128,
183,24,19,218,42,199,172,54,143,90,243,51,132,250,213,74,188,126,181,253,52,143,230,198,89,91,57,38,83,36,236,11,143,211,80,93,16,249,214,82,72,25,147,129,233,134,203,11,155,151,50,82,11,52,179,103,48,
109,104,115,207,74,52,152,86,214,56,142,240,252,249,115,120,252,248,49,60,126,252,24,158,62,125,202,54,186,63,124,248,0,135,135,135,249,108,14,213,245,235,175,191,86,19,226,248,248,24,14,166,95,207,168,
155,25,99,250,53,235,195,135,15,176,191,191,15,127,255,251,223,153,125,49,70,248,199,63,254,81,77,166,234,160,35,0,12,139,5,252,252,243,207,106,221,46,46,46,178,75,22,99,218,151,59,56,56,128,191,255,253,
239,149,236,63,254,241,143,116,160,112,234,124,92,177,44,55,49,132,0,7,251,7,112,117,117,149,65,227,234,242,138,165,223,189,115,23,246,247,247,243,230,59,253,48,64,97,91,35,60,123,246,44,239,37,97,121,
200,174,222,189,123,7,215,215,215,213,175,117,151,151,151,112,247,238,93,184,119,239,30,188,127,255,62,199,111,110,110,194,47,191,252,2,50,156,159,159,171,71,20,176,189,17,40,233,120,161,63,198,124,255,
253,247,85,222,139,139,11,118,230,43,132,0,123,123,123,240,175,255,250,175,76,46,198,104,158,195,202,222,12,212,216,19,243,100,18,113,242,90,97,35,213,60,33,139,144,54,41,89,62,178,40,89,46,32,13,222,
177,8,121,29,99,204,172,211,147,145,122,52,44,176,236,1,195,227,162,215,116,251,38,45,10,169,210,249,74,96,75,248,239,255,254,111,86,146,230,126,101,20,52,210,241,58,198,180,25,171,129,145,151,111,177,
88,192,198,198,70,229,206,45,22,11,216,220,220,132,155,155,155,60,81,112,197,195,52,217,145,82,7,150,177,92,46,153,171,35,1,117,185,92,194,173,91,183,170,124,244,23,165,205,205,77,8,33,48,208,163,178,
219,219,219,85,221,87,171,85,181,231,5,144,54,217,233,177,6,12,180,60,13,156,180,176,179,187,11,43,210,70,147,112,158,99,88,55,202,176,54,55,55,225,226,226,162,122,12,233,214,173,91,48,12,3,92,92,92,228,
190,161,178,90,192,95,70,177,158,203,229,50,179,43,141,65,203,227,43,0,169,109,35,0,92,98,255,145,186,14,195,0,91,91,91,106,217,76,231,84,214,230,230,102,117,50,30,117,174,110,110,224,242,242,18,240,117,
38,160,60,121,65,67,203,211,136,113,84,93,41,43,255,156,178,232,100,181,88,149,230,126,183,202,109,121,80,18,92,44,87,210,3,44,204,183,191,191,223,148,203,215,80,214,5,45,207,114,185,132,240,95,255,245,
95,49,85,2,136,184,15,48,90,28,5,44,89,81,41,223,42,99,29,121,207,62,205,158,222,50,123,108,89,87,254,115,226,230,148,253,57,250,92,61,228,20,190,118,255,165,3,93,56,123,182,44,178,220,196,106,60,70,33,
39,113,55,8,132,80,179,49,118,15,0,10,75,182,236,159,85,175,73,63,237,78,139,21,233,121,117,96,74,22,251,236,75,211,159,255,146,205,120,15,176,210,53,161,145,78,89,49,70,216,216,216,72,207,18,86,3,175,
1,80,154,140,68,112,11,216,52,93,154,158,86,121,211,21,86,199,213,11,0,250,138,219,40,71,3,185,126,219,244,251,30,27,82,217,216,142,253,121,214,43,167,111,130,104,129,14,106,237,254,75,135,57,182,126,
41,217,38,176,68,253,136,103,147,141,80,119,79,62,119,232,233,234,96,43,8,206,115,153,87,203,125,211,238,93,249,105,184,233,219,67,244,227,22,36,139,177,149,132,99,119,73,27,175,218,32,35,215,150,255,
234,173,76,86,154,5,102,234,170,55,109,222,121,101,104,250,51,99,196,213,213,0,31,109,111,64,218,151,235,156,127,231,20,167,146,53,218,28,244,58,211,32,159,7,211,244,90,148,197,211,203,202,48,246,61,90,
139,199,220,208,212,147,219,101,253,242,172,85,127,174,61,218,36,177,116,90,108,168,197,200,172,133,43,70,178,209,28,240,30,103,54,73,135,186,143,145,209,177,120,66,177,24,87,137,118,223,183,226,36,64,
142,154,29,36,93,99,189,149,135,69,108,75,215,62,126,96,188,196,161,37,157,204,248,85,91,15,229,44,64,10,33,228,195,158,45,247,203,163,224,170,28,248,131,65,198,243,134,114,24,211,68,231,187,25,82,228,
140,103,174,27,107,5,172,251,98,224,27,206,189,96,162,185,191,52,94,235,15,107,18,90,105,173,208,157,71,43,215,242,35,201,10,13,0,213,47,117,235,6,15,132,114,32,224,128,175,144,166,57,170,9,233,0,152,
44,107,20,160,52,151,209,36,91,56,104,168,76,9,160,2,191,150,109,213,226,27,66,169,191,1,160,173,80,213,1,129,86,13,182,87,17,99,132,37,62,62,17,66,97,35,189,123,79,232,250,113,102,131,104,95,216,81,75,
95,149,22,202,16,158,227,126,209,138,97,186,59,145,196,138,133,121,91,64,228,2,9,5,52,40,237,228,5,252,33,65,123,36,71,20,172,22,85,1,92,224,16,48,151,77,121,236,96,78,232,117,65,205,9,164,20,135,219,
23,45,91,154,174,156,155,150,91,150,165,201,234,112,121,131,49,164,72,54,65,231,110,175,168,54,71,219,211,192,203,148,204,235,36,201,66,207,22,8,175,43,179,60,27,147,156,1,29,200,122,193,188,184,164,134,
215,2,80,158,37,164,223,39,212,168,88,171,112,13,72,36,88,149,202,64,78,103,215,160,15,114,173,211,44,224,106,177,37,171,147,123,242,91,113,82,63,103,113,211,95,230,17,249,140,200,12,13,57,44,59,136,56,
106,155,102,51,149,107,133,57,160,213,100,49,138,140,231,198,196,200,127,138,183,66,247,34,103,44,8,250,66,65,95,147,84,100,139,188,40,67,241,230,99,154,137,229,30,148,246,199,201,30,241,245,197,118,101,
181,182,42,242,101,242,203,58,233,32,161,44,36,147,2,252,43,235,82,219,94,64,50,198,8,177,122,181,12,168,215,86,208,108,75,155,238,98,18,117,187,72,13,121,111,101,159,163,199,114,105,84,80,141,133,44,
123,43,85,143,91,208,42,87,198,105,126,59,224,202,35,170,155,229,113,159,205,0,33,143,165,104,117,144,46,134,204,131,118,173,235,92,73,61,150,141,69,200,6,196,57,238,242,156,208,114,171,74,251,225,125,
177,7,153,20,203,34,242,107,15,134,247,176,160,94,123,1,0,98,128,228,2,135,226,173,208,78,163,125,175,143,107,124,114,96,30,115,234,117,79,173,49,70,231,97,24,134,124,156,200,26,171,242,154,237,83,2,228,
151,28,2,164,31,206,150,242,100,184,5,50,30,40,89,21,145,95,149,110,149,163,77,68,137,226,26,240,88,204,169,181,90,247,48,48,164,183,146,181,244,128,107,12,133,57,202,144,203,153,146,173,87,85,187,131,
13,140,52,68,36,167,252,128,245,75,133,84,110,139,154,135,49,71,69,115,67,71,221,7,149,132,95,102,167,94,43,77,94,203,108,210,37,89,39,104,167,198,93,22,211,2,190,8,236,23,63,111,155,3,187,81,211,135,
139,163,246,155,38,238,93,247,218,229,213,131,46,152,33,198,242,86,91,45,255,84,55,153,207,210,23,99,212,95,47,147,43,168,209,103,9,38,132,250,162,114,10,24,114,37,144,19,81,115,9,60,224,146,215,154,173,
154,110,147,169,100,247,181,220,7,161,135,178,54,179,125,72,57,99,28,171,213,80,147,203,54,240,148,106,85,244,86,179,210,225,149,200,148,191,111,226,117,224,130,25,188,182,152,174,64,14,165,207,41,15,
203,244,220,73,26,39,199,144,28,43,222,98,54,7,184,44,246,173,217,162,233,182,129,200,126,70,87,206,45,154,44,23,65,237,117,63,94,153,235,7,58,255,135,186,93,66,253,75,40,3,40,136,16,128,191,239,62,198,
244,20,196,146,10,135,16,202,99,33,32,58,0,59,59,242,149,157,254,20,239,1,83,179,138,29,0,227,233,179,64,75,147,163,250,61,203,230,186,195,57,14,210,235,164,91,245,230,117,166,128,236,102,3,0,242,140,
91,162,72,80,186,105,30,18,148,126,228,109,145,153,151,147,135,222,83,240,151,33,66,172,126,225,75,226,243,81,171,103,82,183,244,218,147,31,175,18,208,107,236,221,99,58,86,28,205,107,121,39,30,216,201,
87,92,179,197,112,168,183,34,52,239,196,90,244,180,182,176,244,201,107,51,29,203,93,1,164,39,1,10,131,207,229,57,122,211,117,13,204,58,195,10,246,175,122,101,146,235,147,209,116,141,34,127,192,211,235,
28,201,142,90,46,33,45,219,202,163,149,105,49,60,100,83,21,128,14,33,79,58,171,51,61,23,84,166,91,237,96,201,135,16,84,55,44,137,244,1,169,23,208,69,164,247,62,114,250,95,237,193,16,35,64,128,47,64,169,
176,212,16,208,58,214,198,202,115,206,196,6,31,120,203,184,161,178,252,240,179,244,30,44,208,179,202,244,238,53,172,103,96,57,17,229,236,210,17,226,156,207,41,130,110,15,157,123,45,16,242,88,149,37,159,
108,215,129,71,150,139,243,202,210,171,217,66,231,116,8,193,118,9,45,163,53,208,161,147,223,163,211,22,232,120,19,217,67,123,45,175,150,199,138,167,247,77,54,213,96,4,221,236,75,91,12,196,136,165,191,
158,178,142,163,171,87,131,141,246,176,85,47,79,43,111,8,17,63,182,109,46,34,168,147,98,234,103,121,26,88,182,90,142,92,147,185,13,34,38,219,97,141,167,30,151,104,142,75,39,3,31,223,126,158,116,61,45,
16,130,144,231,177,18,139,94,139,181,201,55,90,120,215,189,243,152,182,186,70,16,60,18,161,229,147,65,234,104,190,192,175,197,182,128,184,135,195,16,148,23,254,165,74,149,185,54,143,13,244,216,19,140,
201,222,114,17,123,239,123,39,188,46,151,218,65,3,244,108,91,50,144,172,68,229,252,90,175,13,19,227,158,101,95,185,229,236,183,175,60,191,109,99,158,64,181,157,54,180,232,118,246,126,52,194,115,139,164,
110,223,205,161,147,181,109,167,86,22,103,109,125,32,88,210,19,64,97,220,116,192,1,32,218,15,64,91,243,194,122,221,140,85,15,28,167,244,51,105,248,229,27,141,93,122,196,34,132,160,234,201,245,50,8,140,
215,55,75,75,128,82,82,127,240,134,9,140,180,85,30,128,130,85,61,136,149,247,196,207,8,180,129,49,63,110,120,107,44,206,187,167,250,52,253,172,198,134,173,58,40,78,171,191,3,4,114,209,128,80,187,126,45,
32,41,109,107,183,99,93,255,156,210,108,11,77,71,143,188,27,4,91,104,149,225,5,13,44,232,164,160,105,125,204,161,143,13,104,76,86,186,76,94,126,61,142,131,79,0,236,43,125,97,160,81,61,44,79,115,1,91,174,
153,42,3,132,65,67,89,120,105,59,166,47,63,67,30,160,61,192,100,217,66,94,224,39,26,200,112,209,52,202,39,149,218,95,77,70,253,116,213,66,48,243,127,201,209,238,101,220,58,131,175,159,81,5,145,94,169,
202,233,101,109,204,145,149,93,214,199,107,189,56,109,0,165,251,190,1,107,233,243,202,182,62,245,213,178,109,14,112,37,87,183,91,92,181,197,90,104,122,193,91,222,251,236,203,142,239,5,5,202,182,45,29,
158,155,237,219,166,129,52,77,43,215,188,121,180,57,143,44,77,103,144,65,218,153,129,37,0,178,246,97,152,192,182,99,174,90,117,98,128,213,114,9,173,208,162,151,120,173,187,11,246,192,182,6,191,69,187,
123,128,108,14,83,160,121,74,217,28,132,91,108,38,210,52,133,157,181,86,249,222,182,77,127,85,65,247,215,207,222,240,185,99,1,160,61,113,215,9,235,50,4,75,143,197,110,173,49,216,179,40,180,198,165,202,
240,1,64,254,118,224,77,238,42,115,210,60,145,2,202,252,0,240,149,120,101,88,198,156,47,66,100,121,232,56,79,215,129,22,32,230,129,214,23,0,17,70,8,80,192,238,75,48,188,16,66,122,91,67,166,117,202,100,
178,86,49,26,168,76,210,21,192,122,222,203,2,176,185,140,138,178,33,154,191,165,199,102,81,52,157,243,36,77,135,55,217,220,9,60,105,166,15,192,166,248,250,120,72,149,119,198,68,81,65,218,162,50,177,15,
60,120,251,231,171,181,237,201,197,167,153,161,254,138,212,178,163,213,38,154,11,133,44,132,233,193,139,113,100,173,148,24,70,251,227,13,69,183,37,83,199,205,89,172,44,121,180,17,239,181,197,112,14,83,
179,88,155,22,184,183,100,219,37,175,105,28,218,140,223,33,4,178,7,141,238,67,214,7,0,75,212,195,247,52,236,138,209,198,208,222,153,221,51,224,90,29,83,228,168,222,130,246,244,26,169,107,190,207,71,251,
99,30,108,116,210,216,95,42,46,158,120,138,174,153,17,181,159,6,217,14,50,157,117,28,209,44,155,91,59,185,110,2,79,108,15,8,25,188,183,34,204,101,59,212,181,208,18,180,161,196,1,218,79,247,203,110,179,
38,166,87,0,109,84,0,186,244,190,98,151,194,134,121,126,135,237,54,108,158,195,12,45,111,35,78,19,155,190,85,129,130,127,80,220,207,52,69,178,171,160,34,79,11,112,165,109,210,205,141,74,30,179,190,89,
62,141,237,186,156,84,199,101,106,108,220,56,7,192,41,213,162,175,0,245,99,8,49,70,243,133,246,152,238,54,122,46,112,178,15,159,179,131,0,233,163,181,245,105,94,122,31,18,247,173,26,195,99,137,61,251,
82,173,184,158,149,81,101,101,204,19,225,182,203,58,212,70,248,54,206,13,114,50,22,224,183,167,178,90,46,182,167,162,191,197,15,57,175,237,99,148,166,77,66,217,122,251,65,124,236,91,91,27,61,122,48,205,
75,239,253,53,84,141,39,204,176,7,32,180,107,107,155,194,11,57,15,249,101,27,117,12,33,176,95,6,91,101,178,235,161,158,203,121,15,75,22,174,185,67,61,171,185,54,41,233,189,100,34,61,110,85,160,19,160,
195,237,235,217,255,193,123,57,128,122,243,182,210,186,1,68,25,23,106,94,186,18,106,106,140,9,245,57,161,126,221,177,112,159,26,147,47,231,234,112,9,181,176,14,88,241,130,185,158,150,27,105,217,55,199,
61,95,103,111,139,50,42,203,70,211,6,202,70,66,205,160,49,158,178,113,58,238,173,121,227,181,149,9,106,98,129,240,230,82,113,241,202,129,215,138,20,69,28,246,188,156,165,245,90,25,170,164,119,176,181,
246,172,242,94,153,48,35,107,15,125,155,197,38,99,17,97,206,126,150,55,48,173,54,144,249,80,174,183,147,169,206,158,243,50,90,104,125,155,175,21,106,214,151,220,3,230,50,124,70,144,111,81,253,82,161,119,
31,107,206,126,87,143,92,20,19,83,203,179,206,222,85,175,45,230,125,76,109,45,251,109,92,181,191,164,211,99,127,143,140,76,31,134,129,125,193,202,99,90,249,26,38,140,85,226,198,113,212,143,53,200,107,
203,61,212,86,139,38,99,17,46,67,165,3,56,80,122,147,156,167,77,75,137,176,71,179,155,235,9,16,99,249,236,85,15,48,201,184,138,13,170,128,195,71,122,18,41,113,65,180,11,166,214,246,10,173,29,236,202,147,
169,234,5,178,21,231,133,222,149,186,39,204,153,216,235,132,106,191,200,113,91,61,91,122,235,57,215,45,245,128,195,100,48,201,160,156,215,218,95,149,54,123,219,38,154,45,26,35,10,33,177,114,74,40,232,
193,209,174,64,236,147,253,18,99,44,46,97,15,61,12,1,223,157,69,89,67,178,22,13,148,121,91,0,168,149,3,0,213,233,90,79,86,186,178,146,209,180,221,146,126,183,165,71,70,167,219,125,108,15,175,145,141,90,
174,236,156,208,195,70,129,157,209,1,246,139,226,16,6,41,137,43,139,201,157,34,0,123,151,17,177,70,245,108,53,0,104,49,100,43,191,118,239,133,80,6,117,147,11,234,204,34,95,153,253,99,121,47,210,14,107,
145,213,218,167,215,93,173,188,0,154,166,106,208,245,121,246,133,65,159,167,93,174,161,65,130,164,119,195,246,176,122,86,112,250,13,54,218,201,147,32,140,49,86,111,46,165,6,178,124,152,20,218,172,78,178,
50,90,9,111,80,91,7,52,189,129,95,192,165,189,207,209,3,168,150,75,41,59,75,174,114,22,195,236,169,131,22,60,230,91,210,200,147,7,16,148,244,74,105,197,2,219,123,59,245,233,111,95,190,29,62,151,137,169,
242,148,113,88,121,12,38,162,201,219,109,110,196,81,249,24,85,166,226,109,53,120,222,133,40,180,42,159,143,69,145,63,132,156,71,115,235,180,190,176,250,39,70,200,222,77,137,175,207,145,81,221,75,122,50,
189,143,101,217,143,236,104,128,34,243,231,180,160,35,176,10,10,120,77,100,172,61,31,95,159,85,39,150,165,76,86,7,19,90,171,156,101,131,92,73,212,213,207,161,231,21,123,116,140,164,27,154,44,222,180,185,
126,40,216,91,33,53,251,43,141,14,80,182,237,209,131,252,65,64,174,208,94,57,44,37,224,115,115,53,3,206,118,89,160,100,45,24,141,182,150,118,202,113,204,220,32,50,81,123,192,161,85,166,149,223,234,67,
9,116,189,238,46,173,35,253,202,56,75,39,192,199,211,227,4,100,6,96,245,248,152,214,196,209,128,201,187,215,130,214,97,45,234,236,14,240,24,39,63,58,181,73,122,189,151,180,29,32,70,250,19,108,173,38,132,
48,249,229,68,45,97,117,21,208,56,76,171,103,50,81,121,121,205,171,215,247,131,3,64,237,202,121,229,81,221,115,66,175,252,92,96,239,201,211,102,115,117,92,228,9,228,79,223,196,4,128,106,1,237,5,14,45,
110,46,139,150,222,69,186,47,86,201,62,212,152,186,69,56,44,27,19,208,7,160,135,193,61,38,69,237,203,103,195,20,183,175,119,153,66,123,135,64,94,47,35,221,167,26,56,178,105,44,78,54,150,52,152,234,148,
70,192,148,117,206,175,72,90,227,43,70,78,171,102,137,178,87,68,0,239,164,55,2,21,103,232,109,160,238,169,199,58,105,88,254,28,57,75,182,57,185,59,203,249,156,64,219,78,186,198,173,114,215,177,171,197,
78,44,189,30,211,240,216,166,6,144,154,29,189,236,69,191,79,37,245,244,167,4,91,25,232,150,13,123,125,177,56,208,105,141,19,105,195,104,180,155,215,158,86,219,172,198,49,1,150,54,217,232,64,210,24,143,
197,130,52,247,71,11,84,71,239,9,111,105,79,213,64,132,194,91,43,77,202,200,65,82,219,48,236,177,195,147,105,229,41,246,244,61,209,223,11,56,86,158,117,24,206,156,188,243,101,53,185,62,55,179,206,209,
214,236,234,152,201,236,138,124,251,189,90,33,3,87,189,223,71,203,243,108,240,88,152,21,76,112,80,108,165,193,122,103,150,171,91,44,56,201,232,50,199,248,135,37,230,179,102,138,57,75,237,100,58,157,216,
67,24,202,43,91,200,233,211,48,253,15,11,209,86,153,57,43,96,143,59,82,100,52,54,195,25,149,12,150,27,213,95,166,29,231,157,238,183,86,95,107,16,90,192,100,185,229,61,249,189,58,182,192,225,255,206,69,
204,87,52,86,117,207,93,61,243,196,21,59,34,63,97,78,39,154,49,150,123,216,144,201,118,130,254,25,182,68,146,90,76,170,159,133,209,80,187,144,118,93,52,242,225,109,127,176,113,28,66,149,63,132,192,220,
73,182,63,28,235,183,251,210,107,233,238,134,16,218,199,26,146,120,58,145,26,71,1,76,161,144,26,156,84,90,193,218,228,244,26,207,146,47,50,245,35,58,147,95,151,27,68,211,235,129,79,204,205,82,135,214,
10,216,146,179,128,166,119,18,204,97,116,153,246,139,50,62,135,97,73,253,158,124,15,232,113,25,89,183,121,54,181,152,125,139,53,202,133,172,53,86,168,206,158,62,211,92,92,21,212,90,64,55,227,158,198,75,
0,104,233,97,178,201,1,48,244,22,124,181,22,95,138,9,94,155,89,139,38,125,172,7,243,47,213,14,138,17,2,217,140,87,221,67,101,213,15,211,234,97,81,95,125,240,80,29,14,104,26,174,158,148,181,216,139,22,
47,117,122,110,100,107,181,181,58,196,163,243,61,147,205,235,96,179,141,146,144,43,107,197,181,130,149,71,3,97,43,164,129,152,45,45,129,206,223,78,238,212,4,125,178,18,121,253,208,227,254,104,241,173,
250,202,62,244,198,159,166,207,26,183,173,113,146,117,6,254,106,101,143,1,226,60,103,243,128,152,35,235,140,68,197,107,7,170,83,214,89,218,225,217,134,97,169,78,8,0,8,198,91,13,172,130,49,109,52,80,221,
6,139,84,98,160,173,42,100,228,181,199,204,100,133,53,219,1,72,39,134,172,36,255,162,129,109,144,127,136,136,101,2,245,176,37,237,190,21,60,121,11,12,123,234,173,233,182,6,134,214,191,189,161,135,193,
1,76,108,61,40,99,206,201,223,203,100,212,188,16,1,70,252,196,149,253,225,140,117,203,239,153,100,50,140,236,11,66,118,159,182,192,82,95,240,184,78,237,240,174,245,144,181,5,172,82,198,99,106,212,182,
97,24,96,181,90,169,50,147,20,251,176,75,139,1,166,131,163,248,14,118,16,147,27,202,92,182,6,191,68,99,141,113,201,60,218,189,87,134,37,223,202,227,231,75,127,233,107,90,34,244,179,155,94,215,137,210,
230,62,121,251,203,38,104,147,119,223,27,214,105,235,255,235,176,14,96,75,25,51,61,148,35,30,189,238,84,111,58,147,169,8,99,29,31,249,141,202,96,122,203,213,23,42,0,124,135,124,145,169,39,190,21,230,184,
108,45,118,36,61,51,234,30,78,177,16,135,6,131,205,255,73,58,150,217,117,80,10,139,228,154,22,42,175,213,130,8,152,181,220,38,140,179,152,130,197,28,120,254,17,160,218,133,138,16,156,179,72,189,19,215,
98,40,52,205,102,143,245,62,73,203,150,58,206,170,51,149,235,100,8,4,69,189,118,237,161,250,74,172,105,3,91,245,27,64,92,165,87,111,142,208,67,15,43,105,197,73,125,210,165,177,92,41,121,61,142,163,127,
168,183,19,8,19,97,82,152,112,17,170,236,163,205,201,39,126,77,48,52,123,122,88,182,101,191,156,239,146,204,88,158,18,35,2,49,66,12,245,139,19,19,96,145,27,121,221,90,125,181,60,115,222,87,78,39,36,21,
205,149,152,140,175,89,93,78,37,241,124,5,77,121,130,187,154,204,169,31,253,105,118,14,155,163,54,121,114,49,198,212,81,160,181,191,190,199,210,203,60,68,65,93,54,183,0,86,47,179,13,0,0,254,10,255,185,
161,2,63,224,222,3,75,235,0,141,113,28,171,133,87,11,222,158,204,156,114,187,220,173,18,209,204,147,227,160,118,15,91,249,122,221,63,171,14,113,180,63,212,234,93,167,143,110,80,0,43,204,116,169,61,230,
64,43,153,20,64,66,103,114,173,249,58,178,130,154,139,88,53,192,244,223,64,10,75,215,58,171,163,159,129,215,88,156,44,219,126,195,168,223,97,158,78,139,97,177,41,97,148,53,103,245,234,145,181,130,92,221,
122,228,101,249,90,58,239,79,128,50,120,244,35,9,158,94,171,126,213,185,184,134,249,205,137,227,200,72,249,30,144,241,100,214,97,37,86,186,198,68,217,56,83,60,31,188,215,108,150,114,242,179,91,214,88,
245,236,247,188,34,237,227,174,110,27,16,93,148,32,208,176,148,9,140,186,9,154,38,175,37,205,211,7,181,206,214,48,46,136,123,118,77,13,158,146,6,24,32,134,250,87,149,26,96,116,214,166,5,139,89,161,62,
235,205,17,104,99,217,66,52,24,141,204,71,116,175,227,42,22,213,182,107,229,77,62,41,107,213,159,3,146,86,62,0,125,120,181,199,198,150,12,117,105,172,172,61,155,198,115,109,232,13,86,155,207,97,88,189,
249,173,178,187,129,77,29,138,250,2,34,137,129,102,159,6,140,52,143,4,67,122,109,201,101,112,203,236,202,152,71,83,220,114,49,44,186,127,66,182,10,197,107,164,207,222,68,146,134,170,62,172,145,175,223,
197,164,174,99,45,59,199,221,65,150,22,66,113,59,185,210,68,97,45,157,86,81,131,98,159,102,155,229,243,91,118,104,117,176,116,75,215,66,134,20,221,231,66,38,73,178,248,9,123,106,221,222,196,68,134,168,
167,47,22,11,38,236,141,222,57,96,213,3,120,242,149,191,22,203,215,250,74,117,213,232,100,13,161,210,163,229,109,141,137,2,108,117,222,94,80,239,1,96,141,157,105,118,245,130,121,222,32,114,198,217,114,
140,163,33,144,28,64,205,173,179,174,67,8,249,25,190,226,210,81,83,192,204,171,93,211,123,38,3,130,124,117,178,20,220,203,144,77,101,149,47,1,186,106,11,242,95,154,151,119,140,239,94,182,66,175,27,69,
153,158,85,23,57,232,181,210,215,113,63,115,94,250,128,172,98,207,156,32,95,44,73,67,15,11,241,194,92,198,213,51,105,105,104,189,155,221,3,174,22,88,1,164,57,37,197,122,221,205,30,251,231,182,143,7,178,
42,152,3,162,75,93,222,152,25,123,217,106,160,103,200,242,151,159,21,207,5,228,247,248,164,27,168,119,86,57,83,149,192,161,184,150,22,67,147,149,212,26,66,27,188,61,172,204,139,151,0,211,98,112,50,14,
235,153,148,232,242,173,58,120,241,90,122,139,129,89,65,50,3,234,50,247,130,103,79,136,201,40,18,225,15,254,158,54,105,185,183,84,190,167,61,122,219,140,202,199,72,198,9,75,172,117,44,134,196,0,71,230,
46,151,9,168,45,108,184,12,123,76,133,123,35,180,105,237,125,92,89,142,199,206,60,48,211,128,167,149,79,186,123,82,150,61,24,61,181,0,161,253,117,57,16,203,103,190,100,101,228,253,218,140,72,105,112,111,
114,240,52,218,152,53,160,202,87,227,244,130,23,75,11,211,83,145,161,111,226,106,29,174,117,136,62,40,251,25,204,28,183,117,142,238,57,192,244,89,32,102,185,132,218,132,36,105,1,214,175,27,234,107,229,
195,199,204,122,67,233,83,204,15,25,45,176,56,106,55,101,150,197,158,54,179,105,165,81,0,178,24,19,149,245,218,172,23,220,122,72,134,165,199,115,137,43,93,177,227,245,212,17,240,51,95,144,39,44,26,7,226,
87,159,154,89,249,147,60,78,8,99,57,155,32,26,70,134,217,224,227,201,203,149,132,255,202,64,255,116,117,180,231,54,242,85,176,93,135,186,83,121,85,214,97,101,115,129,230,75,202,247,235,226,110,51,94,172,
235,68,122,46,73,79,30,143,65,104,242,84,54,118,216,61,215,173,108,233,104,229,83,247,143,140,5,193,3,41,205,67,240,218,109,174,27,239,130,152,18,150,244,70,178,27,89,54,159,148,232,70,34,237,3,0,136,
147,75,136,22,20,112,96,236,202,104,0,57,8,100,185,154,157,89,135,242,141,68,139,254,202,23,219,125,14,235,177,202,155,115,30,77,222,175,227,162,185,32,210,121,240,18,203,238,146,209,40,175,151,127,26,
11,235,50,37,0,218,214,147,194,206,124,125,44,23,127,4,33,131,215,209,97,50,28,197,44,109,111,209,26,207,85,94,163,156,22,0,86,139,106,40,150,200,47,25,105,246,68,113,246,15,243,88,229,106,227,87,157,
167,56,215,135,48,17,137,52,79,188,61,75,26,150,233,185,166,62,132,87,247,124,8,40,165,248,9,200,38,159,92,14,82,143,133,104,254,186,38,71,131,214,56,86,40,212,178,76,54,205,207,150,245,173,242,55,228,
52,89,155,41,1,0,27,60,233,190,199,30,139,233,85,182,24,103,90,52,61,221,64,169,148,237,5,237,76,206,220,208,243,161,81,45,224,30,20,100,27,106,172,45,48,165,3,131,246,205,63,221,245,235,8,211,252,208,
120,153,55,198,188,69,187,119,129,143,49,194,16,6,2,98,220,174,156,135,216,167,185,186,106,181,4,184,106,96,75,221,187,172,115,70,219,45,123,193,10,11,147,128,98,173,154,102,103,10,134,101,129,150,164,
165,45,59,188,107,43,72,121,139,9,105,224,163,2,146,150,159,218,141,192,17,10,216,203,250,244,176,7,239,181,214,61,19,199,115,125,230,182,219,231,0,144,212,135,170,90,38,212,140,130,221,25,153,248,205,
40,237,174,110,35,159,84,78,249,0,0,236,167,107,107,43,196,88,196,52,112,105,177,38,41,99,29,183,168,204,20,11,117,214,77,88,184,182,248,105,46,102,139,84,132,64,191,252,44,60,178,137,177,209,102,179,
234,70,195,82,141,53,66,118,231,4,160,228,10,3,228,9,105,134,88,191,180,203,242,145,173,149,34,153,17,201,0,215,153,135,21,239,209,113,111,229,178,226,178,78,109,224,85,146,41,146,130,79,143,203,216,178,
213,11,45,185,22,120,121,0,53,215,117,245,247,93,250,116,212,237,192,238,108,64,97,183,154,203,164,167,211,80,116,107,83,173,142,235,1,35,115,1,36,58,44,176,178,116,230,52,49,31,123,183,92,90,108,142,
110,237,224,124,166,115,91,230,3,177,231,141,238,229,28,176,10,33,232,175,151,241,220,175,84,180,162,28,35,131,221,192,22,144,104,50,158,77,136,212,33,232,44,173,85,102,245,44,91,192,63,161,220,139,102,
113,159,127,11,105,95,76,115,189,172,201,190,142,27,214,26,164,168,166,34,15,14,64,247,148,247,37,88,84,111,89,214,253,23,209,79,153,15,142,83,227,208,111,11,196,245,244,118,29,248,190,80,142,52,243,120,
237,96,109,101,84,113,177,78,179,246,162,60,61,45,91,228,245,114,185,132,24,163,253,229,156,14,93,50,126,233,14,96,117,165,114,158,91,10,0,27,27,27,112,121,121,153,239,145,106,210,7,26,229,196,235,97,
14,22,248,72,176,178,129,0,203,86,40,111,94,96,227,68,223,234,106,211,215,32,107,171,47,158,185,65,223,159,238,141,121,245,161,131,110,93,224,42,241,253,121,215,9,158,125,115,153,22,134,57,251,82,115,
153,98,61,113,201,138,62,141,131,57,251,50,94,249,235,0,128,156,11,115,221,192,150,219,167,229,209,30,51,235,177,65,130,99,105,23,0,156,91,82,254,214,173,91,204,30,74,46,214,25,135,195,48,192,210,248,
81,4,166,18,212,140,30,64,220,190,125,27,0,0,174,175,175,43,153,117,220,28,237,222,115,81,104,103,240,137,29,50,51,211,2,93,247,172,243,67,116,117,102,229,19,189,163,242,217,123,107,80,201,120,239,221,
240,52,159,148,247,130,229,106,152,101,4,203,25,242,221,193,150,45,33,4,117,171,96,93,160,179,108,178,116,91,123,44,45,93,45,29,94,144,31,116,240,188,142,92,214,100,2,29,71,50,88,113,204,205,5,14,40,189,
32,234,165,119,187,161,0,176,185,181,9,59,59,59,83,36,228,122,181,193,74,248,176,162,156,37,68,205,23,167,202,161,78,23,44,132,54,250,98,177,128,187,119,239,194,56,142,112,115,115,227,187,62,56,121,68,
153,210,134,158,251,117,88,155,169,147,218,214,0,237,214,0,238,182,67,0,69,143,94,223,61,17,186,2,217,224,116,128,103,46,219,107,133,222,149,180,103,50,172,19,223,35,219,51,105,123,218,186,23,92,122,242,
88,229,245,148,97,177,189,222,122,103,246,36,127,217,85,92,75,237,126,177,88,176,183,141,246,216,210,19,198,244,153,175,53,124,73,246,57,250,18,79,41,223,48,12,176,185,185,201,210,104,240,128,204,3,157,
158,149,210,187,239,153,144,8,212,40,210,179,175,214,74,95,215,157,154,11,136,173,224,150,53,253,165,110,83,239,249,173,86,89,115,129,235,75,234,252,92,249,185,174,168,151,62,7,112,123,129,8,239,117,151,
205,118,241,122,245,174,99,11,64,205,166,164,219,184,78,72,223,37,196,159,52,35,168,62,61,101,28,147,73,64,253,86,28,217,115,12,199,251,97,224,111,45,8,192,159,49,178,64,203,186,247,242,73,219,44,64,241,
124,124,79,135,85,94,8,131,234,93,207,98,125,29,29,172,185,4,115,0,175,172,164,200,223,215,103,90,114,2,245,134,207,6,7,168,49,118,29,150,67,211,214,101,48,50,254,102,237,100,173,0,0,8,18,73,68,65,84,
115,88,99,47,160,181,182,75,188,242,116,253,252,199,45,12,218,158,21,77,179,230,254,156,192,116,66,152,246,176,0,212,95,183,88,99,165,8,150,94,27,53,102,55,133,25,24,66,206,171,185,111,244,224,106,8,252,
77,10,45,112,146,54,208,120,205,86,15,112,60,151,164,21,167,77,50,174,123,172,152,168,212,215,147,102,133,94,80,241,228,44,91,122,22,131,207,9,90,155,182,236,242,66,94,66,215,112,207,84,125,206,194,229,
45,122,52,79,11,68,172,189,180,158,49,38,245,120,227,86,222,23,81,239,94,127,139,196,58,140,75,75,227,193,249,72,8,164,95,27,171,95,9,123,105,112,46,130,184,111,115,221,62,173,51,19,104,241,199,0,172,
134,151,118,87,147,29,247,109,58,220,72,43,78,234,166,182,203,107,169,71,27,80,154,62,43,79,203,46,170,219,146,203,105,226,100,117,15,45,159,203,8,62,55,88,122,231,0,164,103,91,143,59,217,83,183,57,140,
200,155,188,236,203,200,51,236,232,169,163,181,16,208,126,79,92,162,112,210,34,134,115,147,223,107,58,166,10,0,12,18,8,105,253,197,184,15,254,78,3,102,145,50,195,48,192,50,86,146,243,66,107,34,82,57,218,
48,178,67,107,176,1,22,143,161,197,18,170,134,12,122,90,139,113,89,101,82,128,150,113,124,48,232,0,87,210,180,122,248,43,246,151,96,82,173,240,127,5,70,115,202,213,250,197,2,101,219,229,208,64,192,46,
215,124,222,50,210,203,62,16,73,151,18,4,184,189,116,204,200,103,91,189,177,217,51,110,61,86,215,179,165,98,18,9,143,181,70,126,175,177,50,111,88,198,88,210,61,185,37,75,235,88,129,62,143,153,124,222,
190,141,213,97,82,62,132,80,173,94,235,48,172,234,158,252,165,173,131,54,89,238,67,140,145,245,72,74,179,87,233,30,55,213,179,157,14,154,86,91,181,66,175,220,231,2,93,171,28,171,13,84,102,253,25,229,114,
93,1,128,124,67,81,251,132,61,186,49,150,167,34,81,208,92,224,99,26,171,85,29,98,25,195,22,107,131,88,160,180,229,186,185,122,58,242,247,186,123,115,159,179,76,0,199,227,100,155,142,227,8,75,237,252,140,
245,96,166,87,184,197,12,188,9,232,201,122,247,173,9,105,173,66,180,76,175,30,230,228,73,212,16,33,48,71,161,254,33,12,213,42,29,99,250,160,36,136,58,155,140,129,42,85,108,155,19,60,0,70,208,204,132,214,
101,198,95,38,124,142,187,229,201,207,201,211,146,109,49,61,175,13,123,203,83,199,109,128,124,234,158,229,145,171,35,72,80,133,122,235,131,0,88,146,197,125,168,18,151,231,146,117,238,80,177,89,2,157,90,
55,113,209,219,55,246,216,46,46,100,222,116,175,11,141,68,182,147,17,225,165,50,1,122,152,19,189,182,210,181,248,2,24,25,79,76,59,123,217,97,159,43,70,253,245,36,179,26,87,170,252,106,181,50,217,90,54,
87,1,52,11,212,180,48,7,204,180,54,246,221,130,62,247,42,137,219,96,219,91,143,230,32,39,172,67,246,109,107,127,169,5,204,244,17,44,141,61,104,135,123,215,1,226,185,31,210,176,236,233,97,73,86,124,174,
147,252,144,200,68,46,205,69,93,60,205,193,250,204,96,92,235,135,136,255,135,24,91,143,230,180,84,81,131,162,207,172,122,125,106,154,110,49,51,219,101,42,58,44,102,214,98,94,61,246,89,96,236,181,101,101,
171,33,79,227,228,243,139,217,213,53,9,96,199,226,194,189,153,207,10,169,74,243,25,209,255,47,189,180,191,89,63,57,114,52,176,190,87,244,120,32,104,186,74,13,128,233,98,49,141,249,226,201,244,220,123,
115,18,128,187,123,82,86,122,15,125,160,53,33,100,75,42,198,121,111,107,232,81,200,27,45,253,13,65,31,20,242,37,119,178,226,26,24,228,191,16,166,73,207,109,232,161,241,221,76,11,106,144,107,233,183,130,
201,34,43,250,206,211,191,212,94,147,7,186,150,124,237,126,3,84,3,139,144,176,47,229,62,122,76,141,218,87,228,245,69,72,91,128,90,219,9,84,174,151,69,105,219,30,52,160,155,54,221,184,229,96,155,215,15,
219,83,215,83,119,131,199,81,7,142,207,173,107,171,95,169,234,50,78,114,170,145,41,111,170,184,186,99,140,217,211,51,93,194,207,13,165,1,138,219,164,161,173,246,41,234,90,7,222,115,23,176,151,217,152,
43,64,224,205,165,178,47,136,85,126,107,128,89,245,160,249,228,181,148,211,218,195,114,79,189,65,56,151,53,91,242,210,30,100,62,76,126,6,70,125,177,253,48,161,166,123,31,43,240,253,155,38,200,16,253,170,
25,14,115,234,117,203,172,184,186,237,215,99,105,26,120,91,186,188,246,200,115,6,117,151,132,42,63,13,235,57,112,250,60,255,63,1,44,57,24,100,161,150,59,167,201,210,251,222,138,247,236,63,85,113,150,110,
37,190,135,97,181,246,75,122,226,91,160,35,169,183,86,190,167,191,53,1,188,96,178,78,178,16,120,229,247,150,103,182,163,211,47,115,234,210,227,126,205,5,174,158,248,222,180,185,237,36,3,206,67,207,115,
105,45,164,154,123,103,217,39,31,246,166,101,126,137,112,115,115,179,62,96,245,80,100,13,156,56,101,212,15,135,150,228,249,12,194,115,1,171,125,140,0,144,222,41,205,127,233,233,118,25,243,138,195,125,
240,117,152,143,238,146,146,235,65,183,83,186,79,235,184,144,95,202,237,236,13,234,216,137,245,239,210,148,81,199,104,79,130,30,247,176,39,244,46,18,169,201,107,166,107,49,237,214,226,208,187,145,159,
221,35,205,107,40,66,77,15,192,219,115,146,114,158,183,208,203,48,91,245,242,78,37,20,153,244,80,117,115,211,189,181,90,247,78,78,78,73,253,124,189,172,203,75,163,212,191,157,87,167,160,149,60,57,219,
21,74,134,186,14,249,212,107,157,143,6,109,245,98,233,164,252,168,29,63,9,245,219,52,188,87,212,244,78,94,173,15,102,133,96,127,174,107,110,176,84,184,175,179,201,155,130,82,151,63,150,123,236,181,100,
189,188,8,188,101,60,114,247,76,251,101,146,149,19,82,157,100,217,61,54,244,252,26,57,199,181,237,145,157,235,97,176,131,66,13,128,84,207,97,101,197,173,51,244,138,209,196,138,244,101,12,34,71,39,130,
7,12,146,21,121,172,9,31,148,198,84,237,235,27,189,110,98,171,161,189,180,117,227,53,176,234,113,67,32,179,59,158,207,99,135,102,189,66,125,120,37,225,160,239,34,153,114,145,255,144,176,142,203,57,55,
180,86,116,141,241,203,208,197,112,140,80,127,168,86,203,219,102,238,42,32,76,89,177,151,90,115,194,138,163,19,191,229,165,96,57,88,22,198,209,122,106,30,212,200,222,228,50,223,85,246,194,130,62,75,184,
206,138,236,13,70,252,88,165,213,48,189,160,36,27,217,106,116,100,35,45,87,71,183,167,126,185,95,43,175,100,81,44,78,198,59,147,69,182,127,143,91,82,91,175,228,233,34,72,84,40,86,41,193,123,45,52,213,
208,98,99,212,175,83,75,227,105,42,123,181,24,168,200,147,197,166,181,54,47,108,202,215,161,214,221,99,210,100,198,113,116,23,188,30,54,36,193,138,205,175,88,152,200,28,187,123,92,53,15,88,188,125,170,
76,253,72,112,95,37,190,70,160,109,185,88,44,96,153,215,66,252,35,141,15,198,132,208,100,27,193,99,89,158,107,55,39,190,186,71,121,197,30,181,252,48,117,130,225,182,34,163,208,190,22,196,63,208,90,244,
98,199,247,238,7,84,182,17,166,219,231,182,0,164,23,51,106,105,28,164,122,86,90,187,156,126,87,106,206,88,41,147,180,99,178,89,101,68,5,20,215,176,133,168,163,10,234,120,28,215,34,77,107,221,8,177,154,
235,218,188,179,198,6,139,35,122,230,128,149,188,183,136,129,39,11,18,59,102,158,157,147,161,5,244,233,109,13,224,79,124,79,65,175,188,69,181,105,90,239,70,96,75,222,186,31,27,250,100,208,88,95,139,114,
183,236,180,228,53,150,194,246,183,4,128,90,238,79,201,11,96,79,87,41,219,7,74,115,242,124,169,176,14,3,146,172,96,238,94,156,5,14,38,67,150,194,68,46,176,104,50,166,9,59,215,198,25,192,196,100,66,201,
75,237,72,222,0,1,179,80,151,33,109,102,219,59,18,96,34,176,211,235,82,87,101,191,108,139,240,101,198,68,170,23,170,172,23,233,16,194,252,147,238,61,242,114,194,160,255,174,101,245,152,71,11,136,52,29,
189,121,122,203,159,27,55,119,47,107,74,52,147,232,38,186,6,226,125,140,75,151,239,235,203,255,63,224,164,5,179,45,167,191,211,212,100,68,76,110,11,0,96,31,165,156,189,251,88,86,59,241,109,8,78,227,52,
23,10,243,168,207,236,54,198,179,197,128,100,156,126,95,168,87,85,14,99,111,105,248,105,174,167,166,91,109,55,234,133,81,192,81,66,217,96,239,199,29,58,183,255,31,1,62,84,94,183,127,217,143,0,0,0,0,73,
69,78,68,174,66,96,130,0,0};

const char* ParaphrasisAudioProcessorEditor::background2_png = (const char*) resource_ParaphrasisAudioProcessorEditor_background2_png;
const int ParaphrasisAudioProcessorEditor::background2_pngSize = 51421;

// JUCER_RESOURCE: led_off_png, 599, "../Resources/Graphics/led_off.png"
static const unsigned char resource_ParaphrasisAudioProcessorEditor_led_off_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,24,0,0,0,24,8,6,0,0,0,224,119,61,248,0,0,0,6,98,75,71,68,0,255,
0,255,0,255,160,189,167,147,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,0,7,116,73,77,69,7,222,8,1,3,49,1,223,48,114,38,0,0,1,228,73,68,65,84,72,199,237,148,189,111,82,97,20,198,127,84,
168,151,143,98,239,5,241,22,27,196,6,155,152,24,219,193,193,218,205,196,205,196,24,23,157,140,137,97,114,112,114,102,50,38,110,174,254,39,20,227,228,226,32,105,117,211,5,241,35,90,240,250,190,220,239,
123,225,186,220,129,165,20,232,226,192,147,156,229,205,115,62,242,60,239,57,176,192,2,255,61,78,77,67,106,52,26,75,103,117,253,193,249,114,249,117,161,80,120,154,203,231,205,126,175,183,63,77,110,226,
56,66,189,94,95,51,12,227,75,173,86,203,172,170,42,142,109,179,127,112,64,179,217,196,50,205,117,224,251,164,252,228,113,3,152,150,245,99,107,123,27,253,92,145,173,171,87,184,123,239,62,158,235,114,99,
103,135,86,171,245,57,138,162,21,96,56,151,68,213,106,245,209,165,205,205,59,237,118,27,211,28,240,252,197,75,132,16,24,134,65,183,219,69,211,180,148,109,219,223,128,15,71,213,88,154,228,207,122,165,242,
76,74,73,191,223,167,245,230,45,82,74,6,82,178,187,123,157,108,54,131,16,2,224,201,164,65,39,53,80,76,41,253,78,167,131,16,2,41,37,50,74,130,186,6,217,85,42,149,139,248,190,15,144,3,78,207,35,81,222,243,
188,244,112,52,186,41,132,192,73,42,148,54,54,40,95,174,178,162,230,121,255,233,35,12,67,8,135,175,98,137,156,89,127,81,17,168,170,154,246,110,224,250,203,97,58,71,170,120,134,72,81,8,131,0,76,19,122,
135,96,59,215,128,14,208,155,85,34,15,112,140,63,226,113,152,82,32,189,76,144,128,48,12,33,8,192,117,2,108,231,97,204,243,230,217,131,20,80,2,46,0,101,224,22,186,126,155,40,242,17,98,15,215,221,139,119,
224,43,240,11,8,102,109,144,136,13,44,1,58,160,142,153,233,1,127,129,159,192,111,192,4,162,89,23,45,2,44,224,48,158,206,26,107,224,2,70,220,196,58,170,248,84,167,34,246,41,5,100,0,37,126,115,226,8,128,
209,137,110,209,24,47,49,198,143,198,98,129,147,225,31,221,7,191,132,145,124,92,114,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* ParaphrasisAudioProcessorEditor::led_off_png = (const char*) resource_ParaphrasisAudioProcessorEditor_led_off_png;
const int ParaphrasisAudioProcessorEditor::led_off_pngSize = 599;

// JUCER_RESOURCE: led_on_png, 1195, "../Resources/Graphics/led_on.png"
static const unsigned char resource_ParaphrasisAudioProcessorEditor_led_on_png[] = { 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,24,0,0,0,24,8,6,0,0,0,224,119,61,248,0,0,0,6,98,75,71,68,0,255,
0,255,0,255,160,189,167,147,0,0,0,9,112,72,89,115,0,0,11,19,0,0,11,19,1,0,154,156,24,0,0,0,7,116,73,77,69,7,222,8,1,3,49,32,147,89,98,120,0,0,4,56,73,68,65,84,72,199,181,150,205,139,149,85,28,199,63,231,
60,231,121,187,47,58,218,140,142,86,76,42,76,121,163,23,84,106,209,155,67,65,17,25,212,78,130,218,245,15,212,162,217,105,17,4,10,17,181,136,8,220,148,109,35,55,69,144,211,162,69,89,144,134,55,8,180,113,
28,25,156,25,188,175,207,251,121,206,105,49,87,175,183,209,52,168,7,158,213,57,231,251,229,247,253,254,206,239,123,4,183,250,172,21,204,225,144,224,208,71,2,80,195,16,82,178,159,18,33,236,63,29,23,55,
93,57,100,37,13,20,41,46,14,30,2,15,131,11,128,164,192,146,83,146,19,80,208,68,115,72,152,219,39,56,105,21,43,184,20,4,24,2,20,62,14,62,57,30,0,30,57,37,25,154,12,73,138,75,202,4,5,51,66,223,154,224,164,
85,244,241,72,8,40,9,16,132,48,248,13,254,160,130,12,72,128,4,75,130,67,74,72,74,141,252,239,36,98,157,44,83,120,64,128,34,196,165,130,166,130,67,69,73,42,86,19,2,8,69,162,13,49,37,49,138,152,130,24,77,
2,164,92,32,191,94,46,57,98,230,54,28,170,40,170,184,72,60,36,62,138,64,73,42,214,82,69,80,67,80,179,150,170,146,84,80,4,72,124,36,30,85,92,170,40,182,225,96,173,88,79,112,24,129,135,3,56,100,40,92,92,
10,60,44,129,181,4,64,136,160,130,160,2,132,214,18,96,9,40,240,112,113,201,80,128,131,135,195,225,161,50,234,26,65,3,65,136,36,193,65,161,48,184,56,184,202,226,61,243,219,199,65,59,43,103,122,121,249,
92,20,39,129,179,227,145,175,230,119,204,124,173,4,185,118,112,49,184,168,1,193,56,146,234,144,64,140,152,123,17,31,69,136,165,138,67,29,67,253,192,217,15,239,185,18,235,99,141,93,83,254,150,205,99,20,
121,206,217,249,37,190,59,125,142,68,219,87,56,248,238,159,72,122,148,244,16,68,104,18,238,38,187,106,182,188,166,255,31,8,2,4,26,9,3,169,222,121,202,237,37,217,241,71,119,239,244,31,152,222,197,139,79,
60,196,231,173,45,156,234,6,60,190,231,126,164,227,30,227,237,39,189,107,251,53,146,128,53,172,129,15,114,164,139,124,4,10,129,131,160,68,220,213,216,247,252,198,208,103,238,146,225,84,186,129,151,190,
92,34,210,208,221,120,39,223,175,74,198,119,52,60,38,166,95,160,28,156,81,8,252,209,206,28,18,108,26,44,40,4,18,193,236,94,103,243,134,250,193,152,10,217,246,105,230,46,68,196,198,161,23,222,193,236,179,
211,76,221,215,160,51,54,129,216,189,231,101,102,247,58,200,1,193,245,88,235,42,24,185,33,198,143,113,245,66,234,16,69,125,122,50,164,51,54,137,153,28,131,49,151,253,15,111,32,159,242,96,123,37,68,88,
239,102,48,195,46,106,97,153,4,52,22,137,69,8,247,242,226,249,147,245,201,123,119,102,26,212,228,24,175,54,124,170,97,134,231,20,124,186,184,2,166,143,253,118,238,155,193,156,178,24,44,254,0,107,29,1,
64,134,69,99,113,214,54,244,46,158,251,81,205,76,190,214,173,143,43,227,106,78,180,250,152,229,152,78,183,13,81,31,162,8,174,156,255,1,128,18,75,137,37,195,174,247,64,8,203,52,150,20,139,194,0,37,58,75,
41,243,168,115,226,163,247,77,13,168,103,180,226,46,157,110,111,13,188,219,46,197,241,207,142,82,20,9,58,75,129,18,133,33,101,13,107,48,198,135,21,172,96,217,132,37,193,80,98,192,196,148,69,219,244,86,
23,229,7,111,28,177,59,247,238,227,233,199,246,16,199,154,95,127,57,35,126,63,253,179,137,187,139,24,211,6,19,35,49,56,24,234,88,86,110,36,81,19,203,20,134,42,37,26,77,150,167,72,221,161,204,151,77,153,
187,114,225,204,79,124,113,190,9,64,218,239,155,60,93,165,204,151,209,121,155,44,79,209,104,28,74,86,49,92,24,18,136,145,97,247,9,138,77,248,64,72,65,133,183,26,117,252,234,56,65,109,43,126,125,43,110,
88,91,243,42,234,81,68,203,164,253,203,100,209,42,239,53,123,184,196,64,66,139,140,215,209,87,37,26,182,169,16,150,37,74,34,52,17,5,134,156,35,205,132,36,105,17,39,151,72,251,243,36,209,2,73,180,64,158,
204,19,39,151,72,146,22,71,154,9,134,156,136,130,8,205,210,104,140,222,94,224,188,249,96,133,208,171,64,117,45,112,136,50,146,60,230,232,153,248,223,5,206,255,16,153,55,190,201,51,66,211,36,195,37,194,
210,197,208,65,211,6,90,64,11,77,27,67,7,75,23,151,136,230,112,122,222,254,171,226,63,122,182,252,5,191,178,14,53,194,182,244,166,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* ParaphrasisAudioProcessorEditor::led_on_png = (const char*) resource_ParaphrasisAudioProcessorEditor_led_on_png;
const int ParaphrasisAudioProcessorEditor::led_on_pngSize = 1195;


//[EndFile] You can add extra defines here...
//[/EndFile]

