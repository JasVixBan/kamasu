#!/usr/bin/python


import numpy as n
from scipy.io.numpyio import fread
import os, sys
from stat import *
from pylab import *
import matplotlib.ticker as mt
import matplotlib.mlab as mlab

fd = open('fft.dat', 'rb')
shape = fread(fd, 2, 'f')
shape = shape.astype(n.int32)
print "shape=", shape 
blob = fread(fd, shape[0] * shape[1], 'f')
Z = blob.reshape(shape)

imshow(Z)#, None)# , extent = (x_labels[0], x_labels[-1],y_labels[0], y_labels[-1]))

gca().axis('tight')
show()
