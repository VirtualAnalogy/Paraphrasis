PluginParameters
================

PluginParameters is a simple library used to keep parameter information for an
audio plugin, such as a VST or AudioUnit. The need for this arises from the
fact that most plugins have a number of parameters they need to maintain, and
this information needs to be sent to various parts of the plugin's processing
code. The VST or AudioUnit side of things also needs to query this information
in a more structured manner, and this can lead to plugin code getting very
messy with huge `switch` blocks to get/set the correct value.


Features
--------

* Small! Less than 200 lines of code, all implementation in header files, so
  dynamic libraries or adding files to your project. Simply include
  `PluginParameters.h` and you've got the whole library at your fingertips.
* Provides a plugin parameter interface with the following implementations:
  - BooleanParameter
  - DecibelParameter
  - FloatParameter
  - FrequencyParameter
  - IntegerParameter
* For all parameter types, you can get the raw value (ie, the thing you
  probably need in your code to do useful stuff), or a scaled value between
  0.0 - 1.0 for use in plugin wrappers.
* The decibel parameter is represented internally as a linear value, which is
  more convenient for most algorithms.
* The frequency parameter uses logarithmic scaling for its value, so it is
  easier to select higher frequencies. This is particularly convenient for
  filters where one MIDI step would otherwise mean a difference of several
  hundred hertz.
* The integer parameters provide a minimum, maximum, and default value.
* All parameter types also have a function to get the displayable value.
* Lookup of parameters can be done either by index or by name, with either the
  `get()` method or the square brackets.
* Threadsafe! PluginParameters can be built to run in a multi-threaded
  environment ideal for audio plugins, with one high-priority audio thread and
  multiple low-priority threads for background tasks or GUI.
* The multithreaded implementation is based on lock-free queues. Although
  condition variables are used to communicate between the asynchronous and
  realtime threads, no mutex locks are made inside the audio thread.


Usage (Single-Threaded)
-----------------------

*Note*: For using PluginParameters in a multithreaded environment, see the below
section for usage and examples.

Assuming that you've pointed your source to include `PluginParameters.h` and
everything compiles fine, your next step is to make a `PluginParameterSet` and
add some parameters to it. This should probably be done in your plugin's
constructor:

```c++
MyPlugin::MyPlugin() {
  // Assumes that there is a PluginParameterSet member named "parameters" in
  // the header file.
  this->parameters.add(new BooleanParameter("Awesomeness", true));
  this->parameters.add(new FrequencyParameter("Frequency", 20.0, 20000.0, 10000.0);
  this->parameters.add(new DecibelParameter("Gain", -60.0, 3.0, 0.0));
}
```

For a VST plugin, a ton of boilerplate code can thus be eliminated:

```c++
float MyPlugin::getParameter(VstInt32 index) {
  return this->parameters[index]->getScaledValue();
}

void MyPlugin::setParameter(VstInt32 index, float value) {
  this->parameters[index]->setScaledValue(value);
}

void MyPlugin::getParameterName (VstInt32 index, char* label) {
  vst_strncpy(label, this->parameters[index]->getName().c_str(), kVstMaxParamStrLen);
}

void MyPlugin::getParameterDisplay(VstInt32 index, char* text) {
  vst_strncpy(text, this->parameters[index]->getDisplayText().c_str(), kVstMaxParamStrLen);
}
```

When you actually want to use the parameter data in your code, it might look
something like this:

```c++
void MyPlugin::processReplacing (float** inputs, float** outputs, VstInt32 sampleFrames) {
  if(this->parameters["Awesomeness"]->getValue()) {
    for(int i = 0; i < sampleFrames; i++) {
      *outputs[0][i] = *inputs[0][i] * this->parameters["Gain"]->getValue();
      *outputs[1][i] = *inputs[1][i] * this->parameters["Gain"]->getValue();
    }
  }
}
```

Note: The above example code may look a bit different than your actual
implementation. It's just to give you a general idea as to how the library
should be used.


Usage (Multithreaded)
---------------------

If you intend on using a `PluginParameterSet` with a GUI (particularly with
GUI components that implement the `PluginParameterObserver` interface), then
you will need to use the multithreaded features of PluginParameters.
Attempting to use the single-threaded version in a multithreaded environment
may result in priority inversion (and thus, occaisional stuttering on the
audio thread), or race conditions caused by multiple objects attempting to
get/set parameter values.

The multithreaded mode must be enabled at compile-time like so:

```c++
#define ENABLE_MULTITHREADED 1
#include "PluginParameters.h"
```

Some dependencies of the multithreaded implementation require C++11 support,
so you may need to enable this for your compiler as necessary. Likewise, you
will need to add `tinythread.cpp` to the list of files compiled by your
project.

