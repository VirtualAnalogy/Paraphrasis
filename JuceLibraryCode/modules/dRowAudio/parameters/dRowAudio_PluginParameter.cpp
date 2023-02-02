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

PluginParameter::PluginParameter()
{
    init ("parameter",      // name
          UnitGeneric,      // unit
          "A parameter",        // description
          1.0,              // value
          0.0,              // min
          1.0,              // max
          0.0,              // default
          1.0,              // skew factor
          0.1,              // smooth coeff
          0.01,             // step
          "");              // unit suffix
}

PluginParameter::PluginParameter (const PluginParameter& other)
{
    name = other.name;
    description = other.description;
    unitSuffix = other.unitSuffix;
    min = other.min;
    max = other.max;
    defaultValue = other.defaultValue;
    smoothCoeff = other.smoothCoeff;
    smoothValue = other.smoothValue;
    skewFactor = other.skewFactor;
    step = other.step;
    unit = other.unit;
    setValue (static_cast<double> (other.valueObject.getValue()));
}

void PluginParameter::init (const juce::String& name_, ParameterUnit unit_, juce::String description_,
                            double value_, double min_, double max_, double default_,
                            double skewFactor_, double smoothCoeff_, double step_, juce::String unitSuffix_)
{
    name = name_;
    unit = unit_;
    description = description_;

    min = min_;
    max = max_;
    setValue (value_);
    defaultValue = default_;

    smoothCoeff = smoothCoeff_;
    smoothValue = getValue();

    skewFactor = skewFactor_;
    step = step_;

    unitSuffix = unitSuffix_;

    // default label suffix's, these can be changed later
    #if __clang__
     #pragma clang diagnostic push
     #pragma clang diagnostic ignored "-Wswitch-enum"
    #endif

    switch (unit)
    {
        case UnitPercent:       setUnitSuffix ("%");                         break;
        case UnitSeconds:       setUnitSuffix ("s");                         break;
        case UnitPhase:         setUnitSuffix (CharPointer_UTF8 ("\xc2\xb0"));      break;
        case UnitHertz:         setUnitSuffix ("Hz");                        break;
        case UnitDecibels:      setUnitSuffix ("dB");                        break;
        case UnitDegrees:       setUnitSuffix (CharPointer_UTF8 ("\xc2\xb0"));      break;
        case UnitMeters:        setUnitSuffix ("m");                         break;
        case UnitBPM:           setUnitSuffix ("BPM");                       break;
        case UnitMilliseconds:  setUnitSuffix ("ms");                        break;
        default:                                                             break;
    }

   #if __clang__
    #pragma clang diagnostic push
   #endif
}

void PluginParameter::setValue (double value)
{
    valueObject = jlimit (min, max, value);
}

void PluginParameter::setNormalisedValue (double normalisedValue)
{
    setValue ((max - min) * jlimit (0.0, 1.0, normalisedValue) + min);
}

void PluginParameter::setUnitSuffix (const juce::String& newSuffix)
{
    unitSuffix = newSuffix;
}

void PluginParameter::smooth()
{
    if (smoothValue != getValue())
    {
        if (smoothCoeff == 1.0 || almostEqual (smoothValue, getValue()))
            smoothValue = getValue();
        else
            smoothValue = ((getValue() - smoothValue) * smoothCoeff) + smoothValue;
    }
}

void PluginParameter::setSmoothCoeff (double newSmoothCoef)
{
    smoothCoeff = newSmoothCoef;
}

void PluginParameter::setSkewFactor (double newSkewFactor)
{
    skewFactor = newSkewFactor;
}

void PluginParameter::setSkewFactorFromMidPoint (const double valueToShowAtMidPoint)
{
    if (max > min)
        skewFactor = std::log (0.5) / std::log ((valueToShowAtMidPoint - min) / (max - min));
}

void PluginParameter::setStep (double newStep)
{
    step = newStep;
}

void PluginParameter::writeXml (XmlElement& xmlState)
{
    xmlState.setAttribute (name, getValue());
}

void PluginParameter::readXml (const XmlElement* xmlState)
{
    setValue (xmlState->getDoubleAttribute (name, getValue()));
}

void PluginParameter::setupSlider (Slider& slider)
{
    slider.setRange             (min, max, step);
    slider.setSkewFactor        (skewFactor);
    slider.setValue             (getValue(), dontSendNotification);
    slider.setTextValueSuffix   (unitSuffix);
}

double PluginParameter::normaliseValue (double scaledValue) const noexcept
{
    return (scaledValue - min) / (max - min);
}
