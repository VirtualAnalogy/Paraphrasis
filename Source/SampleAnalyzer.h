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
#ifndef SAMPLE_ANALYZER_H_INCLUDED
#define SAMPLE_ANALYZER_H_INCLUDED

#include "JuceHeader.h"
#include "ParameterDefitions.h"
#include "PartialList.h"

/**
 Sample analyzer reads audio files and converts it into Loris::PartialList. It can reverse loaded sample.
 Analysis runs in another thread.
 */
class SampleAnalyzer : public ThreadWithProgressWindow
{
public:
    /**
     Create new SampleAnalyzer object.
     @param formatManager format manager object for loading audio files.
     @param syncObj sinalize when thread/analysis is finished.
     */
    SampleAnalyzer(AudioFormatManager &formatManager, WaitableEvent &syncObj, const String &name = "Paraphrasis is loading...");
    virtual ~SampleAnalyzer();
	
    /** Start the analysis thread. When analysis is finished WitableEvent passed in constructor is signaled. */
    void run() noexcept override;
    
    void setSamplePath(const String & path) noexcept            { this->m_samplePath = path; }
    String samplePath()  noexcept                               { return m_samplePath; }
    
    void setFrequencyResolution(double resolutionHz) noexcept   { this->m_resolution = resolutionHz; }
    double frequencyResolution() const noexcept                 { return m_resolution; }
    
    void setPitch(double pitchHz) noexcept                      { this->m_pitch = pitchHz; }
    double pitch() const noexcept                               { return m_pitch; }
    
    void setReverse(bool reverse) noexcept                      { this->reverse = reverse; }
    
    Loris::PartialList& partials() noexcept                     { return m_partials; }
    
private:
    
    /** Read file specified by samplePath using formatManager passed in constructor */
    bool loadAudioFile() noexcept;
    /** Analyse loaded sampes. */
    void analyze() noexcept;
    /** Read SDIF file using Loris. */
    bool loadSdif() noexcept;
    /** Fix phases and order partials by time. */
    void postProcessPartials() noexcept;
    
    String m_samplePath;
    double m_resolution = kParameterFrequencyResolution_defaultValue;
    double m_pitch      = kParameterSamplePitch_defaultValue;
    bool reverse        = false;
    
    AudioFormatManager& formatManager;
    WaitableEvent& analyzerSync;
    
    Loris::PartialList m_partials;
    std::vector<double> buffer;
    double sampleRate = 0;
    
};



#endif  // ANALYZER_H_INCLUDED
