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

stuff = [

    { 'src' : 'templates/unary_array_transforms.h',
      'dest' : 'src/generated/unary_array_transforms.h',
      'next' : forall(one_to_n=[one_to_n], OP=functions)},
 
    { 'src' : 'templates/unary_array_op.cu',
      'dest' : 'src/generated/unary_array_op.cu',
      'next' : forall(OP=functions, N=one_to_n) },

    { 'src' : 'templates/unary_array_grammar.hpp',
      'dest' : 'include/resophonic/kamasu/unary_array_grammar.hpp',
      'next' : [{'functions' : functions}]},

    { 'src' : 'templates/unary_array_op.h',
      'dest' : 'src/generated/unary_array_op.h',
      'next' : forall(OP=functions, N=one_to_n) },

    { 'src' : 'templates/elementwise_array_scalar.cu',
      'dest' : 'src/generated/elementwise_array_scalar.cu',
      'next' : forall(N=one_to_n) },

    { 'src' : 'templates/elementwise_array_scalar.h',
      'dest' : 'src/generated/elementwise_array_scalar.h',
      'next' : forall(one_to_n=[one_to_n], OP=array_scalar_ops, RVAL=rvals, T=['float']) },

    { 'src' : 'templates/elementwise_array_array.cu',
      'dest' : 'src/generated/elementwise_array_array.cu',
      'next' : forall(N=one_to_n, enum=[enum]) },

    { 'src' : 'templates/UnaryFunctionDispatch.h',
      'dest' : 'src/generated/UnaryFunctionDispatch.h',
      'next' : forall(one_to_n=[one_to_n], OP=functions, RVAL=rvals, T=['float']) },


    ]

pattern = re.compile(r'\/\*(.*?)\*\/', re.DOTALL)

for target in stuff:
    print target['src'], "=>", target['dest']
    ifile = open(target['src'])
    try:
        os.unlink(target['dest'])
    except:
        pass
    ofile = open(target['dest'], 'w')
    

    lines = ifile.read()

    print >>ofile, '//\n//\n// this is a generated file\n//\n//\n'
    for env in target['next']:
        env = dict(env)
        def r(x):
            matched = x.group(1)
            res = eval(matched, env)
            return str(res)

        print >>ofile, re.sub(pattern, r, lines)


