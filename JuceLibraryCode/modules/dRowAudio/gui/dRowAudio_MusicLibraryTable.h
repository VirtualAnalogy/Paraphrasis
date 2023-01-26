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

#ifndef DROWAUDIO_MUSICLIBRARYTABLE_H
#define DROWAUDIO_MUSICLIBRARYTABLE_H

#include "../audio/dRowAudio_AudioUtility.h"
#include "../utility/dRowAudio_ITunesLibrary.h"
#include "../utility/dRowAudio_Comparators.h"

/** Table to display and interact with a music library.
    The easiest way to use this is to load a default or saved iTunes library like so:

    @code
        MusicLibraryTable table;
        table.setLibraryToUse (ITunesLibrary::getInstance());

        File parsedLibraryFile (File::getSpecialLocation (File::userDesktopDirectory).getChildFile ("saved_library_file.xml"));
        ValueTree libraryTree (readValueTreeFromFile (parsedLibraryFile));

        ITunesLibrary::getInstance()->setLibraryTree (libraryTree);
        ITunesLibrary::getInstance()->setLibraryFile (ITunesLibrary::getDefaultITunesLibraryFile());
    @endcode
*/
class MusicLibraryTable : public juce::Component,
                          public juce::TableListBoxModel,
                          public ITunesLibrary::Listener
{
public:
    /** Create the MusicLibraryTable.

        This will initially be blank, set an ITunesLibrary to use first with
        setLibraryToUse(). The table will then be continually updated as the library
        is parsed.
    */
    MusicLibraryTable();

    /** Destructor. */
    ~MusicLibraryTable() override;

    //==============================================================================
    /** Sets the ITunesLibrary to use. */
    void setLibraryToUse (ITunesLibrary* library);

    /** Filters the table to only rows containing the given text. */
    void setFilterText (const juce::String& filterText);

    /** Returns the table list box component. */
    juce::TableListBox& getTableListBox() { return table; }

    //==============================================================================
    /** A set of colour IDs to use to change the colour of various aspects of the main table.

        These constants can be used either via the Component::setColour(), or LookAndFeel::setColour()
        methods. TextEditor

        @see Component::setColour, Component::findColour, LookAndFeel::setColour, LookAndFeel::findColour
     */
    enum ColourIds
    {
        backgroundColourId                  = 0x2000000, /**< The colour to use for the cell's background - this can be
                                                              transparent if necessary. */

        unfocusedBackgroundColourId         = 0x2000001, /**< The colour to use for the cell's background
                                                              when the table is unfocused. */

        selectedBackgroundColourId          = 0x2000002, /**< The colour to use for the cell's background if the
                                                              row is selected. */

        selectedUnfocusedBackgroundColourId = 0x2000003, /**< The colour to use for the cell's background if the
                                                              row is selected and the table is unfocused. */

        textColourId                        = 0x2000004, /**< The colour that will be used for the cell's text. */

        selectedTextColourId                = 0x2000005, /**< The colour with which to draw the text in selected
                                                              cells. */

        unfocusedTextColourId               = 0x2000006, /**< The colour with which to draw the text in cells when
                                                              the table is unfocused. */

        selectedUnfocusedTextColourId       = 0x2000007, /**< The colour with which to draw the text in selected
                                                              cells when the table is unfocused. */

        outlineColourId                     = 0x2000008, /**< The colour used to draw an outline around the cells. */

        selectedOutlineColourId             = 0x2000009, /**< The colour used to draw an outline around selected cells. */

        unfocusedOutlineColourId            = 0x2000010, /**< The colour used to draw an outline around the cells when
                                                              the table is unfocused. */

        selectedUnfocusedOutlineColourId    = 0x2000011, /**< The colour used to draw an outline around selected cells
                                                              when the table is unfocused. */
    };

    //==============================================================================
    /** @internal */
    void libraryChanged (ITunesLibrary* library) override;
    /** @internal */
    void libraryUpdated (ITunesLibrary* library) override;
    /** @internal */
    void libraryFinished (ITunesLibrary* library) override;
    /** @internal */
    int getNumRows() override;
    /** @internal */
    void paintRowBackground (juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    /** @internal */
    void paintCell (juce::Graphics& g,
                    int rowNumber,
                    int columnId,
                    int width, int height,
                    bool rowIsSelected) override;
    /** @internal */
    void sortOrderChanged (int newSortColumnId, bool isForwards) override;
    /** @internal */
    int getColumnAutoSizeWidth (int columnId) override;
    /** @internal */
    void resized() override;
    /** @internal */
    void focusOfChildComponentChanged (FocusChangeType cause) override;
    /** @internal */
    juce::var getDragSourceDescription (const juce::SparseSet<int>& currentlySelectedRows) override;

private:
    //==============================================================================
    juce::Font font;
    ITunesLibrary* currentLibrary;
    juce::TableListBox table;
    juce::String currentFilterText;

    juce::ValueTree dataList;
    juce::ValueTree filteredDataList;
    juce::SortedSet<int> selectedRowsLibIds;

    int filteredNumRows;
    bool finishedLoading;

    //==============================================================================
    void updateTableFilteredAndSorted();
    void findSelectedRows();
    void setSelectedRows();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MusicLibraryTable)
};

#endif // DROWAUDIO_MUSICLIBRARYTABLE_H
