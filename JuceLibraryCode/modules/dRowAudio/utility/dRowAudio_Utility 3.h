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

#ifndef DROWAUDIO_UTILITY_H
#define DROWAUDIO_UTILITY_H

#include "dRowAudio_XmlHelpers.h"
#include "dRowAudio_DebugObject.h"

//==============================================================================
/** @file

    This file contains some useful utility functions and macros.
 */
//==============================================================================

/** Returns the Resources folder in the package contents on a Mac and if an equivalent exists on Windows.
    This will return File::nonexistent if the file does not exist so check for this first.
*/
inline static juce::File getResourcesFolder()
{
    return juce::File::getSpecialLocation (juce::File::currentExecutableFile).getParentDirectory().getParentDirectory().getChildFile ("Resources");
}

/** If the String passed in is a local path, this will return a string with the file://localhost part
    of the file path stripped and any escaped characters (e.g. %20) converted to ascii
 */
inline static juce::String stripFileProtocolForLocal (const juce::String& pathToStrip)
{
    if (pathToStrip.startsWith ("file://localhost"))
    {
       #if JUCE_WINDOWS
        juce::String temp (pathToStrip.substring (pathToStrip.indexOf (7, "/") + 1));
       #else
        juce::String temp (pathToStrip.substring (pathToStrip.indexOf (7, "/")));
       #endif
        return juce::URL::removeEscapeChars (temp);
    }

    return {};
}

/** Converts an iTunes formatted date string (e.g. 2010-12-27T17:44:32Z)
    into a Time object.
 */
inline static juce::Time parseITunesDateString (const juce::String& dateString)
{
    int year    = dateString.substring (0, 4).getIntValue();
    int month   = dateString.substring (5, 7).getIntValue() - 1;
    int day     = dateString.substring (8, 10).getIntValue();
    int hours   = dateString.substring (11, 13).getIntValue();
    int minutes = dateString.substring (14, 16).getIntValue();
    int seconds = dateString.substring (17, 19).getIntValue();

    return juce::Time (year, month, day, hours, minutes, seconds, 0, true);
}

/** Reverses an array */
template<class Type>
void reverseArray (Type* array, int length)
{
    Type swap;

    for (int a = 0; a < --length; a++)  //increment a and decrement b until they meet eachother
    {
        swap = array[a];                //put what's in a into swap space
        array[a] = array[length];       //put what's in b into a
        array[length] = swap;           //put what's in the swap (a) into b
    }
}

/** Reverses two arrays at once.

    This will be quicker than calling reverseArray twice.

    The arrays must be the same length.
*/
template <class Type>
void reverseTwoArrays (Type* array1, Type* array2, int length)
{
    Type swap;

    for (int a = 0; a < --length; a++)  //increment a and decrement b until they meet eachother
    {
        swap = array1[a];               //put what's in a into swap space
        array1[a] = array1[length];     //put what's in b into a
        array1[length] = swap;          //put what's in the swap (a) into b

        swap = array2[a];               //put what's in a into swap space
        array2[a] = array2[length];     //put what's in b into a
        array2[length] = swap;          //put what's in the swap (a) into b
    }
}

/**  Finds the key for a given track from the chemical-records website.
    This will attempt to find the key listed on the chemical website for a given release number
    eg. "31R038" and track title eg. "Wait For Me".
    This is in the Mixed in Key format eg. 11A and will return an empty string if nothing could be found.

    @param releaseNo    The catalogue number to look for.
    @param trackName    The track name to look for.
    @param retryLimit    An optional number of retries as sometimes the URL won't load first time.
*/
static inline juce::String findKeyFromChemicalWebsite (const juce::String& releaseNo, const juce::String& trackName)
{
    juce::URL chemicalURL ("http://www.chemical-records.co.uk/sc/servlet/Info");
    chemicalURL = chemicalURL.withParameter ("Track", releaseNo);

    juce::String pageAsString (chemicalURL.readEntireTextStream());
    juce::String trackInfo (pageAsString.fromFirstOccurrenceOf ("<table class=\"tracks\" cellspacing=\"0\" cellpadding=\"4\">", true, false));
    trackInfo = trackInfo.upToFirstOccurrenceOf("</table>", true, false);

    std::unique_ptr<juce::XmlElement> tracksXml (juce::XmlDocument::parse (trackInfo));

    if (tracksXml != nullptr)
    {
        juce::XmlElement* tracksElem (XmlHelpers::findXmlElementContainingSubText (tracksXml.get(), trackName));

        if (tracksElem != nullptr)
        {
            juce::XmlElement* nextElem = tracksElem->getNextElement();

            if (nextElem != nullptr)
            {
                juce::XmlElement* keyElem = nextElem->getFirstChildElement();

                if (keyElem != nullptr)
                    return keyElem->getAllSubText();
            }
        }
    }

    return {};
}

