import unittest
from nose.tools import *
from resophonic import kamasu as k

def dims_impl(n,dim):
    arr = k.array(*([dim]*n))
    assert_equals(arr.n_dims(), n)
    assert_equals(arr.linear_size(), dim**n)

def test():
    for dim in [2,3,4]:
        for i in range(1,6):
            yield dims_impl, i, dim
    
