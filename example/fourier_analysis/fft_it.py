#!/usr/bin/python


import numpy as n
from scipy.io.numpyio import fread, fwrite
import os, sys
from stat import *
from pylab import *
import matplotlib.ticker as mt
import matplotlib.mlab as mlab

def tdsgram(x, NFFT=256, Fs=2, detrend=mlab.detrend_none,
            window = mlab.window_hanning, noverlap=128):
    x = np.asarray(x)
    assert(NFFT>noverlap)
    #if np.log(NFFT)/np.log(2) != int(np.log(NFFT)/np.log(2)):
    #   raise ValueError, 'NFFT must be a power of 2'
    if NFFT % 2:
        raise ValueError('NFFT must be even')


    # zero pad x up to NFFT if it is shorter than NFFT
    if len(x)<NFFT:
        n = len(x)
        x = np.resize(x, (NFFT,))
        x[n:] = 0


    # for real x, ignore the negative frequencies
    if np.iscomplexobj(x):
        numFreqs=NFFT
    else:
        numFreqs = NFFT//2+1

    if mlab.cbook.iterable(window):
        assert(len(window) == NFFT)
        windowVals = np.asarray(window)
    else:
        windowVals = window(np.ones((NFFT,),x.dtype))
    step = NFFT-noverlap
    ind = np.arange(0,len(x)-NFFT+1,step)
    n = len(ind)
    Pxx = np.zeros((numFreqs,n), np.float_)
    # do the ffts of the slices

    for i in range(n):
        thisX = x[ind[i]:ind[i]+NFFT]
        thisX = windowVals*detrend(thisX)
        fx = np.absolute(np.fft.fft(thisX))**2
        Pxx[:,i] = fx[:numFreqs]
    # Scale the spectrum by the norm of the window to compensate for
    # windowing loss; see Bendat & Piersol Sec 11.5.2
    Pxx /= (np.abs(windowVals)**2).sum()
    t = 1/Fs*(ind+NFFT/2)
    freqs = Fs/NFFT*np.arange(numFreqs)

    if np.iscomplexobj(x):
        # center the frequency range at zero
        freqs = np.concatenate((freqs[NFFT/2:]-Fs,freqs[:NFFT/2]))
        Pxx   = np.concatenate((Pxx[NFFT/2:,:],Pxx[:NFFT/2,:]),0)

    return Pxx, freqs, t




#
# generate signal
#
sr = 48000.0

nsamples = os.stat(sys.argv[1])[ST_SIZE] / 4
print nsamples, " samples"

fd = open(sys.argv[1], 'rb')

signal = fread(fd, nsamples, 'f')
print "signals is", type(signal), signal.shape, "\ndata: ", repr(signal)

ax1 = subplot(211)
Pxx, freqs, bins, im = specgram(signal, NFFT=512, Fs=48000, noverlap=256)

# cla()
# gca()
# Pxx, freqs, bins = tdsgram(signal, NFFT=512, Fs=48000, noverlap=256)
# 
# 
# Z = 10*np.log10(Pxx)
# Z =  np.flipud(Z)
# 
# print "z=", Z
# 
# xextent = 0, np.amax(bins)
# xmin, xmax = xextent
# freqs += 0
# extent = xmin, xmax, freqs[0], freqs[-1]
# im = imshow(Z, None, extent=extent)
# axis('auto')
# 
# show()


# offset = 1500
winlen = 512
nfreqs = winlen//2+1
winstep = 256
# print signal[:2048]
starts = range(0, (len(signal)-winlen), winstep)

results = n.zeros((nfreqs, len(starts)))

x_labels = n.array(starts)/sr
y_labels = n.array([(sr*x)/winlen for x in range(winlen/2)])
# print x_labels
# print y_labels

index = 0
for start_off in starts:
    if start_off % 1000 == 0:
        # print "****", start_off, "****"
        pass
    rawfft = n.fft.fft(signal[start_off:start_off+winlen] * hanning(winlen))**2
    for x in range(len(rawfft)):
        binfreq = (float(sr)*float(x)/float(winlen))
        amp = abs(rawfft[x])
                   
        #if binfreq > 1800 and binfreq < 3000:
        #print '%f %f' % (binfreq, amp)

        #print ">>>>", len(results[index,:]), len(rawfft[1:])
    #print rawfft
    # print "results is ", results[:,index].shape, " rawfft ", rawfft[:nfreqs].shape
    results[:,index] = n.abs(rawfft[:nfreqs])
    index += 1

results /= (np.abs(hanning(winlen))**2).sum()



print "pxxmax = ", n.max(Pxx), " mean ", n.mean(Pxx), "resmax = ", n.max(results), " mean ", n.mean(results)
print "pxxahpe=", Pxx.shape, " resshape", results.shape

print "Time to plot"

#print outfft.astype(n.float32)
# spectral()

# pcolor(x_labels, y_labels, results.T)

Z = 10*np.log10(results.astype(n.float32))
Z = n.flipud(Z)

print "Z.size is ", Z.size
print "Z.shape is ", Z.shape

outfd = open(sys.argv[2], 'wb')
fwrite(outfd, 2, n.array(Z.shape).astype(n.float32))
fwrite(outfd, Z.size, Z)



# 
# imshow(Z, None, extent = (x_labels[0], x_labels[-1],y_labels[0], y_labels[-1]))
# 
# gca().axis('tight')
# show()
