TeragonGuiComponents
====================


Usage
-----

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


[1]: https://github.com/teragonaudio/PluginParameters
[2]: http://www.juce.com
[3]: https://github.com/teragonaudio/TeragonGuiComponents/blob/master/LICENSE-GRAPHICS.txt
[4]: https://github.com/teragonaudio/TeragonGuiComponents/blob/master/LICENSE-CODE.txt
