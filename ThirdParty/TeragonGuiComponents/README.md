TeragonGuiComponents
====================

TeragonGuiComponents is a set of widgets designed for use in audio software.
The graphics were done by [Max Rudberg][5] and are licensed under the Creative
Commons License (see the LICENSE-GRAPHICS.txt file for more details). This
project also includes a few classes for use in VST plugins with Juce.

Should you wish to reuse the graphics, please give proper attribution to both
[Max Rudberg][5] and [Teragon Audio][6].


Setting up TeragonGuiComponents in a Project
--------------------------------------------

To use TeragonGuiComponents, the plugin needs to store parameter data in a
[PluginParameters][1] set. These parameters are linked directly to the GUI
components and will be notified when the component is changed. If you are
storing parameter data in some other format and don't feel comfortable
migrating to PluginParameters, then you can at least mirror the data in a
PluginParameters set and observe parameter changes to synchronize the set with
your preferred data storage container.

Please note that PluginParameters must be built in multithreaded mode,
otherwise parameter updates will be delivered from the audio thread. See the
README of the PluginParameters project for more details. Also be sure to look
at the source code of the demo project which demonstrates usage of
PluginParameters with the GUI components.

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
* `teragon::ThreadsafePluginParameterSet&`
* `teragon::ResourceCache*`

The `TeragonGuiComponents.h` header file must therefore be included in the
editor's header.

Correspondingly, the plugin processor should pass up a reference to its
parameter set and a new resource cache made with `Resources::getCache()` (this
will require including `Resources.h` from the file where `getCache()` is
called since this rather long header is not part of `TeragonGuiComponents.h`).

**NOTE**: The reason that the ResourceCache is passed as a raw pointer instead
of a reference is that the editor should take ownership of the cache upon
construction. This way, you can delete the cache in the editor's destructor
and spare a bit of memory to the system when the editor is closed. You could
also choose to keep a ResourceCache in the processor and pass its address up
to the editor, but this is not recommended. In either case, you must make sure
that the cache is deleted at some point or else memory will be leaked.


Adding Components
-----------------

Within the Juce GUI editor, you'll be adding a bunch of Generic Components
rather than Juce's own knobs, sliders and buttons. The classes for the
components must be given in the virtual class section (you can leave the class
as `Component`) of the editor's right-hand panel. Each component takes the
following arguments:

* A reference to the parameter set (`teragon::ThreadsafePluginParameterSet&`)
* The parameter name (`const ParameterString&`)
* A pointer to the resource cache (`const teragon::ResourceCache*`)

Where the size of each component is as follows:

* `teragon::ImageKnobLarge`: 113x113
* `teragon::ImageKnobSmall`: 66x66
* `teragon::ImageSlider`: 62x134
* `teragon::IndicatorLight`: 24x24
* `teragon::PushButton`: 72x(Variable)
* `teragon::ToggleButton`: 72x(Variable)
* `teragon::StatusBar`: (Variable)x70

Both of the buttons are drawn at the top of their 70x40 frame, but only take
up 24px of height. Labels should be placed *below* the buttons, and this area
is also clickable, since otherwise the buttons could be hard to hit with the
mouse.

An example application with all components can be found in the `Demo` folder,
this is a good reference for how to use the classes. Also each class has some
usage documentation in the header file.


Background Images
-----------------

Backgrounds for plugins are created in an image editor, such as Photoshop or
Pixelmator. I prefer using [Pixelmator][7] since it is reasonably priced
(compared to Photoshop) and very powerful while easy to use (compared to
GIMP). It also has nice snapping gridlines for doing accurate layout. In the
top-level folder of the project, there is a Pixelmator template for creating
the backgrounds. It has each component in a separate layer, making it easy to
create GUI mockups. Each component also has a semi-transparent alignment
helper layer for use in making pixel-perfect layouts within Introjucer.

If you choose not to use the Pixelmator template, please be aware of the
following style guidelines:

* Use "Title Case" (not "Sentence case") for component labels.
* Text for large knob labels is Open Sans Semi-Bold, 15pt, 100% white.
* Text for all other labels is Open Sans Semi-Bold, 12pt, 100% white.
* Text for all knob unit labels is Open Sans Semi-Bold, 9pt, 50% white.
* Tile the texture image for the background.
* Tile the contrast texture to separate groups of related components. Box
  them in using a rounded rectangle with 3px corner radius.

When the background is finished, it can be imported into the Introjucer for
the main window's background. My layout workflow looks something like this:

1. Make copy of Template.pxm document in project.
2. Drag around components in Pixelmator until layout looks nice.
3. Set labels, component names, etc.
4. Export PNG from Pixelmator with all layers visible.
5. Import PNG into Introjucer.
6. Make Components in Introjucer, align to blue boundary shapes.
7. Re-export PNG from Pixelmator with all layers disabled except the
   background and label names. Object such as slider wells and disabled states
   (for indicator lights and buttons) are not necessary to export, these are
   done in the Component classes.
8. Go back to Introjucer, reload background image.
9. Fill in Component parameters in Introjucer.

That's it! Now you have a fully-functional GUI for your plugin.


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
[5]: http://www.maxrudberg.com
[6]: http://www.teragonaudio.com
[7]: http://www.pixelmator.com
