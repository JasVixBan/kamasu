#!/usr/bin/python

import numpy as n
from scipy.io.numpyio import fwrite
import sys

#
# generate signal
#
sr = 48000.0

signal = n.zeros((1500,))

def sin_at(sr, freq):
    n_samples = sr/freq
    return n.sin(n.linspace(0, 2*n.pi, n_samples))[:-1]


for i in [ord(x) for x in 'KaMaSu']:
    print "10 cycles of %dHz" % i
    for j in range(5):
        signal = n.hstack((signal, sin_at(sr, i)))

signal = n.hstack((signal, n.zeros((1500,))))

writable_signal = signal.astype(n.float32)

print "Writing %u samples of %u bytes to signal.dat" % (writable_signal.size,
                                                        writable_signal.itemsize)

fd = open('signal.dat', 'wb')
fwrite(fd, writable_signal.size, writable_signal)

