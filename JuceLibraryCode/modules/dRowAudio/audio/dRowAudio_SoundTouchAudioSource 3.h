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

#ifndef DROWAUDIO_SOUNDTOUCHAUDIOSOURCE_H
#define DROWAUDIO_SOUNDTOUCHAUDIOSOURCE_H

#if DROWAUDIO_USE_SOUNDTOUCH || DOXYGEN

#include "dRowAudio_SoundTouchProcessor.h"

/** An audio source that can independently change the rate,
    tempo and pitch of an audio source.

    This uses the SoundTouch library to perform the processing.
*/
class SoundTouchAudioSource : public juce::PositionableAudioSource
{
public:
    /** Creates a SoundTouchAudio source.
        The numberOfSamplesToBuffer parameter is how many samples the source will
        buffer internally. Due to the way SoundTouch processes samples any changes
        of playback settings will only come into effect some time after this number
        of samples has been process. For fine control try reducing this but beware
        the extra function calls will use more CPU.
    */
    SoundTouchAudioSource (juce::PositionableAudioSource* source,
                           bool deleteSourceWhenDeleted = false,
                           int numberOfSamplesToBuffer = 2048,
                           int numberOfChannels = 2);

    /** Destructor. */
    ~SoundTouchAudioSource();

    //==============================================================================
    /** Sets all of the settings at once. */
    void setPlaybackSettings (const SoundTouchProcessor::PlaybackSettings& newSettings);

    /** Returns all of the settings. */
    const SoundTouchProcessor::PlaybackSettings& getPlaybackSettings() const { return soundTouchProcessor.getPlaybackSettings(); }

    /** Returns the lock used when setting the buffer read positions. */
    const juce::CriticalSection& getBufferLock() { return bufferStartPosLock; }

    /** Returns the SoundTouchProcessor being used. */
    SoundTouchProcessor& getSoundTouchProcessor() { return soundTouchProcessor; }

    //==============================================================================
    /** @internal */
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    /** @internal */
    void releaseResources() override;
    /** @internal */
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& info) override;
    /** @internal */
    void setNextReadPosition (juce::int64 newPosition) override;
    /** @internal */
    juce::int64 getNextReadPosition() const override;
    /** @internal */
    juce::int64 getTotalLength() const override { return source->getTotalLength(); }
    /** @internal */
    bool isLooping() const override { return source->isLooping(); }
    /** @internal */
    void setLooping (bool shouldLoop) override { source->setLooping (shouldLoop); }

private:
    //==============================================================================
    juce::OptionalScopedPointer<juce::PositionableAudioSource> source;
    int numberOfSamplesToBuffer, numberOfChannels;
    juce::AudioSampleBuffer buffer;
    juce::CriticalSection bufferStartPosLock;
    juce::int64 volatile nextReadPos, effectiveNextPlayPos;
    double volatile sampleRate;
    bool isPrepared;

    SoundTouchProcessor soundTouchProcessor;

    void readNextBufferChunk();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundTouchAudioSource)
};

#endif
#endif // DROWAUDIO_SOUNDTOUCHAUDIOSOURCE_H
