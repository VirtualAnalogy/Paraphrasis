/*
 ==============================================================================
 This file was auto-generated!
 It contains the basic startup code for a Juce application.
 ==============================================================================
 */
// My stuff
#include "PluginProcessor.h"
#include "PluginEditor.h"
// Juce
#include "juce_FileLogger.h"
// Loris
#include "Analyzer.h"
#include "AiffFile.h"
#include "PartialUtils.h"
#include "SdifFile.h"
#include "Synthesizer.h"
#include "RealTimeSynthesizer.h"

#include "Channelizer.h"

#define PAD
#ifdef PAD
  #define FUNDAMENTAL_FREQUENCY 440 //pad
#else
  #define FUNDAMENTAL_FREQUENCY 109 //pno
#endif

//==============================================================================
class LorisSound : public SynthesiserSound
{
public:
    LorisSound() {}

    bool appliesToNote(const int /*midiNoteNumber*/)
    {
        return true;
    }
    bool appliesToChannel(const int /*midiChannel*/)
    {
        return true;
    }
};

//==============================================================================
/** A simple demo synth voice that just plays a sine wave.. */
class LorisVoice  : public SynthesiserVoice
{
public:
    LorisVoice(Loris::PartialList partials) :
        tailOff(0.0), sampleIndex(0), synth(buffer)
    {
        Logger::getCurrentLogger()->writeToLog(String(":: new voice initialized "));
        secPerSample = 1.0 / 44100;
    
        synth.setupRealtime(partials);

        lastFreqMultiplyer = 1.0;
        play = false;
    }

    bool canPlaySound(SynthesiserSound* sound)
    {
        return dynamic_cast <LorisSound*>(sound) != 0;
    }

    void startNote(int midiNoteNumber, float velocity,
                   SynthesiserSound* /*sound*/, int /*currentPitchWheelPosition*/)
    {
        level = velocity * 0.15;
        sampleIndex = 0;
        tailOff = 0.0;
        
        double freqMultiplyer = MidiMessage::getMidiNoteInHertz (midiNoteNumber) / FUNDAMENTAL_FREQUENCY;
    
        synth.resetSynth(freqMultiplyer / lastFreqMultiplyer);//scale back to original and scale to desired pitch
        
        lastFreqMultiplyer = freqMultiplyer;
        play = true;
    }

    void stopNote(bool allowTailOff)
    {
        if (allowTailOff)
        {
            // start a tail-off by setting this flag. The render callback will pick up on
            // this and do a fade out, calling clearCurrentNote() when it's finished.
            
            if (tailOff == 0.0) // we only need to begin a tail-off if it's not already doing so - the
                // stopNote method could be called more than once.
                tailOff = 1.0;
        }
        else
        {
            // we're being told to stop playing immediately, so reset everything..
            stop();
        }
    }

    void pitchWheelMoved(int /*newValue*/)
    {
        // can't be bothered implementing this for the demo!
    }

    void controllerMoved(int /*controllerNumber*/, int /*newValue*/)
    {
        // not interested in controllers in this case.
    }

