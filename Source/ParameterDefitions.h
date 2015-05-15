/*
  ==============================================================================

    ParameterDefitions.h
    Created: 30 Jul 2014 9:19:29am
    Author:  Tomas Medek

  ==============================================================================
*/

#ifndef PARAMETERDEFITIONS_H_INCLUDED
#define PARAMETERDEFITIONS_H_INCLUDED

static const char* kParameterSamplePitch_name = "Sample Pitch";
static const  int kParameterSamplePitch_minValue = 50;
static const  int kParameterSamplePitch_maxValue = 10000;
static const  int kParameterSamplePitch_defaultValue = 440;

static const char* kParameterFrequencyResolution_name = "Frequency Resolution";
static const  int kParameterFrequencyResolution_minValue = 30;
static const  int kParameterFrequencyResolution_maxValue = 10000;
static const  int kParameterFrequencyResolution_defaultValue = 40;

static const char* kParameterReverse_name = "Reverse";
static const  bool kParameterReverse_defaultValue = false;

static const double kDefaultPitchResolutionRation = 0.8;

static const char* kParameterLastSamplePath_name = "Last Sample Path";


#endif  // PARAMETERDEFITIONS_H_INCLUDED
