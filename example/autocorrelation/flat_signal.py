#!/usr/bin/python

import numpy as n
from scipy.io.numpyio import fwrite
import sys

#
# generate signal
#
sr = 48000.0
seconds = 10
freq = 5000

signal = n.zeros((sr * seconds,))

def sin_at(sr, freq):
    n_samples = float(sr)/float(freq)
    return n.sin(n.linspace(0, 2*n.pi, n_samples))[:-1]


for i in xrange(len(signal)):
    signal[i] = n.sin(i/sr * 2 * n.pi * freq)

writable_signal = signal.astype(n.float32)

print "Writing %u samples of %u bytes to signal.dat" % (writable_signal.size,
                                                        writable_signal.itemsize)

fd = open('signal.dat', 'wb')
fwrite(fd, writable_signal.size, writable_signal)

