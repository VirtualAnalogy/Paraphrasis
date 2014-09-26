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

#include "SampleAnalyzer.h"

#include "Analyzer.h"
#include "Channelizer.h"
#include "PartialUtils.h"
#include "AiffFile.h"
#include "PartialUtils.h" 

SampleAnalyzer::SampleAnalyzer(AudioFormatManager &formatManager, WaitableEvent& syncObj, const String &name)
    : ThreadWithProgressWindow(name, false, false),
      formatManager(formatManager),
      analyzerSync(syncObj)
{

}
//==============================================================================
SampleAnalyzer::~SampleAnalyzer()
{
    
}

//==============================================================================
void SampleAnalyzer::run() noexcept
{
    buffer.clear();
    sampleRate = 0;
    
    if ( !m_samplePath.isEmpty() )
    {
        if ( ! readViaJuce() )
        {
            NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Ooops...", "Paraphrasis can not load file, sorry...");
            analyzerSync.signal();
            return;
        }
            
        if (threadShouldExit())
        {
            analyzerSync.signal();
            return;
        }
        
        analyze();
    }
    analyzerSync.signal();
}

//==============================================================================
bool SampleAnalyzer::readViaJuce() noexcept
{
    AudioFormatReader* reader = formatManager.createReaderFor (File(m_samplePath));
    
    if (reader == nullptr)
    {
        return false;
    }
    
    // check if user really wants to load a long sample
    if (reader->lengthInSamples / reader->sampleRate > 20)
    {
        bool result = NativeMessageBox::showOkCancelBox(AlertWindow::QuestionIcon, "Do you...?", "Do you REALLY want to load sample longer than 20 sec?");
        
        if ( !result )
        {
            delete reader;
            return false;
        }
    }
    
    // read samples
    setStatusMessage("Reading file...");
    AudioSampleBuffer fileSamples(2, reader->lengthInSamples);
    reader->read(&fileSamples, 0, reader->lengthInSamples, 0, true, true);
    
    // reverse
    if (reverse)
        fileSamples.reverse(0, reader->lengthInSamples);
    
    // mono -> stereo
    if (reader->numChannels == 2 && fileSamples.getNumChannels() == 2)
    {
        // huh strange stereo to mono algorith which seems to be working...
        // credits or inspiration: http://www.dsprelated.com/showmessage/106421/2.php
        int64 numSamples = fileSamples.getNumSamples();
        for (int i = 0; i < numSamples; i++)
        {
            *fileSamples.getWritePointer(0, i) = std::max(*fileSamples.getReadPointer(0, i), *fileSamples.getReadPointer(1, i));
        }
    }
    
    // delete reader ASAP so we dont forget and prevent memory leaks
    int64 lengthInSamples = reader->lengthInSamples;
    sampleRate = reader->sampleRate;
    delete reader;
    reader = nullptr;
    
    // transform data from JUCE to Loris (from float to double)
    buffer.reserve(lengthInSamples);
    const float *sample = fileSamples.getReadPointer(0);
    for (int i = 0; i < lengthInSamples; i++)
    {
        buffer.push_back(sample[i]);
    }
    
    return true;
}

//==============================================================================
void SampleAnalyzer::analyze() noexcept
{
    // analyze
    setStatusMessage("Anayzing sample...");
    Loris::Analyzer analyzer(m_resolution);
    analyzer.analyze(buffer, sampleRate);
    
    m_partials.clear();
    m_partials = std::move(analyzer.partials());
    
    setStatusMessage("Processing partials...");
    // chanelize - mark partial - not needed now
//    Loris::Channelizer channelizer(m_pitch);
//    channelizer.channelize(m_partials.begin(), m_partials.end());
    
    // partials in partial list will be sorted by start time
    m_partials.sort(Loris::PartialUtils::compareStartTimeLess());
}