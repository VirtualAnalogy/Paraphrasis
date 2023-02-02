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

//==================================================================================
class BrowserColumn : public BasicFileBrowser,
                      public DragAndDropContainer,
                      public ChangeBroadcaster
{
public:
    BrowserColumn (WildcardFileFilter* filesToDisplay_)
        : BasicFileBrowser (BasicFileBrowser::openMode
                            + BasicFileBrowser::canSelectFiles
                            + BasicFileBrowser::canSelectDirectories
                            + BasicFileBrowser::canSelectMultipleItems,
                            juce::File::getSpecialLocation (File::userMusicDirectory),
                            filesToDisplay_),
          fileDragEnabled (false)
    {
        addMouseListener (this, true);
    }
    
    ~BrowserColumn()
    {
        setLookAndFeel (nullptr);
    }

    void mouseDrag (const MouseEvent&) override
    {
        if (fileDragEnabled)
        {
            juce::StringArray files;

            for (int i = 0; i < getNumSelectedFiles(); ++i)
            {
                File file (getSelectedFile (i));

                if (file.existsAsFile())
                    files.add (file.getFullPathName());
            }

            fileDragEnabled = false;
            performExternalDragDropOfFiles (files, false);
        }
    }

    void mouseUp (const MouseEvent&) override
    {
        fileDragEnabled = false;
    }

    void selectionChanged() override
    {
        BasicFileBrowser::selectionChanged();

        sendSynchronousChangeMessage();
    }

    void fileClicked (const File&, const MouseEvent&) override
    {
        fileDragEnabled = true;
    }

    void fileDoubleClicked (const File&) override {}

private:
    bool fileDragEnabled;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrowserColumn)
};

