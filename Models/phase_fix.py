import numpy as np
import matplotlib.pyplot as plt
from copy import deepcopy

iAmp = 0
iF   = 1
iPhi = 2
iSamp= 3

def create_model() :
    """
    Create testing model for phasing correction. First partial start at sample 32, but with
    corrected phase. Next (3rd partial) starts at zero.
    """
    model = []
    s1 = np.array([0.274, 438.805, np.deg2rad(-156.2), 32])
    model.append(s1)
    s2 = np.array([0.0905, 1316.42, np.deg2rad(86.07), 0])
    model.append(s2)
    return model

def render_model(model, duration, fs) :
    """
    Render model for given duration and sample rate.
    """
    t = np.arange(0, duration, 1 / float(fs))
    buffer = np.zeros(t.size)
    for partial in model :
	buffer[partial[iSamp]:] += partial[iAmp] * np.cos(2 * np.pi * partial[iF] * t[0:t.size-partial[iSamp]] + partial[iPhi])

    return buffer

def transpose(model, frequency_scale, phaseFix, fs) :
    """
    Transpose frequency of all partial and correct the phase.
    """
    model2 = deepcopy(model) # create deep copy of model - do not overwrite origin one
    for partial in model2 :
        partial[iF] = frequency_scale * partial[iF]
	if phaseFix and partial[iSamp] != 0 : # can not divide by zero
	    # Phase correction - to original phase add phase change.
	    # If we transposed/pitch-shifted the sound using sample rate change, the transpose octave above would
	    # mean create new signal with every second sample missing, so the partial would start earlier. If we
	    # would like to have partial transposed but in the same time t0 as original data what the new phase will be?
	    # It will be the original phase with the phase change during the delta of time. What delta of time it is?
	    # The start time in sample-removing pitch shifted signal would be half of time if we transpose octave up so the
	    # delta time is t0 - t0/transposeFactor. So the new phase is like this (here we do not have time t0 so we get
	    # it from partial[iSamp]/float(fs)).
	    partial[iPhi] = partial[iPhi] + 2 * np.pi*partial[iF] * float(partial[iSamp])/float(fs)*(1-1/float(frequency_scale))
    return model2

def run_test(phaseFix = True, dur = 0.01, fs = 44100) :
    """
    Test phase correction for different tranpose scale
    """
    model = create_model()
    s = render_model(model, dur, fs)

    model2 = transpose(model, 0.5, phaseFix, fs)
    ss = render_model(model2, dur, fs)

    model3 = transpose(model, 2, phaseFix, fs)
    sss = render_model(model3, dur, fs)

    plt.plot(s)
    plt.plot(ss)
    plt.plot(sss)
    plt.show()

