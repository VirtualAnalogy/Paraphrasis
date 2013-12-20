/*
Copyright (c) 2013 Teragon Audio. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
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
