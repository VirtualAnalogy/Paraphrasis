/*
 * Copyright (c) 2013 Teragon Audio. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __PluginParameter_h__
#define __PluginParameter_h__

#include <string>
#include <vector>

namespace teragon {
typedef std::string ParameterString;
typedef double ParameterValue;

static const int kDefaultDisplayPrecision = 1;

class PluginParameter;
class PluginParameterObserver {
public:
  PluginParameterObserver() {}
  virtual ~PluginParameterObserver() {}

  /**
   * Method to be called when a parameter's value has been updated.
   */
  virtual void onParameterUpdated(const PluginParameter* parameter) = 0;
};
typedef std::vector<PluginParameterObserver*> ParameterObserverMap;

class PluginParameter {
public:
  /**
   * Create a new parameter with defaults for the minimum and maximum values.
   *
   * @param inName The parameter name
   */
  PluginParameter(ParameterString inName) :
    name(inName), minValue(0.0), maxValue(1.0), defaultValue(0.0), value(0.0),
    type(0), precision(kDefaultDisplayPrecision) {}

  /**
    * Create a new floating point parameter. This is probably the most common
    * parameter type used in a plugin.
    *
    * @param inName The parameter name
    * @param inMinValue The parameter's minimum value
    * @param inMaxValue The parameter's maximum value
    * @param inDefaultValue The parameter's initial default value
    *
    * Note that there is *no* checking done for the parameter ranges, so you
    * need to make sure that they are sane. If the range was otherwise invalid,
    * an exception would need to be thrown, and that would therefore impose the
    * requirement of exception handling on the plugin developer.
    *
    * Therefore this class has been intentionally kept rather minimal, and
    * operates under the assumption that you are not insane and choose sensible
    * values for the minimum, maximum, and default values.
    */
  PluginParameter(ParameterString inName, ParameterValue inMinValue,
  ParameterValue inMaxValue, ParameterValue inDefaultValue) :
    name(inName), minValue(inMinValue), maxValue(inMaxValue), defaultValue(inDefaultValue),
    value(inDefaultValue), type(0), precision(kDefaultDisplayPrecision) {}
  virtual ~PluginParameter() {}

  /**
   * @return The parameter's display name
   */
  const ParameterString& getName() const { return name; }

  /**
   * Get the parameter's name for serialization operations. All characters which
   * are not in the A-Z, a-z, 0-9 range are simply removed.
   *
   * @return A the parameter's name, safe for serialization operations
   */

  const ParameterString getSafeName() const { return makeSafeName(name); }

  /**
   * Get the serialized version of a string
   *
   * @param string The string to convert
   * @return A string safe for serialization operations
   */
  static const ParameterString makeSafeName(const ParameterString& string) {
    ParameterString result;
    for(size_t i = 0; i < string.length(); ++i) {
      if(((string[i] >= 'a' && string[i] <= 'z') ||
          (string[i] >= '0' && string[i] <= '9') ||
          (string[i] >= 'A' && string[i] <= 'Z'))) {
        result += string[i];
      }
    }
    return result;
  }

  /**
   * @return The display text for the parameter
   */
  virtual const ParameterString getDisplayText() const = 0;

  /**
   * @return The parameter's value, scaled in the range {0.0 - 1.0}
   */
  virtual const ParameterValue getScaledValue() const = 0;

  /**
   * Set the parameter's value, scaled in the range {0.0 - 1.0}
   *
   * @param value The parameter value, must be between {0.0 - 1.0}
   */
  virtual void setScaledValue(const ParameterValue value) = 0;

  /**
   * Get the parameter's interval value, which will be between the minimum
   * and maximum values set in the constructor.
   */
  virtual const ParameterValue getValue() const { return value; }

  /**
   * Set the parameter's interval value directly.
   *
   * @param value Value, which must be between the minimum and maximum values
   */
  virtual void setValue(const ParameterValue inValue) {
    value = inValue;
    for(ParameterObserverMap::iterator iterator = observers.begin(); iterator != observers.end(); ++iterator) {
      (*iterator)->onParameterUpdated(this);
    }
  }

  /**
   * @return Get the parameter's minimum value
   */
  virtual const ParameterValue getMinValue() const { return minValue; }

  /**
   * @return Get the parameter's maximum value
   */
  virtual const ParameterValue getMaxValue() const { return maxValue; }

  /**
   * @return Get the parameter's initial default value. Useful for reset.
   */
  virtual const ParameterValue getDefaultValue() const { return defaultValue; }

  /**
   * @parameter Get the parameter's user-defined type
   */
  virtual const unsigned int getType() const { return type; }

  /**
   * Set the parameter's user-defined type. The type can be useful for treating
   * groups of parameters in a given way, such as parameters which require a GUI
   * update or a set which is common to a single oscillator in a multi-oscillator
   * synthesizer. By default, the type is 0. This field is unsigned to make it
   * easier use with bitfields.
   *
   * @param inType Type to set
   */
  virtual void setType(unsigned int inType) { this->type = inType; }

  /**
   * Number of floating point digits to be displayed, for parameters which
   * support display precision.
   *
   * @param inPrecision Number of decimal digits to display
   */
  virtual void setDisplayPrecision(unsigned int inPrecision) { this->precision = inPrecision; }

  /**
   * Set a display unit (such as "ms" for milliseconds) to be shown in the
   * parameter's getDisplayText() string.
   *
   * @param inUnit Unit string to display
   */
  virtual void setUnit(const ParameterString& inUnit) { this->unit = inUnit; }

  /**
   * Add an observer to be alerted any time this parameter is set to a new value.
   *
   * @param observer Pointer to observing instance
   */
  virtual void addObserver(PluginParameterObserver* observer) {
    observers.push_back(observer);
  }

  /**
   * Remove an observer from the list of observers for this parameter. If you do not call
   * this method before your observer goes out of scope, future calls to this parameter's
   * setValue() method may result in segfaults.
   *
   * @param observer Instance to remove
   */
  virtual void removeObserver(PluginParameterObserver* observer) {
    ParameterObserverMap::iterator iterator = observers.begin();
    while(iterator != observers.end() && observers.size() > 0) {
      if(*iterator == observer) {
        iterator = observers.erase(iterator);
      }
      else {
        ++iterator;
      }
    }
  }

protected:
  void notifyObservers() const {
    for(ParameterObserverMap::const_iterator iterator = observers.begin(); iterator != observers.end(); ++iterator) {
      (*iterator)->onParameterUpdated(this);
    }
  }

  const ParameterString& getUnit() const { return unit; }
  const int getDisplayPrecision() const { return precision; }

private:
  ParameterString name;
  ParameterString unit;
  const ParameterValue minValue;
  const ParameterValue maxValue;
  const ParameterValue defaultValue;
  ParameterValue value;
  unsigned int type;
  unsigned int precision;

  ParameterObserverMap observers;
};
}

#endif