    void renderNextBlock(AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
    {
        if ( !play ) return;
        
        synth.synthesizeNext(numSamples);
        
        if (tailOff > 0.)
        {
            while (--numSamples >= 0)
            {
                double currentSample = sampleIndex < buffer.size() ? buffer[sampleIndex] * tailOff : 0.0;
                
                tailOff *= 0.99;
                
                if (tailOff <= 0.005)
                {
                    stop();
                    break;
                }

                for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample(i, startSample, currentSample);

                ++startSample;
                ++sampleIndex;
            }
        }
        else
        {
            while (--numSamples >= 0)
            {
                double currentSample = sampleIndex < buffer.size() ? buffer[sampleIndex] : 0.0;
                
                for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample(i, startSample, currentSample);
                
                ++startSample;
                ++sampleIndex;
            }
        }
    }
    
    void stop()
    {
        play = false;
        tailOff = 0.;
        sampleIndex = 0;
        clearCurrentNote();
    }

private:
    double level, tailOff;
    int sampleIndex;
    std::vector<double> buffer;
    double secPerSample;
    
    Loris::PartialList partials;
    Loris::PartialList filteredPartials;
    Loris::RealTimeSynthesizer synth;
    double lastFreqMultiplyer;
    bool play;
};


//==============================================================================
ParaphrasisAudioProcessor::ParaphrasisAudioProcessor()
{
    userParams[masterBypass]=0.0f;//default to not bypassed
    //repeat for "OtherParams"
    uiUpdateFlag=true;//Request UI update
    
    initLogging();

    initLoris();

    for (int i = 10; --i >= 0;)
        synth.addVoice(new LorisVoice(partials));    // These voices will play our custom sine-wave sounds..

    synth.addSound(new LorisSound());
}

//==============================================================================
ParaphrasisAudioProcessor::~ParaphrasisAudioProcessor()
{
    deleteLogger();
}
//==============================================================================
void ParaphrasisAudioProcessor::deleteLogger()
{
    Logger* logger = Logger::getCurrentLogger();
    Logger::setCurrentLogger(nullptr);
    delete logger;
}
//==============================================================================
void ParaphrasisAudioProcessor::initLogging()
{
    deleteLogger();
    Logger* logger = FileLogger::createDefaultAppLogger(String("/Users/tomasmedek/Documents/"), String("Paraphrasis.log"), String("Paraphrasis Log"));
    Logger::setCurrentLogger(logger);
    
}
//==============================================================================
void ParaphrasisAudioProcessor::initLoris()
{
    decltype(std::chrono::high_resolution_clock::now()) begin, end;
    
#define LOAD_FROM_AIFF 1
#if LOAD_FROM_AIFF

#ifdef PAD
    Loris::AiffFile inputFile("/Users/tomasmedek/Documents/Tmp/LorisTest/pad-quater.aiff");
#else
    Loris::AiffFile inputFile("/Users/tomasmedek/Documents/Tmp/LorisTest/Piano.ff.C3.mono.cropped.aiff");
#endif
    
    Loris::AiffFile::samples_type samples = inputFile.samples();
    Loris::AiffFile::markers_type markers = inputFile.markers();
    double analysisRate = inputFile.sampleRate();
    
    Logger::getCurrentLogger()->writeToLog(String(":: File loaded and has samples ") + String((int) samples.size()));
    
    Loris::Analyzer analyzer(FUNDAMENTAL_FREQUENCY * 0.85);
    Logger::getCurrentLogger()->writeToLog(String(":: Analyzing"));
    begin = std::chrono::high_resolution_clock::now();
    analyzer.analyze(samples, analysisRate);
    end = std::chrono::high_resolution_clock::now();
    Logger::getCurrentLogger()->writeToLog(String(":: Analysis done in ") + String((int)std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count()) + String(" ms"));
    partials = analyzer.partials();
    
    Logger::getCurrentLogger()->writeToLog(String(":: Partials found ") + String((int) partials.size()));
    
    Loris::Channelizer channelizer(FUNDAMENTAL_FREQUENCY);
    channelizer.channelize(partials.begin(), partials.end());
    
#else
    Loris::SdifFile sdifFile("/Users/tomasmedek/Downloads/loris-1.8/utils/partials.sdif");
    
    Logger::getCurrentLogger()->writeToLog(String(":: SDIF file "));
    partials = sdifFile.partials();
#endif
    
#if 0
    Logger::getCurrentLogger()->writeToLog(String(":: Filtering partials for first 10 harmonics"));
    auto it = partials.begin();
    Loris::PartialList filteredPartials;
    while ( it != partials.end() )
        {
        if ( it->label() <= 10 )
            {
            filteredPartials.push_back( *it );
            }
        it++;
        }
    partials = filteredPartials;
#endif
    
#if WRITE_SDIF
    Loris::SdifFile sdifFileWrite(partials.begin(), partials.end());
    sdifFileWrite.write("/Users/tomasmedek/Documents/Tmp/LorisTest/pad-cropped.sdif");
#endif
    //Loris::PartialUtils::scaleNoiseRatio(partials.begin(), partials.end(), 0);
    Loris::PartialUtils::scaleBandwidth(partials.begin(), partials.end(), 0);
    Logger::getCurrentLogger()->writeToLog(String(":: Final partials count ") + String((int) partials.size()));
}
//==============================================================================
const String ParaphrasisAudioProcessor::getName() const
{
    return JucePlugin_Name;
}
//==============================================================================
int ParaphrasisAudioProcessor::getNumParameters()
{
    return totalNumParam;
}
//==============================================================================
float ParaphrasisAudioProcessor::getParameter(int index)
{
    //TODO: add cases for any special parameters
    if (index >= 0  && index < totalNumParam)
        return userParams[index];
    else
        return 0.0f;//invalid index
}
//==============================================================================
void ParaphrasisAudioProcessor::setParameter(int index, float newValue)
{
    //TODO: add cases for any special parameters
    if (index >= 0 && index < totalNumParam)
        userParams[index] = newValue;

    uiUpdateFlag = true;//Request UI update for when it did not come from  the primary editor
}
//==============================================================================
const String ParaphrasisAudioProcessor::getParameterName(int index)
{
    switch (index)
    {
        case masterBypass :
            return "Master Bypass";
        //OtherParams...
        default :
            return String::empty;
    }
}
//==============================================================================
const String ParaphrasisAudioProcessor::getParameterText(int index)
{
    if (index>=0 && index < totalNumParam)
        return String(userParams[index]);  //return parameter value as string
    else
        return String::empty;
}
//==============================================================================
const String ParaphrasisAudioProcessor::getInputChannelName(int channelIndex) const
{
    return String(channelIndex + 1);
}
//==============================================================================
const String ParaphrasisAudioProcessor::getOutputChannelName(int channelIndex) const
{
    return String(channelIndex + 1);
}
//==============================================================================
bool ParaphrasisAudioProcessor::isInputChannelStereoPair(int index) const
{
    return true;
}
//==============================================================================
bool ParaphrasisAudioProcessor::isOutputChannelStereoPair(int index) const
{
    return true;
}
//==============================================================================
bool ParaphrasisAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}
//==============================================================================
bool ParaphrasisAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}
//==============================================================================
bool ParaphrasisAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}
//==============================================================================
double ParaphrasisAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}
//==============================================================================
int ParaphrasisAudioProcessor::getNumPrograms()
{
    return 0;
}
//==============================================================================
int ParaphrasisAudioProcessor::getCurrentProgram()
{
    return 0;
}
//==============================================================================
void ParaphrasisAudioProcessor::setCurrentProgram(int index)
{
}
//==============================================================================
const String ParaphrasisAudioProcessor::getProgramName(int index)
{
    return String::empty;
}
//==============================================================================
void ParaphrasisAudioProcessor::changeProgramName(int index, const String& newName)
{
}
//==============================================================================
void ParaphrasisAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    synth.setCurrentPlaybackSampleRate(sampleRate);
}
//==============================================================================
void ParaphrasisAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}
//==============================================================================
void ParaphrasisAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    //for (int channel = 0; channel < getNumInputChannels(); ++channel)
    //{
    //    float* channelData = buffer.getWritePointer (channel);
    // ..do something to the data...
    //}
    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    //for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    //{
    //    buffer.clear (i, 0, buffer.getNumSamples() );
    //}

    const int numSamples = buffer.getNumSamples();

    // and now get the synth to process these midi events and generate its output.
    if (userParams[masterBypass] == 0.0f)
        synth.renderNextBlock(buffer, midiMessages, 0, numSamples);
}
//==============================================================================
bool ParaphrasisAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}
//==============================================================================
AudioProcessorEditor* ParaphrasisAudioProcessor::createEditor()
{
    return new ParaphrasisAudioProcessorEditor(this);
}
//==============================================================================
void ParaphrasisAudioProcessor::getStateInformation(MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    //Save userParams/Data to file
    XmlElement root("Root");
    XmlElement* el;
    el = root.createNewChildElement("Bypass");
    el->addTextElement(String(userParams[masterBypass]));
    copyXmlToBinary(root,destData);
}
//==============================================================================
void ParaphrasisAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    //Load userParams/Data from file
    XmlElement* pRoot = getXmlFromBinary(data,sizeInBytes);
    if (pRoot!=NULL)
    {
        forEachXmlChildElement((*pRoot), pChild)
        {
            if (pChild->hasTagName("Bypass"))
            {
                String text = pChild->getAllSubText();
                setParameter(masterBypass, text.getFloatValue());
            }
        }
        delete pRoot;
        uiUpdateFlag=true;//Request UI update
    }
}
//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ParaphrasisAudioProcessor();
}