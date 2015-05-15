from scipy.io.wavfile import read 
import numpy as np
import sys, math, os
import matplotlib.pyplot as plt

INT16_FAC = (2**15)-1
INT32_FAC = (2**31)-1
INT64_FAC = (2**63)-1

norm_fact = {'int16':INT16_FAC, 'int32':INT32_FAC, 'int64':INT64_FAC,'float32':1.0,'float64':1.0}

def wavread(filename):
	"""
	Read a sound file and convert it to a normalized floating point array
	filename: name of file to read
	returns fs: samplint rate of file, x: floating point array
	"""
	
	if (os.path.isfile(filename) == False):                  # raise error if wrong input file
		raise ValueError("Input file is wrong")
		
	fs, x = read(filename)
	
	if (len(x.shape) !=1):                                   # raise error if more than one channel
		raise ValueError("Audio file should be mono")

	if (fs !=44100):                                         # raise error if more than one channel
		raise ValueError("Sampling rate of input sound should be 44100")

	#scale down and convert audio into floating point number in range of -1 to 1
	x = np.float32(x)/norm_fact[x.dtype.name]
	return fs, x

def magnitude(x, fs, f) :
    t = np.arange(0, x.size / float(fs), 1. / fs)
    s = np.cos(2 * np.pi * f * t) + 1j * np.sin(2 * np.pi * f * t)
    return sum(x * np.conjugate(s))

def test_file(filename, f) :
    fs, x = wavread(filename)
    return magnitude(x, fs, f)


def DFT(x) :
    N = x.size
    n = np.arange(0, N)
    X = np.array([])
    for k in range(N) :
        s = np.cos(2 * np.pi * k / N * n) + 1j * np.sin(2 * np.pi * k / N * n)
	X = np.append(X, sum(x * np.conjugate(s)))

    return X

def process_file(filename, f, partials) :
    fs, x = wavread(filename)
    X = DFT(x)
    find_partials(x, fs, f, partials)

def find_partials(X, fs, f0, partials, rng = 10) :
    N = X.size
    P  = []
    for i in range(1,partials + 1) :
       k = int(i * f0 * N / float(fs))
       max_k = k
       for j in range(k - rng, k + rng) :
           if 0 < j < X.size :
	       if abs(X[j]) > abs(X[k]) :
	           k = j
       A = abs(X[k]) / float(N)
       f = k * float(fs) / float(N)
       p = np.rad2deg(np.angle(X[k]))
       P.append(np.array([A, f, p]))

    return P
	
def synthesise(P, fs = 44100, duration = 0.1) :
    t = np.arange(0, duration, 1 / float(fs))
    s = np.zeros(t.size)
    for i in range(len(P)) :
        s = s + P[i][0] * np.cos(2 * np.pi * P[i][1] * t + np.deg2rad(P[i][2]))
    return s
    
def analyze_file(filename, f0, p, t = 0.05) :
    fs, x = wavread(filename)
    X = DFT(x)
    P = find_partials(X, fs, f0, p)
    s = synthesise(P, fs, t)
    ss = s / max(s)
    xx = x / max(x)
    length = max(ss.size, xx.size)
    ss = ss[0:length]
    xx = xx[0:length]
    plt.plot(xx)
    plt.plot(ss)
    for pp in P :
	print pp
    plt.show()
    return P

