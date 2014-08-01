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
    addAndMakeVisible (knob = new teragon::ImageKnobLarge (parameters, "Sample Pitch", r));
    knob->setName ("knob");

    addAndMakeVisible (knob2 = new teragon::ImageKnobLarge (parameters, "Frequency Resolution", r));
    knob2->setName ("knob");

    addAndMakeVisible (sampleLbl = new Label ("sampleLbl",
                                              String::empty));
    sampleLbl->setFont (Font (Font::getDefaultMonospacedFontName(), 13.50f, Font::plain));
    sampleLbl->setJustificationType (Justification::centredLeft);
    sampleLbl->setEditable (false, false, false);
    sampleLbl->setColour (Label::backgroundColourId, Colour (0x009f9d9d));
    sampleLbl->setColour (TextEditor::textColourId, Colours::black);
    sampleLbl->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (selectBtn = new ImageButton ("selectBtn"));
    selectBtn->setButtonText (TRANS("new button"));
    selectBtn->addListener (this);

    selectBtn->setImages (false, true, true,
                          Image(), 1.000f, Colour (0x00000000),
                          Image(), 1.000f, Colour (0x00000000),
                          Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (analyzeBtn = new ImageButton ("analyzeBtn"));
    analyzeBtn->setButtonText (TRANS("new button"));
    analyzeBtn->addListener (this);

    analyzeBtn->setImages (false, true, true,
                           Image(), 1.000f, Colour (0x00000000),
                           Image(), 1.000f, Colour (0x00000000),
                           Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (pitchLbl = new Label ("pitchLbl",
                                             TRANS("20k")));
    pitchLbl->setFont (Font (13.00f, Font::plain));
    pitchLbl->setJustificationType (Justification::centred);
    pitchLbl->setEditable (true, true, false);
    pitchLbl->setColour (Label::textColourId, Colour (0xf2c3c3c3));
    pitchLbl->setColour (TextEditor::textColourId, Colours::black);
    pitchLbl->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    pitchLbl->setColour (TextEditor::highlightColourId, Colour (0x40ffffff));
    pitchLbl->addListener (this);

    addAndMakeVisible (resolutionLbl = new Label ("resolutionLbl",
                                                  TRANS("20k")));
    resolutionLbl->setFont (Font (13.00f, Font::plain));
    resolutionLbl->setJustificationType (Justification::centred);
    resolutionLbl->setEditable (true, true, false);
    resolutionLbl->setColour (Label::textColourId, Colour (0xffc3c3c3));
    resolutionLbl->setColour (Label::outlineColourId, Colour (0x00ffffff));
    resolutionLbl->setColour (TextEditor::textColourId, Colours::black);
    resolutionLbl->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    resolutionLbl->setColour (TextEditor::highlightColourId, Colour (0x40ffffff));
    resolutionLbl->addListener (this);

    addAndMakeVisible (resolutionBtn = new ImageButton ("analyzeBtn"));
    resolutionBtn->setButtonText (TRANS("new button"));
    resolutionBtn->addListener (this);

    resolutionBtn->setImages (false, true, true,
                              Image(), 1.000f, Colour (0x00000000),
                              Image(), 1.000f, Colour (0x00000000),
                              Image(), 1.000f, Colour (0x00000000));
    cachedImage_background2_png = ImageCache::getFromMemory (background2_png, background2_pngSize);

    //[UserPreSize]
    // load custom Paraphrasis font
    Font font = Font(Typeface::createSystemTypefaceFor(Resources::anitaSemiSquare_ttf, Resources::anitaSemiSquare_ttfSize));
    font.setHeight(11.5f);
    pitchLbl->setFont(font);
    resolutionLbl->setFont(font);

    // remove the ugly purple border from label's text edit
    LookAndFeel& laf = LookAndFeel::getDefaultLookAndFeel();
    laf.setColour(TextEditor::focusedOutlineColourId, Colour (0x00ffffff));
    laf.setColour(TextEditor::outlineColourId, Colour (0x00ffffff));
    laf.setColour(TextEditor::highlightColourId, Colour (0x40ffffff));
    LookAndFeel::setDefaultLookAndFeel(&laf);

    // load images for the image buttons
    selectBtn->setImages (false, true, true,
                          ImageCache::getFromMemory (Resources::button_select_normal_png, Resources::button_select_normal_pngSize), 1.000f, Colour (0x00000000),
                          Image(), 1.000f, Colour (0x00000000),
                          ImageCache::getFromMemory (Resources::button_select_down_png, Resources::button_select_down_pngSize), 1.000f, Colour (0x00000000));
    analyzeBtn->setImages (false, true, true,
                          ImageCache::getFromMemory (Resources::button_analyze_normal_png, Resources::button_analyze_normal_pngSize), 1.000f, Colour (0x00000000),
                          Image(), 1.000f, Colour (0x00000000),
                          ImageCache::getFromMemory (Resources::button_analyze_down_png, Resources::button_analyze_down_pngSize), 1.000f, Colour (0x00000000));
    resolutionBtn->setImages (false, true, true,
                           ImageCache::getFromMemory (Resources::button_analyze_normal_png, Resources::button_analyze_normal_pngSize), 1.000f, Colour (0x00000000),
                           Image(), 1.000f, Colour (0x00000000),
                           ImageCache::getFromMemory (Resources::button_analyze_down_png, Resources::button_analyze_down_pngSize), 1.000f, Colour (0x00000000));

    // register this as parameter observer
    parameters.get(kParameterSamplePitch_name)->addObserver(this);
    parameters.get(kParameterFrequencyResolution_name)->addObserver(this);

    // set last values
    onParameterUpdated(parameters.get(kParameterFrequencyResolution_name));
    onParameterUpdated(parameters.get(kParameterSamplePitch_name));
    onParameterUpdated(parameters.get(kParameterLastSamplePath_name));
    //[/UserPreSize]

    setSize (300, 300);
    
    detector.setMinMaxFrequency(kParameterSamplePitch_minValue, kParameterSamplePitch_maxValue);
    detector.setDetectionMethod(drow::PitchDetector::squareDifferenceFunction);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ParaphrasisAudioProcessorEditor::~ParaphrasisAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    // unregister observer
    parameters.get(kParameterSamplePitch_name)->removeObserver(this);
    parameters.get(kParameterFrequencyResolution_name)->removeObserver(this);
    //[/Destructor_pre]

    knob = nullptr;
    knob2 = nullptr;
    sampleLbl = nullptr;
    selectBtn = nullptr;
    analyzeBtn = nullptr;
    pitchLbl = nullptr;
    resolutionLbl = nullptr;
    resolutionBtn = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ParaphrasisAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xffbdbdbd));

    g.setColour (Colours::black);
    g.drawImage (cachedImage_background2_png,
                 0, 0, 300, 300,
                 0, 0, cachedImage_background2_png.getWidth(), cachedImage_background2_png.getHeight());

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ParaphrasisAudioProcessorEditor::resized()
{
    knob->setBounds (60, 129, 64, 64);
    knob2->setBounds (176, 129, 64, 64);
    sampleLbl->setBounds (24, 45, 176, 20);
    selectBtn->setBounds (194, 41, 88, 30);
    analyzeBtn->setBounds (105, 230, 92, 48);
    pitchLbl->setBounds (57, 192, 70, 24);
    resolutionLbl->setBounds (173, 192, 70, 24);
    resolutionBtn->setBounds (128, 155, 44, 32);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ParaphrasisAudioProcessorEditor::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == selectBtn)
    {
        //[UserButtonCode_selectBtn] -- add your button handler code here..
        String filePath = parameters.get(kParameterLastSamplePath_name)->getDisplayText();
        File lastFile;
        if ( filePath.isEmpty() )
            lastFile = File::getSpecialLocation (File::userHomeDirectory);
        else
            lastFile = File(filePath);

        FileChooser myChooser ("Please select the sample file you want to load...", lastFile, formatManager.getWildcardForAllFormats());
        if (myChooser.browseForFileToOpen())
        {
            File sampleFile (myChooser.getResult());
            if ( sampleFile.exists() )
            {
                sampleLbl->setText(sampleFile.getFileName(), juce::dontSendNotification);
                path = sampleFile.getFullPathName().toRawUTF8();
                parameters.setData(kParameterLastSamplePath_name, path.c_str(), path.length());
                
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
    else if (buttonThatWasClicked == analyzeBtn)
    {
        //[UserButtonCode_analyzeBtn] -- add your button handler code here..
        getProcessor()->loadSample();
        //[/UserButtonCode_analyzeBtn]
    }
    else if (buttonThatWasClicked == resolutionBtn)
    {
        //[UserButtonCode_resolutionBtn] -- add your button handler code here..
        parameters.set(kParameterFrequencyResolution_name, kDefaultPitchResolutionRation * parameters.get(kParameterSamplePitch_name)->getValue());
        //[/UserButtonCode_resolutionBtn]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void ParaphrasisAudioProcessorEditor::labelTextChanged (Label* labelThatHasChanged)
{
    //[UserlabelTextChanged_Pre]
    //[/UserlabelTextChanged_Pre]

    if (labelThatHasChanged == pitchLbl)
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
    else if (labelThatHasChanged == resolutionLbl)
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
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ParaphrasisAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public ParameterObserver"
                 constructorParams="ParaphrasisAudioProcessor* ownerFilter, teragon::ConcurrentParameterSet&amp; p, teragon::ResourceCache *r, AudioFormatManager &amp;formatManager"
                 variableInitialisers="AudioProcessorEditor(ownerFilter),&#10;    parameters(p),&#10;    resources(r),&#10;    formatManager(formatManager)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="300" initialHeight="300">
  <BACKGROUND backgroundColour="ffbdbdbd">
    <IMAGE pos="0 0 300 300" resource="background2_png" opacity="1" mode="0"/>
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
         fontsize="13.5" bold="0" italic="0" justification="33"/>
  <IMAGEBUTTON name="selectBtn" id="63e2e3bfd7cbefd5" memberName="selectBtn"
               virtualName="" explicitFocusOrder="0" pos="194 41 88 30" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
  <IMAGEBUTTON name="analyzeBtn" id="56836504f0a08694" memberName="analyzeBtn"
               virtualName="" explicitFocusOrder="0" pos="105 230 92 48" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
  <LABEL name="pitchLbl" id="400eaffd0e2f9582" memberName="pitchLbl" virtualName=""
         explicitFocusOrder="0" pos="57 192 70 24" textCol="f2c3c3c3"
         edTextCol="ff000000" edBkgCol="0" hiliteCol="40ffffff" labelText="20k"
         editableSingleClick="1" editableDoubleClick="1" focusDiscardsChanges="0"
         fontname="Default font" fontsize="13" bold="0" italic="0" justification="36"/>
  <LABEL name="resolutionLbl" id="c17f4e0142be49bf" memberName="resolutionLbl"
         virtualName="" explicitFocusOrder="0" pos="173 192 70 24" textCol="ffc3c3c3"
         outlineCol="ffffff" edTextCol="ff000000" edBkgCol="0" hiliteCol="40ffffff"
         labelText="20k" editableSingleClick="1" editableDoubleClick="1"
         focusDiscardsChanges="0" fontname="Default font" fontsize="13"
         bold="0" italic="0" justification="36"/>
  <IMAGEBUTTON name="analyzeBtn" id="5822ed37b120e159" memberName="resolutionBtn"
               virtualName="" explicitFocusOrder="0" pos="128 155 44 32" buttonText="new button"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1" colourNormal="0" resourceOver=""
               opacityOver="1" colourOver="0" resourceDown="" opacityDown="1"
               colourDown="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif

//==============================================================================
// Binary resources - be careful not to edit any of these sections!

// JUCER_RESOURCE: background2_png, 50787, "../Resources/Graphics/background2.png"
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
35,111,162,44,75,108,111,111,99,105,105,9,155,155,155,73,191,240,188,60,78,218,12,181,233,225,195,135,88,91,91,139,244,159,78,167,120,240,224,1,78,78,78,240,255,245,246,109,107,118,220,54,214,96,237,45,
117,75,173,115,171,157,137,124,76,190,196,115,49,111,50,223,60,212,60,192,220,207,171,205,69,226,88,178,99,201,178,91,103,245,185,139,255,5,139,36,0,46,128,172,45,229,103,34,119,21,15,32,200,34,23,22,
184,89,172,253,253,125,163,115,234,95,207,179,176,250,89,140,115,146,6,172,122,23,125,23,142,179,104,206,124,61,182,55,178,125,34,4,162,240,191,255,251,191,49,221,216,140,65,199,233,120,62,224,244,137,
163,149,224,4,226,195,53,44,238,93,77,171,190,157,76,147,245,115,25,222,171,58,30,179,227,191,219,122,64,136,192,136,235,36,245,151,229,50,19,211,231,127,229,98,229,72,151,197,205,214,147,22,62,131,165,
114,15,68,26,93,120,91,156,252,220,117,245,126,245,225,65,131,155,21,214,184,51,94,153,158,123,178,107,154,55,145,188,224,129,64,175,158,116,157,198,122,157,152,68,4,250,30,201,214,6,86,3,223,167,184,
131,150,193,207,218,89,249,181,204,16,234,137,163,86,157,66,22,35,21,40,207,141,237,150,182,252,231,97,254,23,197,233,9,172,255,34,151,80,203,180,234,32,82,84,89,177,59,157,255,83,38,65,217,223,209,97,
15,86,158,90,53,158,84,30,211,204,113,249,37,107,43,15,138,71,109,183,228,11,125,156,157,222,107,234,239,245,121,36,162,160,104,20,50,30,174,140,216,95,227,202,147,93,234,186,252,103,142,13,141,243,250,
171,97,199,170,126,175,205,154,161,123,50,137,218,245,210,214,32,212,177,101,201,230,229,172,177,198,219,208,120,6,206,184,68,222,6,4,22,117,239,181,9,237,209,210,247,61,32,203,215,115,140,242,60,172,
28,52,83,105,38,128,209,120,78,125,189,7,168,101,161,70,20,151,20,132,236,207,106,125,203,61,144,133,208,223,213,109,113,81,37,195,89,94,35,50,220,215,81,230,19,99,251,65,83,100,48,44,153,86,94,43,78,
111,34,237,149,27,97,33,40,48,98,108,50,70,43,140,228,43,108,53,112,150,171,242,108,234,203,181,37,14,140,179,244,107,22,27,251,75,153,202,52,217,120,33,123,82,54,253,166,229,176,60,230,65,133,6,40,232,
184,17,183,206,10,61,128,26,45,111,177,61,126,61,162,219,104,30,161,91,164,222,241,50,178,33,222,123,130,218,95,245,228,46,17,221,60,242,94,30,153,210,116,92,138,172,174,143,1,80,89,46,2,42,49,32,168,
238,180,205,101,244,177,181,90,215,82,62,180,191,146,104,102,106,89,97,203,226,163,126,177,6,248,8,139,208,114,122,44,107,136,37,133,246,151,202,85,229,59,161,184,76,198,88,23,192,18,99,33,233,188,111,
27,230,144,245,36,48,166,6,92,37,228,138,161,60,163,233,122,220,242,182,241,118,89,114,71,24,81,47,30,129,187,181,150,173,137,11,143,227,175,31,89,122,246,244,231,99,115,218,76,237,241,50,117,210,49,196,
92,246,90,136,3,223,2,99,33,84,7,62,7,45,228,50,162,201,39,192,100,10,114,221,39,239,85,138,50,175,158,252,232,122,212,29,209,96,194,255,202,235,44,175,99,29,12,43,11,7,77,80,204,141,180,5,175,187,140,
145,190,66,148,211,207,150,171,21,66,214,205,106,74,11,110,58,237,95,21,122,242,69,186,180,102,245,146,229,215,204,155,7,125,248,158,55,193,173,49,101,77,76,52,15,172,16,141,107,84,174,55,175,56,152,122,
222,140,215,14,34,249,225,218,30,64,107,227,192,119,186,251,192,197,253,97,12,108,229,76,119,139,49,149,206,0,239,228,33,182,16,103,255,51,94,222,95,175,12,17,3,46,106,65,206,43,199,34,27,214,147,226,
243,31,135,109,1,11,226,213,181,90,55,178,221,182,84,95,95,78,15,192,242,95,13,64,252,195,164,94,59,70,193,105,100,82,202,2,185,130,117,245,52,249,6,152,66,101,96,253,131,4,97,249,8,12,55,212,25,27,42,
52,9,245,245,234,254,235,4,15,92,173,54,136,177,151,219,144,34,210,181,144,201,89,107,181,27,49,230,119,9,195,18,31,68,223,39,47,37,22,89,81,25,249,74,12,100,127,108,245,190,142,158,107,104,165,231,201,
96,201,211,244,145,168,93,132,108,216,210,204,174,41,214,193,13,126,73,180,38,108,175,29,89,22,119,16,208,207,253,163,15,222,138,179,210,80,191,136,120,40,133,129,40,144,107,201,68,229,121,64,237,176,
210,120,252,136,44,145,182,48,74,21,217,45,39,210,35,53,50,70,220,27,43,14,165,105,128,241,38,184,204,43,127,253,227,121,214,26,63,93,191,117,173,235,65,198,170,151,70,252,231,115,157,78,114,204,9,102,
84,54,12,115,93,105,1,172,13,120,179,33,51,169,5,180,204,190,44,154,148,244,45,111,236,232,89,86,86,220,204,222,37,68,233,89,17,93,143,201,22,10,40,249,15,182,15,74,75,179,33,144,100,20,151,212,19,13,
2,125,173,235,177,242,88,32,197,243,162,193,26,163,189,56,111,5,196,62,129,96,44,179,87,14,212,165,117,26,97,6,232,100,135,17,247,111,100,66,175,149,233,231,103,99,47,51,192,60,57,213,59,119,129,228,243,
228,103,188,89,6,169,196,69,124,214,5,100,249,196,152,162,42,167,221,46,79,142,215,118,111,60,10,93,192,56,215,233,214,203,207,233,182,55,86,234,184,12,249,93,194,68,197,148,213,91,230,112,179,182,146,
23,162,141,135,102,86,203,30,92,119,50,53,101,83,77,136,65,240,186,61,86,135,66,47,31,74,183,100,161,143,57,36,221,215,3,107,15,100,43,243,138,226,121,115,93,197,179,8,202,217,77,166,175,169,131,168,117,
139,115,246,148,71,222,123,140,107,36,172,5,151,146,111,81,38,15,120,60,97,100,137,79,97,89,226,190,122,40,126,62,146,125,154,231,77,88,214,64,249,222,187,228,57,200,158,239,50,170,210,178,150,97,91,6,
213,51,178,136,233,245,193,188,29,107,189,107,41,195,79,23,80,28,107,93,91,209,114,198,242,74,23,138,94,33,1,96,124,113,12,53,96,180,225,57,47,186,207,127,189,119,254,214,176,64,175,14,148,199,75,31,1,
41,30,111,13,18,143,189,229,116,46,215,218,58,2,235,143,234,149,29,245,124,150,11,23,92,151,44,157,118,142,173,11,105,125,189,116,216,151,165,156,241,107,217,72,61,121,130,140,232,197,243,6,118,63,48,
174,209,54,6,84,159,197,122,60,249,94,153,81,6,84,174,165,131,1,235,44,172,145,147,20,106,141,58,175,155,255,67,134,183,150,75,71,62,136,56,154,136,66,20,178,167,105,99,29,145,220,42,110,161,55,15,150,
123,131,24,202,40,251,176,210,172,58,80,199,161,184,92,102,36,244,44,30,215,205,58,112,110,196,125,42,125,23,235,96,240,116,29,5,127,43,79,8,65,26,39,170,48,160,13,207,104,221,109,69,40,138,175,65,98,
160,43,94,152,81,77,200,172,196,97,218,35,186,54,160,162,159,171,102,174,198,228,67,125,132,222,135,229,215,149,181,202,177,1,193,41,4,19,44,155,188,170,109,124,172,66,61,140,31,94,26,246,21,219,241,33,
78,237,88,193,194,184,167,198,63,13,88,245,228,123,228,82,61,49,206,201,37,212,19,25,77,110,164,144,101,249,215,2,68,166,198,198,121,3,48,140,208,94,75,23,139,141,120,212,89,203,28,161,209,158,30,92,118,
163,135,218,218,209,211,103,212,13,211,250,104,107,200,211,184,220,253,253,125,122,240,224,1,205,243,44,94,200,213,97,111,111,143,30,60,120,64,49,198,154,15,100,221,219,223,19,242,60,38,162,39,90,29,75,
68,72,56,63,69,193,146,53,146,230,201,96,216,225,26,114,108,56,137,136,90,111,65,220,199,246,27,135,8,156,123,215,252,30,25,110,164,103,175,13,181,15,228,156,182,176,193,2,202,6,248,28,38,152,255,226,
207,124,49,235,110,53,64,95,115,183,205,90,184,215,155,207,70,100,143,178,176,53,108,205,210,29,185,103,80,30,133,229,228,5,31,248,172,250,44,67,96,221,231,201,33,100,242,69,140,38,255,88,59,120,158,12,
94,232,217,17,165,115,150,30,60,120,64,95,127,253,53,61,122,244,136,254,246,183,191,193,143,37,156,158,158,210,195,135,15,233,171,175,190,162,135,15,31,154,249,78,78,78,232,225,195,135,244,245,215,95,
187,249,70,88,229,8,208,244,216,160,55,201,237,184,190,107,136,234,77,219,72,214,3,106,174,187,230,105,253,56,111,242,143,214,17,99,22,93,16,185,94,3,61,60,143,108,164,204,136,87,196,241,101,243,159,255,
249,159,255,157,1,37,76,45,168,100,234,166,7,55,82,44,198,88,206,56,231,157,163,203,160,251,94,154,190,231,150,180,135,210,61,170,202,235,245,216,138,149,198,79,109,109,242,197,88,44,99,160,214,183,183,
254,121,245,6,98,223,40,100,249,71,1,221,10,229,199,20,96,56,62,124,248,64,167,167,167,244,248,241,99,58,60,60,164,119,239,222,209,213,213,85,35,227,253,251,247,229,120,151,124,12,244,229,146,47,128,124,
252,184,104,46,47,63,139,220,198,230,159,210,79,223,7,213,47,33,84,67,147,199,250,20,210,115,155,54,83,250,74,241,84,255,241,189,135,141,204,64,85,22,120,86,77,189,33,48,213,209,38,93,233,22,67,192,137,
81,185,132,217,37,163,154,158,117,160,140,57,54,56,5,149,55,235,203,211,180,46,89,87,87,79,117,127,112,112,32,238,173,249,108,225,1,143,11,83,160,205,127,253,215,127,253,119,118,201,132,210,194,162,219,
19,66,43,144,63,93,180,235,228,247,234,177,128,146,135,81,48,180,234,68,116,217,147,173,255,53,105,92,55,106,31,66,15,88,161,5,51,242,91,244,220,146,213,76,70,10,110,123,78,79,79,233,221,187,119,229,40,
222,147,147,147,114,18,102,206,23,66,160,211,211,83,122,255,254,61,29,30,30,150,124,23,23,23,2,104,136,18,35,251,240,225,3,29,30,30,210,209,209,17,157,158,158,210,249,249,57,3,151,73,128,60,133,80,38,
152,7,244,163,70,161,148,137,213,0,150,118,51,246,90,251,61,214,3,248,226,146,127,150,253,37,229,204,20,99,218,41,206,243,233,231,31,89,93,230,248,162,229,132,210,197,0,242,177,149,227,188,103,207,159,
79,154,239,84,192,191,92,131,177,161,175,57,196,217,121,210,253,52,77,5,176,160,81,85,245,53,233,37,46,221,79,211,36,191,154,163,175,53,226,246,64,72,7,196,192,80,195,172,191,156,34,142,228,231,121,32,
240,130,123,75,190,188,206,60,121,137,79,137,93,217,101,112,120,150,78,13,52,4,66,94,223,232,224,197,163,231,1,235,36,57,152,120,221,25,164,238,222,189,75,123,123,123,230,219,248,153,145,221,189,123,151,
110,222,184,65,87,192,229,35,34,122,247,238,93,201,183,221,110,33,107,67,122,240,250,32,168,59,125,110,165,195,56,176,45,130,223,103,144,199,250,177,60,176,87,179,199,197,92,33,89,81,51,30,173,54,123,
243,152,203,155,71,242,25,114,243,189,213,31,200,184,91,99,172,48,231,156,78,145,166,48,149,49,42,250,36,198,194,78,197,87,115,116,165,94,220,167,166,123,200,204,175,97,89,182,30,102,5,235,172,122,217,
113,249,213,1,245,224,22,75,46,243,214,62,66,95,96,182,218,208,228,9,84,172,119,15,148,145,124,62,8,202,195,100,253,193,7,136,126,77,202,213,203,209,59,135,205,102,67,127,253,235,95,233,206,157,59,244,
244,233,83,250,237,183,223,196,118,147,236,26,79,211,36,242,29,31,31,139,175,102,107,121,7,7,7,244,244,233,83,122,253,250,53,200,167,39,200,122,112,178,2,250,102,164,190,206,125,107,49,96,253,252,44,240,
210,101,130,122,94,165,76,142,139,186,12,81,19,153,99,212,120,69,227,170,97,251,70,123,144,78,57,120,253,197,239,123,127,45,89,217,56,32,163,148,219,98,191,252,12,226,114,71,88,0,167,21,241,38,225,40,
64,102,80,201,215,25,105,245,166,73,235,97,181,72,205,101,203,181,131,82,127,142,11,36,127,173,139,140,53,81,107,253,82,30,123,45,172,128,139,140,165,24,107,31,115,0,224,114,144,204,98,141,168,29,224,
68,245,89,240,35,163,117,176,6,135,14,25,92,242,103,164,126,255,253,119,216,190,205,102,67,223,127,255,61,221,190,125,155,254,241,143,127,148,124,250,89,108,183,91,250,235,95,255,74,183,110,221,162,191,
255,253,239,244,234,213,43,209,39,40,140,176,166,30,118,165,103,64,194,5,138,243,156,105,51,211,51,63,131,182,110,15,136,118,209,27,133,176,232,83,251,44,221,55,50,13,217,158,103,163,199,149,150,137,210,
136,8,158,188,128,60,4,62,215,242,191,188,185,90,178,73,57,110,185,12,11,228,154,3,252,248,245,26,139,156,149,202,86,214,98,9,26,236,138,123,165,243,169,186,136,210,227,10,156,53,44,101,181,94,158,142,
93,54,8,126,205,20,109,177,192,76,231,43,10,226,52,175,143,61,166,195,251,176,62,75,205,64,124,96,90,27,182,219,45,125,255,253,247,116,235,214,45,250,225,135,127,44,224,210,90,215,27,55,110,148,124,127,
251,219,223,10,8,105,102,155,229,237,239,239,211,15,63,252,160,192,170,13,227,64,27,72,60,42,203,253,33,201,211,130,218,47,229,185,128,35,241,94,176,0,2,77,80,116,221,115,227,122,186,174,113,253,80,89,
157,175,199,186,208,146,193,46,109,200,117,167,151,159,169,82,203,244,103,28,188,114,154,110,140,197,194,220,119,227,20,128,105,16,3,21,55,141,178,25,9,183,4,105,96,183,29,23,136,8,185,146,211,146,159,
168,184,134,170,79,83,28,99,128,41,107,163,219,136,165,110,155,217,1,70,17,231,176,59,211,0,17,33,87,43,199,108,183,91,250,249,231,159,232,234,234,154,206,207,207,105,187,109,79,149,37,74,95,171,254,249,
231,159,233,250,250,138,206,206,206,27,247,46,183,125,187,221,210,179,103,207,232,234,234,146,206,206,206,186,253,128,152,101,239,218,202,159,131,158,72,38,131,81,247,150,43,167,153,152,204,135,25,75,
79,111,20,252,37,142,180,107,92,247,201,72,189,81,235,33,100,72,163,160,61,147,24,155,169,104,186,118,242,175,205,242,172,231,154,54,142,50,85,80,64,238,20,119,13,249,95,222,65,197,125,82,150,132,203,
185,230,52,52,167,169,73,45,40,109,108,93,174,46,107,114,38,188,117,45,117,190,198,32,161,214,142,184,234,8,156,26,151,80,155,122,98,44,48,18,220,102,208,232,96,128,83,73,227,148,154,235,67,117,179,110,
12,89,25,213,7,203,223,179,179,51,241,107,160,21,80,62,52,89,60,121,220,29,195,233,74,238,50,126,117,61,150,91,131,235,171,198,168,196,45,253,63,2,136,58,100,246,91,243,247,89,132,5,44,235,193,185,255,
58,144,169,135,3,116,30,168,36,239,170,77,231,191,152,98,25,8,196,252,250,132,75,136,92,54,30,248,32,64,155,12,55,155,141,123,116,49,175,7,229,241,174,215,128,143,87,199,104,189,97,154,10,243,132,76,175,
154,208,20,199,89,164,206,147,243,45,50,129,50,85,206,138,208,90,216,54,157,235,16,168,237,139,209,9,93,228,117,242,90,192,49,34,159,149,234,234,55,149,182,201,109,1,141,164,78,123,45,253,134,221,66,167,
236,68,184,79,144,241,215,198,157,235,87,129,129,125,102,153,240,68,183,141,174,109,232,71,129,201,235,19,173,123,174,139,227,129,229,30,90,132,8,165,111,175,231,235,229,221,174,117,204,68,43,150,175,
209,119,211,184,60,221,113,232,1,233,124,154,165,233,78,234,177,12,111,16,160,186,137,136,2,175,15,12,46,210,242,153,188,107,37,179,132,129,151,97,181,30,58,222,10,114,176,80,243,85,233,145,58,93,240,
10,161,244,201,42,189,216,43,87,17,77,239,140,237,157,87,145,108,221,170,123,143,6,60,191,95,3,206,22,24,244,38,47,234,71,61,118,123,76,74,199,203,254,237,191,39,107,1,164,151,134,116,180,112,160,215,
118,171,207,248,15,74,90,247,17,70,60,77,19,109,51,133,64,232,200,27,138,59,79,6,89,87,110,108,110,48,2,68,121,175,175,43,58,7,88,46,93,39,171,211,232,21,176,251,40,179,240,120,233,138,228,99,137,189,
7,137,228,165,116,17,219,173,27,129,177,190,31,5,176,28,55,179,195,15,71,152,155,126,214,189,122,70,66,121,95,204,113,241,116,94,138,24,44,44,125,134,153,144,136,111,127,77,68,236,195,3,65,139,33,241,
180,148,63,80,8,108,110,25,250,55,96,210,1,79,11,244,172,190,203,31,153,245,228,104,176,241,158,131,5,50,186,143,208,247,6,181,28,47,232,126,25,218,135,101,85,212,118,60,111,240,178,62,66,237,3,173,128,
136,169,36,82,84,254,220,207,7,69,253,16,172,208,217,25,236,22,187,202,197,180,213,209,237,69,15,75,230,239,184,155,220,83,36,162,137,198,78,56,237,1,239,232,179,27,5,160,85,64,21,42,71,202,110,116,97,
86,157,65,201,3,223,46,50,194,40,173,188,122,162,104,150,162,157,185,102,92,100,67,91,112,84,141,247,89,78,76,173,87,189,247,63,71,143,238,189,252,40,239,200,49,54,228,48,25,203,96,214,162,61,87,21,204,
139,229,127,97,74,125,56,194,238,172,191,60,255,22,78,168,165,129,186,17,218,2,107,54,20,227,242,93,194,92,145,3,70,168,83,208,53,106,92,30,110,83,233,156,54,31,42,107,213,161,243,175,57,34,57,132,48,
148,95,60,24,230,0,5,35,127,175,238,118,2,102,32,167,229,218,118,161,202,194,172,214,209,212,160,175,35,197,246,53,164,209,176,10,208,86,76,100,34,123,44,77,97,18,13,70,135,48,10,182,160,183,176,76,56,
175,158,152,154,169,89,6,154,95,35,227,136,228,35,87,139,203,138,121,64,176,180,57,239,57,227,152,157,199,76,231,61,65,241,23,16,3,8,188,179,13,66,61,54,135,234,221,194,9,94,219,208,116,158,231,18,205,
243,44,119,152,235,78,44,172,43,22,234,239,89,211,134,162,51,214,22,168,254,234,101,177,38,46,67,235,222,27,96,186,254,4,148,202,101,10,181,221,233,54,20,203,172,7,159,28,252,237,132,182,250,213,181,110,
161,174,14,229,255,242,115,240,113,96,245,232,62,83,125,51,2,36,107,88,216,40,48,237,154,207,99,58,58,204,52,83,136,59,48,192,21,121,81,254,124,239,125,96,212,139,67,134,214,26,215,149,237,72,153,81,253,
162,135,202,162,0,227,149,187,128,220,127,238,25,233,182,137,118,118,187,54,84,134,53,242,235,158,119,157,153,134,240,229,235,138,170,184,71,117,142,212,49,26,44,247,141,167,123,101,75,157,96,66,199,220,
134,229,191,114,146,204,68,100,3,224,34,98,97,66,181,47,56,163,149,213,181,44,45,84,1,109,126,34,177,9,178,198,215,221,249,174,124,182,77,195,11,159,3,80,70,203,114,96,78,81,216,21,211,229,144,33,244,
216,183,167,183,174,215,171,111,132,245,233,241,153,191,152,36,183,81,84,179,22,99,44,99,113,132,169,88,96,23,107,99,68,190,124,61,50,47,44,29,80,222,16,66,217,218,160,251,39,253,85,207,143,89,242,146,
206,134,100,8,236,35,20,35,12,37,223,155,29,162,26,94,45,121,250,147,169,43,26,36,22,85,70,249,56,7,212,110,105,170,46,10,112,244,92,190,79,113,197,26,221,0,88,244,234,209,180,29,61,220,92,190,7,0,30,
251,245,2,234,163,241,194,4,231,114,87,94,168,6,204,98,33,188,138,36,179,222,141,176,18,52,9,139,235,87,244,94,94,141,50,94,19,25,9,163,19,216,212,17,188,53,208,200,238,164,115,215,19,49,205,146,14,94,
211,146,58,85,192,76,241,248,117,39,107,135,123,173,47,201,72,219,166,178,140,184,200,213,245,91,64,155,158,73,78,155,231,89,126,170,222,99,37,253,117,148,38,17,230,227,150,30,117,118,205,239,13,24,108,
53,197,150,10,146,155,89,69,253,0,124,135,128,75,249,254,195,0,161,218,231,214,97,220,235,248,54,61,208,52,49,16,48,118,188,115,57,65,70,40,105,56,174,55,141,61,214,99,197,175,97,192,57,221,27,143,158,
113,109,141,193,242,118,2,73,6,170,39,125,201,175,220,158,6,172,20,113,208,99,207,106,167,183,20,161,227,70,198,173,55,198,123,108,41,181,119,118,211,71,210,66,8,229,244,141,36,147,136,168,95,150,136,
210,113,60,212,206,93,113,166,123,57,154,55,84,55,130,103,214,215,186,179,50,96,244,192,45,83,224,114,72,26,248,85,77,237,9,119,39,116,143,37,246,130,53,24,114,167,151,7,222,113,247,4,232,214,76,68,113,
113,36,51,155,82,1,177,78,125,143,40,181,76,167,194,20,70,250,163,25,196,206,47,77,158,188,93,220,245,145,60,150,88,94,124,244,121,123,19,118,68,63,17,167,152,97,211,126,125,107,120,18,101,108,49,22,161,
235,242,152,89,142,235,177,83,79,150,254,139,126,109,52,217,99,244,189,45,116,207,28,9,65,82,96,254,64,10,1,24,96,149,130,11,170,113,22,164,193,137,255,69,71,184,72,5,237,9,152,27,157,50,82,147,127,2,
147,21,221,55,224,169,27,202,104,129,231,206,65,89,59,132,58,16,85,251,129,92,241,96,2,199,50,12,106,200,24,244,218,100,75,100,58,176,178,214,0,204,117,143,78,144,94,240,128,63,165,143,149,173,33,63,59,
57,145,121,222,161,159,255,123,97,49,10,35,19,21,197,143,228,65,174,105,239,23,60,75,182,252,178,183,159,183,231,97,89,172,77,232,64,213,248,133,16,154,95,48,145,193,117,193,52,221,16,81,222,56,202,50,
90,148,90,91,5,221,64,94,78,15,10,47,63,2,136,130,59,162,195,218,233,86,95,205,176,235,105,229,244,211,215,184,190,49,182,31,58,205,241,26,208,245,131,109,192,39,242,119,253,176,177,64,238,141,245,224,
181,238,177,151,158,141,21,95,229,244,216,204,238,152,190,3,232,201,151,213,61,96,214,121,208,36,92,3,54,99,250,125,62,176,106,250,198,89,223,34,162,50,7,116,143,196,50,201,241,254,192,84,212,31,87,77,
8,242,220,45,15,104,80,240,158,123,79,214,28,211,14,132,242,213,28,61,248,181,224,222,32,217,197,242,55,46,87,8,148,59,53,239,52,95,114,182,236,36,9,48,7,164,103,45,188,116,239,225,121,64,139,218,108,
129,31,2,127,30,16,8,246,210,61,139,104,229,17,241,161,186,234,35,101,80,112,7,43,95,31,138,246,120,240,2,122,78,177,70,176,186,26,193,102,29,61,208,71,159,1,211,244,207,154,172,107,38,180,7,84,214,103,
184,132,158,197,215,162,210,1,66,6,251,81,161,7,56,169,43,140,253,98,106,140,35,183,84,183,139,119,153,197,172,123,238,98,62,115,127,91,39,86,61,75,200,250,122,10,175,200,186,31,41,131,153,149,44,103,
253,146,167,129,96,13,131,26,5,159,116,29,169,71,35,60,208,65,131,119,20,68,188,47,73,199,24,203,231,191,61,25,40,205,99,24,94,185,207,145,143,7,143,233,229,96,45,55,0,97,41,31,99,134,197,204,57,147,204,
170,91,167,231,195,1,68,25,192,150,115,30,17,191,236,242,38,162,186,135,112,128,221,53,64,177,177,243,35,214,89,150,115,114,125,203,178,3,58,253,99,196,205,243,234,69,65,235,52,59,223,61,92,46,204,122,
116,216,90,159,229,226,193,102,32,121,82,243,191,245,103,80,179,92,140,229,161,39,48,15,37,142,178,36,212,121,75,190,66,112,67,168,54,100,0,196,180,62,197,24,161,52,230,74,133,96,189,154,187,14,212,145,
117,201,214,76,7,52,16,189,53,67,171,175,71,93,70,171,126,157,103,189,59,215,202,181,88,188,149,127,164,142,25,29,171,2,92,91,171,78,203,242,247,116,116,25,147,102,52,29,247,110,173,251,168,227,180,222,
209,171,67,183,209,0,174,28,120,60,246,140,150,124,121,205,42,218,239,166,114,25,89,79,162,60,239,165,27,43,60,18,34,218,22,168,49,6,18,175,212,99,73,89,240,118,123,163,201,35,26,189,212,151,193,199,99,
61,154,227,244,226,145,238,40,148,182,2,144,106,172,111,74,20,67,205,2,55,209,190,65,189,146,235,59,160,107,42,152,116,1,207,138,247,225,218,254,232,5,221,198,81,89,187,214,151,235,28,169,175,157,144,
68,22,66,201,172,182,139,166,39,61,47,140,120,183,20,107,159,255,212,212,197,220,55,30,70,63,113,175,175,45,192,131,117,27,101,144,113,19,44,173,0,30,151,149,255,68,34,253,42,14,197,146,55,203,161,230,
247,63,94,63,142,143,49,210,76,68,91,254,53,147,17,215,203,139,139,49,214,207,52,57,44,173,78,64,73,229,155,124,138,227,55,175,198,12,232,131,93,61,82,233,105,24,90,15,79,215,131,238,171,206,57,29,38,
67,217,150,53,149,237,40,207,58,151,90,210,157,9,189,48,195,17,87,240,83,192,197,10,208,109,74,9,221,252,58,206,101,89,177,207,94,122,50,144,193,106,39,57,201,201,103,200,89,83,167,165,7,202,99,185,161,
250,249,102,175,129,131,103,249,181,46,18,81,192,94,16,15,158,124,34,106,214,213,204,126,211,44,51,198,18,233,245,181,5,178,219,124,252,239,40,56,45,119,101,66,242,188,104,31,150,59,233,203,211,103,105,
209,201,7,130,166,142,28,146,208,0,68,140,49,116,22,155,45,43,111,221,15,129,93,104,219,53,10,26,136,9,34,122,158,153,97,30,36,168,157,110,121,35,207,46,65,50,69,101,173,151,128,88,99,211,78,182,62,163,
227,120,46,223,96,180,113,144,93,43,55,104,17,45,244,211,250,226,10,165,142,107,93,63,4,156,146,5,250,242,98,84,191,222,131,42,123,198,194,100,94,89,156,234,167,24,99,243,209,10,20,122,111,24,232,251,
109,193,9,160,136,118,247,106,156,189,78,85,252,77,99,242,230,160,101,122,19,198,146,231,185,41,30,96,244,226,80,167,89,219,23,154,251,80,127,250,205,192,196,95,21,42,121,103,249,74,6,122,227,190,231,
6,173,177,142,156,198,34,96,224,6,131,47,206,238,2,82,92,22,175,26,90,77,160,51,10,22,112,41,33,11,11,85,125,201,251,43,80,249,42,146,158,44,229,121,197,246,121,233,144,215,204,196,155,5,28,68,141,137,
231,77,200,17,86,168,65,162,252,93,198,30,66,99,205,106,185,46,104,110,89,108,39,18,152,171,138,36,228,128,188,29,130,229,169,244,249,72,187,225,171,57,86,3,122,192,178,72,89,172,27,99,97,198,47,20,250,
30,179,184,172,83,141,231,121,146,158,242,89,105,213,16,104,142,80,109,30,151,127,153,235,186,134,236,193,166,251,252,7,128,64,238,95,34,241,203,223,40,192,174,9,232,4,210,150,113,143,1,97,47,14,49,2,
139,165,122,46,31,138,211,175,208,100,249,245,130,29,159,179,228,39,254,76,149,139,210,212,153,215,96,58,172,37,199,243,124,124,225,95,79,124,143,21,115,32,247,0,93,200,43,173,37,217,62,160,35,191,14,
185,44,243,54,56,209,128,110,159,6,148,1,112,137,177,126,24,53,69,74,3,161,95,207,179,228,232,251,173,30,72,35,44,197,114,251,18,19,169,175,247,240,192,215,159,122,236,167,52,41,230,103,193,243,183,141,
169,50,250,204,78,232,52,226,246,57,204,132,175,173,45,26,99,25,224,62,91,196,8,210,61,128,93,195,34,123,109,235,149,213,207,121,77,176,217,98,101,231,136,185,246,24,157,102,244,168,44,98,71,186,79,45,
195,68,164,143,126,201,253,96,235,164,39,157,48,240,139,16,139,93,34,50,224,213,209,155,212,121,190,104,128,201,119,226,203,207,234,87,231,134,13,77,88,167,106,140,115,190,73,141,207,88,250,141,63,95,
225,98,82,104,227,12,114,148,195,102,179,145,239,18,66,165,156,107,148,230,14,242,133,6,53,168,175,100,180,74,215,14,64,13,178,24,160,215,248,30,115,44,58,5,246,32,201,0,65,5,92,189,126,66,245,200,100,
190,7,141,154,182,163,118,160,190,200,193,29,116,3,161,153,212,139,121,95,13,102,192,136,245,0,106,212,69,28,9,158,75,138,228,142,0,72,133,97,92,6,177,162,53,245,181,113,133,87,213,103,206,153,75,36,66,
167,156,34,37,122,207,175,176,32,49,238,243,56,163,154,10,246,89,241,186,71,190,77,200,121,137,206,147,255,206,243,220,30,145,44,132,172,180,200,185,156,229,90,232,82,158,229,231,95,43,30,101,129,158,
78,163,101,51,243,201,244,46,198,40,62,72,81,58,154,203,1,86,90,103,67,253,41,65,87,104,193,172,189,191,225,212,98,14,86,128,109,86,107,57,221,50,29,183,202,16,66,65,101,71,110,129,23,118,5,183,93,243,
241,188,150,1,136,32,175,190,143,132,158,113,138,231,110,42,66,52,12,98,115,201,235,3,158,38,7,141,40,147,60,104,112,135,251,220,148,204,198,109,12,161,11,86,85,83,106,14,22,36,106,13,245,22,189,100,92,
168,44,225,9,238,177,24,212,1,214,228,194,110,157,236,137,32,162,48,109,236,177,62,43,109,36,191,84,137,47,78,179,78,87,109,202,180,56,103,51,7,187,1,164,60,109,68,127,20,188,58,117,122,117,225,241,217,
71,85,38,215,175,230,223,133,237,32,221,100,93,254,115,24,145,91,101,72,22,59,42,27,245,191,30,131,150,78,220,16,153,236,88,109,219,33,98,32,102,200,46,215,6,80,120,115,74,62,63,219,187,168,50,16,39,244,
65,178,1,45,226,125,209,150,147,76,44,235,129,89,89,58,15,11,76,126,141,180,187,184,140,163,46,165,85,38,130,188,232,132,82,109,65,18,57,194,109,178,234,119,219,27,228,94,166,94,155,52,80,88,236,176,215,
167,40,148,178,122,127,90,1,209,106,205,189,186,44,182,102,13,80,187,236,114,150,84,51,208,91,183,197,170,123,172,158,117,101,117,254,244,213,26,249,177,79,108,119,52,200,167,114,149,237,226,151,217,93,
55,16,128,164,6,21,4,146,86,30,175,94,162,246,215,102,68,36,70,67,118,52,144,156,30,248,228,144,183,58,241,243,233,184,112,89,166,101,162,90,230,150,84,240,26,230,185,137,57,29,77,6,203,194,67,107,239,
0,131,117,18,132,96,134,170,131,107,230,244,2,37,146,49,2,202,168,190,17,157,161,158,20,104,166,241,163,78,70,24,224,40,243,90,20,16,32,135,228,192,159,252,101,70,211,197,95,163,71,214,193,28,117,198,
120,244,38,9,202,139,216,18,145,116,217,101,124,96,10,246,189,3,143,217,244,230,20,138,107,218,199,140,81,143,225,140,130,137,167,203,40,139,234,201,69,198,148,191,43,139,136,2,154,143,185,158,173,142,
236,49,171,28,230,121,238,158,42,96,201,225,131,199,114,57,77,214,198,38,202,168,43,71,68,226,69,84,79,191,17,23,204,235,27,43,63,47,135,88,16,103,37,41,129,154,157,253,107,88,25,55,6,37,143,16,15,182,
7,144,76,215,95,134,225,109,176,234,27,9,107,39,207,174,249,244,196,234,141,233,81,121,22,112,141,220,115,93,114,176,140,122,73,35,34,190,144,206,231,137,181,127,15,121,25,150,94,28,208,45,66,49,194,248,
44,182,168,235,244,62,168,234,233,31,66,192,231,97,229,140,252,175,190,214,63,87,106,176,81,211,207,236,172,145,120,145,30,241,6,54,219,205,89,210,213,215,100,44,139,203,203,32,0,205,44,110,148,76,140,
131,76,223,125,155,99,148,125,154,57,59,26,176,169,240,42,118,54,226,58,142,176,206,181,76,107,212,221,209,249,215,24,216,209,49,103,245,1,175,135,167,105,64,240,216,218,49,92,120,0,0,32,0,73,68,65,84,
150,39,171,148,99,19,167,228,79,25,26,249,221,246,46,70,111,164,253,45,136,202,116,235,218,159,67,216,173,132,237,88,38,85,15,8,183,61,84,27,83,76,14,86,107,240,142,50,153,122,157,31,82,127,66,96,166,
166,227,203,21,57,78,200,82,214,223,5,172,101,179,130,50,94,161,91,111,42,123,238,41,132,185,60,42,84,123,210,32,215,107,126,82,45,94,39,255,91,228,18,54,6,90,223,207,25,248,196,65,19,219,171,87,79,186,
28,60,57,58,62,255,0,129,116,64,70,93,199,245,192,107,228,62,111,247,24,1,99,244,236,50,243,66,245,32,192,45,247,205,246,8,12,230,90,55,212,23,41,62,40,57,3,46,39,3,89,173,103,8,129,127,151,176,229,68,
150,98,90,8,111,16,178,80,158,235,152,27,138,30,80,207,80,187,104,92,38,56,122,216,173,133,182,116,179,6,172,5,184,57,159,213,102,196,60,37,192,165,127,34,46,180,249,16,168,11,153,226,237,2,174,75,159,
193,240,244,17,131,245,57,66,217,208,8,234,179,198,85,79,167,164,187,126,141,76,254,18,138,0,217,114,161,122,12,52,223,155,103,163,71,233,132,91,229,45,128,181,0,25,77,254,30,51,242,100,88,233,30,104,
90,95,209,41,139,238,29,221,165,39,177,184,191,41,161,164,199,24,235,121,88,68,125,122,143,20,214,64,161,15,159,11,161,61,42,152,119,192,168,245,214,135,146,117,39,208,66,137,57,60,84,154,155,116,185,
119,239,30,221,187,119,79,20,11,33,208,135,15,31,232,237,219,183,180,191,191,79,15,30,60,160,237,118,91,210,78,78,62,210,241,241,43,215,82,18,201,7,229,13,126,109,253,224,96,93,46,239,223,191,79,239,222,
189,35,34,162,91,183,110,209,193,193,65,201,114,121,121,73,31,62,124,160,121,158,233,238,221,187,116,126,126,78,23,23,23,139,60,255,3,19,232,196,140,222,228,220,53,88,147,116,77,62,107,240,239,239,239,
211,157,59,119,154,114,151,151,151,165,223,238,222,189,75,55,111,222,44,105,231,231,231,244,254,253,251,33,29,122,105,136,109,229,16,66,128,156,62,132,137,238,220,185,67,239,222,189,37,34,162,131,131,
3,218,219,219,43,233,23,23,23,244,241,227,71,154,231,153,238,221,187,71,39,39,39,226,75,52,89,182,168,199,209,67,223,175,97,170,86,60,215,1,233,52,10,84,189,235,24,99,235,18,122,126,166,197,178,60,197,
44,69,81,227,248,125,115,242,67,204,15,157,53,52,80,125,95,41,171,17,185,188,20,81,219,69,162,45,123,123,123,20,99,20,3,54,132,64,23,23,23,20,99,164,199,143,31,83,8,129,222,190,77,131,105,179,217,208,
31,254,240,7,58,61,61,163,211,147,83,214,118,214,71,170,189,250,128,68,61,136,57,229,178,92,193,105,154,232,206,193,1,125,253,245,215,244,127,255,247,127,116,227,198,13,250,203,95,254,66,111,223,190,165,
235,235,107,10,20,232,232,232,136,222,189,123,71,207,159,63,167,195,195,67,122,243,230,13,93,94,94,182,125,11,94,155,234,189,184,43,54,54,114,221,168,254,92,13,131,164,50,178,141,153,80,233,221,164,64,
190,37,75,171,119,112,112,64,143,31,63,166,143,31,63,138,151,203,51,40,31,125,113,68,143,31,63,166,55,111,222,16,81,122,54,127,252,227,31,233,233,211,167,13,104,245,24,85,143,129,33,3,38,20,14,105,60,
29,28,28,208,147,39,79,232,221,187,183,116,247,238,93,250,234,171,175,232,237,219,183,37,255,209,209,17,189,124,249,146,142,143,143,233,240,240,144,46,46,46,232,226,226,2,246,151,101,240,214,158,136,192,
219,55,2,34,86,222,60,127,107,124,102,184,227,198,143,215,19,99,228,71,36,143,49,171,250,133,151,234,146,228,203,105,154,210,145,178,75,255,212,98,33,171,234,202,174,90,26,160,200,39,55,169,244,60,174,
129,29,171,96,37,59,121,158,103,58,59,59,43,3,88,235,116,227,198,13,250,229,151,95,232,244,244,180,196,223,189,123,55,29,155,65,120,173,69,63,60,196,36,33,136,128,254,200,87,251,123,123,116,227,198,13,
162,152,22,221,111,223,190,77,239,223,189,163,159,127,250,169,228,189,251,225,30,29,61,126,156,250,89,13,156,219,183,111,211,205,155,55,233,221,187,119,0,140,248,17,52,109,31,200,188,178,204,174,193,155,
248,107,202,162,180,147,147,19,250,137,245,11,15,183,110,221,162,23,47,94,208,241,241,113,137,155,231,153,246,247,247,27,192,90,163,87,92,242,71,112,144,64,214,75,220,47,189,119,235,214,45,113,4,203,254,
254,62,189,121,243,134,158,63,127,190,24,225,64,231,231,231,116,235,214,173,50,249,179,1,155,227,76,7,183,15,104,154,38,161,59,98,46,58,13,93,155,0,197,214,148,120,158,188,225,92,192,98,148,164,166,46,
235,164,217,159,202,219,191,136,18,219,136,92,231,124,29,107,155,205,166,253,8,69,174,44,197,213,202,178,27,149,173,177,204,91,43,231,167,26,8,70,67,245,154,154,225,174,214,131,38,99,2,15,172,89,88,110,
102,222,60,40,227,136,30,61,58,164,7,15,30,148,184,171,171,43,122,241,226,5,157,159,159,23,153,57,111,8,190,101,9,33,208,118,187,165,163,163,35,122,254,252,185,208,251,203,47,191,164,127,254,243,159,174,
254,89,86,249,66,246,18,119,114,122,74,39,167,167,244,135,127,251,55,154,151,231,117,61,207,162,23,231,124,175,250,235,209,163,71,116,116,116,68,63,253,244,19,30,152,161,119,144,10,232,247,212,17,194,
8,140,148,67,108,93,255,213,101,180,49,64,174,52,207,123,251,246,109,250,230,155,111,74,153,203,203,75,122,253,250,117,97,37,122,59,78,150,235,189,132,157,89,219,201,201,73,137,123,240,224,1,93,93,93,
209,251,247,239,107,255,133,169,244,135,213,62,30,62,124,248,64,155,205,134,190,248,226,139,18,39,206,235,103,243,41,198,88,62,251,62,207,51,125,241,197,23,116,239,222,61,122,246,236,153,235,194,161,107,
20,135,118,150,167,155,246,181,28,79,174,54,70,215,215,232,131,172,65,204,37,79,38,111,91,8,96,91,3,31,46,11,200,23,176,66,65,163,161,149,71,222,215,6,165,52,76,167,123,46,41,17,21,70,1,215,126,68,185,
10,148,153,93,253,246,219,239,244,234,213,107,209,142,39,79,158,208,253,251,247,139,149,203,3,132,235,54,207,179,136,211,212,247,224,224,64,0,119,8,129,238,223,191,79,207,158,61,107,245,7,236,203,251,
200,4,186,182,220,236,63,254,241,143,116,112,112,64,63,252,240,67,153,176,107,232,56,239,171,181,65,79,34,139,85,245,220,147,158,27,194,195,251,247,239,27,93,31,61,122,68,55,110,220,160,167,79,159,210,
60,207,116,125,125,77,87,87,87,162,239,230,121,46,235,66,72,199,91,183,110,209,217,217,89,105,83,8,129,246,247,247,27,163,214,107,171,213,30,34,201,178,137,234,94,165,92,126,154,38,10,33,125,250,253,235,
175,191,166,237,118,75,207,158,61,163,235,235,235,242,161,12,221,71,44,82,153,149,88,188,32,164,255,136,190,35,160,149,245,245,202,140,200,201,127,203,105,13,89,248,210,148,102,99,166,88,75,98,241,196,
7,78,8,68,198,222,44,81,134,42,116,104,160,25,161,225,38,227,202,96,155,81,214,9,185,3,174,175,175,155,15,59,124,248,240,161,80,112,162,52,80,248,58,84,182,198,252,107,42,72,111,244,99,198,52,165,5,214,
251,247,239,55,105,191,254,250,107,153,52,214,90,150,213,14,110,125,115,92,190,191,190,190,166,203,203,203,6,96,71,130,197,86,123,114,80,159,116,219,20,178,241,193,249,145,177,210,186,93,93,93,149,245,
198,156,118,121,121,73,127,248,195,31,104,179,217,136,103,167,203,54,12,203,121,135,78,247,243,151,95,126,217,228,251,248,241,35,189,121,243,26,218,112,36,231,122,190,22,50,179,87,195,159,35,247,96,174,
175,175,203,90,235,167,178,171,53,121,245,152,176,198,135,71,34,70,140,102,237,35,25,223,188,154,195,43,227,127,123,130,245,218,9,82,188,132,142,27,162,65,201,27,252,58,61,134,241,119,255,110,223,190,
221,252,170,244,240,225,67,58,62,62,166,205,102,67,23,23,23,244,228,201,19,250,240,225,3,17,17,109,183,91,186,115,231,14,253,250,235,175,37,191,6,166,124,127,116,116,68,15,30,60,80,122,68,186,186,186,
42,107,98,211,52,209,225,225,33,124,160,104,194,230,127,151,151,151,116,112,112,64,119,239,222,45,64,116,120,120,88,128,41,203,251,229,151,95,232,143,127,252,55,250,243,159,255,76,79,159,62,117,89,132,
23,135,194,154,53,158,180,178,32,89,56,111,177,156,16,56,94,176,171,178,97,165,172,69,80,164,244,124,110,237,239,215,50,148,24,214,229,229,37,197,165,239,15,15,15,5,251,189,123,247,46,189,124,249,82,105,
28,73,227,213,118,187,165,239,191,255,190,220,111,54,27,122,249,242,37,133,16,202,243,36,162,242,92,78,78,78,40,0,23,49,215,155,159,113,30,47,211,52,209,245,245,53,29,30,30,210,201,201,73,241,60,30,62,
124,72,167,167,167,172,251,34,253,244,211,79,244,229,151,95,210,55,223,124,83,92,66,161,125,135,137,174,1,43,174,175,149,63,198,204,216,218,29,252,87,87,87,205,222,182,166,174,88,159,165,87,79,160,32,
1,203,27,132,30,27,226,76,76,203,241,190,140,204,131,183,87,203,163,156,252,154,179,68,173,155,238,128,28,175,153,199,139,23,47,202,34,230,139,23,47,232,222,189,123,197,58,95,94,94,210,179,103,207,224,
175,52,28,80,136,136,94,189,122,85,172,125,8,129,254,242,151,191,16,81,160,179,179,51,58,63,63,167,237,118,75,95,127,253,53,157,157,157,209,207,63,255,44,128,6,181,153,136,202,207,219,239,223,191,167,
215,175,95,211,163,71,143,74,59,46,47,47,233,247,223,127,39,34,162,179,179,179,52,73,99,164,95,126,121,78,71,71,71,116,116,116,68,191,252,242,11,148,139,14,89,211,253,215,164,105,27,164,94,43,74,5,144,
204,229,77,133,238,202,89,27,202,96,54,214,205,246,247,247,233,240,241,99,17,87,250,37,18,253,254,251,239,244,197,23,95,208,99,150,231,253,251,247,101,203,67,169,67,169,22,99,2,187,31,127,252,177,232,
144,215,157,98,140,244,234,213,43,138,148,126,85,190,125,251,118,250,213,241,3,91,196,207,253,80,47,202,253,245,124,77,31,79,62,82,164,72,111,222,190,161,155,123,55,233,240,240,176,20,189,184,184,72,242,
99,122,174,121,237,242,231,127,254,147,254,176,180,229,229,203,223,68,69,122,157,175,89,107,157,166,98,56,196,156,158,38,65,60,98,74,40,63,42,148,107,214,55,136,208,240,57,185,221,110,63,201,173,204,215,
49,70,218,108,55,245,196,81,84,217,218,208,163,126,158,76,180,127,43,203,24,209,69,235,109,89,25,158,254,225,195,135,194,158,80,158,121,158,233,248,248,216,172,63,175,239,240,244,12,128,151,151,151,101,
91,1,151,23,66,160,131,131,3,250,234,171,175,232,248,248,152,126,251,253,119,225,130,231,65,162,235,33,34,250,241,199,31,75,220,139,23,47,204,190,120,241,226,133,208,41,3,153,110,103,14,154,225,8,227,
87,250,149,136,248,47,60,10,51,70,127,55,12,6,187,30,177,244,90,142,46,255,254,253,123,119,79,213,249,249,121,250,5,81,210,184,122,153,4,203,56,54,142,248,58,32,95,199,220,108,54,244,228,201,19,186,113,
227,6,253,253,239,127,167,203,204,42,178,76,181,135,144,203,189,190,186,166,103,79,19,75,186,158,175,233,249,47,245,199,26,221,23,250,71,27,52,6,60,87,140,183,25,206,213,104,60,69,57,32,196,218,151,246,
194,44,214,110,145,12,116,157,238,137,242,120,203,115,40,208,114,166,123,161,236,185,128,114,7,3,143,99,215,233,156,240,60,33,229,209,183,124,162,74,48,32,194,95,169,73,10,214,235,218,216,220,103,85,30,
207,107,172,105,57,113,40,205,93,115,97,102,69,239,87,74,150,167,166,231,120,20,98,140,116,239,222,61,250,246,219,111,233,228,228,132,166,105,162,63,44,150,250,213,171,87,141,203,214,212,163,226,122,109,
240,242,166,251,165,69,48,30,10,234,174,15,238,18,242,88,177,140,78,142,243,128,172,183,158,102,185,216,252,30,149,45,215,68,194,152,68,214,23,127,254,243,159,105,187,221,210,171,87,175,232,209,163,71,
68,68,116,114,114,82,152,91,207,232,150,122,66,174,4,235,148,12,90,172,251,223,192,222,57,253,98,49,79,179,72,128,6,57,203,45,67,108,59,242,235,5,244,150,27,10,33,208,117,246,96,68,95,230,54,80,217,10,
226,186,156,75,215,132,16,210,78,119,107,178,98,192,177,175,167,137,111,148,36,66,160,146,239,45,84,110,193,138,131,99,110,196,192,195,167,22,193,173,224,130,85,109,70,146,207,126,209,204,155,86,243,54,
140,92,223,235,215,175,73,247,235,175,191,254,74,219,237,150,230,121,46,107,31,188,209,101,49,56,53,194,214,133,236,9,208,123,142,30,144,230,118,186,174,90,144,235,131,62,19,242,159,147,54,112,184,186,
117,47,67,91,113,107,203,234,248,55,111,222,208,249,217,153,120,46,239,223,191,47,107,97,124,31,223,136,60,215,237,38,60,126,75,92,238,211,40,243,244,13,23,127,69,73,146,38,196,102,52,136,181,50,171,99,
15,231,216,34,167,28,16,26,216,235,57,145,196,122,23,126,126,172,109,44,207,246,250,250,186,97,46,181,94,255,93,65,93,110,158,181,18,182,229,180,58,67,118,204,58,26,217,179,28,200,202,38,25,181,190,150,
154,250,139,254,122,237,109,158,103,122,245,234,85,83,230,213,171,87,68,68,116,122,122,42,22,105,123,97,100,2,112,189,70,93,232,90,70,203,149,242,198,132,240,75,222,223,99,197,81,19,123,174,43,170,95,
238,15,196,25,173,241,34,101,75,221,223,190,125,219,212,157,151,18,136,136,126,251,237,55,236,98,177,182,232,251,110,155,156,224,129,95,15,168,211,33,134,168,140,195,112,76,153,62,75,157,166,201,93,155,
237,213,53,171,35,147,99,140,180,13,233,110,129,221,69,9,6,84,5,117,151,124,197,110,138,135,80,223,35,148,251,96,218,135,132,38,191,5,70,186,49,40,111,207,85,146,249,165,94,85,94,5,233,242,234,74,177,
2,68,33,200,118,20,153,20,202,171,37,150,27,163,203,160,62,240,250,104,164,156,150,97,129,182,14,200,210,183,0,134,88,176,239,158,17,249,63,162,104,217,146,61,55,185,68,189,40,53,91,96,206,78,184,168,
42,215,158,32,154,217,10,77,148,17,70,134,148,235,55,194,238,184,235,133,126,69,91,34,42,163,10,248,89,232,122,122,207,122,179,153,26,253,244,120,177,100,173,1,155,210,10,53,7,100,93,51,113,102,87,101,
164,126,158,227,172,177,149,182,21,114,88,26,64,237,50,0,23,112,227,159,8,66,29,160,193,5,178,148,136,89,16,102,113,136,133,49,160,113,38,84,150,233,177,173,70,199,144,92,62,20,218,178,245,58,83,89,138,
81,12,244,80,21,53,65,36,170,252,30,51,229,249,161,254,74,87,171,205,35,192,130,2,172,43,37,20,195,230,25,20,36,199,115,107,248,68,106,234,4,249,97,187,249,56,213,99,36,235,158,203,112,125,129,17,64,245,
64,221,131,116,178,71,13,114,46,235,187,77,227,236,202,234,191,53,140,202,243,108,80,188,118,233,155,50,129,200,120,37,124,121,6,161,178,231,101,172,110,249,166,72,254,151,87,234,13,42,190,248,151,129,
13,130,204,82,57,127,161,85,76,150,80,235,178,172,122,211,44,131,112,232,95,238,178,110,163,236,140,223,91,140,16,51,183,86,78,51,160,13,48,210,117,160,87,37,188,114,214,128,68,58,240,178,187,236,98,95,
19,60,189,70,210,215,214,181,75,90,201,99,228,139,139,241,65,192,131,130,213,167,45,147,112,116,1,253,98,129,129,149,199,186,206,246,148,22,215,55,39,37,213,244,11,203,158,238,252,168,30,185,38,169,141,
46,212,105,150,191,56,234,60,250,239,52,77,248,203,207,232,58,18,17,250,194,78,185,94,88,215,204,31,46,179,108,153,81,241,48,83,11,44,61,61,244,117,249,203,234,227,160,34,126,53,201,29,162,58,6,117,172,
6,207,146,143,15,198,12,124,36,155,230,185,100,252,97,114,29,44,61,80,158,209,224,229,29,117,47,215,214,91,153,164,63,41,185,171,83,159,161,93,135,216,88,104,136,181,116,28,6,101,5,74,185,190,58,110,242,
140,84,122,69,153,223,10,240,153,51,3,174,101,244,198,81,111,12,161,227,147,107,190,84,123,146,147,101,230,119,252,50,168,69,49,207,90,89,124,228,183,198,84,123,53,90,142,7,140,150,55,33,62,164,170,51,
242,2,46,88,49,213,33,69,95,1,64,162,59,68,28,118,255,116,29,66,103,237,238,12,76,192,238,196,100,15,65,50,72,246,119,112,162,103,134,74,81,247,23,53,147,210,109,179,163,174,126,89,125,215,96,181,195,
2,83,244,113,77,173,215,114,209,196,53,198,82,77,112,14,114,150,46,252,218,155,184,60,88,134,43,145,145,250,83,124,157,224,53,110,81,46,125,163,146,25,178,156,47,51,154,102,130,130,197,110,75,55,222,54,
219,5,206,215,160,29,221,62,168,167,37,244,116,241,0,104,132,229,89,44,138,200,248,240,42,129,227,101,136,240,195,29,5,25,171,83,123,101,56,10,175,3,177,26,52,5,69,238,19,242,161,181,92,126,246,251,8,
251,73,236,210,103,7,61,16,236,245,185,25,202,195,244,203,104,32,24,157,188,126,213,62,19,204,247,107,24,33,146,99,233,186,171,251,215,211,9,89,117,226,227,0,212,33,237,106,5,43,57,174,83,105,244,172,
61,157,80,95,240,177,152,255,206,113,54,13,19,4,10,197,12,181,46,174,43,231,0,79,214,47,255,213,31,68,182,216,35,146,171,219,41,94,126,230,193,5,26,78,163,84,131,70,6,87,243,112,98,20,19,46,102,62,170,
242,162,135,223,211,85,187,137,186,141,30,224,18,211,35,212,12,166,44,47,88,244,182,7,200,214,160,25,25,220,35,242,172,124,40,239,218,54,231,60,150,49,146,149,229,63,134,126,104,98,13,238,172,23,101,192,
196,208,247,222,24,214,236,121,20,28,150,155,118,147,165,83,214,10,150,124,13,86,249,42,2,119,184,128,129,209,135,90,199,53,203,7,232,168,100,27,236,136,242,186,250,172,54,144,106,89,49,198,229,67,170,
234,180,2,107,18,73,247,7,15,66,15,180,184,44,97,41,120,60,74,135,15,150,136,72,174,79,141,48,20,147,189,133,202,143,68,63,104,171,193,234,178,38,176,232,143,229,239,148,169,114,102,58,70,255,233,56,11,
100,119,97,72,208,133,74,21,46,215,209,101,137,107,92,74,107,76,96,64,21,221,12,101,133,64,194,136,17,245,25,45,98,16,136,97,6,231,217,136,178,20,170,155,107,140,145,202,94,8,198,163,16,243,172,237,128,
7,191,110,159,101,96,114,74,204,98,115,177,161,180,116,26,242,76,140,56,79,127,157,191,178,87,118,158,63,144,167,175,225,135,84,209,196,174,241,190,47,205,227,242,53,95,7,48,8,154,124,216,212,62,194,98,
225,152,94,243,60,219,96,179,12,38,171,45,60,4,112,37,116,55,192,16,130,0,7,28,149,182,236,19,23,45,67,84,217,99,74,86,159,235,124,64,49,229,187,248,12,212,10,62,75,43,82,137,196,47,72,158,188,62,99,204,
63,228,172,209,205,122,54,57,45,93,71,177,57,17,201,65,113,22,107,177,202,246,245,117,54,96,198,216,204,3,95,214,122,246,214,115,247,80,249,30,136,17,213,141,163,117,185,101,233,55,115,136,226,58,248,
223,173,246,49,137,90,38,210,99,93,124,50,161,207,201,23,29,45,134,195,22,212,219,52,255,30,130,71,190,206,172,13,149,81,140,201,252,202,141,193,166,178,149,240,250,7,83,107,101,249,3,174,3,233,145,178,
167,13,117,168,255,210,188,198,86,56,243,39,128,91,66,126,14,86,127,140,2,155,126,166,253,32,1,206,116,223,242,228,6,243,79,111,177,17,105,43,128,68,212,175,43,130,245,202,113,232,177,125,196,238,120,
250,60,71,126,172,28,235,135,90,57,106,155,150,133,198,158,233,78,178,52,244,145,83,222,6,228,69,89,198,161,25,215,202,232,122,30,25,143,230,109,219,10,4,84,214,158,199,105,38,179,182,35,188,107,207,26,
107,249,72,78,51,72,116,39,3,189,154,60,224,33,36,217,242,21,129,105,242,247,93,241,184,105,226,3,149,247,101,219,70,254,23,245,129,184,55,76,20,210,141,105,196,210,250,72,162,215,34,172,73,247,201,161,
231,19,170,58,139,129,8,74,143,80,251,165,108,21,208,131,158,239,154,167,58,54,200,155,132,26,68,151,122,196,120,2,122,142,94,19,181,46,209,124,141,25,220,8,187,202,175,194,72,16,156,153,150,120,46,233,
58,62,133,165,17,201,143,175,84,176,205,227,188,214,95,141,45,246,42,98,140,194,16,109,229,137,11,50,115,189,174,150,57,159,180,32,39,89,82,6,49,14,126,157,26,209,250,214,41,227,146,7,158,228,96,49,51,
60,201,123,44,192,119,121,169,220,115,197,106,190,218,225,208,138,16,149,159,222,231,217,119,153,117,93,220,202,245,202,52,237,73,30,14,133,188,241,175,183,40,173,158,1,206,223,50,183,126,8,162,127,154,
106,91,180,183,85,116,202,215,225,159,19,248,165,191,171,91,175,87,245,234,20,233,236,107,60,186,140,6,137,158,1,178,198,15,119,211,17,195,209,117,123,75,4,90,47,203,48,123,215,189,188,186,110,222,46,
180,152,222,0,246,140,211,114,124,30,127,211,52,211,54,191,12,169,39,177,84,172,164,16,229,247,127,212,251,117,68,242,0,59,173,128,207,176,152,197,211,76,200,8,227,174,137,15,120,57,172,121,69,197,27,
52,217,10,103,64,40,76,133,49,212,152,81,15,12,116,34,130,103,186,143,180,23,177,130,146,150,127,142,113,218,209,6,195,184,116,202,204,51,99,55,70,81,45,179,93,75,50,216,4,95,255,67,233,204,208,72,230,
163,211,45,144,198,99,80,142,237,80,74,243,103,106,177,149,162,171,195,184,186,64,57,0,254,30,128,120,158,144,23,103,233,235,165,115,207,199,51,216,26,15,178,71,211,138,175,155,91,183,214,154,83,161,216,
153,64,149,162,149,97,136,252,236,90,255,242,104,53,14,1,23,212,197,185,214,22,6,185,87,104,173,192,202,235,233,237,110,230,140,68,97,26,127,241,152,98,164,122,46,88,31,164,161,235,171,202,88,3,174,48,
174,29,61,185,79,114,1,141,162,187,76,208,64,10,255,84,95,251,76,212,30,103,122,178,161,254,204,241,2,180,12,96,67,50,2,211,55,198,152,60,9,135,137,234,248,17,192,64,122,163,243,177,80,29,86,249,212,175,
185,5,25,88,171,107,103,49,174,220,7,250,99,26,113,113,15,117,125,28,59,90,194,25,22,134,5,94,205,17,141,99,96,133,214,139,208,53,234,156,30,195,89,147,87,55,176,7,100,58,31,215,217,122,72,72,63,15,12,
144,94,141,254,129,40,132,201,32,28,32,214,235,19,103,0,90,186,101,253,122,97,141,123,177,38,240,9,139,194,167,214,211,115,237,173,116,79,7,109,238,99,36,177,46,9,203,16,6,1,158,230,185,104,40,158,203,
179,192,199,50,254,158,215,51,82,111,154,67,57,62,136,62,137,70,189,22,184,234,125,85,61,44,208,241,33,168,69,119,221,120,132,130,61,176,178,242,141,12,24,180,243,92,43,108,5,15,232,44,144,226,121,135,
89,86,103,93,167,182,159,72,51,167,72,215,226,222,173,75,187,19,44,175,54,14,141,134,6,67,224,113,35,147,182,215,231,107,243,25,165,23,25,141,38,110,41,107,18,22,61,64,113,107,226,91,178,240,243,93,239,
78,245,243,140,3,74,51,78,89,25,225,2,131,252,35,76,203,138,183,198,155,254,193,64,231,229,231,97,233,242,122,187,138,149,143,235,189,213,13,234,129,146,190,182,26,55,2,116,173,0,130,52,25,185,116,200,
229,203,215,46,107,84,178,181,126,158,142,169,188,92,215,177,172,104,211,52,199,242,175,101,23,189,201,145,173,33,23,131,192,107,52,192,95,37,85,212,136,21,199,245,142,157,214,128,6,115,111,28,142,4,107,
34,142,48,31,30,134,158,217,146,165,125,133,102,140,121,162,113,106,149,65,115,133,183,213,98,65,163,94,147,53,126,19,112,134,218,86,99,158,18,17,133,72,20,203,124,175,46,38,50,174,57,126,219,179,184,
35,161,76,122,82,0,16,66,179,1,212,171,101,173,107,104,149,247,220,69,45,169,116,142,81,151,71,81,137,234,32,72,174,154,172,192,163,188,186,95,122,245,229,176,14,8,112,186,7,224,104,80,194,197,233,184,
126,204,88,245,72,61,234,206,246,0,116,29,149,223,75,247,38,126,117,133,240,22,31,15,204,70,192,79,30,52,56,206,238,96,158,242,140,112,125,22,64,89,110,169,168,55,86,125,225,203,234,198,179,137,212,122,
90,158,65,243,140,128,174,195,92,116,239,177,25,228,6,76,68,226,60,44,212,24,82,91,40,234,165,125,24,159,167,79,137,155,234,250,80,77,215,224,67,34,62,221,103,0,25,99,57,158,171,186,26,88,69,36,25,8,6,
24,14,179,212,61,125,81,189,57,196,152,134,225,228,148,237,179,71,116,74,105,46,43,239,89,14,53,185,139,99,179,88,217,84,200,154,132,233,247,131,152,107,239,178,189,166,246,17,80,25,0,140,209,186,172,
62,244,234,68,172,8,6,208,201,104,162,35,230,196,211,224,175,217,188,143,245,163,2,114,16,179,203,207,211,98,77,229,154,242,11,227,222,145,56,128,97,113,100,68,138,88,148,141,7,206,58,218,70,232,7,206,
27,95,175,145,178,232,190,12,216,252,203,228,114,47,234,212,19,123,1,129,76,71,81,125,104,160,89,238,155,229,174,88,109,144,253,182,208,50,193,88,218,137,44,16,109,49,172,145,250,207,194,178,164,37,189,
137,145,161,63,185,237,77,191,35,158,89,146,53,14,0,60,31,178,250,50,211,72,221,227,245,122,125,129,54,218,34,70,182,22,76,71,92,224,156,134,234,95,110,136,152,23,68,68,20,162,220,150,177,217,108,104,
142,49,29,143,195,101,36,37,100,89,146,227,77,215,195,245,201,31,147,29,49,0,51,27,11,22,75,220,234,78,237,209,96,132,222,60,63,223,210,224,61,96,205,208,60,164,46,113,203,14,102,81,110,249,185,222,99,
58,252,120,149,114,12,7,43,151,221,87,162,250,0,17,216,114,107,231,1,5,108,123,160,230,140,168,22,160,152,2,13,120,227,178,158,155,211,115,95,180,222,40,236,226,162,238,154,191,91,151,2,40,107,199,191,
175,19,239,163,118,255,23,2,120,196,82,120,254,24,211,209,39,90,135,158,129,235,233,157,198,124,191,93,93,64,84,44,173,94,231,19,36,210,117,30,124,22,104,102,221,103,163,109,86,126,126,237,205,113,140,
51,129,2,251,110,66,115,68,178,190,78,233,246,225,121,108,174,211,60,207,106,75,62,102,28,93,247,206,201,139,6,41,4,55,79,6,154,24,25,197,73,118,174,5,2,154,82,243,186,209,195,72,251,180,196,75,98,144,
173,106,160,178,250,208,2,74,175,31,120,24,117,95,61,139,110,246,229,142,50,123,236,129,159,82,154,45,191,151,31,201,212,69,172,15,96,88,22,222,11,35,110,165,7,46,48,255,160,46,86,93,86,125,61,80,26,41,
227,213,159,235,190,190,190,22,174,101,34,7,36,236,175,219,247,52,139,77,229,91,239,157,177,222,117,141,107,7,200,168,5,239,213,101,162,50,23,155,221,120,208,49,168,147,44,116,207,33,111,245,64,108,42,
81,220,36,140,131,26,162,238,13,128,24,103,205,35,182,233,129,110,110,180,215,181,217,197,174,86,10,102,90,36,237,22,132,43,80,35,237,252,178,176,39,89,36,175,5,10,30,103,185,251,158,172,181,101,220,116,
53,238,68,18,251,100,252,162,108,53,156,134,161,226,113,124,174,161,57,131,88,80,147,55,69,18,251,179,92,219,39,82,160,235,98,140,149,78,250,192,194,234,209,180,250,64,102,70,114,203,148,88,116,71,19,
68,130,68,245,133,181,2,22,213,19,76,133,3,8,11,154,181,32,25,252,122,154,166,6,161,197,67,101,94,84,113,33,35,246,243,117,64,172,65,222,231,186,112,30,175,108,189,68,113,162,148,57,105,184,139,168,231,
72,171,67,108,242,230,246,109,54,155,242,165,233,146,43,86,215,70,191,30,196,195,102,179,145,107,54,224,121,134,16,154,117,29,157,39,203,105,141,230,68,155,205,148,172,243,210,102,228,114,241,112,117,
117,37,218,207,79,33,225,65,127,39,15,201,212,96,135,190,123,208,119,245,36,99,134,160,10,222,179,243,130,199,64,61,128,179,152,86,3,58,70,219,120,64,207,52,198,72,52,167,249,141,250,219,107,199,90,198,
185,205,3,179,235,166,81,40,95,56,70,129,163,160,40,167,209,146,0,243,0,29,55,226,242,244,116,78,241,68,164,23,173,89,171,80,59,60,253,172,60,22,192,160,254,104,245,208,233,53,143,216,211,194,126,173,
105,234,99,183,223,124,243,13,109,183,91,250,251,223,255,94,202,133,16,10,3,221,223,223,167,63,253,233,79,244,242,229,75,250,253,247,223,69,221,95,124,241,5,221,186,117,139,158,62,125,10,245,219,108,54,
244,151,191,252,133,142,143,143,69,217,220,94,34,162,163,163,35,186,123,247,46,253,240,195,15,110,59,191,251,238,59,186,188,188,164,103,207,158,37,245,151,54,125,243,205,55,180,221,108,232,31,63,254,72,
243,60,23,125,173,112,118,118,86,218,74,68,244,213,87,95,209,221,187,119,161,110,111,223,190,165,95,126,249,197,148,133,38,24,55,234,232,153,114,249,61,55,144,135,252,76,160,113,86,69,202,75,196,124,92,
52,178,243,117,203,88,144,171,231,17,15,171,13,154,49,149,50,133,211,4,145,215,204,79,120,174,203,246,180,158,129,248,8,133,14,218,98,143,184,139,189,53,49,139,213,192,116,99,110,235,134,242,184,10,78,
57,190,92,129,7,164,44,123,201,73,213,93,26,0,38,164,83,8,163,128,170,217,150,100,115,49,70,177,118,195,82,26,153,83,8,180,191,191,79,7,7,7,68,68,116,239,222,61,122,247,238,157,216,247,195,25,228,209,
209,17,157,158,158,210,201,201,201,144,101,12,33,208,225,225,33,77,211,68,143,30,61,162,227,227,99,200,62,44,182,169,195,63,255,249,79,250,238,187,239,138,172,176,232,116,235,214,45,250,199,63,254,65,
249,171,228,23,23,23,16,64,111,223,190,77,143,31,63,166,143,31,63,138,248,24,35,125,252,248,17,126,145,249,250,250,122,232,43,58,158,229,183,226,71,153,18,15,124,77,118,228,243,96,205,209,54,98,30,96,
175,164,202,72,121,242,53,82,119,20,120,123,253,163,9,204,72,89,116,173,79,114,216,122,147,74,186,104,181,129,22,42,98,70,65,77,135,14,35,108,196,167,40,32,157,107,28,2,87,189,84,80,1,160,119,212,238,
154,123,85,154,103,52,173,151,180,56,68,212,128,75,189,182,38,72,113,93,98,164,195,199,143,233,244,244,148,230,121,166,195,195,67,122,247,238,157,200,203,7,210,201,201,9,125,249,229,151,244,195,15,63,
36,247,80,244,125,108,252,213,105,154,232,193,131,7,116,124,124,76,15,31,62,76,215,191,31,167,236,124,253,112,142,20,231,8,207,117,226,121,79,78,78,232,249,243,231,244,228,201,19,250,240,225,3,77,211,
68,135,135,135,244,252,249,115,58,57,57,41,249,175,175,175,233,242,242,82,200,184,117,235,22,61,122,244,136,222,189,123,71,207,159,63,111,250,229,234,234,74,124,78,126,77,232,187,123,56,190,239,198,131,
201,205,92,70,62,22,71,78,146,128,242,156,50,250,51,245,213,243,145,188,96,13,75,180,2,154,43,122,188,194,249,191,16,142,73,205,153,24,151,151,159,123,149,113,32,224,147,103,185,88,82,252,178,22,67,67,
148,212,202,95,239,241,2,50,234,140,154,70,205,160,9,33,185,87,214,192,64,131,209,26,180,40,136,129,202,214,42,224,160,118,228,228,114,200,69,230,233,68,201,213,187,115,231,14,253,244,211,79,116,125,125,
77,127,250,211,159,232,206,157,59,101,226,86,195,147,244,121,241,226,57,125,249,229,87,244,229,151,95,210,143,63,254,72,196,234,65,199,18,31,29,29,81,140,145,126,253,245,87,138,49,210,227,199,143,43,203,
138,181,39,243,206,232,25,44,220,234,240,234,213,43,186,115,231,14,125,245,213,87,52,77,19,189,123,247,142,94,189,122,133,122,168,220,237,237,237,209,183,223,126,75,167,167,167,244,211,79,63,53,50,115,
31,221,185,115,135,246,246,246,68,90,102,148,40,140,50,41,43,30,177,22,56,238,120,121,53,167,248,242,9,151,97,141,239,17,48,77,215,4,79,50,45,122,13,200,180,219,141,230,92,255,199,11,11,124,99,156,225,
175,163,243,60,203,141,163,166,175,157,127,21,19,249,210,138,20,17,81,100,32,162,25,67,102,88,38,147,90,198,98,177,48,129,43,110,33,178,205,118,114,231,171,68,179,3,117,121,47,222,179,160,93,171,204,218,
217,200,138,120,43,196,232,98,111,14,135,135,135,116,118,118,86,88,213,135,15,31,10,203,226,207,164,116,125,36,250,249,231,159,233,79,127,250,19,125,241,197,23,244,242,229,203,82,135,102,182,155,205,134,
14,15,15,233,248,248,152,98,140,133,101,229,56,101,182,136,136,104,154,54,164,125,122,196,72,94,188,120,65,127,254,243,159,41,198,72,207,159,63,7,253,92,239,111,220,184,65,223,126,251,45,93,92,92,208,
179,103,207,160,220,124,125,112,112,64,247,238,221,19,146,142,143,143,27,23,82,151,183,66,143,121,120,231,195,91,207,143,199,85,15,6,215,135,221,60,204,222,176,43,182,206,213,211,245,152,192,205,148,207,
166,5,121,107,68,104,46,183,227,65,247,85,206,59,77,83,251,93,194,102,93,132,173,73,213,164,177,252,50,143,116,11,75,188,240,156,124,208,200,76,195,179,56,68,114,138,4,102,246,122,44,197,163,177,94,240,
30,178,140,244,7,174,14,189,53,32,46,103,127,127,159,238,223,191,47,24,199,203,151,47,11,203,66,147,148,40,210,249,249,57,189,120,241,156,158,60,249,146,78,78,106,30,173,223,195,135,15,41,198,72,175,94,
29,19,81,164,171,171,75,122,253,250,117,1,172,121,190,22,114,137,72,197,217,186,95,92,92,208,199,143,31,105,158,231,242,203,37,10,155,205,134,190,253,246,91,138,49,210,211,167,79,225,65,135,60,252,250,
235,175,244,235,175,191,54,114,208,36,71,115,192,51,156,72,214,136,225,242,234,206,198,125,180,44,146,229,25,180,222,47,118,68,145,120,23,166,164,168,244,226,191,78,87,54,88,188,132,24,75,30,221,30,92,
167,29,143,242,153,107,88,8,9,235,145,191,45,83,202,215,94,199,85,62,38,227,117,62,29,188,65,97,1,141,151,222,163,208,168,109,150,44,45,99,148,197,69,16,199,20,108,117,94,226,173,50,143,31,63,166,179,
179,51,58,63,63,167,255,248,143,255,144,105,71,143,233,253,135,247,76,124,44,207,243,250,122,166,227,227,87,180,191,127,139,158,60,249,146,62,126,252,72,49,70,1,6,155,205,134,30,119,65,116,107,0,0,32,
0,73,68,65,84,61,122,68,191,255,254,59,61,120,240,144,190,248,226,11,33,255,193,131,7,194,141,227,227,0,181,29,133,220,119,86,190,12,86,211,52,209,15,63,252,32,54,41,231,58,145,204,146,190,188,217,208,
99,19,58,126,215,60,8,8,109,23,200,6,41,175,156,167,83,123,223,223,182,128,162,133,147,96,182,57,27,168,89,188,141,48,59,253,189,203,117,57,192,47,4,34,254,210,225,90,102,193,193,202,178,8,68,212,186,
106,100,131,64,6,184,222,250,152,200,63,160,179,85,47,175,171,183,158,212,115,19,117,26,159,44,197,154,86,129,173,140,124,31,234,90,70,32,146,59,229,25,105,189,113,243,6,221,191,127,159,126,249,229,23,
154,227,156,214,163,22,17,55,111,222,164,39,127,124,66,119,239,220,45,107,55,156,5,231,253,77,47,95,190,164,219,183,111,211,253,251,247,233,244,244,84,236,123,122,252,248,49,133,16,232,205,155,55,116,
227,198,141,36,127,9,15,30,60,160,163,163,35,122,243,230,141,24,15,211,52,209,141,27,55,96,191,32,22,101,25,186,252,107,232,87,95,125,69,55,110,222,160,103,79,159,21,176,202,12,128,8,31,14,135,126,176,
137,49,150,61,91,18,76,170,44,30,202,126,46,227,21,30,190,207,15,13,240,30,99,202,186,106,96,67,243,168,55,63,67,104,143,86,146,237,107,245,231,101,144,97,71,164,164,149,205,226,24,251,202,219,105,184,
44,138,114,105,41,164,130,73,193,116,35,243,43,157,183,205,100,1,129,23,246,20,230,29,109,53,84,119,152,85,87,145,201,242,123,242,122,105,124,112,136,124,49,203,175,117,69,138,101,240,121,204,171,196,
241,180,44,76,5,143,165,53,113,133,79,83,177,88,150,59,27,66,160,199,135,143,233,226,226,162,128,198,197,249,133,72,191,127,239,62,29,30,30,150,197,119,254,97,128,202,182,102,250,233,167,159,202,90,82,
174,47,179,171,87,175,94,209,229,229,101,243,107,221,249,249,57,221,191,127,159,30,60,120,64,175,95,191,46,241,123,123,123,244,253,247,223,55,253,112,122,122,10,183,40,228,126,205,64,201,251,120,111,111,
143,110,223,190,77,68,68,223,125,247,93,83,246,236,236,76,236,249,10,33,208,221,187,119,233,223,255,253,223,69,190,24,163,185,15,171,120,51,212,98,79,140,145,52,24,65,38,0,216,72,51,79,152,17,242,216,
127,8,65,24,37,203,5,228,193,219,22,161,175,99,140,197,144,122,121,180,28,132,5,150,62,20,177,199,197,175,249,1,128,201,40,164,70,151,43,133,45,225,127,254,231,127,68,77,136,61,20,20,52,210,243,117,140,
105,49,118,196,173,211,229,116,60,186,39,234,111,115,24,149,131,234,29,113,91,172,251,145,58,117,250,167,212,199,195,237,131,3,186,190,186,146,96,18,234,239,76,219,237,150,110,222,188,41,24,214,222,222,
30,157,157,157,53,175,33,221,188,121,147,166,105,162,179,179,179,194,192,120,94,20,246,247,247,105,158,103,186,184,184,40,245,101,118,165,7,242,60,207,116,122,122,218,200,216,219,219,163,72,68,231,103,
103,69,255,28,166,105,162,253,253,125,88,183,144,185,212,181,183,183,215,236,140,207,50,175,175,174,232,252,252,156,242,113,38,4,222,188,224,161,199,218,99,156,161,43,101,149,95,83,23,159,172,22,171,66,
238,119,175,222,158,55,162,193,197,114,37,61,192,202,229,14,15,15,187,249,202,53,85,187,128,202,108,183,91,254,43,33,17,127,120,162,81,220,252,128,70,35,43,97,185,122,92,1,143,53,89,172,12,209,87,139,
102,247,244,241,88,163,151,207,210,79,231,255,87,198,241,240,126,249,85,208,202,123,121,121,41,64,34,132,80,192,69,7,13,38,87,203,4,71,33,255,170,155,23,244,243,253,197,197,133,41,223,210,49,231,135,95,
47,138,145,206,78,79,133,225,212,125,191,97,229,174,174,174,234,107,71,140,213,100,70,161,119,95,103,157,208,36,241,88,77,146,61,17,127,1,164,29,19,149,38,113,247,207,114,233,144,43,136,66,5,51,73,232,
45,86,164,227,80,123,133,247,177,244,213,200,28,213,44,138,175,99,233,250,219,107,70,35,73,49,46,117,29,227,242,46,161,62,4,13,178,172,14,187,208,13,65,229,122,76,102,148,109,213,235,130,199,174,92,34,
194,22,183,83,143,5,186,159,147,105,89,121,98,204,253,56,94,102,183,122,124,6,225,5,238,82,160,251,207,29,214,232,250,185,242,90,105,213,13,196,59,249,186,108,132,187,123,108,130,179,63,88,214,0,91,201,
224,188,150,121,245,220,55,116,239,230,7,203,42,245,154,127,220,130,21,49,0,50,143,221,45,239,60,180,206,194,209,24,209,67,203,50,121,105,22,152,33,196,143,203,226,157,87,7,146,159,25,99,177,174,6,248,
32,54,166,245,43,109,46,191,115,170,93,201,136,54,7,220,102,30,244,251,96,72,174,176,36,74,111,75,174,168,195,97,162,35,229,71,67,87,14,103,235,59,6,107,205,101,173,62,104,146,88,50,71,217,144,37,19,213,
81,152,98,200,247,121,102,179,116,106,159,113,92,232,148,136,103,20,75,112,149,104,63,251,94,156,6,200,25,233,193,210,17,235,213,243,138,235,150,174,125,252,208,158,82,190,222,242,201,156,191,106,235,
161,156,5,72,217,93,235,185,95,188,242,17,10,94,232,169,33,11,197,203,142,114,24,83,8,205,38,55,151,33,69,201,120,70,216,212,8,32,228,182,111,38,185,224,60,10,38,200,37,231,241,232,121,88,147,208,74,235,
133,225,50,168,94,235,245,40,102,161,137,168,249,165,110,215,224,129,80,9,12,28,242,17,210,188,68,51,33,29,0,211,117,205,10,148,214,50,154,164,139,4,13,200,148,136,26,240,235,233,214,24,223,16,106,251,
13,0,237,133,166,13,25,104,97,176,189,138,24,35,109,243,235,19,33,84,54,226,77,96,30,167,253,113,225,10,82,101,71,61,121,77,90,168,67,120,141,251,197,27,150,211,221,137,164,44,86,46,219,3,34,23,72,56,
160,81,237,39,47,228,117,27,189,168,13,31,52,168,170,1,184,32,33,96,45,155,242,216,193,154,48,234,130,154,19,8,84,167,223,134,176,66,215,149,115,211,74,207,138,52,221,28,153,223,96,12,41,82,76,208,181,
203,43,80,231,104,123,26,249,50,37,203,54,105,178,48,178,4,34,219,42,52,47,202,36,103,0,3,217,40,152,87,151,212,240,90,136,234,187,132,252,251,132,136,138,245,42,71,64,162,193,170,54,134,74,186,184,38,
60,200,209,67,179,128,171,199,150,172,135,60,82,222,138,211,242,37,139,91,254,10,143,200,103,68,102,232,228,203,117,7,21,199,117,67,58,243,124,189,176,6,180,186,44,6,228,241,220,152,24,229,79,241,86,24,
54,114,134,65,192,134,130,77,114,150,183,230,87,117,0,111,62,166,153,88,239,9,244,127,158,236,49,31,95,108,55,22,245,85,205,95,39,191,110,19,6,9,96,72,22,1,249,175,110,75,171,123,5,201,24,35,197,230,104,
25,130,215,86,64,186,165,69,119,53,137,134,93,164,78,126,207,178,175,145,99,185,52,16,84,99,37,203,158,165,26,113,11,122,245,234,56,228,183,83,182,60,170,185,37,127,94,103,51,64,200,99,41,168,13,218,197,
208,101,178,94,187,58,87,90,142,165,99,205,100,3,226,26,119,121,77,232,185,85,181,255,242,125,213,39,51,41,81,68,149,71,47,134,143,176,160,81,125,137,136,98,160,228,2,135,234,173,240,135,198,159,61,30,
215,249,205,129,117,204,105,212,61,181,198,24,159,135,97,154,104,187,221,54,172,206,147,39,214,41,137,202,33,135,68,233,135,179,109,62,115,136,55,152,255,213,241,232,218,106,136,254,170,116,175,30,52,
17,53,138,35,224,177,152,83,207,90,143,48,176,76,111,53,107,25,1,215,24,42,115,212,161,212,179,36,91,71,85,187,131,141,140,180,140,72,78,253,33,183,47,85,210,184,45,176,140,96,142,64,114,71,70,251,12,
154,28,126,157,131,114,173,52,125,173,139,105,151,100,151,224,109,187,233,25,18,152,39,146,248,197,207,91,230,200,143,17,201,203,198,17,253,166,153,215,174,71,245,242,218,193,13,102,136,81,110,47,209,
229,151,182,233,114,150,188,24,35,62,94,166,52,16,209,103,13,38,140,250,102,225,28,48,180,37,208,19,17,185,4,30,112,233,107,164,43,146,109,50,149,226,190,214,251,160,228,112,214,102,246,15,171,103,142,
115,99,13,81,190,162,131,76,105,172,162,103,205,234,3,111,178,44,229,199,38,222,0,46,152,193,235,139,229,138,244,80,250,148,250,114,157,158,59,201,227,244,24,210,99,197,51,102,107,128,203,98,223,72,23,
36,219,6,34,251,29,93,61,183,120,178,54,130,232,184,31,175,206,221,3,159,255,83,219,47,161,253,37,84,0,20,69,10,36,207,187,143,49,189,5,177,229,153,67,8,137,130,33,235,158,31,118,148,150,157,255,20,239,
1,83,183,137,3,0,227,201,179,64,11,229,227,242,61,205,214,186,195,37,142,210,113,210,189,118,203,54,115,64,118,139,17,17,123,199,45,81,36,170,143,105,29,18,212,231,40,251,162,48,47,167,12,191,231,224,
175,67,164,216,252,194,151,178,175,71,173,145,73,221,147,107,79,254,124,149,128,30,177,119,143,233,88,113,188,172,229,157,120,96,167,143,184,22,198,112,194,27,165,121,221,8,148,117,188,110,163,229,157,
244,88,34,31,7,241,154,40,189,9,80,25,124,169,207,145,155,174,91,96,198,12,43,216,191,234,213,73,142,39,163,233,26,69,249,130,167,247,112,52,59,234,185,132,188,110,171,12,170,211,98,120,153,77,53,0,58,
133,50,233,172,135,233,185,160,58,221,234,7,43,127,8,1,186,97,41,203,24,144,122,33,187,136,252,222,71,78,255,171,61,57,196,72,20,232,51,80,170,92,107,8,89,59,209,199,104,131,124,213,193,7,222,58,110,120,
94,185,249,89,123,15,22,232,89,117,122,247,8,235,5,88,46,68,185,184,116,140,56,151,125,138,132,245,225,115,175,7,66,30,171,178,242,39,221,49,240,232,122,243,188,178,228,34,93,248,156,14,33,216,46,161,
165,52,2,29,62,249,61,58,109,129,142,55,145,61,180,71,101,81,25,43,158,223,119,217,84,135,17,12,179,47,100,12,212,136,229,191,158,138,7,199,173,87,135,141,142,176,85,175,76,175,108,8,49,31,164,106,26,
145,44,147,99,234,39,121,26,185,110,88,143,182,201,82,7,21,83,244,176,198,211,136,75,180,198,165,211,65,142,111,191,76,186,94,12,132,34,228,101,172,196,42,215,98,109,250,68,11,239,122,116,30,243,94,71,
4,193,35,17,168,156,14,90,70,247,0,191,30,219,34,230,30,78,83,0,7,254,165,70,213,185,182,142,13,140,232,19,140,201,222,115,17,71,239,71,39,60,206,151,250,1,1,122,209,45,41,200,44,81,221,191,54,170,195,
194,184,87,233,87,111,37,251,29,171,207,239,219,88,38,80,171,167,13,45,88,207,209,143,70,120,110,145,150,237,187,57,124,178,246,245,68,117,73,214,54,6,130,53,61,1,84,142,91,54,56,16,69,251,5,104,107,94,
88,199,205,88,237,200,227,148,127,38,45,191,123,137,216,165,71,44,66,8,80,78,105,151,65,96,188,103,179,181,50,112,74,234,15,222,176,128,17,178,242,68,28,172,218,65,12,206,137,95,17,120,7,231,242,121,193,
27,177,56,239,158,203,67,242,69,139,13,93,49,40,46,214,223,1,2,109,52,40,180,174,95,15,72,106,223,218,253,216,182,191,164,116,251,2,201,24,201,239,6,197,22,122,117,120,1,129,5,159,20,60,109,140,57,140,
177,1,196,100,181,203,228,149,199,113,18,124,2,229,103,133,13,3,143,26,97,121,200,5,236,185,102,48,15,49,6,77,213,240,242,126,76,95,126,166,50,64,71,128,201,210,133,29,224,167,58,200,112,209,16,229,211,
66,237,175,38,103,249,220,106,101,48,243,127,201,65,247,58,110,151,193,55,206,168,130,74,111,68,149,244,106,27,75,100,163,151,245,241,90,47,14,13,160,116,63,54,96,45,121,94,221,214,167,190,122,186,173,
1,174,228,234,14,103,135,186,88,134,102,20,188,245,189,207,190,236,248,81,80,224,108,219,146,225,185,217,190,110,8,164,121,90,189,150,221,131,230,124,102,105,152,65,6,173,103,1,150,64,153,181,79,211,2,
182,3,115,213,106,147,0,172,158,75,104,133,30,189,204,215,216,93,176,7,182,53,248,45,218,61,2,100,107,152,2,47,83,235,150,32,220,99,51,145,167,1,118,214,179,242,163,125,155,254,194,140,238,175,159,163,
225,83,199,2,81,127,226,238,18,118,101,8,150,28,139,221,90,99,112,196,40,244,198,37,100,248,68,164,127,59,240,38,119,83,56,73,94,72,1,103,126,68,249,72,188,58,44,99,41,23,41,138,50,124,156,167,235,192,
43,80,243,0,61,11,162,72,51,5,170,96,247,57,24,94,8,33,157,214,80,104,29,152,76,150,21,227,129,231,73,178,2,89,239,123,89,0,182,150,81,113,54,196,203,247,228,216,44,138,167,75,158,132,100,120,147,205,
157,192,139,100,254,2,108,138,111,183,135,52,101,87,76,20,8,210,22,149,137,99,224,33,251,191,92,237,172,79,169,62,205,12,248,43,82,79,143,94,159,32,23,42,179,16,33,39,95,204,179,232,165,196,48,250,31,
111,168,178,173,60,109,220,26,99,101,229,207,58,230,123,100,12,215,48,53,139,181,161,32,189,37,91,47,125,205,227,178,206,249,59,132,196,214,160,179,251,80,228,17,209,54,203,145,107,26,118,195,120,103,
140,156,254,217,147,227,231,227,114,43,218,243,235,76,93,203,125,217,218,31,203,96,227,147,198,254,82,113,245,196,83,116,203,140,184,254,60,232,126,208,233,226,193,49,201,186,187,209,206,117,19,120,98,
127,64,232,224,157,138,176,150,237,112,215,2,37,160,161,36,1,218,79,247,235,238,179,38,33,87,1,109,4,0,93,159,62,208,11,176,97,89,222,97,187,29,157,215,48,67,203,219,136,203,196,230,167,42,112,240,15,
192,253,76,83,164,184,10,16,121,122,128,171,117,211,110,110,4,101,204,246,150,252,105,108,183,245,164,54,110,83,103,231,133,115,162,60,165,122,244,149,168,125,13,33,198,104,30,104,159,211,221,78,47,21,
46,250,229,247,236,40,80,250,104,109,187,155,151,223,135,196,125,155,206,240,88,226,200,186,84,47,110,196,50,66,86,38,60,17,169,187,110,67,171,132,175,227,218,160,39,99,5,126,123,42,195,122,115,127,2,
249,61,126,40,121,237,24,163,52,117,82,194,118,91,15,146,99,223,90,218,24,145,147,211,188,244,209,95,67,97,60,99,134,35,0,129,174,173,101,10,47,148,50,236,151,237,44,99,10,161,57,221,213,171,83,92,79,
237,92,46,107,88,186,114,228,14,141,88,115,52,41,249,189,102,34,35,110,85,224,19,96,192,237,27,89,255,201,247,122,0,141,150,237,165,13,3,8,24,23,176,44,183,132,72,140,49,161,62,37,232,83,104,249,77,182,
206,159,234,162,122,97,23,176,146,21,75,57,61,55,210,210,111,141,123,190,203,218,22,103,84,150,142,166,14,156,141,132,150,65,231,120,206,198,249,184,183,230,141,215,87,38,168,41,3,225,205,165,234,226,
213,13,175,13,41,138,121,216,203,122,182,214,177,50,92,200,232,96,235,173,89,149,181,50,165,70,145,30,198,22,139,77,198,162,194,154,245,44,111,96,90,125,160,203,229,124,163,15,153,203,28,217,47,131,66,
239,219,124,189,208,178,190,228,30,8,151,225,19,130,62,69,245,115,133,209,117,172,53,235,93,35,249,162,154,152,168,204,46,107,87,163,186,152,247,49,245,181,126,110,243,117,255,75,58,35,250,143,228,209,
233,211,52,137,79,186,121,76,171,92,211,130,177,32,110,158,103,188,173,65,95,91,238,33,178,22,93,198,162,92,134,70,6,73,160,244,38,185,76,91,76,137,210,7,233,45,229,4,138,177,126,246,106,4,152,116,92,
195,6,33,224,200,145,158,178,212,184,160,250,37,167,182,250,42,169,3,236,202,203,211,180,139,116,47,174,11,163,150,122,36,172,153,216,187,132,102,189,200,113,91,61,93,70,219,185,214,45,245,128,195,100,
48,73,161,82,214,90,95,213,58,123,203,38,72,23,196,136,66,72,172,156,19,10,190,113,116,40,48,253,244,115,137,49,86,151,112,132,30,134,144,207,206,226,172,33,105,155,21,212,101,123,0,136,234,33,162,102,
119,173,151,87,187,178,154,209,244,221,146,113,183,101,36,15,166,219,99,108,47,95,103,54,106,185,178,107,194,8,27,37,177,71,135,196,47,138,83,152,116,206,108,89,76,238,20,137,196,89,70,76,27,232,217,34,
0,232,49,100,171,60,186,247,66,168,131,186,203,5,49,179,40,87,230,243,177,188,23,173,135,101,100,81,255,140,186,171,141,23,192,211,160,4,44,207,211,47,76,120,158,14,185,134,6,9,210,222,141,88,195,26,177,
224,252,27,108,252,33,47,25,105,142,177,57,185,148,43,40,202,229,164,208,103,117,154,149,241,70,120,131,218,218,160,233,13,252,10,46,253,117,142,17,64,181,92,74,253,176,180,149,179,24,230,72,27,80,240,
152,111,77,99,111,30,80,0,233,141,208,134,5,246,215,118,218,221,223,126,254,126,248,84,38,6,243,115,198,97,149,49,152,8,202,111,247,185,17,199,243,199,8,153,138,183,212,224,121,23,170,210,166,126,57,22,
85,249,16,74,25,228,214,161,103,97,61,159,24,169,120,55,53,190,221,71,198,101,111,249,206,244,49,150,101,191,178,131,0,69,151,47,105,1,35,48,4,133,124,205,242,88,107,62,190,60,171,77,162,72,157,172,14,
38,244,172,156,165,131,182,36,208,250,57,244,188,97,143,142,146,124,65,83,196,155,58,183,47,5,123,22,18,233,223,72,116,128,178,175,15,14,250,7,1,109,161,189,122,68,74,200,239,205,181,12,184,232,101,129,
146,101,48,58,125,173,245,212,227,88,184,65,108,162,142,128,67,175,78,171,188,245,12,53,208,141,186,187,188,141,252,43,227,34,157,1,159,76,143,11,144,25,128,53,226,99,90,19,7,1,147,119,143,2,122,96,61,
234,236,14,240,24,23,63,58,245,73,58,222,75,235,78,20,35,255,9,182,21,19,66,88,252,114,38,150,177,186,6,104,28,166,53,50,153,120,126,125,45,155,55,246,131,3,81,235,202,121,245,113,217,107,194,104,254,
181,192,62,82,166,207,230,218,184,40,19,216,159,177,137,73,68,141,1,29,5,14,20,183,150,69,107,239,34,221,87,173,244,51,68,76,221,34,28,150,142,9,232,3,241,205,224,30,147,226,250,149,189,97,192,237,27,
53,83,89,223,41,176,227,101,180,251,212,2,71,81,77,196,233,206,210,10,115,153,90,9,90,138,174,249,21,9,117,62,80,114,177,154,53,202,182,136,68,222,78,239,12,84,146,161,247,129,122,164,29,187,164,229,250,
215,228,179,242,118,39,247,96,61,159,18,120,223,105,215,184,87,239,46,122,245,216,137,37,215,99,26,30,219,68,0,137,244,24,101,47,248,62,213,52,242,60,53,216,234,192,151,108,196,241,197,106,67,167,53,78,
180,14,222,151,156,123,237,211,127,175,231,57,1,22,154,108,124,32,33,198,99,177,32,228,254,160,192,101,140,238,240,214,250,52,29,196,40,188,101,105,82,65,9,146,104,193,112,68,15,47,79,175,76,213,103,236,
141,254,81,192,177,202,236,194,112,214,148,93,159,23,229,27,115,51,219,18,125,201,174,140,149,204,174,230,239,159,171,21,10,112,181,235,125,188,62,79,7,143,133,89,193,4,7,160,43,15,214,153,89,174,108,
101,112,146,210,117,142,201,15,75,172,103,205,28,115,182,104,103,58,159,216,83,152,234,145,45,108,247,105,88,254,151,43,65,86,102,141,5,28,113,71,106,30,196,102,36,163,210,193,114,163,198,235,180,227,
188,221,253,150,245,181,6,161,5,76,150,91,62,82,222,107,99,15,28,254,117,46,98,185,226,177,208,61,119,229,172,203,14,244,136,114,135,57,159,104,198,88,30,97,67,38,219,9,248,51,108,137,36,245,152,212,56,
11,227,161,117,33,237,182,32,242,225,45,127,136,113,28,66,83,62,132,32,220,73,177,62,28,219,211,125,249,181,118,119,67,8,253,109,13,41,123,218,145,26,103,5,76,161,146,154,60,169,80,197,104,114,122,157,
103,229,175,121,218,87,116,22,191,174,116,8,146,235,129,79,44,221,210,134,158,5,236,229,179,128,102,116,18,172,97,116,133,246,171,58,62,133,97,105,249,94,254,17,208,147,121,116,219,214,233,212,99,246,
61,214,168,13,89,111,172,112,153,35,207,12,185,184,16,212,122,64,183,226,158,199,107,0,232,201,17,121,147,3,96,200,173,248,106,25,95,142,9,94,159,89,70,147,191,214,147,203,111,225,3,138,145,2,91,140,135,
238,33,176,250,97,177,30,22,245,197,131,135,203,112,64,211,112,245,116,94,139,189,160,120,45,211,115,35,123,214,214,122,32,30,157,31,153,108,222,3,54,251,40,101,114,243,90,113,189,96,149,65,32,108,133,
52,16,139,166,53,240,249,59,200,157,186,160,207,44,145,247,28,70,220,31,20,223,107,175,126,134,222,248,67,242,172,113,219,27,39,69,102,144,71,43,123,12,48,207,115,49,15,152,58,186,205,153,168,120,253,
192,101,234,54,107,61,60,221,114,216,194,9,65,68,193,56,213,192,170,56,167,205,6,170,219,96,145,106,12,188,87,85,30,125,237,49,51,221,96,164,59,17,123,136,161,8,41,191,104,228,62,40,63,68,196,58,129,70,
216,18,186,239,5,47,191,5,134,35,237,70,178,173,129,129,158,239,104,24,97,112,68,11,91,15,96,204,57,229,71,153,12,44,75,145,104,206,159,184,178,63,156,177,107,253,35,147,76,135,89,124,65,200,126,166,61,
176,196,6,79,202,68,155,119,173,151,172,45,96,213,121,60,166,198,117,155,166,137,174,175,175,97,158,37,151,248,176,75,143,1,166,141,163,249,12,118,82,147,155,234,92,182,6,191,70,99,196,184,116,25,116,
239,213,97,229,239,149,241,203,165,191,252,152,150,72,227,236,102,212,117,226,180,121,44,191,253,101,147,172,147,119,63,26,118,233,235,127,117,216,5,176,117,30,51,61,212,45,30,163,238,212,104,186,200,
211,16,198,54,62,202,27,200,96,70,235,197,134,138,40,159,33,95,243,180,19,223,10,107,92,182,30,59,210,158,25,119,15,151,88,138,83,135,193,150,255,36,25,219,226,58,128,202,34,187,230,149,234,107,88,17,
3,179,158,219,148,227,44,166,96,49,7,89,126,38,106,86,161,34,5,103,47,210,232,196,181,24,10,79,179,217,99,187,78,210,211,165,141,179,218,204,243,13,50,4,134,162,94,191,142,80,125,16,107,234,32,172,126,
7,136,155,244,230,228,8,28,70,88,73,47,78,203,211,46,141,229,74,233,235,121,158,253,77,189,131,64,152,8,19,96,194,53,83,163,31,239,78,57,241,91,130,129,244,25,97,217,150,254,122,190,107,50,99,121,74,130,
8,196,72,49,180,7,39,38,192,98,55,250,186,103,125,81,153,53,231,149,243,9,201,179,150,70,44,202,183,172,174,164,178,120,105,65,83,153,224,90,147,53,237,227,63,205,174,97,115,92,39,47,95,140,49,61,40,66,
253,143,215,88,70,153,135,170,104,72,231,30,192,226,58,251,0,64,228,91,248,79,13,13,248,145,244,30,68,218,0,104,204,243,220,24,94,20,188,53,153,53,245,14,185,91,53,162,91,166,196,81,235,30,246,202,141,
186,127,86,27,226,108,127,168,213,187,78,31,221,224,0,86,153,233,22,189,230,192,27,153,4,80,66,103,118,141,124,29,221,64,228,34,54,29,176,252,55,176,202,210,53,102,117,252,51,240,136,197,233,186,237,19,
70,253,7,230,201,180,24,150,152,18,70,93,107,172,215,72,94,43,104,235,54,146,95,215,143,210,229,243,36,170,131,7,111,73,240,228,90,237,107,246,197,117,212,239,78,28,39,143,206,63,2,50,94,158,93,88,137,
149,142,152,168,24,103,192,243,201,247,72,103,157,79,127,118,203,26,171,158,254,158,87,132,62,238,234,246,1,147,197,9,2,15,91,157,32,168,155,162,105,250,90,211,60,60,168,49,91,203,113,65,221,139,107,174,
240,146,52,209,68,49,180,191,170,180,0,131,89,27,10,22,179,202,242,172,147,35,178,142,117,9,209,96,52,186,28,147,189,139,171,88,69,219,174,149,55,249,116,94,171,253,18,144,80,253,68,252,229,213,17,29,
123,121,184,75,99,21,29,89,52,94,171,195,104,176,250,124,13,195,26,45,111,213,61,12,108,112,40,98,3,162,137,1,210,15,1,35,47,163,193,144,95,91,249,10,184,21,118,101,204,163,37,110,187,153,54,195,63,33,
91,149,230,235,76,159,189,137,164,21,133,62,172,81,110,220,197,228,174,99,155,119,141,187,147,89,90,8,213,237,148,66,19,133,181,100,90,85,77,64,63,164,155,229,243,91,122,160,54,88,178,181,107,161,67,138,
30,115,33,83,78,102,252,148,62,173,108,111,98,102,134,136,211,55,155,141,200,236,141,222,53,96,53,2,120,250,200,95,139,229,163,103,5,93,53,62,89,67,104,228,160,178,189,49,81,129,173,45,59,10,234,35,0,
140,216,25,210,107,20,204,203,2,145,51,206,182,115,156,141,12,201,1,68,110,157,117,29,66,40,239,240,85,151,142,171,66,102,89,116,205,239,69,30,82,228,107,144,165,228,181,12,221,85,86,253,26,160,155,190,
96,255,229,101,229,131,241,221,203,94,24,117,163,56,211,179,218,162,7,61,170,125,23,247,179,148,229,47,200,2,125,214,4,125,176,36,15,35,44,196,11,107,25,215,200,164,229,161,119,54,187,7,92,61,176,34,74,
115,74,103,27,117,55,71,244,95,219,63,30,200,66,48,167,140,46,109,125,115,97,236,117,169,129,239,33,43,95,126,6,158,11,233,239,241,105,55,16,63,172,186,167,42,129,67,117,45,45,134,166,27,137,58,2,13,222,
17,86,230,197,107,128,233,49,56,29,151,219,153,132,224,252,189,54,120,241,40,189,199,192,172,160,153,1,119,153,71,193,115,36,196,164,20,139,240,7,255,72,159,244,220,91,158,127,164,63,70,251,140,231,143,
145,141,19,145,216,202,216,76,137,1,206,194,93,174,19,16,25,182,108,134,61,166,34,189,17,222,181,246,58,174,174,199,99,103,30,152,33,224,233,149,211,238,158,206,43,94,140,94,122,128,209,254,182,30,138,
245,51,95,186,49,250,126,103,70,4,58,220,155,28,50,141,119,102,11,168,250,104,156,81,240,18,105,97,121,43,50,140,77,92,244,192,209,3,193,131,114,156,193,172,113,91,215,200,94,3,76,159,4,98,150,75,136,
38,36,75,11,180,123,219,178,188,94,185,252,154,217,104,168,207,52,151,167,130,22,185,58,174,55,103,150,85,159,62,179,233,165,113,0,178,24,19,207,235,245,217,40,184,141,144,12,75,142,231,18,55,178,226,
192,241,212,145,242,103,190,168,76,216,172,28,169,95,125,90,102,229,79,242,184,32,140,229,108,146,234,24,29,86,131,143,151,95,91,18,249,43,3,255,51,244,160,61,183,81,90,193,126,27,218,135,42,155,178,11,
43,91,11,52,159,51,255,184,44,233,54,231,139,93,157,72,207,37,25,41,227,49,8,148,159,231,141,3,122,175,117,43,123,50,122,229,224,250,145,97,16,60,144,66,30,130,215,111,107,221,120,23,196,64,216,242,27,
205,110,116,221,114,82,102,55,50,211,62,34,162,184,184,132,89,131,10,14,130,93,25,29,160,7,129,174,23,233,89,100,128,111,36,90,244,87,31,108,247,41,172,199,170,111,205,126,52,125,191,139,139,230,130,200,
224,198,203,92,247,80,30,68,121,189,242,203,88,216,149,41,17,241,190,94,4,14,150,27,99,185,249,71,16,54,120,29,25,38,195,1,106,161,181,69,107,60,55,101,141,122,122,0,216,24,213,80,53,209,95,50,66,250,
68,181,247,47,151,177,234,69,227,23,206,211,60,215,167,176,16,137,52,79,188,53,75,30,182,233,189,166,49,132,135,107,62,12,148,82,252,2,100,139,79,174,7,169,199,66,144,191,142,242,241,128,58,199,10,149,
90,214,201,134,252,108,221,222,166,124,39,31,202,107,51,37,34,18,131,39,221,143,232,99,49,189,70,23,99,79,11,146,51,12,148,160,110,47,160,61,57,107,195,200,135,70,81,200,107,80,84,116,104,177,182,194,
20,6,6,244,205,63,236,250,13,132,101,126,32,94,230,141,49,207,104,143,26,248,24,35,77,97,98,32,38,245,42,101,152,126,200,213,133,205,82,224,138,192,150,187,119,69,230,138,190,219,142,130,85,174,76,3,138,
101,53,205,135,169,24,150,5,90,154,150,246,244,240,174,173,160,243,91,76,8,129,15,4,36,84,158,235,157,129,35,84,176,215,237,25,97,15,222,177,214,35,19,199,115,125,214,246,219,167,0,144,150,151,69,245,
84,104,25,133,184,51,10,201,155,89,235,221,220,70,57,169,156,250,137,136,196,79,215,214,82,136,97,196,16,184,244,88,147,206,99,109,183,104,212,84,134,186,200,102,44,28,25,63,228,98,246,72,69,8,252,203,
207,202,35,91,24,27,239,54,171,109,60,108,97,172,17,138,59,167,0,165,52,152,168,76,72,51,196,246,208,46,203,71,182,44,69,82,35,178,1,142,153,135,21,239,209,113,207,114,89,113,69,38,26,120,77,206,20,201,
193,103,196,101,236,233,234,133,94,190,30,120,121,0,181,214,117,245,215,93,198,100,180,253,32,238,108,64,17,183,200,101,194,233,60,84,217,104,170,181,113,35,96,100,26,64,38,195,2,43,75,102,73,83,243,113,
116,201,165,199,230,248,210,78,158,207,124,110,235,114,164,214,188,179,123,185,6,172,66,8,248,120,25,207,253,74,85,3,225,57,50,216,29,108,1,9,202,227,233,148,145,58,4,204,210,122,117,54,239,178,133,252,
39,212,123,213,45,238,251,111,33,173,139,33,215,203,154,236,187,184,97,189,65,154,197,52,228,193,1,232,145,250,62,7,139,26,173,203,186,255,44,242,57,243,201,227,212,216,244,219,3,113,156,222,111,131,92,
23,42,145,102,25,175,31,172,165,140,38,46,182,105,214,90,148,39,167,167,139,190,222,110,183,20,99,180,191,156,51,32,75,199,111,221,1,12,45,149,243,222,82,32,186,113,227,6,157,159,159,151,251,76,53,249,
11,141,122,226,141,48,7,11,124,52,88,217,64,144,235,6,148,183,24,216,184,208,183,182,217,252,24,100,100,125,243,158,155,236,251,243,181,49,175,61,124,208,237,10,92,53,126,188,236,46,193,211,111,45,211,
202,97,205,186,212,90,166,216,78,92,102,209,151,113,176,102,93,198,171,127,23,0,208,115,97,173,27,216,115,251,80,25,244,154,217,136,14,26,28,107,191,16,229,185,165,243,223,188,121,83,232,195,201,197,46,
227,112,154,38,218,26,63,138,208,82,3,44,232,1,196,157,59,119,136,136,232,242,242,178,201,179,139,155,131,238,61,23,133,63,12,57,177,67,97,102,40,112,187,103,237,31,226,214,89,212,207,228,206,224,179,
247,214,160,210,241,222,217,240,188,156,206,239,5,203,213,48,235,8,150,51,228,187,131,61,93,66,8,112,169,96,87,160,179,116,178,100,91,107,44,61,89,61,25,94,208,31,116,240,188,142,82,215,162,2,31,71,58,
88,113,194,205,37,9,40,163,32,234,165,15,187,161,68,180,183,191,71,183,111,223,94,34,169,180,171,15,86,202,135,85,245,108,41,34,95,156,11,167,54,93,177,16,222,233,155,205,134,238,223,191,79,243,60,211,
213,213,149,239,250,228,201,163,234,212,58,140,220,239,194,218,76,153,92,183,14,104,247,6,240,176,30,10,40,70,228,250,238,137,146,21,216,2,167,3,60,107,217,94,47,140,90,210,145,201,176,75,252,72,222,145,
73,59,210,215,163,224,50,82,198,170,111,164,14,139,237,141,182,187,176,39,253,203,46,112,45,209,253,102,179,17,167,141,142,232,50,18,230,244,153,175,29,124,73,241,57,250,26,207,41,223,52,77,180,183,183,
39,210,120,240,128,204,3,157,17,75,233,221,143,76,200,12,212,57,203,200,186,90,47,125,87,119,106,45,32,246,130,91,215,242,151,187,77,163,251,183,122,117,173,5,174,207,41,243,83,243,175,117,69,189,244,
53,128,59,10,68,249,30,187,108,182,139,55,42,119,23,93,136,90,54,165,221,198,93,66,250,46,97,254,73,51,18,244,233,57,227,88,84,34,238,183,230,145,189,70,241,124,63,77,242,212,130,64,242,29,35,11,180,172,
123,175,156,214,205,2,20,207,199,247,100,88,245,133,48,65,239,122,21,235,27,120,192,200,37,88,3,120,213,146,102,254,190,59,211,210,19,104,52,124,50,56,80,139,177,187,176,28,158,182,43,131,209,241,159,
194,26,71,1,173,183,92,226,213,135,229,203,31,183,114,64,107,86,60,205,154,251,107,130,144,73,97,89,195,34,130,191,110,137,206,74,17,34,189,85,106,46,110,138,80,48,132,82,22,185,111,124,227,106,8,242,
36,133,30,56,105,29,120,60,210,213,3,28,207,37,233,197,161,73,38,101,207,13,19,213,242,70,210,172,48,10,42,94,62,75,151,17,99,240,41,1,245,105,79,47,47,20,19,186,131,123,6,229,57,134,203,51,122,188,76,
15,68,172,181,180,145,49,166,229,120,227,86,223,215,172,222,61,62,69,98,23,198,133,210,100,112,62,18,66,233,215,198,230,87,194,81,26,92,170,96,238,219,90,183,15,61,204,4,90,242,53,0,171,227,181,222,205,
100,207,235,54,3,110,164,21,167,101,115,221,245,181,150,131,6,20,146,103,149,233,233,197,101,91,249,74,154,218,89,61,66,203,215,50,130,79,13,150,220,53,0,233,233,54,226,78,142,180,109,13,35,242,38,175,
248,50,242,10,61,70,218,104,25,2,254,220,19,151,168,156,180,102,203,115,83,222,35,25,75,3,136,38,13,132,188,253,106,220,7,127,165,33,23,209,121,166,105,162,109,108,114,174,11,189,137,200,243,241,142,209,
15,180,5,27,18,241,57,244,88,66,211,145,1,167,245,24,151,85,39,7,104,29,39,7,3,6,184,154,134,218,225,91,236,207,193,164,122,225,95,5,70,107,234,69,207,197,2,101,219,229,64,32,96,215,107,190,111,25,249,
229,24,136,164,75,13,2,82,95,62,102,244,187,173,222,216,28,25,183,30,171,27,89,82,49,137,132,199,90,163,188,71,172,204,27,150,49,214,116,47,223,86,164,13,88,160,79,99,38,159,182,110,99,61,48,157,63,132,
208,88,175,93,24,86,115,207,254,242,222,201,58,89,238,67,140,81,60,145,148,102,91,233,17,55,213,211,157,15,154,94,95,245,194,104,190,79,5,186,94,61,86,31,64,102,253,9,245,74,89,129,136,125,67,17,125,194,
62,187,49,150,167,162,81,208,52,240,49,141,213,166,13,177,142,97,139,181,81,172,80,218,115,221,92,57,3,229,71,221,189,181,239,89,38,128,147,113,186,79,231,121,166,45,218,63,99,189,152,233,85,110,49,3,
111,2,122,121,189,251,222,132,180,172,16,175,211,107,135,57,121,18,53,204,16,88,162,178,252,41,76,141,149,142,49,125,80,146,84,155,77,198,192,133,2,221,214,4,15,128,51,104,22,66,235,50,227,207,19,62,197,
221,242,242,175,41,211,203,219,99,122,94,31,142,214,7,199,109,160,178,235,94,148,209,214,145,52,168,82,187,244,193,0,44,229,205,235,80,53,174,204,37,107,223,33,208,89,3,29,108,155,186,24,125,54,246,216,
174,163,81,146,19,0,0,5,152,73,68,65,84,46,100,89,116,111,43,141,44,239,32,35,202,151,96,2,140,48,39,126,109,165,163,248,10,24,5,79,76,61,71,217,225,152,43,198,253,245,148,231,122,190,134,249,175,175,
175,77,182,86,212,5,128,102,129,26,10,107,192,12,245,177,239,22,140,185,87,41,187,13,182,163,237,232,14,114,198,58,244,179,237,173,47,245,128,153,191,130,133,216,3,218,220,187,11,16,175,253,144,134,165,
207,8,75,178,226,75,155,244,135,68,22,114,105,26,117,245,54,135,120,102,6,227,218,61,196,252,127,138,177,247,106,78,79,20,87,40,250,204,106,212,167,230,233,22,51,179,93,166,42,195,98,102,61,230,53,162,
159,5,198,94,95,54,186,26,249,121,156,126,127,177,184,186,38,1,28,48,46,210,155,249,164,144,154,180,158,17,253,255,146,203,159,183,120,78,78,62,30,196,179,7,114,60,16,52,93,165,14,192,12,177,152,206,124,
241,242,140,220,123,115,146,72,186,123,58,175,246,30,198,64,107,65,200,94,174,24,215,157,214,48,34,80,118,90,250,27,2,30,20,250,144,59,221,112,4,6,229,47,133,101,210,75,29,70,104,252,48,211,162,22,228,
122,242,173,96,178,200,134,190,203,244,207,181,214,228,129,174,149,191,117,191,137,154,129,197,72,216,231,114,31,61,166,198,245,171,249,177,17,66,6,168,183,156,192,243,141,178,40,180,236,193,67,118,211,
150,27,183,158,220,231,237,203,246,220,245,196,110,240,60,99,224,248,212,182,246,158,43,23,93,199,73,73,53,10,149,69,21,87,118,140,177,120,122,166,75,248,169,161,118,64,117,155,16,218,162,79,81,183,50,
242,189,116,1,71,153,141,105,1,130,236,46,200,190,40,54,229,173,1,102,181,131,151,211,215,58,31,234,15,203,61,245,6,225,90,214,108,229,215,250,100,230,35,242,175,192,168,207,182,30,166,196,12,175,99,5,
185,126,211,5,25,38,31,170,225,48,167,81,183,204,138,107,251,126,55,150,134,192,219,146,229,245,71,153,51,89,118,77,104,202,243,176,155,3,135,231,249,191,4,176,244,96,208,149,90,238,28,202,203,239,71,
27,62,178,254,212,196,89,178,65,252,8,195,234,173,151,140,196,247,64,71,83,111,84,191,39,191,55,1,188,96,178,78,102,8,188,250,71,235,51,251,209,121,46,107,218,50,226,126,173,5,174,145,248,209,180,181,
253,164,67,158,135,158,231,210,51,164,200,189,179,244,211,47,123,243,58,63,71,184,186,186,218,29,176,70,40,50,2,39,73,25,241,230,208,154,188,158,65,120,46,96,179,142,17,136,210,153,210,242,151,158,97,
151,177,88,28,233,131,239,194,124,176,75,202,174,39,172,167,118,159,118,113,33,63,151,219,57,26,224,216,137,237,239,210,156,81,199,104,79,130,17,247,112,36,140,26,137,212,229,45,211,181,152,118,207,56,
140,46,228,23,247,8,121,13,53,83,215,3,240,214,156,116,62,207,91,24,101,152,189,118,121,187,18,106,158,244,82,117,119,209,189,103,173,71,39,167,164,164,126,185,81,214,229,165,113,234,223,47,139,41,104,
147,159,237,237,10,181,64,219,134,178,235,181,45,199,3,178,94,34,157,213,31,209,246,147,208,158,166,225,29,81,51,58,121,209,51,88,21,130,253,185,174,181,193,18,225,30,103,83,22,5,181,44,127,44,143,232,
107,229,245,202,102,224,173,227,81,186,103,232,151,73,81,79,72,109,210,117,143,232,48,242,107,228,26,215,118,36,239,90,15,67,108,20,234,0,36,220,135,85,4,247,246,208,3,165,153,22,233,203,24,44,31,159,
8,30,48,104,86,228,177,166,252,162,116,78,69,95,223,24,117,19,123,29,237,165,237,26,143,192,106,196,13,161,194,238,100,57,143,29,154,237,10,237,230,149,132,131,190,139,100,230,139,242,135,132,93,92,206,
181,161,103,209,17,227,215,97,136,225,24,161,253,80,45,42,219,103,238,16,16,150,162,249,41,245,230,132,21,199,39,126,207,75,201,245,228,186,114,28,111,39,242,160,102,113,146,203,122,87,217,11,27,254,46,
225,46,22,217,27,140,249,99,149,86,199,140,130,146,238,100,171,211,51,27,233,185,58,88,159,246,112,191,94,89,205,162,68,156,142,119,38,139,238,255,17,183,164,213,30,148,25,34,72,60,83,108,82,130,119,44,
52,151,208,99,99,220,175,131,181,201,52,200,94,45,6,170,202,148,108,139,173,45,134,13,124,29,106,215,53,38,148,103,158,103,215,224,141,176,33,13,86,98,126,197,202,68,214,232,61,226,170,121,192,226,173,
83,21,234,199,130,123,148,248,14,129,247,229,102,179,161,109,177,133,249,143,86,62,24,19,2,229,237,4,143,101,121,174,221,154,248,230,62,231,7,250,192,250,195,242,16,12,183,53,51,10,244,181,32,249,129,
214,42,55,63,248,209,245,128,70,55,198,116,199,220,22,162,116,48,35,74,147,32,53,98,105,237,122,198,93,169,53,99,165,78,210,129,201,102,213,17,1,40,238,160,11,19,199,5,180,241,121,92,171,52,212,187,145,
98,51,215,209,188,179,198,134,136,99,114,214,128,149,190,183,136,129,151,151,52,118,172,220,59,167,67,15,232,211,105,13,228,79,124,79,192,104,126,139,106,243,180,209,133,192,94,126,235,126,238,200,211,
1,177,190,30,229,238,233,105,229,71,44,69,172,111,41,0,181,220,159,90,150,200,158,174,58,239,24,40,173,41,243,185,194,46,12,72,179,130,181,107,113,22,56,152,12,89,103,102,249,130,136,102,99,154,177,115,
52,206,136,22,38,19,106,89,174,71,242,6,24,152,133,182,14,173,179,88,222,209,0,19,73,236,94,215,178,26,253,117,95,132,207,51,38,82,187,178,200,214,72,135,16,214,239,116,31,201,175,39,76,246,223,81,81,
143,121,244,128,8,201,24,45,51,90,255,218,184,181,107,89,75,162,153,196,23,209,17,136,143,49,46,156,127,236,89,254,255,1,39,20,204,190,92,254,46,83,83,16,49,189,44,64,148,159,81,42,57,186,142,101,245,
147,92,134,144,52,14,185,80,185,12,124,103,183,51,158,45,6,164,227,240,125,165,94,77,61,130,189,165,225,135,92,79,36,27,246,27,247,194,56,224,128,80,23,216,199,113,135,207,237,255,7,91,208,94,105,9,56,
220,31,0,0,0,0,73,69,78,68,174,66,96,130,0,0};

const char* ParaphrasisAudioProcessorEditor::background2_png = (const char*) resource_ParaphrasisAudioProcessorEditor_background2_png;
const int ParaphrasisAudioProcessorEditor::background2_pngSize = 50787;


//[EndFile] You can add extra defines here...
//[/EndFile]
