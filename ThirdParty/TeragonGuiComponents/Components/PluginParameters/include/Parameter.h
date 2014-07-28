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

#ifndef __PluginParameters_Parameter_h__
#define __PluginParameters_Parameter_h__

#include <string>
#include <vector>

namespace teragon {

typedef std::string ParameterString;
typedef double ParameterValue;

static const unsigned int kDefaultDisplayPrecision = 1;

class Parameter;

class ParameterObserver {
public:
    ParameterObserver() {}
    virtual ~ParameterObserver() {}

#if PLUGINPARAMETERS_MULTITHREADED
    virtual bool isRealtimePriority() const = 0;
#endif

    /**
     * Method to be called when a parameter's value has been updated.
     */
    virtual void onParameterUpdated(const Parameter *parameter) = 0;
};

typedef std::vector<ParameterObserver *> ParameterObserverMap;

class Parameter {
public:
    /**
     * Create a new parameter with defaults for the minimum and maximum values.
     *
     * @param inName The parameter name
     */
    Parameter(const ParameterString &inName) :
    name(inName), unit(""), minValue(0.0), maxValue(1.0), defaultValue(0.0), value(0.0),
    precision(kDefaultDisplayPrecision), description("") {}

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
    Parameter(const ParameterString &inName,
              ParameterValue inMinValue,
              ParameterValue inMaxValue,
              ParameterValue inDefaultValue) :
    name(inName), unit(""), minValue(inMinValue), maxValue(inMaxValue), defaultValue(inDefaultValue),
    value(inDefaultValue), precision(kDefaultDisplayPrecision), description("") {}

    virtual ~Parameter() {}

    /**
     * @return The parameter's display name
     */
    const ParameterString &getName() const {
        return name;
    }

    /**
     * Get the parameter's name for serialization operations. All characters which
     * are not in the A-Z, a-z, 0-9 range are simply removed.
     *
     * @return A the parameter's name, safe for serialization operations
     */

    const ParameterString getSafeName() const {
        return makeSafeName(name);
    }

    /**
     * Get the serialized version of a string
     *
     * @param string The string to convert
     * @return A string safe for serialization operations
     */
    static const ParameterString makeSafeName(const ParameterString &string) {
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
     * Get the parameter's interval value, which will be between the minimum
     * and maximum values set in the constructor.
     */
    virtual const ParameterValue getValue() const {
        return value;
    }

#if PLUGINPARAMETERS_MULTITHREADED
    friend class Event;
    friend class ScaledEvent;

    // The multi-threaded version shouldn't allow parameters to have their value
    // be directly set in this manner. Instead, all parameter setting must be
    // done by the owning parameter set, as it can dispatch the operation on
    // the correct thread. Allowing this function to remain public might tempt
    // misuse when caching parameters to directly get/set their value, as this
    // would not notify all observers on both threads (not to mention other
    // potential concurrency problems).
protected:
#endif

    /**
     * Set the parameter's interval value directly.
     *
     * @param value Value, which must be between the minimum and maximum values
     */
    virtual void setValue(const ParameterValue inValue) {
        // TODO: Possible ABA problem here
        if(value != inValue) {
            value = inValue;
            notifyObservers();
        }
    }

    /**
     * Set the parameter's value, scaled in the range {0.0 - 1.0}
     *
     * @param value The parameter value, must be between {0.0 - 1.0}
     */
    virtual void setScaledValue(const ParameterValue value) = 0;

#if PLUGINPARAMETERS_MULTITHREADED
public:
#endif

    /**
     * @return Get the parameter's minimum value
     */
    virtual const ParameterValue getMinValue() const {
        return minValue;
    }

    /**
     * @return Get the parameter's maximum value
     */
    virtual const ParameterValue getMaxValue() const {
        return maxValue;
    }

    /**
     * @return Get the parameter's initial default value. Useful for resetting parameters.
     */
    virtual const ParameterValue getDefaultValue() const {
        return defaultValue;
    }

    /**
     * Get the number of decimal places for displaying floating-point parameter values.
     */
    virtual const unsigned int getDisplayPrecision() const {
        return precision;
    }

    /**
     * Number of floating point digits to be displayed, for parameters which support
     * display precision.
     *
     * @param inPrecision Number of decimal digits to display
     */
    virtual void setDisplayPrecision(unsigned int inPrecision) {
        this->precision = inPrecision;
    }

    /**
     * Get the unit string for the parameter. This is generally used by getDisplayText(),
     * and is by default an empty string.
     */
    virtual const ParameterString &getUnit() const {
        return unit;
    }

    /**
     * Set a display unit (such as "ms" for milliseconds) to be shown in the
     * parameter's getDisplayText() string.
     *
     * @param inUnit Unit string to display
     */
    virtual void setUnit(const ParameterString &inUnit) {
        this->unit = inUnit;
    }

    /**
     * Get the parameter description, which is a string that describes what the function of
     * the parameter is. This can be used to provide user-facing help for parameters.
     */
    const ParameterString &getDescription() const {
        return description;
    }

    /**
     * Set the parameter's description.
     *
     * @param description Parameter description
     */
    void setDescription(const ParameterString &inDescription) {
        this->description = inDescription;
    }

    /**
     * Add an observer to be alerted any time this parameter is set to a new value.
     *
     * @param observer Pointer to observing instance
     */
    virtual void addObserver(ParameterObserver *observer) {
        observers.push_back(observer);
    }

    /**
     * Get a given observer for the parameter.
     *
     * @param index Observer to get. If the index is invalid, NULL will be returned.
     * @return The ParameterObserver, or NULL if the index is out of range.
     */
    virtual ParameterObserver *getObserver(const size_t index) const {
        return index < observers.size() ? observers.at(index) : NULL;
    }

    /**
     * Get the total number of observers for the parameter. Useful for iterating over
     * the list of observers.
     */
    virtual const size_t getNumObservers() const {
        return observers.size();
    }

    /**
     * Remove an observer from the list of observers for this parameter. If you do not call
     * this method before your observer goes out of scope, future calls to this parameter's
     * setValue() method may result in segfaults.
     *
     * @param observer Instance to remove
     */
    virtual void removeObserver(ParameterObserver *observer) {
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
    /**
     * Notify all observers that a parameter has been updated. If PluginParameters
     * is built with PLUGINPARAMETERS_MULTITHREADED=1, this method has no effect, since it
     * will be called synchronously, and observer updates are instead executed
     * from the EventDispatcher in that case.
     */
    virtual void notifyObservers() const {
#if !PLUGINPARAMETERS_MULTITHREADED
        for(ParameterObserverMap::const_iterator iterator = observers.begin(); iterator != observers.end(); ++iterator) {
            (*iterator)->onParameterUpdated(this);
        }
#endif
    }

private:
    // Disallow assignment operator. It doesn't really make sense to try
    // to assign one parameter to another, and if this is allowed then we
    // must drop the const several fields.
    Parameter &operator = (const Parameter &) {
        return *this;
    }

private:
    const ParameterString name;
    ParameterString unit;
    const ParameterValue minValue;
    const ParameterValue maxValue;
    const ParameterValue defaultValue;
    ParameterValue value;
    unsigned int precision;
    ParameterString description;

    ParameterObserverMap observers;
};

} // namespace teragon

#endif // __PluginParameters_Parameter_h__
