#!/usr/bin/python

import sys, re, os

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

array_scalar_ops = ['boost::proto::tag::' + op
                    for op in ['plus', 'minus', 'divides', 'multiplies']] \
                    + ['resophonic::kamasu::tag::pow']

rvals = ['boost::mpl::true_', 'boost::mpl::false_']

types = ['float'] # add 'double' here

KAMASU_MAX_ARRAY_DIM = 6

one_to_n = range(1,KAMASU_MAX_ARRAY_DIM)

def enum(thing, upto):
    return ','.join([thing % n for n in range(upto)])




def forall(**kwargs):
    if len(kwargs) == 1:
        k = kwargs.keys()[0]
        v = kwargs[k]
        for value in v:
            yield [(k, value)]
    else:
        k = kwargs.keys()[0]
        v = kwargs[k]
        for value in v:
            newargs = kwargs.copy()
            del(newargs[k])
            for nextthing in forall(**newargs):
                yield[(k,value)] + nextthing

pattern = re.compile(r'\/\*(.*?)\*\/', re.DOTALL)

execfile(sys.argv[1])

ifile = open(sys.argv[2])
try:
    os.unlink(sys.argv[3])
except:
    pass
ofile = open(sys.argv[3], 'w')

lines = ifile.read()

print >>ofile, '//\n//\n// this is a generated file\n//\n//\n'

for env in next:
    env = dict(env)
    def r(x):
        matched = x.group(1)
        res = eval(matched, env)
        return str(res)

    print >>ofile, re.sub(pattern, r, lines)


