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

#ifndef DROWAUDIO_DEBUGOBJECT_H
#define DROWAUDIO_DEBUGOBJECT_H

/** Useful class to convert some objects to a String representation.

    You shouldn't use one of these directly, instead use the DBG_OBJ macro to
    ensure you don't hang on for one longer than you should do.
    If you do want to e.g. for saving to a file etc. never hang on for long to
    avoid deleting any variables it may be referencing. Simply create one on the
    stack and immidiately use its toString() method.

    Alternatively just use one of the statis convertToString methods to convert
    almost any common JUCE object to a string.

    @example
    @code
        ValueTree myValueTree ("my_tree_type");
        String output (DebugObject (myValueTree).toString());
    @endcode
 */
class DebugObject
{
public:
    //==============================================================================
    enum ObjectType
    {
        xmlType,
        valueTreeType
    };

    //==============================================================================
    explicit DebugObject (const juce::XmlElement* arg)
        : type (xmlType), objectXml (arg) {}

    explicit DebugObject (const juce::XmlElement& arg)
        : type (xmlType), objectXml (&arg) {}

    explicit DebugObject (const juce::ValueTree& arg)
        : type (valueTreeType), objectValueTree (arg) {}

    juce::String toString() const
    {
        switch (type)
        {
            case xmlType:       return getStringFromXml (objectXml, true);
            case valueTreeType: return getStringFromValueTree();
            default:            break;
        }

        return {};
    }

    //==============================================================================
    static juce::String convertToString (const juce::var& arg)
    {
        return arg.toString();
    }

    template<typename ValueType>
    static juce::String convertToString (const juce::Range<ValueType>& arg)
    {
        juce::String os;
        return os << arg.getStart() << " - " << arg.getEnd() << " (" << arg.getLength() << ")";
    }

    template<typename ValueType>
    static juce::String convertToString (const juce::Point<ValueType>& arg)
    {
        return arg.toString();
    }

    template<typename ValueType>
    static juce::String convertToString (const juce::Line<ValueType>& arg)
    {
        juce::String os;
        return os << "(" << arg.getStart().toString()
                << ") - (" << arg.getEnd().toString() << ")";
    }

    template<typename ValueType>
    static juce::String convertToString (const juce::Rectangle<ValueType>& arg)
    {
        return arg.toString();
    }

    static juce::String convertToString (const juce::XmlElement* arg)
    {
        return DebugObject (arg).toString();
    }

    static juce::String convertToString (const juce::XmlElement& arg)
    {
        return DebugObject (arg).toString();
    }

    static juce::String convertToString (const juce::ValueTree& arg)
    {
        return DebugObject (arg).toString();
    }

    static juce::String convertToString (const juce::StringArray& arg)
    {
        return arg.joinIntoString (",");
    }

    static juce::String convertToString (const juce::StringPairArray& arg)
    {
        return arg.getDescription();
    }

private:
    //==============================================================================
    ObjectType type;

    const juce::XmlElement* objectXml;
    juce::ValueTree objectValueTree;

    //==============================================================================
    static juce::String getStringFromXml (const juce::XmlElement* xml, bool includeXmlHeader)
    {
        if (xml == nullptr)
            return "invalid XmlElement";

        juce::XmlElement::TextFormat fmt;
        fmt.addDefaultHeader = includeXmlHeader;
        fmt.newLineChars = nullptr;
        
        return juce::String (juce::NewLine::getDefault()) + xml->toString (fmt);
    }

    juce::String getStringFromValueTree() const
    {
        std::unique_ptr<juce::XmlElement> treeAsXml (objectValueTree.createXml());
        return treeAsXml == nullptr ? "invalid ValueTree" : getStringFromXml (treeAsXml.get(), false);
    }

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DebugObject)
};

#endif //DROWAUDIO_DEBUGOBJECT_H