//==============================================================================
/** Draws a line representing the normalised set of samples to the given Image.

    Note the samples must be in the range of 1-0 and the line will be stretched to fit the whole image.
*/
static inline void drawBufferToImage (const juce::Image& image, const float* samples, int numSamples, juce::Colour colour, float thickness)
{
    if (image.isNull())
        return;

    jassert (image.getWidth() > 0 && image.getHeight() > 0);

    juce::Graphics g (image);
    g.setColour (colour);
    const float imageXScale = image.getWidth() / (float) numSamples;

    juce::Path p;
    bool isFirst = true;

    for (int i = 0; i < numSamples; ++i)
    {
        const float x = i * imageXScale;
        const float y = image.getHeight() - (samples[i] * image.getHeight());

        if (isFirst)
        {
            p.startNewSubPath (x, y);
            isFirst = false;
        }

        p.lineTo (x, y);
    }

    g.strokePath (p, juce::PathStrokeType (thickness));
}

/** Dumps a given image to a File in png format.

    If the file parameter is nonexistant a temp file will be created on the desktop.
*/
static inline void saveImageToFile (const juce::Image& image, juce::File file = {})
{
    if (! file.exists())
        file = juce::File::getSpecialLocation (juce::File::userDesktopDirectory).getNonexistentChildFile ("tempImage", ".png");

    juce::PNGImageFormat format;
    std::unique_ptr<juce::OutputStream> os (file.createOutputStream());

    if (os != nullptr)
        format.writeImageToStream (image, *os);
}

//==============================================================================
/** Holds a ValueTree as a ReferenceCountedObject.

    This is somewhat obfuscated but makes it easy to transfer ValueTrees as var objects
    such as when using them as DragAndDropTarget::SourceDetails::description members.
*/
class ReferenceCountedValueTree : public juce::ReferenceCountedObject
{
public:
    /** Creates a ReferenceCountedValueTree for a given ValueTree. */
    ReferenceCountedValueTree (const juce::ValueTree& treeToReference) :
        tree (treeToReference)
    {
    }

    /** Sets the ValueTree being held. */
    void setValueTree (const juce::ValueTree& newTree)
    {
        tree = newTree;
    }

    /** Returns the ValueTree being held. */
    juce::ValueTree getValueTree() const { return tree; }

    typedef juce::ReferenceCountedObjectPtr<ReferenceCountedValueTree> Ptr;

    /** Provides a simple way of getting the tree from a var object which
        is a ReferencedCountedValueTree.
    */
    static inline juce::ValueTree getTreeFromObject (const juce::var& treeObject)
    {
        ReferenceCountedValueTree* refTree
            = dynamic_cast<ReferenceCountedValueTree*> (treeObject.getObject());

        return refTree == nullptr ? juce::ValueTree() : refTree->getValueTree();
    }

private:
    //==============================================================================
    juce::ValueTree tree;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReferenceCountedValueTree)
};

//==============================================================================
/** Holds an Identifier as a ReferenceCountedObject.

    This is useful so that Identifiers can be passed around as var objects
    without having to convert them to Strings and back which defeats the point of them.
 */
class ReferenceCountedIdentifier : public juce::ReferenceCountedObject
{
public:
    /** Creates a ReferenceCountedIdentifier for a given Identifier. */
    ReferenceCountedIdentifier (const juce::Identifier& identifierToReference) :
        identifier (identifierToReference)
    {
    }

    /** Sets the Identifier to be held.
     */
    void setIdentifier (const juce::Identifier& newIdentifier)
    {
        identifier = newIdentifier;
    }

