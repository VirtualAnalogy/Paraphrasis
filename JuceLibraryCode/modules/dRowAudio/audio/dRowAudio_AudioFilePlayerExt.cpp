/*
  ==============================================================================

  This file is part of the dRowAudio JUCE module
  Copyright 2004-13 by dRowAudio.

  ------------------------------------------------------------------------------

  dRowAudio is provided under the terms of The MIT License (MIT):

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

  ==============================================================================
*/

#if DROWAUDIO_USE_SOUNDTOUCH

AudioFilePlayerExt::AudioFilePlayerExt()
{
    loopingAudioSource = std::make_unique<LoopingAudioSource>(&audioTransportSource, false);
    reversibleAudioSource = std::make_unique<ReversibleAudioSource>(&audioTransportSource, false);
    filteringAudioSource = std::make_unique<FilteringAudioSource>(reversibleAudioSource.get(), false);

    masterSource = filteringAudioSource.get();
}

AudioFilePlayerExt::~AudioFilePlayerExt()
{
    audioTransportSource.setSource (nullptr);
}

//==============================================================================
void AudioFilePlayerExt::setPlaybackSettings (const SoundTouchProcessor::PlaybackSettings& newSettings)
{
    jassert (soundTouchAudioSource != nullptr);

    currentSoundtouchSettings = newSettings;
    soundTouchAudioSource->setPlaybackSettings (newSettings);

    listeners.call (&Listener::audioFilePlayerSettingChanged, this, SoundTouchSetting);
}

const SoundTouchProcessor::PlaybackSettings& AudioFilePlayerExt::getPlaybackSettings() const
{
    if (soundTouchAudioSource != nullptr)
        return soundTouchAudioSource->getPlaybackSettings();

    return currentSoundtouchSettings;
}

void AudioFilePlayerExt::setPlayDirection (bool shouldPlayForwards)
{
    jassert (reversibleAudioSource != nullptr);
    reversibleAudioSource->setPlayDirection (shouldPlayForwards);

    listeners.call (&Listener::audioFilePlayerSettingChanged, this, PlayDirectionSetting);
}

bool AudioFilePlayerExt::isPlayingForwards() const
{
    jassert (reversibleAudioSource != nullptr);
    return reversibleAudioSource->isPlayingForwards();
}

void AudioFilePlayerExt::setFilterGain (FilteringAudioSource::FilterType type, float newGain)
{
    jassert (filteringAudioSource != nullptr);
    filteringAudioSource->setGain (type, newGain);

    listeners.call (&Listener::audioFilePlayerSettingChanged, this, FilterGainSetting);
}

//==============================================================================
void AudioFilePlayerExt::setLoopTimes (double startTime, double endTime)
{
    currentLoopStartTime = startTime;
    currentLoopEndTime = endTime;

    loopingAudioSource->setLoopTimes (startTime, endTime);
}

void AudioFilePlayerExt::setLoopBetweenTimes (bool shouldLoop)
{
    shouldBeLooping = shouldLoop;

    if (loopingAudioSource != nullptr)
        loopingAudioSource->setLoopBetweenTimes (shouldLoop);

    listeners.call (&Listener::audioFilePlayerSettingChanged, this, LoopBetweenTimesSetting);
}

bool AudioFilePlayerExt::isBetweenLoopTimes()
{
    if (loopingAudioSource != nullptr)
        return loopingAudioSource->isBetweenLoopTimes();

    return shouldBeLooping;
}

void AudioFilePlayerExt::setPosition (double newPosition, bool ignoreAnyLoopBounds)
{
    if (ignoreAnyLoopBounds && loopingAudioSource != nullptr)
    {
        const double sampleRate = audioFormatReaderSource->getAudioFormatReader()->sampleRate;

        if (sampleRate > 0.0)
            loopingAudioSource->setNextReadPositionIgnoringLoop (secondsToSamples (newPosition, sampleRate));
    }
    else
    {
        AudioFilePlayer::setPosition (newPosition);
    }
}

//==============================================================================
bool AudioFilePlayerExt::setSourceWithReader (AudioFormatReader* reader)
{
    if (soundTouchAudioSource != nullptr)
        currentSoundtouchSettings = soundTouchAudioSource->getPlaybackSettings();

    audioTransportSource.setSource (nullptr);
    loopingAudioSource = nullptr;
    soundTouchAudioSource = nullptr;
    bufferingAudioSource = nullptr;

    if (reader != nullptr)
    {
        // we SHOULD let the AudioFormatReaderSource delete the reader for us..
        audioFormatReaderSource = std::make_unique<AudioFormatReaderSource>(reader, true); 
        bufferingAudioSource = std::make_unique<BufferingAudioSource>(audioFormatReaderSource.get(),
                                                                      *bufferingTimeSliceThread,
                                                                      false,
                                                                      32768);
        soundTouchAudioSource = std::make_unique<SoundTouchAudioSource>(bufferingAudioSource.get());
        loopingAudioSource = std::make_unique<LoopingAudioSource>(soundTouchAudioSource.get(), false);
        loopingAudioSource->setLoopBetweenTimes (shouldBeLooping);
        updateLoopTimes();

        audioTransportSource.setSource (loopingAudioSource.get(),
                                        0, nullptr,
                                        reader->sampleRate);

        listeners.call (&Listener::fileChanged, this);
        setPlaybackSettings (currentSoundtouchSettings);

        return true;
    }

    setLibraryEntry (ValueTree());
    listeners.call (&Listener::fileChanged, this);

    return false;
}

void AudioFilePlayerExt::updateLoopTimes()
{
    const double duration = audioTransportSource.getLengthInSeconds();
    currentLoopEndTime = jmin (currentLoopEndTime, duration);

    if (currentLoopStartTime > currentLoopEndTime)
        currentLoopStartTime = jmax (0.0, currentLoopEndTime - 1.0);
}

#endif //DROWAUDIO_USE_SOUNDTOUCH
