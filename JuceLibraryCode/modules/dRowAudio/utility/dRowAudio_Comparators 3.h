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

#ifndef DROWAUDIO_COMPARATORS_H
#define DROWAUDIO_COMPARATORS_H

namespace ValueTreeComparators
{
    /** A standard Lexiographc ValueTreeComparator. */
    class Lexicographic
    {
    public:
        Lexicographic (const juce::Identifier attributeToSort_, bool forwards)
            : attributeToSort (attributeToSort_),
              direction (forwards ? 1 : -1)
        {
        }

        int compareElements (const juce::ValueTree& first, const juce::ValueTree& second) const
        {
            const int result = first[attributeToSort].toString().compareNatural (second[attributeToSort].toString());

            return direction * result;
        }

    private:
        const juce::Identifier attributeToSort;
        const int direction;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Lexicographic)
    };

    //==============================================================================
    /** A standard Numberical ValueTreeComparator. */
    template<typename NumericalType>
    class Numerical
    {
    public:
        Numerical (const juce::Identifier attributeToSort_, bool forwards)
            : attributeToSort (attributeToSort_),
              direction (forwards ? 1 : -1)
        {
        }

        int compareElements (const juce::ValueTree& first, const juce::ValueTree& second) const
        {
            const int result = (NumericalType (first[attributeToSort]) > NumericalType (second[attributeToSort])) ? 1 : -1;

            return direction * result;
        }

    private:
        const juce::Identifier attributeToSort;
        const int direction;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Numerical)
    };

    //==============================================================================
    /** A Lexiographc ValueTreeComparator which will use a second comparitor if the
        result is the same, useful when sorting tables without using the much
        slower maintainSortOrder method.
    */
    class LexicographicWithBackup
    {
    public:
        LexicographicWithBackup (const juce::Identifier attributeToSort_, const juce::Identifier backupAttribute_, bool forwards)
            : attributeToSort (attributeToSort_),
              backupAttribute (backupAttribute_),
              direction (forwards ? 1 : -1)
        {
        }

        int compareElements (const juce::ValueTree& first, const juce::ValueTree& second) const
        {
            int result = first[attributeToSort].toString().compareNatural (second[attributeToSort].toString());

            if (result == 0)
                result = first[backupAttribute].toString().compareNatural (second[backupAttribute].toString());

            return direction * result;
        }

    private:
        const juce::Identifier attributeToSort;
        const juce::Identifier backupAttribute;
        const int direction;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LexicographicWithBackup)
    };

}

//==============================================================================
namespace XmlComparators
{
    /** An Xml comparator used to sort Lexicographical data. */
    class LexicographicSorter
    {
    public:
        LexicographicSorter (const juce::String attributeToSort_, bool forwards)
            : attributeToSort (attributeToSort_),
              direction (forwards ? 1 : -1)
        {
        }

        int compareElements (juce::XmlElement* first, juce::XmlElement* second) const
        {
            int result = first->getStringAttribute (attributeToSort)
                         .compareNatural (second->getStringAttribute (attributeToSort));

            if (result == 0)
                result = first->getStringAttribute ("ID")
                         .compareNatural (second->getStringAttribute ("ID"));

            return direction * result;
        }

    private:
        const juce::String attributeToSort;
        const int direction;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LexicographicSorter)
    };

    //==============================================================================
    /** An Xml comparator used to sort number data. */
    class NumberDataSorter
    {
    public:
        NumberDataSorter (const juce::String attributeToSort_, bool forwards)
            : attributeToSort (attributeToSort_),
              direction (forwards ? 1 : -1)
        {
        }

        int compareElements (juce::XmlElement* first, juce::XmlElement* second) const
        {
            if (first->getStringAttribute (attributeToSort).isEmpty()
                    || second->getStringAttribute (attributeToSort).isEmpty())
                return direction * -1;

            int result = ((first->getStringAttribute (attributeToSort).getDoubleValue()
                           <= (second->getStringAttribute (attributeToSort).getDoubleValue()))
                          ? -1 : 1);

            return direction * result;
        }

    private:
        const juce::String attributeToSort;
        const int direction;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NumberDataSorter)
    };
}

#endif  // DROWAUDIO_COMPARATORS_H
