#!/usr/bin/python


import sys
import numpy as n
from scipy.io.numpyio import fread
import os, sys
from stat import *
from pylab import *
import matplotlib.ticker as mt
import matplotlib.mlab as mlab

print "Opening %s" % sys.argv[1]
fd = open(sys.argv[1], 'rb')

title = sys.argv[2]

shape = fread(fd, 2, 'f')
shape = shape.astype(n.int32)
print "shape=", shape, " going to read %d bytes", shape[0] * shape[1] 
blob = fread(fd, shape[0] * shape[1], 'f')
print "Blob size is %d" % blob.size
Z = blob.reshape(shape)

imshow(Z.T)  #, None)# , extent = (x_labels[0], x_labels[-1],y_labels[0], y_labels[-1]))

gca().axis('tight')
gca().set_title(title)
show()
