/*
 * Copyright (c) 2013 - Teragon Audio LLC
 *
 * Permission is granted to use this software under the terms of either:
 * a) the GPL v2 (or any later version)
 * b) the Affero GPL v3
 *
 * Details of these licenses can be found at: www.gnu.org/licenses
 *
 * This software is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * ------------------------------------------------------------------------------
 *
 * This software uses the JUCE library.
 *
 * To release a closed-source product which uses JUCE, commercial licenses are
 * available: visit www.juce.com for more information.
 */

#ifndef ANIMATIONCONSTANTS_H_INCLUDED
#define ANIMATIONCONSTANTS_H_INCLUDED

namespace teragon {

/**
* Framerate for animations, in frames per second.
*/
static const float kAnimationFrameRate = 30.0f;

/**
* Used for scheduling timers, so this constant is how many milliseconds a
* frame is shown for.
*/
static const int kAnimationTimerRateInMs = (int)((1.0f / kAnimationFrameRate) * 1000.0f);

/**
* Length of fade animations, in milliseconds.
* TODO: Separate durations for fade in/out
*/
static const float kFadeDurationInMs = 100.0f;

/**
* Fade animations modulate the opacity from 0.0 -> 1.0 (or backwards), this
* constant controls how much to change this value per frame.
*/
static const float kFadeDurationStepRate = 1.0f / (kFadeDurationInMs / kAnimationTimerRateInMs);

}

#endif  // ANIMATIONCONSTANTS_H_INCLUDED