    /** Returns the Identifier being held. */
    const juce::Identifier& getIdentifier() const { return identifier; }

    typedef juce::ReferenceCountedObjectPtr<ReferenceCountedIdentifier> Ptr;

    //==============================================================================
    /** Provides a simple way of getting the Identifier from a var object which
        is a ReferenceCountedIdentifier.
    */
    static inline juce::Identifier getIdentifierFromObject (const juce::var& identiferObject)
    {
        ReferenceCountedIdentifier* refIdentifer
            = dynamic_cast<ReferenceCountedIdentifier*> (identiferObject.getObject());

        return refIdentifer == nullptr ? juce::Identifier::null : refIdentifer->getIdentifier();
    }

private:
    //==============================================================================
    juce::Identifier identifier;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReferenceCountedIdentifier)
};

//==============================================================================
/** Holds a MemoryBlock as a ReferenceCountedObject.

    This can be a useful way of managing a MemoryBlock's lifetime and also enables
    you to pass it around in a ValueTree.
*/
class ReferencedCountedMemoryBlock : public juce::ReferenceCountedObject
{
public:
    /** Creates a ReferencedCountedMemoryBlock with a blank MemoryBlock.
     */
    ReferencedCountedMemoryBlock()
    {}

    /** Creates a ReferencedCountedMemoryBlock for a given MemoryBlock.
        Note that this will take a copy of the data so you can dispose of the the
        block passed in as you like.
     */
    ReferencedCountedMemoryBlock (const juce::MemoryBlock& memoryBlockToReference)
        : memoryBlock (memoryBlockToReference)
    {}

#if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
    /** Creates a ReferencedCountedMemoryBlock for a given MemoryBlock.
        This will move the data from the given memory block so don't expect to
        use it afterwards.
     */
    ReferencedCountedMemoryBlock (MemoryBlock&& other)
        : memoryBlock (other)
    {}
#endif

    /** Returns the MemoryBlock being held.
     */
    const juce::MemoryBlock& getMemoryBlock() const { return memoryBlock; }

    /** Provides a simple way of getting the MemoryBlock from a var object which
        is a ReferencedCountedMemoryBlock.
     */
    static inline const juce::MemoryBlock* getMemoryBlockFromObject (const juce::var& blockObject)
    {
        ReferencedCountedMemoryBlock* refBlock
            = dynamic_cast<ReferencedCountedMemoryBlock*> (blockObject.getObject());

        return refBlock == nullptr ? nullptr : &refBlock->getMemoryBlock();
    }

    typedef juce::ReferenceCountedObjectPtr<ReferencedCountedMemoryBlock> Ptr;

private:
    //==============================================================================
    juce::MemoryBlock memoryBlock;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReferencedCountedMemoryBlock)
};

//==============================================================================
/** Writes a ValueTree to a specified file.

    This is a helper method to conveniently write a ValueTree to a File,
    optionally storing it as Xml.
*/
static inline bool writeValueTreeToFile (const juce::ValueTree& treeToWrite, const juce::File& fileToWriteTo, bool asXml = true)
{
    if (fileToWriteTo.hasWriteAccess())
    {
        if (asXml)
        {
            std::unique_ptr<juce::XmlElement> treeAsXml (treeToWrite.createXml());

            if (treeAsXml != nullptr)
            {
                fileToWriteTo.replaceWithText (treeAsXml->toString());
                return true;
            }

            return false;
        }

        juce::TemporaryFile tempFile (fileToWriteTo);
        std::unique_ptr<juce::FileOutputStream> outputStream (tempFile.getFile().createOutputStream());

        if (outputStream != nullptr)
        {
            treeToWrite.writeToStream (*outputStream);
            outputStream = nullptr;

            return tempFile.overwriteTargetFileWithTemporary();
        }
    }

    return false;
}

