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

using namespace soundtouch;

SoundTouchProcessor::SoundTouchProcessor()
    : interleavedInputBufferSize (512),
      interleavedOutputBufferSize (512)
{
    setPlaybackSettings (settings);

    interleavedInputBuffer.malloc ((size_t) interleavedInputBufferSize * 2);
    interleavedOutputBuffer.malloc ((size_t) interleavedOutputBufferSize * 2);
    
    soundTouch.setSetting (SETTING_USE_QUICKSEEK, 1);
}

void SoundTouchProcessor::initialise (int numChannels, double sampleRate)
{
    const ScopedLock sl (lock);
    soundTouch.setChannels ((uint32) numChannels);
    soundTouch.setSampleRate ((uint32) sampleRate);
    soundTouch.clear();
}

void SoundTouchProcessor::writeSamples (float** sourceChannelData, int numChannels, int numSamples, int startSampleOffset)
{
    const int requiredBufferSize = numSamples * numChannels;

    if (interleavedInputBufferSize < requiredBufferSize)
    {
        interleavedInputBuffer.malloc ((size_t) requiredBufferSize);
        interleavedInputBufferSize = requiredBufferSize;
    }

    for (int i = 0; i < numChannels; ++i)
        sourceChannelData[i] += startSampleOffset;
                                            
    using SourceFormat = AudioData::Format<AudioData::Float32, AudioData::NativeEndian>;
    using DestFormat   = AudioData::Format<AudioData::Float32, AudioData::NativeEndian>;

    AudioData::interleaveSamples (AudioData::NonInterleavedSource<SourceFormat> { sourceChannelData, numChannels },
                                  AudioData::InterleavedDest<DestFormat> { interleavedInputBuffer, numChannels },
                                  numSamples);                 

    for (int i = 0; i < numChannels; ++i)
        sourceChannelData[i] -= startSampleOffset;

    const ScopedLock sl (lock);
    soundTouch.putSamples ((SAMPLETYPE*) interleavedInputBuffer, (uint32) numSamples);
}

void SoundTouchProcessor::readSamples (float** destinationChannelData, int numChannels, int numSamples, int startSampleOffset)
{
    const int requiredBufferSize = numSamples * numChannels;

    if (interleavedOutputBufferSize < requiredBufferSize)
    {
        interleavedOutputBuffer.malloc ((size_t) requiredBufferSize);
        interleavedOutputBufferSize = requiredBufferSize;
    }

    int numSamplesDone = 0;
    int numThisTime = 0;

    {
        const ScopedLock sl (lock);

        for (;;)
        {
            const int maxNumSamples = numSamples - numSamplesDone;
            numThisTime = (int) soundTouch.receiveSamples ((SAMPLETYPE*) &interleavedOutputBuffer[numChannels * numSamplesDone], (uint32) maxNumSamples);

            numSamplesDone += numThisTime;

            if (numSamplesDone == numSamples || numThisTime == 0)
                break;
        }
    }

    if (numSamplesDone < numSamples)
        zeromem (&interleavedOutputBuffer[numChannels * numSamplesDone], (size_t) numChannels * sizeof (numSamples - numSamplesDone));

    for (int i = 0; i < numChannels; ++i)
        destinationChannelData[i] += startSampleOffset;
                                              
    using SourceFormat = AudioData::Format<AudioData::Float32, AudioData::NativeEndian>;
    using DestFormat   = AudioData::Format<AudioData::Float32, AudioData::NativeEndian>;

    AudioData::deinterleaveSamples (AudioData::InterleavedSource<SourceFormat> { interleavedOutputBuffer, numChannels },
                                    AudioData::NonInterleavedDest<DestFormat>  { destinationChannelData,  numChannels },
                                    numSamples);                                          
                                              
    for (int i = 0; i < numChannels; ++i)
        destinationChannelData[i] -= startSampleOffset;
}

void SoundTouchProcessor::setPlaybackSettings (const PlaybackSettings& newSettings)
{
    settings = newSettings;

    const ScopedLock sl (lock);
    soundTouch.setRate (settings.rate);
    soundTouch.setTempo (settings.tempo);
    soundTouch.setPitch (settings.pitch);
}

void SoundTouchProcessor::setSoundTouchSetting (int settingId, int settingValue)
{
    soundTouch.setSetting (settingId, settingValue);
}

int SoundTouchProcessor::getSoundTouchSetting (int settingId)
{
    return soundTouch.getSetting (settingId);
}

#endif //DROWAUDIO_USE_SOUNDTOUCH
