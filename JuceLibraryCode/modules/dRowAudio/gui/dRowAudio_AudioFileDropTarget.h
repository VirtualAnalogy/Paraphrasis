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

#ifndef DROWAUDIO_AUDIOFILEDROPTARGET_H
#define DROWAUDIO_AUDIOFILEDROPTARGET_H

#if DROWAUDIO_USE_SOUNDTOUCH

//==============================================================================
/** A Component that acts as a drag and drop target for audio files and
    MusicLibraryTable drag sources. This will draw a coloured bezel if it can
    read the drag source provided.
 */
class AudioFileDropTarget : public juce::Component,
                            public juce::ComponentListener,
                            public juce::DragAndDropTarget,
                            public juce::FileDragAndDropTarget
{
public:
    //==============================================================================
    /** Creates an AudioFileDropTarget, which controls an AudioFilePlayer.

        If you supply a component to attach itself to, the AudioFileDropTarget
        will automatically position itself around that component and pass any
        mouse events which are not drags onto it.

        @see AudioFilePlayer
     */
    AudioFileDropTarget (AudioFilePlayerExt* audioFilePlayerToControl,
                         juce::Component* componentToAttachTo = nullptr);

    /** Destructor.
     */
    ~AudioFileDropTarget();

    /** Sets the colour of the bezel to be drawn.
     */
    void setBezelColour (juce::Colour newColour);

    /** Retruns the current bezel colour being used.
     */
    juce::Colour getBezelColour() const { return bezelColour; }

    //==============================================================================
    /** @internal */
    void paint (juce::Graphics& g) override;
    /** @internal */
    bool hitTest (int x, int y) override;
    /** @internal */
    void mouseEnter (const juce::MouseEvent& e) override;
    /** @internal */
    void mouseExit (const juce::MouseEvent& e) override;
    /** @internal */
    void componentMovedOrResized (juce::Component& component,
                                  bool wasMoved,
                                  bool wasResized) override;
    /** @internal */
    bool isInterestedInDragSource (const SourceDetails& dragSourceDetails) override;
    /** @internal */
    void itemDragExit (const SourceDetails& dragSourceDetails) override;
    /** @internal */
    void itemDropped (const SourceDetails& dragSourceDetails) override;
    /** @internal */
    bool isInterestedInFileDrag (const juce::StringArray& files) override;
    /** @internal */
    void fileDragExit (const juce::StringArray& files) override;
    /** @internal */
    void filesDropped (const juce::StringArray& files, int x, int y) override;

private:
    //==============================================================================
    AudioFilePlayerExt* audioFilePlayer;
    SafePointer<juce::Component> attachedComponent;
    bool dragTested, interestedInDrag;
    juce::Colour bezelColour;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioFileDropTarget)
};

#endif
#endif  // DROWAUDIO_AUDIOFILEDROPTARGET_H
