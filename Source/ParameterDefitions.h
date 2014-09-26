/*
 This is Paraphrasis synthesiser.
 
 Copyright (c) 2014 by Tomas Medek
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY, without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 
 tom@virtualanalogy.com
 
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

static const int kDefaultSynthesiserVoiceNumbers = 16;// going to be a parameter


#endif  // PARAMETERDEFITIONS_H_INCLUDED