/** Reads a ValueTree from a stored file.

    This will first attempt to parse the file as Xml, if this fails it will
    attempt to read it as binary. If this also fails it will return an invalid
    ValueTree.
*/
static inline juce::ValueTree readValueTreeFromFile (const juce::File& fileToReadFrom)
{
    std::unique_ptr<juce::XmlElement> treeAsXml (juce::XmlDocument::parse (fileToReadFrom));
    if (treeAsXml != nullptr)
    {
        return juce::ValueTree::fromXml (*treeAsXml);
    }

    std::unique_ptr<juce::FileInputStream> fileInputStream (fileToReadFrom.createInputStream());
    if (fileInputStream != nullptr
        && fileInputStream->openedOk())
    {
        return juce::ValueTree::readFromStream (*fileInputStream);
    }

    return {};
}

//==============================================================================
/** Simple class that reads a ValueTree from a file and saves it back again on destruction. */
class ScopedValueTreeFile
{
public:
    /** Creates a blank ScopedValueTreeFile.
        This initially does nothing, use the setFile() method to read the contents
        into the internal tree and then retrieve it using getTree().
    */
    ScopedValueTreeFile()
        : asXml (true)
    {
    }

    /** Creates a ScopedValueTreeFile for a given file.
        Thsi will read the contents of the File into the internal ValueTree which
        you can then retrieve with the getTree() method.
    */
    ScopedValueTreeFile (const juce::File& sourceFile)
        : asXml (true)
    {
        setFile (sourceFile);
    }

    /** Destructor.
        Saves the contents of the tree to the current file.
    */
    ~ScopedValueTreeFile()
    {
        save();
    }

    /** Sets the file to use.
        This will attempt to read the contents of the File into the ValueTree which
        you can obtain using the getTree() method.
     */
    void setFile (const juce::File& newFile) { file = newFile; tree = readValueTreeFromFile (file); }

    /** Saves the file to disk using a TemporaryFile in case there are any problems. */
    juce::Result save()
    {
        return writeValueTreeToFile (tree, file, asXml) ? juce::Result::ok()
                                                        : juce::Result::fail (TRANS ("Error saving file to disk"));
    }

    /** Returns the ValueTree being used. */
    juce::ValueTree getTree() const { return tree; }

    /** Returns the File being used. */
    const juce::File& getFile() const { return file; }

    /** Sets the tree to save to the file as XML or binary data. */
    void setSaveAsXml (bool saveAsXml) { asXml = saveAsXml; }

    /** Returns true if the file will be saved as XML. */
    bool getSaveAsXml() const { return asXml; }

private:
    //==============================================================================
    bool asXml;
    juce::File file;
    juce::ValueTree tree;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScopedValueTreeFile)
};

//==============================================================================
/** Simple utility class to send a change message when it goes out of scope. */
struct ScopedChangeSender
{
    ScopedChangeSender (juce::ChangeBroadcaster& owner) : broadcaster (owner) {}
    ~ScopedChangeSender() { broadcaster.sendChangeMessage(); }

private:
    juce::ChangeBroadcaster& broadcaster;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScopedChangeSender)
};

//==============================================================================
/** Useful macro to print a variable name and value to the console. */
#define DBG_VAR(dbgvar)     { DBG (JUCE_STRINGIFY(dbgvar) << ": " << dbgvar) }

/** Useful macro to print a Point to the console. */
#define DBG_POINT(dbgpoint) { DBG (JUCE_STRINGIFY(dbgpoint) << ": " << DebugObject::convertToString (dbgpoint)) }

/** Useful macro to print a Range to the console. */
#define DBG_RANGE(dbgrange) { DBG (JUCE_STRINGIFY(dbgrange) << ": " << DebugObject::convertToString (dbgrange)) }

/** Useful macro to print a Line to the console. */
#define DBG_LINE(dbgline)   { DBG (JUCE_STRINGIFY(dbgline) << ": " << DebugObject::convertToString (dbgline)) }

/** Useful macro to print a Rectangle to the console. */
#define DBG_RECT(dbgrect)   { DBG (JUCE_STRINGIFY(dbgrect) << ": " << DebugObject::convertToString (dbgrect)) }

/** Prints a string representation of a lot of common objects to the console for
    debugging purposes.
 */
#define DBG_OBJ(dbgobj)     { DBG (JUCE_STRINGIFY(dbgobj) << ": " << DebugObject::convertToString (dbgobj)) }

#endif //DROWAUDIO_UTILITY_H
