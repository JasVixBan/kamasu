#!/usr/bin/python

import numpy as n
import pylab

def hann_window(N):
    def impl(x):
        return 0.5 * (1.0 - n.cos(2.0 * n.pi * x /(impl.N-1)));
    impl.N = N
    return impl


win = hann_window(512)

pylab.plot([win(x) for x in range(512)])

pylab.show()
