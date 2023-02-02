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

#ifndef DROWAUDIO_CURLEASYSESSION_H
#define DROWAUDIO_CURLEASYSESSION_H

#if DROWAUDIO_USE_CURL || DOXYGEN

#include "dRowAudio_CURLManager.h"

/** Creates a CURLEasySession.

    One of these is used to handle a specific transfer optionally on a
    background thread. Either create one on the stack for quick tranfers and
    when it goes out of scope it will clean up after itself or create an object
    to re-use and use the various methods to control the transfer.

    @todo directory list is returned if this is found before a file transfer
    @todo rename remote file if it already exists
*/
class CURLEasySession : public juce::TimeSliceClient
{
public:
    /** Creates an uninitialised CURLEasySession.

        You will need to set up the transfer using setLocalFile() and setRemotePath()
        and then call beginTransfer() to actucally perform the transfer.
    */
    CURLEasySession();

    /** Creates a session and performs the transfer. */
    CURLEasySession (const juce::String& localPath,
                     const juce::String& remotePath,
                     bool upload,
                     const juce::String& username = juce::String(),
                     const juce::String& password = juce::String());

    /** Destructor */
    ~CURLEasySession();

    //==============================================================================
    /** Sets the the source of an upload to an input stream. */
    void setInputStream (juce::InputStream* newInputStream);

    /** Sets the local file to either upload or download into. */
    void setLocalFile (const juce::File& newLocalFile);

    /** Returns the local file being used.

        If an input stream has been specified this will return File::nonexistent.
    */
    const juce::File& getLocalFile() const { return localFile; }

    /** Sets the remote path to use.

        This can be a complete path with a file name. If so the path will be used
        as the destination file for an upload or as the source for a download.
        If this ends with a '/' character a random file name will be generated.
    */
    void setRemotePath (const juce::String& newRemotePath);

    /** Returns the remote path being used.

        If this ends with a '/' character it specifies a directory.
    */
    const juce::String& getRemotePath() const { return remotePath; }

    /** Sets the user name and password of the connection.
        This is only used if required by the connection to the server.
    */
    void setUserNameAndPassword (const juce::String& username, const juce::String& password);

    //==============================================================================
    /** Returns the current working directory of the remote server. */
    juce::String getCurrentWorkingDirectory() const;

    /**    Returns the directory listing of the remote file. */
    juce::StringArray getDirectoryListing();

    /** Returns the content type of the current remote path. */
    //String getContentType(); // not yet ready

    //==============================================================================
    /** Turns on full debugging information.

        This is probably best turned off in release builds to avoid littering the console.
    */
    void enableFullDebugging (bool shouldEnableFullDebugging);

    /** Begins the transfer.

        Returns an error code or an empty String if everything is set up ok.
        The transfer will actually take place on a background thread so use getLastError()
        to determine the last error that occured.
    */
    void beginTransfer (bool transferIsUpload, bool performOnBackgroundThread = true);

    /** Stops the current transfer. */
    void stopTransfer();

    /** Resets the state of the session to the parameters that have been specified. */
    void reset();

    /** Returns the progress of the current transfer. */
    float getProgress() const { return progress.get(); }

    //==============================================================================
    /** A class for receiving callbacks from a CURLEasySession.

        Note that these callbacks will be called from the transfer thread so make sure
        any code within them is thread safe!
     */
    class Listener
    {
    public:
        /** Destructor */
        virtual ~Listener() {}

        /** Called when a transfer is about to start. */
        virtual void transferAboutToStart (CURLEasySession* /*session*/) {}

        /** Called when a transfer is about to start. */
        virtual void transferProgressUpdate (CURLEasySession* /*session*/) {}

        /** Called when a transfer is about to start. */
        virtual void transferEnded (CURLEasySession* /*session*/) {}
    };

    /** Adds a listener to be called when this slider's value changes. */
    void addListener (Listener* listener);

    /** Removes a previously-registered listener. */
    void removeListener (Listener* listener);

    //==============================================================================
    /** @internal */
    int useTimeSlice() override;

private:
    //==============================================================================
    CURL* handle;
    juce::String remotePath, userNameAndPassword;
    bool isUpload, shouldStopTransfer;
    juce::Atomic<float> progress;

    juce::File localFile;
    std::unique_ptr<juce::FileOutputStream> outputStream;
    std::unique_ptr<juce::InputStream> inputStream;
    juce::MemoryBlock directoryContentsList;

    juce::CriticalSection transferLock;
    juce::ListenerList<Listener> listeners;

    //==============================================================================
    int performTransfer (bool transferIsUpload);

    static size_t writeCallback (void* sourcePointer, size_t blockSize, size_t numBlocks, CURLEasySession* session);
    static size_t readCallback (void* destinationPointer, size_t blockSize, size_t numBlocks, CURLEasySession* session);
    static size_t directoryListingCallback (void* sourcePointer, size_t blockSize, size_t numBlocks, CURLEasySession* session);
    static int internalProgressCallback (CURLEasySession* session, double dltotal, double dlnow, double ultotal, double ulnow);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CURLEasySession)
};

#endif
#endif  // DROWAUDIO_CURLEASYSESSION_H