When a `ThreadsafePluginParameterSet` (which should be used instead of the
regular `PluginParameterSet`) is created by your plugin, it will create a new
low-priority background thread for asynchronous parameter events.  This thread
will be automatically shut down and destroyed with the parameter set.
Furthermore, the high-priority audio thread must execute the parameter set's
event loop.

In multithreaded mode, you should directly modify parameter values. Instead,
you must schedule changes via an event dispatcher. Therefore a full
implementation would look something like this:

In plugin's audio processing code:

```c++
MyPlugin::MyPlugin() {
  // Assumes that there is a ThreadsafePluginParameterSet  member named
  // "parameters" in the header file.
  this->parameters.add(new BooleanParameter("Awesomeness", true));
  this->parameters.add(new FrequencyParameter("Frequency", 20.0, 20000.0, 10000.0);
  this->parameters.add(new DecibelParameter("Gain", -60.0, 3.0, 0.0));
}

void MyPlugin::process(float** inputs, float** outputs, long blocksize) {
  this->parameters.processRealtimeEvents();
  // Other processing code follows...
}

float MyPlugin::getParameter(VstInt32 index) {
  return this->parameters[index]->getScaledValue();
}

void MyPlugin::setParameter(VstInt32 index, float value) {
  this->parameters.setScaled(index, value);
}

void MyPlugin::getParameterName (VstInt32 index, char* label) {
  vst_strncpy(label, this->parameters[index]->getName().c_str(), kVstMaxParamStrLen);
}

void MyPlugin::getParameterDisplay(VstInt32 index, char* text) {
  vst_strncpy(text, this->parameters[index]->getDisplayText().c_str(), kVstMaxParamStrLen);
}
```

In plugin's GUI code:

```c++
// This code will be highly implementation-specific, but basically let's
// assume that some GUI code is ready to set a parameter value after user
// interaction. However in this example we'll assume that the GUI also wants
// to be notified about updates to the parameter, so it therefore would
// implement PluginParameterObserver.
MyGui::onValueUpdated(int index, float newValue) {
  // We must pass "this" as the last argument so we don't notify ourselves
  // when sending parameter changes to the audio thread.
  this->parameters.set(index, newValue, this);
}

bool MyGui::isRealtimePriority() const {
  return false;
}

void MyGui::onParameterUpdated(const PluginParameter* parameter) {
  // Set widget to reflect parameter's new value
}
```

You can also have parameter observers on the realtime thread. This can be
useful to recalculate cached values based on parameter data (like filter
coefficients, for example).

Note that `ThreadsafePluginParameterSet` *cannot* guarantee that the async
thread will be ready to process events after the parameter set itself is
finished being constructed. In other words, never do this:

```c++
void MyPlugin::initialize() {
  // Assumes a member of type ThreadsafePluginParameterSet*
  parameters = new ThreadsafePluginParameterSet();
  parameters.add(new BooleanParameter("test"));
  parameters.set("test", true); // BAD!
}
```

The reason that this code is bad is because the async thread may not be fully
started when the call to `set()` has been made, and therefore the parameter
change would not be correctly scheduled on that thread.  The only way to
guarantee this behavior would be to have a mutex within both `set()` and
`processRealtimeEvents()`, which has performance consequences for the audio
thread.

Therefore the recommended best practice is *don't call set() during
initialization*, or unexpected behavior may occur. If you absolutely must
schedule parameter changes during instantiation, you may define
`SLEEP_AFTER_CREATION_MS` to some value in your prefix header, however this is
also not recommended as it will only reduce the probability of errors, not
eliminate them.


Testing
-------

PluginParameters comes with a small test suite which is used to develop the
library as well as fix bugs. If you think you've found a bug in
PluginParameters, then please build the test suite and run it before reporting
a bug for your platform.

PluginParameters is built with [CMake][1] and should compile cleanly out of
the box. Building on unix platforms (including Mac OSX) is simply a matter of
running `cmake . ; make`. On Windows, one can run `cmake.exe -G "Visual Studio
11"` to generate a Visual Studio project file which can build the project.


License
-------

PluginParameters is licensed under the BSD licnese. See the file `LICENSE.txt`
provided with the source code for more details. If built with
`ENABLE_MULTITHREADED`, then code from [TinyThread++][2] and
[readerwriterqueue][3] is used. Please see the respective license files for
each of these libraries, which can be found in the `include` directory.

Finally, a big thanks to the authors of TinyThread++ and readerwriterqueue for
making this library possible. Multithreaded code is hard!


[1]: http://www.cmake.org
[2]: http://tinythreadpp.bitsnbites.eu
[3]: https://github.com/cameron314/readerwriterqueue
