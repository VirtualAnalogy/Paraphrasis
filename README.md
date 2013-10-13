TeragonGuiComponents
====================


Setting up TeragonGuiComponents in a Project
--------------------------------------------

To use TeragonGuiComponents, the plugin needs to store parameter data in a
[PluginParameters][1] set. These parameters are linked directly to the GUI
components and will be notified when the component is changed. If you are
storing parameter data in some other format and don't feel comfortable
migrating to PluginParameters, then you can at least mirror the data in a
PluginParameters set and observe parameter changes to synchronize the set with
your preferred data storage container.

TeragonGuiComponents also is built on [Juce][2], though it is certainly
possible to use the graphics with VSTGUI (or other GUI toolkits). While use of
the actual code powering the TeragonGuiComponents is covered under the [BSD
license][3], the graphics are under a [separate Creative Common license][4],
which requires attribution to be given. See the "Licensing" section for more
details.

The plugin also needs to have an editor component in Juce, which is typically
generated in the Introjucer. I've experienced times when the auto-generated
editor produced by the Introjucer new project wizard does not yield a
functional editor (ie, the GUI editor tabs are not shown). In such cases, just
delete the default editor and make a new GUI Component to your project.

Also all files under TeragonGuiComponents/Components/Source must be added to
your project. You may need to also add this directory to the list of header
search paths in your project.

The editor class will need to take a few additional constructor parameters:

* `AudioProcessor*` (which is actually needed in all Juce plugin GUIs)
* `teragon::PluginParameterSet`
* `teragon::ResourceCache*`

The `TeragonGuiComponents.h` header file must therefore be included in the
editor's header.

And correspondingly, the plugin processor should pass up a reference to its
parameter set and a new resource cache made with `Resources::getCache()` (this
will require including `Resources.h` from the file where `getCache()` is
called since this rather long header is not part of `TeragonGuiComponents.h`).

The reason that the ResourceCache is passed as a raw pointer instead of a
reference is that the editor should take ownership of the cache upon
construction. This way, you can delete the cache in the editor's destructor
and spare a bit of memory to the system when the editor is closed.  You could
also choose to keep a ResourceCache in the processor and pass its address up
to the editor, but this is not recommended.


Adding Components
-----------------

Within the Juce GUI editor, you'll be adding a bunch of Generic Components
rather than Juce's own knobs, sliders and buttons. The classes for the
components must be given in the virtual class section (you can leave the class
as `Component`) of the editor's right-hand panel. Each component takes two
arguments: a `PluginParameter*` and a `ResourceCache::ImageStates*`. The
`ImageState` for a given component can be acquired with a call to 
`resources->get("image_name")`, where each component has the respective name:

* `teragon::ImageKnob` -- `large_knob` or `small_knob`
* `teragon::ImageSlider` -- `slider`
* `teragon::IndicatorLight` -- `indicator_light`
* `teragon::PushButton` -- `push_button`
* `teragon::ToggleButton` -- `toggle_button`

Where the size of each graphic is as follows:

* `large_knob`: 113x113
* `small_knob`: 66x66
* `slider`: 62x134
* `indicator_light`: 24x24
* `push_button`: 70x40
* `toggle_button`: 70x40

Both of the buttons are drawn at the top of their 70x40 frame, but only take
up 24px of height. Labels should be placed *below* the buttons, and this area
is also clickable, since otherwise the buttons could be hard to hit with the
mouse.

An example application with all components can be found in the `Demo` folder,
this is a good reference for how to use the classes.


Background Images
-----------------

Backgrounds for plugins are created in an image editor, such as Photoshop or
Gimp. Tile the primary texture for the background and the secondary texture
for groups of controls. When making control groups, the secondary texture
should have rounded corners of 3px.

Once the controls have been placed in Introjucer, I usually set the background
color to bright red `#FFFF0000` and then take a screenshot.  Importing this
into Photoshop, and then open up some of the control PNGs, placing them over
the Juce layout boxes. Now control labels can be placed, use Open Sans
Semi-Bold for all labels, pure white. For control names, use 15pt font at 100%
opacity (except for small knobs, which should have 11pt), and for label units
use 9pt at 50% opacity. Use "Sentence Case" for labels.

When the background is finished, it can be imported into the Introjucer for
the main window's background.


LCD Screens
-----------

LCD screens are a bit special because different plugins require different
sizes. The screen is meant to be part of the background image, but making it
is done with an Android application, since Android's internal 9-slicing
abilities make generating such images much more quickly than in Photoshop (at
least for me and my limited Photoshop abilities).

There are two screens, one is intended for single-line displays and the other
for multi-line displays. Both are included in the app's main layout XML.
Simply edit the main.xml file to make the LCD the desired height, then take a
screenshot and crop it in an image editor. If you don't have an Android
device, the emulator will work just fine for this, however make sure that an
MDPI image is used so that the screenshot aligns to be the same pixel
dimensions as the desktop.


[1]: https://github.com/teragonaudio/PluginParameters
[2]: http://www.juce.com
[3]: https://github.com/teragonaudio/TeragonGuiComponents/blob/master/LICENSE-GRAPHICS.txt
[4]: https://github.com/teragonaudio/TeragonGuiComponents/blob/master/LICENSE-CODE.txt
