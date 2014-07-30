/*
  ==============================================================================

    SampleAnalyzer.h
    Created: 30 Jul 2014 6:40:21am
    Author:  Tomas Medek

  ==============================================================================
*/

#ifndef SAMPLE_ANALYZER_H_INCLUDED
#define SAMPLE_ANALYZER_H_INCLUDED

#include "JuceHeader.h"
#include "ParameterDefitions.h"
#include "PartialList.h"

class SampleAnalyzer : public ThreadWithProgressWindow
{
public:
    SampleAnalyzer(AudioFormatManager &formatManager, WaitableEvent &syncObj, const String &name = "Paraphrasis is loading...");
    virtual ~SampleAnalyzer();
    
    void run() override;
    
    void setSamplePath(const String & path)
    {
        this->samplePath = path;
    }
    String samplaPath() const
    {
        return samplePath;
    }
    
    void setFrequencyResolution(double resolutionHz)
    {
        this->m_resolution = resolutionHz;
    }
    double frequencyResolution() const
    {
        return m_resolution;
    }
    
    void setPitch(double pitchHz)
    {
        this->m_pitch = pitchHz;
    }
    double pitch() const
    {
        return m_pitch;
    }
    
    Loris::PartialList partials() const
    {
        return m_partials;
    }
    
private:
    
    bool readViaJuce();
    bool readViaLoris();
    void analyze();
    
    String samplePath;
    double m_resolution = kParameterFrequencyResolution_defaultValue;
    double m_pitch = kParameterSamplePitch_defaultValue;
    
    AudioFormatManager& formatManager;
    WaitableEvent& analyzerSync;
    
    Loris::PartialList m_partials;
    std::vector<double> buffer;
    double sampleRate = 0;
    
};



#endif  // ANALYZER_H_INCLUDED
