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


Usage
-----

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


License
-------

PluginParameters is licensed under the BSD licnese. See the file `LICENSE.txt`
provided with the source code for more details.
