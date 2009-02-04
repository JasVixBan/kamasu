#!/usr/bin/python


import numpy as n
from scipy.io.numpyio import fread
import os, sys
from stat import *
from pylab import *
#
# generate signal
#
sr = 48000.0

nsamples = os.stat(sys.argv[1])[ST_SIZE] / 4

fd = open(sys.argv[1], 'rb')

blob = fread(fd, nsamples, 'f')
shape = (nsamples,)
signal = blob.reshape(shape)

plot(signal)
show()
