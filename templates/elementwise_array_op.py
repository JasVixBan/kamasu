#!/usr/bin/python

import sys, re

functions = ['sqrt', 'rsqrt','cbrt',
             'exp', 'exp2', 'exp10', 'expm1',
             'log', 'log2', 'log10', 'log1p',
             'sin', 'cos', 'tan',
             'asin', 'acos', 'atan',
             'sinh', 'cosh', 'tanh',
             'asinh', 'acosh', 'atanh',
             'erf', 'erfc', 'lgamma', 'tgamma',
             'logb', 'ilogb',
             'trunc', 'round', 'rint', 'nearbyint',
             'ceil', 'floor', 'lrint', 'lround', 'llrint',
             'llround']

KAMASU_MAX_ARRAY_DIM = 6

files = ['elementwise_array_op.cu', 'elementwise_array_op.h']

for fname in files:
    ifile = open('templates/' + fname)
    ofile = open('src/' + fname, 'w')

    lines = ifile.read()

    global_vars = {}
    def r(x):
        global local_vars
        matched = x.group(1)
        res = eval(matched, global_vars)
        return str(res)

    one_to_n = range(1,KAMASU_MAX_ARRAY_DIM)

    for op in functions:
        for N in range(1,KAMASU_MAX_ARRAY_DIM):
            global_vars['OP'] = op
            global_vars['N'] = N
            global_vars['one_to_n'] = range(1,N)
            print >>ofile, re.sub(r'\/\*(.*?)\*\/', r, lines)