//==================================================================================
class ColumnFileBrowserContents   : public Component,
                                    public FileBrowserListener,
                                    public ChangeListener,
                                    public ComponentListener
{
public:
    ColumnFileBrowserContents (WildcardFileFilter* filesToDisplay_, Viewport* parentViewport)
        : filesToDisplay (filesToDisplay_),
          viewport (parentViewport)
    {
        activeLookAndFeel = std::make_unique<ColumnFileBrowserLookAndFeel>();
        activeLookAndFeel->setColour (DirectoryContentsDisplayComponent::highlightColourId,
                                      Colours::darkorange);
        inactiveLookAndFeel = std::make_unique<ColumnFileBrowserLookAndFeel>();
    
        auto* firstColumn = new BrowserColumn (filesToDisplay_);
        columns.add (firstColumn);
        addAndMakeVisible (firstColumn);
        firstColumn->setSize (300, 50);
        addListenersToColumn (firstColumn);
        firstColumn->setLookAndFeel (activeLookAndFeel.get());
        
        activeColumn = 0;
    }
    
    void addListenersToColumn (BrowserColumn* column)
    {
        column->addListener (this);
        column->addChangeListener (this);
        column->addComponentListener (this);
    }

    void resized() override
    {
        int width = 0;
        const int height = getHeight();

        for (int i = 0; i < columns.size(); ++i)
        {
            columns[i]->setBounds (width, 0, columns[i]->getWidth(), height);
            width += columns[i]->getWidth();
        }

        setSize (width, height);
    }

    void selectedFileChanged (const File& file)
    {
        // if last column clicked add new column
        if (columns[activeColumn] == columns.getLast())
        {
            addColumn (file);
        }
        else // otherwise remove uneeded columns and change last
        {
            for (int i = 0; i < columns.size(); ++i)
            {
                if (columns[activeColumn] == columns[i])
                {
                    columns.removeLast (columns.size() - 1 - i - (file.isDirectory() ? 1 : 0));

                    if (file.isDirectory())
                        columns.getLast()->setRoot (file);

                    break;
                }
            }

            resized();
        }

        // stick to edges of viewport
        if (getWidth() < viewport->getWidth())
        {
            viewport->setViewPosition (0, 0);
        }
        else if (file.exists() || (getRight() < viewport->getRight()))
        {
            const int ammountToSubtract = viewport->getRight() - getRight();
            viewport->setViewPosition (viewport->getViewPositionX() - ammountToSubtract, 0);
        }
    }

    bool addColumn (const File& rootDirectory)
    {
        if (rootDirectory.isDirectory() && rootDirectory.exists())
        {
            const int startingWidth = columns.getLast()->getWidth();

            auto* newColumn = new BrowserColumn (filesToDisplay);
            columns.add (newColumn);
            addAndMakeVisible (newColumn);
            newColumn->setSize (startingWidth, 50);
            newColumn->setLookAndFeel (inactiveLookAndFeel.get());
            newColumn->setRoot (rootDirectory);
            addListenersToColumn (newColumn);

            resized();

            return true;
        }

        return false;
    }

    void changeListenerCallback (ChangeBroadcaster* changedComponent) override
    {
        auto changedColumn = static_cast<BrowserColumn*> (changedComponent);

        if (changedColumn->getHighlightedFile().getFileName().isNotEmpty())
        {
            columns[activeColumn]->setLookAndFeel (inactiveLookAndFeel.get());
            activeColumn = columns.indexOf (changedColumn);
            columns[activeColumn]->setLookAndFeel (activeLookAndFeel.get());
            columns[activeColumn]->repaint();

            selectedFileChanged (changedColumn->getHighlightedFile());
        }
    }

    void componentMovedOrResized (Component&, bool, bool wasResized) override
    {
        if (wasResized)
            resized();
    }

    bool keyPressed (const KeyPress& key) override
    {
        if (key.isKeyCode (KeyPress::leftKey))
        {
            if (activeColumn != 0)
            {
                FileListComponent* list = dynamic_cast<FileListComponent*> (columns[activeColumn]->getDisplayComponent());
                list->deselectAllRows();

                int newActiveColumn = jmax (0, activeColumn - 1);
                columns[newActiveColumn]->selectionChanged();
                columns[newActiveColumn]->grabKeyboardFocus();
            }

            return true;
        }

        if (key.isKeyCode (KeyPress::rightKey))
        {
            if (columns[activeColumn]->getNumSelectedFiles() == 1
                && columns[activeColumn]->getSelectedFile (0).isDirectory()
                && getNumValidChildFiles (columns[activeColumn]->getSelectedFile (0)) > 0)
            {
                int newActiveColumn = activeColumn + 1;
                addColumn (columns[activeColumn]->getSelectedFile (0));

                FileListComponent* list = dynamic_cast<FileListComponent*> (columns[newActiveColumn]->getDisplayComponent());

                if (list != nullptr)
                {
                    ListBoxModel* model = list->getModel();

                    if (model != nullptr)
                    {
                        if (model->getNumRows() > 0)
                        {
                            columns[newActiveColumn]->grabKeyboardFocus();
                            list->selectRow (0);
                        }
                    }
                }
            }

            return true;
        }

        return false;
    }

    void selectionChanged() override {}
    void fileClicked (const File&, const MouseEvent&) override {}
    void fileDoubleClicked (const File&) override {}
    void browserRootChanged (const File&) override {}

private:
    //==================================================================================
    std::unique_ptr<LookAndFeel> activeLookAndFeel;
    std::unique_ptr<LookAndFeel> inactiveLookAndFeel;
    
    WildcardFileFilter* filesToDisplay;
    Viewport* viewport;
    OwnedArray <BrowserColumn> columns;

    int activeColumn;

    friend class ColumnFileBrowser;

    //==================================================================================
    int getNumValidChildFiles (const File& sourceFile) const
    {
        return sourceFile.getNumberOfChildFiles (File::findFilesAndDirectories + juce::File::ignoreHiddenFiles,
                                                 filesToDisplay == nullptr
                                                    ? "*"
                                                    : filesToDisplay->getDescription().fromFirstOccurrenceOf ("(", false, false).upToFirstOccurrenceOf (")", false, false));
    }

    //==================================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ColumnFileBrowserContents)
};

//==================================================================================
ColumnFileBrowser::ColumnFileBrowser (WildcardFileFilter* filesToDisplay_)
    : Viewport ("ColumnFileBrowser"),
      wildcard (filesToDisplay_)
{
    addMouseListener (this, true);
    setWantsKeyboardFocus (false);

    setScrollBarsShown (false, true);
    setScrollBarThickness (10);

    fileBrowser = std::make_unique<ColumnFileBrowserContents> (filesToDisplay_, this);
    setViewedComponent (fileBrowser.get());
}

void ColumnFileBrowser::setActiveColumHighlightColour (Colour colour)
{
    fileBrowser->activeLookAndFeel->setColour (DirectoryContentsDisplayComponent::highlightColourId, colour);
}

void ColumnFileBrowser::resized()
{
    Viewport::resized();
    fileBrowser->setSize (fileBrowser->getWidth(), getMaximumVisibleHeight());
}

void ColumnFileBrowser::visibleAreaChanged (const Rectangle<int>& /*newVisibleArea*/)
{
    resized();
}

void ColumnFileBrowser::mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel)
{
    if (! (e.mods.isAltDown() || e.mods.isCtrlDown()))
    {
        if (e.eventComponent != this && e.eventComponent != &getHorizontalScrollBar())
            if (wheel.deltaX != 0.0f)
                Viewport::useMouseWheelMoveIfNeeded (e, wheel);
    }
}
