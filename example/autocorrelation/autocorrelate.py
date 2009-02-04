#!/usr/bin/python

import numpy as n
from pylab import *

def logistic(x):
    return 1.0 / (1.0 + n.exp(-x))

sr = 48000.0

def sin_at(sr, freq):
    n_samples = sr/freq
    return n.sin(n.linspace(0, 2*n.pi, n_samples))[:-1]

signal = n.zeros((0,))

for i in [ord(x) for x in 'KaMaSu']:
    print "10 cycles of %dHz" % i
    for j in range(5):
        signal = n.hstack((signal, sin_at(sr, i)))

signal = n.hstack((signal, n.zeros((0,))))

def autocorrelate(a):
    winlen = int(sr/70)

    freqs = n.zeros((len(a)-winlen,))

    for outer in range(0, len(a)-(winlen*2), 2):
        print float(outer)/(len(a)-(winlen*2))

        corr_coeff = n.zeros((winlen,))
        for inner in range(winlen):
            periodic_autocorr = sum(a[outer:outer+winlen]
                                    * a[outer+inner:outer+inner+winlen]) / winlen
            corr_coeff[inner] = periodic_autocorr

        delta_corr = corr_coeff[1:] - corr_coeff[0:-1]
        for i in range((sr/200)/4, len(delta_corr)-1):
            if delta_corr[i] >= 0 and delta_corr[i+1] < 0:
                # print "@", outer, sr/(i+2), " Hz"
                freqs[outer] = sr/(i+2)
                break
            
    return freqs

f = autocorrelate(signal)
plot(f)

show()
