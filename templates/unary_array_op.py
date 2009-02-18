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

KAMASU_MAX_ARRAY_DIM = 6

def forall(**kwargs):
    if len(kwargs) == 1:
        for k, v in kwargs.iteritems():
            for value in v:
                yield [(k, value)]
    else:
        for k, v in kwargs.iteritems():
            for value in v:
                newargs = kwargs.copy()
                del(newargs[k])
                for nextthing in forall(**newargs):
                    yield[(k,value)] + nextthing

stuff = [{ 'src' : 'templates/unary_array_transforms.h',
           'dest' : 'src/unary_array_transforms.h.generated',
           'next' : forall(OP=functions)},

         { 'src' : 'templates/unary_array_op.cu',
           'dest' : 'src/unary_array_op.cu.generated',
           'next' : forall(OP=functions, N=range(1,KAMASU_MAX_ARRAY_DIM)) },

         { 'src' : 'templates/unary_array_grammar.hpp',
           'dest' : 'include/resophonic/kamasu/unary_array_grammar.hpp',
           'next' : [{'functions' : functions}]},

         { 'src' : 'templates/unary_array_op.h',
           'dest' : 'src/unary_array_op.h.generated',
           'next' : forall(OP=functions, N=range(1,KAMASU_MAX_ARRAY_DIM)) }

         ]

pattern = re.compile(r'\/\*(.*?)\*\/', re.DOTALL)

for target in stuff:
    print target['src'], "=>", target['dest']
    ifile = open(target['src'])
    try:
        os.unlink(target['dest'])
    finally:
        pass
    ofile = open(target['dest'], 'w')
    

    lines = ifile.read()

    print >>ofile, '//\n//\n// this is a generated file\n//\n//\n'
    for env in target['next']:
        env = dict(env)
        env['KAMASU_MAX_ARRAY_DIM'] = KAMASU_MAX_ARRAY_DIM
        print env
        def r(x):
            matched = x.group(1)
            res = eval(matched, env)
            return str(res)

        print >>ofile, re.sub(pattern, r, lines)


