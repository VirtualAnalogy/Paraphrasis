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

#ifndef DROWAUDIO_AUDIOFILEPLAYER_H
#define DROWAUDIO_AUDIOFILEPLAYER_H

#include "../streams/dRowAudio_StreamAndFileHandler.h"

/** This class can be used to load and play an audio file from disk.

    This combines the functionality of an AudioTransportSource,
    AudioFormatReader and AudioFormatReaderSource.

    @see AudioTransportSource
    @see AudioFormatReader
    @see AudioFormatReaderSource
    @see AudioFilePlayerExt
*/
class AudioFilePlayer : public StreamAndFileHandler,
                        public juce::PositionableAudioSource,
                        public juce::ChangeListener
{
public:
    /** Creates an empty AudioFilePlayer.

        This is a quick way to create an AudioFilePlayer as it will use its own
        AudioFormatManager and TimeSliceThread.
    */
    AudioFilePlayer();

    /** Creates an empty AudioFilePlayer that will use a supplied background thread
        and format manager.

        If either of these parameters is nullptr the AudioFilePlayer will create its
        own. This constructor is useful if you have lots of players and don't want
        loads of background thread running etc. If you supply your own thread
        remember to start it!
    */
    explicit AudioFilePlayer (juce::TimeSliceThread* threadToUse,
                              juce::AudioFormatManager* formatManagerToUse);

    /** Destructor.

        If you subclass from this, make sure to call
        audioTransportSource->setSource (nullptr) in your destructor so you don't
        mess up the audio chain dependancies and crash
    */
    virtual ~AudioFilePlayer() override;

    //==============================================================================
    /** Starts playing (if a source has been selected). */
    void start();

    /** Stops playing. */
    void stop();

    /** Play the audio file from the start. */
    void startFromZero();

    /** Pauses or plays the audio file. */
    void pause();

    /** Returns true if it's currently playing. */
    bool isPlaying() const noexcept { return audioTransportSource.isPlaying(); }

    //==============================================================================
    /** Changes the current playback position in the source stream.  */
    virtual void setPosition (double newPosition, bool ignoreAnyLoopBounds = false);

    /** Returns the position that the next data block will be read from in seconds.  */
    double getCurrentPosition() const { return audioTransportSource.getCurrentPosition(); }

    /** Returns the stream's length in seconds. */
    double getLengthInSeconds() const { return audioTransportSource.getLengthInSeconds(); }

    /** Returns true if the player has stopped because its input stream ran out of data. */
    bool hasStreamFinished() const noexcept { return audioTransportSource.hasStreamFinished(); }

    //==============================================================================
    /** Returns the AudioFormatReaderSource currently being used. */
    juce::AudioFormatReaderSource* getAudioFormatReaderSource() const { return audioFormatReaderSource.get(); }

    /** Returns the AudioTransportSource being used. */
    juce::AudioTransportSource* getAudioTransportSource() { return &audioTransportSource; }

    /** Sets the AudioFormatManager to use. */
    void setAudioFormatManager (juce::AudioFormatManager* newManager, bool deleteWhenNotNeeded);

    /** Returns the AudioFormatManager being used. */
    juce::AudioFormatManager* getAudioFormatManager() const { return formatManager; }

    /** Sets the TimeSliceThread to use. */
    void setTimeSliceThread (juce::TimeSliceThread* newThreadToUse, bool deleteWhenNotNeeded);

    /** Returns the background TimeSliceThread being used. */
    juce::TimeSliceThread* getTimeSliceThread() const { return bufferingTimeSliceThread; }

    //==============================================================================
    /** A class for receiving callbacks from a AudioFilePlayer.

        To be told when a player's file changes, you can register an AudioFilePlayer::Listener
        object using AudioFilePlayer::addListener().

        @see AudioFilePlayer::addListener, AudioFilePlayer::removeListener
    */
    class Listener
    {
    public:
        /** Destructor. */
        virtual ~Listener() {}

        /** Called when the player's file is changed.

            You can find out the new file using AudioFilePlayer::getFile().
        */
        virtual void fileChanged (AudioFilePlayer* player) = 0;

        /** Called when the the player is stopped or started.
            You can find out if it is currently stopped with isPlaying().
        */
        virtual void playerStoppedOrStarted (AudioFilePlayer* /*player*/) {}

        /** To avoid having to create a new listener interface for each subclass of AudioFilePlayer
            you can call this and send a SettingCode to your listeners to identify what sort of change occured
            e.g. playback rate, filter gain etc.
        */
        virtual void audioFilePlayerSettingChanged (AudioFilePlayer* /*player*/, int /*settingCode*/) {}
    };

    /** Adds a listener to be called when this slider's value changes. */
    void addListener (Listener* listener);

    /** Removes a previously-registered listener. */
    void removeListener (Listener* listener);

    //==============================================================================
    /** @internal */
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    /** @internal */
    void releaseResources() override;
    /** @internal */
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    /** @internal */
    void setNextReadPosition (juce::int64 newPosition) override { audioTransportSource.setNextReadPosition (newPosition); }
    /** @internal */
    juce::int64 getNextReadPosition() const override { return audioTransportSource.getNextReadPosition(); }
    /** @internal */
    juce::int64 getTotalLength() const override { return audioTransportSource.getTotalLength(); }
    /** @internal */
    bool isLooping() const override { return audioTransportSource.isLooping(); }
    /** @internal */
    void setLooping (bool shouldLoop) override;
    /** @internal */
    bool fileChanged (const juce::File& file) override;
    /** @internal */
    bool streamChanged (juce::InputStream* inputStream) override;
    /** @internal */
    void changeListenerCallback (juce::ChangeBroadcaster* source) override;

protected:
    //==============================================================================
    juce::OptionalScopedPointer<juce::TimeSliceThread> bufferingTimeSliceThread;
    juce::OptionalScopedPointer<juce::AudioFormatManager> formatManager;

    AudioSource* masterSource;
    std::unique_ptr<juce::AudioFormatReaderSource> audioFormatReaderSource;
    juce::AudioTransportSource audioTransportSource;

    juce::ListenerList<Listener> listeners;

    //==============================================================================
    /** Sets up the audio chain when a new source is chosen.

        By default this will create a new AudioFormatReader source and attach it to the
        AudioTransportSource. If you want to add your own sources overide this method.
        If you do change this make sure you set the masterSource member to the top level
        of your audio source chain.
    */
    virtual bool setSourceWithReader (juce::AudioFormatReader* reader);

private:
    //==============================================================================
    void commonInitialise();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioFilePlayer)
};

#endif // DROWAUDIO_AUDIOFILEPLAYER_H
