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

* Provides a parameter database which supports the following data types:
  - BlobParameter
  - BooleanParameter
  - DecibelParameter
  - FloatParameter
  - FrequencyParameter
  - IntegerParameter
  - StringParameter
* For all parameter types, you can get the raw value (ie, the thing you
  probably need in your code to do useful stuff), or a scaled value between
  0.0 - 1.0. This makes PluginParameters ideal for use in VST plugins, which
  need a 0.0 - 1.0 representation of all data.
* The decibel parameter is represented internally as a linear value, which is
  more convenient for most audio processing work. Additionally, it is
  logarithmic, which is useful when fitting it to a knob or fader control.
* The frequency parameter uses logarithmic scaling for its value, so it is
  easier to select higher frequencies. This is particularly convenient for
  filters where one MIDI step would otherwise mean a difference of several
  hundred hertz.
* All parameters provide a minimum, maximum, and default value.
* All parameter types also have a function to get the displayable value as a
  string.
* Parameters have string unit suffixes for pretty-printing the value. For
  example, DecibelParameter automatically adds "dB" to the printed value, and
  FrequencyParameter adds "Hz" or "kHz", depending on the frequency.
* Parameters can have an unlimited number of observers, which will receive a
  callback when the parameter value is changed. Observers can be added or
  removed to a parameter at any time.
* Lookup of parameters can be done either by index or by name, with either the
  `get()` method or the square brackets (ie, `parameters["frequency"]`).
* Small! Just a few hundred lines of code, and only one CPP file to add to your
  project (tinythread.cpp, which is from a third-party library). Simply include
  `PluginParameters.h` and you've got the whole library at your fingertips.
* Threadsafe! PluginParameters can be built to run in a multi-threaded
  environment ideal for audio plugins, with one high-priority audio thread and
  multiple low-priority threads for background tasks or GUI.
* The multi-threaded implementation is based on lock-free queues, and is
  completely mutex-free for high performance in realtime audio applications.


Usage (Single-Threaded)
-----------------------

*Note*: As of PluginParameters version 3.0, the multi-threaded implementation is
the default. To use the single-threaded implementation, you will need to define
the following preprocessor definition in your project:

```c++
#define PLUGINPARAMETERS_MULTITHREADED 0
#include "PluginParameters.h"
```

Assuming that you've pointed your source to include `PluginParameters.h` and
everything compiles fine, your next step is to make a `ParameterSet` and add
some parameters to it. This should probably be done in your plugin's
constructor:

```c++
MyPlugin::MyPlugin() {
  // Assumes that there is a ParameterSet member named "parameters" in
  // the header file.
  this->parameters.add(new BooleanParameter("Awesomeness", true));
  this->parameters.add(new FrequencyParameter("Frequency", 20.0, 20000.0, 10000.0);
  this->parameters.add(new DecibelParameter("Gain", -60.0, 3.0, 0.0));
}
```

For a VST plugin, a ton of boilerplate code regarding parameter values can be
eliminated and replaced with the following:

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
should be used. For real-world examples of PluginParameters, check out the
source code for any of the [Teragon Audio plugins][4].


Usage (Multi-threaded)
----------------------

If you intend on using PluginParameters in combination with a plugin GUI, then
you will need to use the multi-threaded features of PluginParameters. Attempting
to use the single-threaded version in a multi-threaded environment may result in
priority inversion (and thus, occaisional stuttering on the audio thread), or
race conditions caused by multiple objects attempting to get/set parameter
values.

The multi-threaded mode must be enabled at compile-time like so:

```c++
#define PLUGINPARAMETERS_MULTITHREADED 1
#include "PluginParameters.h"
```

*Note*: As of PluginParameters version 3.0, the multi-threaded implementation is
the default; it is not necessary to force this definition anymore. Simply
including `PluginParameters.h` is enough.

Some dependencies of the multi-threaded implementation require C++11 support,
so you may need to enable this for your compiler as necessary. Likewise, you
will need to add `tinythread.cpp` to the list of files compiled by your
project.

When a `ConcurrentParameterSet` (which should be used instead of the standard
`PluginParameterSet`) is created by your plugin, it will create a new
low-priority background thread for asynchronous parameter events. This thread
will be automatically shut down and destroyed when the `ConcurrentParameterSet`
is destroyed.

In multi-threaded mode, you may not directly modify parameter values. Instead,
you must schedule changes via an event dispatcher. Therefore a full
implementation would look something like this:

In VST plugin's audio processing code:

```c++
MyPlugin::MyPlugin() {
  // Assumes that there is a ConcurrentParameterSet member named
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

void MyPlugin::suspend() {
  this->parameters.pause();
}

void MyPlugin::resume() {
  this->parameters.resume();
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
  // Update widget to reflect parameter's new value
}
```

You can also have parameter observers on the realtime thread. This can be
useful to recalculate cached values based on parameter data (like filter
coefficients, for example).

Note that `ConcurrentParameterSet` *cannot* fully guarantee that the
asynchronous event thread will be ready to process events after the parameter
set itself is finished being constructed. In other words, never do this:

```c++
// Assumes a member of type ThreadsafePluginParameterSet*, and a
// PluginParameterObserver* named observer.
void MyPlugin::initialize() {
  parameters = new ThreadsafePluginParameterSet();
  Parameter *p = new BooleanParameter("test");
  p->addObserver(observer);
  parameters.add(p);
  parameters.set("test", true); // BAD! Here we cannot guarantee that the
  // observer will be called. The easy fix is to simply call set() elsewhere
  // after this constructor exits.

  // Also never do this:
  parameters = new ConcurrentParameterSet();
  delete parameters;
}
```

The reason that this code is bad is because the low-priority event thread may
not be fully started when the call to `set()` has been made, and therefore the
parameter change would not be correctly scheduled on that thread. The only way
to guarantee this behavior would be to have a mutex within both `set()` and
`processRealtimeEvents()`, which has performance consequences for the audio
thread.

That said, as long as you don't attempt to schedule parameter changes or destroy
the parameter set immediately after construction, `ConcurrentParameterSet`
should be safe and reliable to use. Also it should be noted that all `Parameter`
subclasses provide a constructor which allows you to set a default value, so it
shouldn't be necessary to schedule parameter changes immediately after
constructing the parameter set.


Testing
-------

PluginParameters comes with a small test suite which is used to develop the
library as well as fix bugs. If you think you've found a bug in
PluginParameters, then please build the test suites and run it before reporting
a bug for your platform. The test suites are built using CMake, and generate two
executables, `pluginparametertest` and `multithreadedtest`.

PluginParameters is built with [CMake][1] and should compile cleanly out of
the box. Building on unix platforms (including Mac OSX) is simply a matter of
running `cmake . ; make`. On Windows, one can run `cmake.exe -G "Visual Studio
12"` to generate a Visual Studio project file which can build the project.


License
-------

PluginParameters is licensed under the BSD licnese. See the file `LICENSE.txt`
provided with the source code for more details. If built in multi-threaded mode,
then code from [TinyThread++][2] and [readerwriterqueue][3] is used. Please see
the respective license files for each of these libraries, which can be found in
the `include` directory.

Finally, a big thanks to the authors of TinyThread++ and readerwriterqueue for
making this library possible. Writing multi-threaded code is hard!


[1]: http://www.cmake.org
[2]: http://tinythreadpp.bitsnbites.eu
[3]: https://github.com/cameron314/readerwriterqueue
[4]: https://github.com/teragonaudio
