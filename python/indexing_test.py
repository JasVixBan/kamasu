import unittest
from nose.tools import *
from resophonic import kamasu as k

primes = [3,7] # ,11,13,17,51]

def basic(n):
    arr = k.array(n)
    assert_equals(arr.n_dims(), 1)
    for i in range(n):
        arr[i] = i * 0.5;
    
    for i in range(n):
        assert_equals(arr[i], i * 0.5)

def basic_test1d():
    for i in primes:
        for n in range(1,5):
            yield basic, i*n*10

def basic_2d(n):
    arr = k.array(n,n)
    assert_equals(arr.n_dims(), 2)

    for i in range(n):
        for j in range(n):
            arr[i,j] = i*n + j;

    for i in range(n):
        for j in range(n):
            assert_equals(arr[i,j], i*n + j)


def basic_test_2d():
    for i in primes:
        for n in range(1,5):
            yield basic_2d, i*n

