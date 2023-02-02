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

#ifndef DROWAUDIO_ITUNESLIBRARYPARSER_H
#define DROWAUDIO_ITUNESLIBRARYPARSER_H

#include "dRowAudio_Utility.h"

/** Parses an iTunes Xml library into a ValueTree using a background thread.

    If the tree passed in already contains a generated library this will merge
    any new data from the file into it preserving any sub-trees or attributes
    that may have been added.

    You shouldn't need to use this directly, use the higher-level iTunesLibrary
    instead.
 */
class ITunesLibraryParser : public juce::Thread
{
public:
    /** Creates a parser with a given valid library file and a ValueTree with which
        to put the parsed data.
    */
    ITunesLibraryParser (const juce::File& iTunesLibraryFileToUse,
                         const juce::ValueTree& elementToFill,
                         const juce::CriticalSection& lockToUse);

    /** Destructor. */
    ~ITunesLibraryParser() override;

    //==============================================================================
    /** Returns true if the parser has finished. */
    bool hasFinished() const { return finished; }

    /** Returns the lock being used. */
    const juce::CriticalSection& getLock() const { return lock; }

    //==============================================================================
    /** @internal */
    void run() override;

private:
    //==============================================================================
    const juce::CriticalSection& lock;

    const juce::File iTunesLibraryFile;
    juce::ValueTree treeToFill, partialTree;
    std::unique_ptr<juce::XmlElement> iTunesDatabase;
    juce::XmlElement *iTunesLibraryTracks, *currentElement;

    int numAdded;
    bool finished;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ITunesLibraryParser)
};

#endif  // DROWAUDIO_ITUNESLIBRARYPARSER_H
