#!/usr/bin/python


import numpy as n
from scipy.io.numpyio import fread, fwrite
import os, sys
from stat import *
from pylab import *
import matplotlib.ticker as mt
import matplotlib.mlab as mlab




#
# generate signal
#
sr = 48000.0
winlen = 2048
nfreqs = winlen//2+1
winstep = 64

nsamples = os.stat(sys.argv[1])[ST_SIZE] / 4
print nsamples, " samples"

if len(sys.argv) == 4:
    nsamples = int(sys.argv[3])

fd = open(sys.argv[1], 'rb')

signal = fread(fd, nsamples, 'f')
print "signals is", type(signal), signal.shape

starts = range(0, (len(signal)-winlen), winstep)

results = n.zeros((len(starts), nfreqs))

# x_labels = n.array(starts)/sr
# y_labels = n.array([(sr*x)/winlen for x in range(winlen/2)])
# print x_labels
# print y_labels

index = 0
for start_off in starts:
    if start_off % 1000 == 0:
        # print "****", start_off, "****"
        pass
    rawfft = n.fft.fft(signal[start_off:start_off+winlen])# * hanning(winlen))**2
    for x in range(len(rawfft)):
        binfreq = (float(sr)*float(x)/float(winlen))
        amp = abs(rawfft[x])
                   
        #if binfreq > 1800 and binfreq < 3000:
        #print '%f %f' % (binfreq, amp)

        #print ">>>>", len(results[index,:]), len(rawfft[1:])
    #print rawfft
    # print "results is ", results[:,index].shape, " rawfft ", rawfft[:nfreqs].shape
    results[index,::-1] = n.abs(rawfft[:nfreqs])
    index += 1

# results /= (np.abs(hanning(winlen))**2).sum()



print "resmax = ", n.max(results), " mean ", n.mean(results)
print "resshape", results.shape

#print outfft.astype(n.float32)
# spectral()

# pcolor(x_labels, y_labels, results.T)

Z = 10*np.log10(results.astype(n.float32))
# reverses in time
# Z = n.flipud(Z)

print "Z.size is ", Z.size
print "Z.shape is ", Z.shape

try:
    os.unlink(sys.argv[2])
    print "removed ", sys.argv[2]
except:
    print sys.argv[2], " doesnt exist"

outfd = open(sys.argv[2], 'wb')
fwrite(outfd, 2, n.array(Z.shape).astype(n.float32))

fwrite(outfd, Z.size, Z)

# imshow(Z, None, extent = (x_labels[0], x_labels[-1],y_labels[0], y_labels[-1]))
# 
# gca().axis('tight')
# show()
