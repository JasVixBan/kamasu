#!/usr/bin/python

import sys
from scipy.io.numpyio import fread
import numpy as n
from pylab import *

#
# generate signal
#
sr = 48000.0

datfile = sys.argv[1]
nsamples = int(sys.argv[2])

print "Reading %d samples from %s" % (nsamples, datfile)
fd = open(datfile, 'rb')
datatype = 'f'
shape = (nsamples,)
data = fread(fd, nsamples, datatype)
signal = data.reshape(shape)

#
# autocorr routine
#

def autocorrelate(a):
    winlen = int(sr/70)

    freqs = n.zeros((len(a)-winlen,))

    for outer in range(0, len(a)-(winlen*2), 2):
        print "%d%%" % 100 * float(outer)/(len(a)-(winlen*2))

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

#
# doit
#

f = autocorrelate(signal)
plot(f)

show()
