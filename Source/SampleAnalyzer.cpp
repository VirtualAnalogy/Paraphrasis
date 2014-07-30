/*
  ==============================================================================

    ;
    Created: 30 Jul 2014 6:40:21am
    Author:  Tomas Medek

  ==============================================================================
*/

#include "SampleAnalyzer.h"

#include "Analyzer.h"
#include "Channelizer.h"
#include "PartialUtils.h"
#include "AiffFile.h"
#include "PartialUtils.h" 

SampleAnalyzer::SampleAnalyzer(AudioFormatManager &formatManager, WaitableEvent& syncObj, const String &name)
    : ThreadWithProgressWindow(name, true, true),
      formatManager(formatManager),
      analyzerSync(syncObj)
{

}
//==============================================================================
SampleAnalyzer::~SampleAnalyzer()
{
    
}
//==============================================================================
void SampleAnalyzer::run()
{
    buffer.clear();
    sampleRate = 0;
    
    if ( ! readViaJuce() && ! readViaLoris() )
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
    
    analyzerSync.signal();
}
//==============================================================================
bool SampleAnalyzer::readViaJuce()
{
    AudioFormatReader* reader = formatManager.createReaderFor (File(samplePath));
    
    if (reader == nullptr)
    {
        return false;
    }
    
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
    AudioSampleBuffer fileSamples(1, reader->lengthInSamples);
    reader->read(&fileSamples, 0, reader->lengthInSamples, 0, true, false);
    
    // delete reader ASAP so we dont forget and prevent memory leaks
    int64 lengthInSamples = reader->lengthInSamples;
    sampleRate = reader->sampleRate;
    delete reader;
    reader = nullptr;
    
    // transform data from JUCE to Loris
    buffer.reserve(lengthInSamples);
    const float *sample = fileSamples.getReadPointer(0);
    for (int i = 0; i < lengthInSamples; i++)
    {
        buffer.push_back(sample[i]);
    }
    
    return true;
}
//==============================================================================
bool SampleAnalyzer::readViaLoris()
{
    try
    {
        Loris::AiffFile inputFile(samplePath.toStdString());
        
        buffer = inputFile.samples();
        Loris::AiffFile::markers_type markers = inputFile.markers();
        sampleRate = inputFile.sampleRate();
        return true;
    }
    catch (...)
    {
        return false;
    }
   
    return false;
}
//==============================================================================
void SampleAnalyzer::analyze()
{
    // analyze
    setStatusMessage("Anayzing sample...");
    Loris::Analyzer analyzer(m_resolution);
    analyzer.analyze(buffer, sampleRate);
    
    m_partials.clear();
    m_partials = analyzer.partials();
    
    setStatusMessage("Processing partials...");
    // chanelize - mark partial
    Loris::Channelizer channelizer(m_pitch);
    channelizer.channelize(m_partials.begin(), m_partials.end());
    
    // partials in partial list will be sorted by start time
    m_partials.sort(Loris::PartialUtils::compareStartTimeLess());
}