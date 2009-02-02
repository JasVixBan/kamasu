print 'YAH OPS TEST'
import unittest
from nose.tools import *
from resophonic import kamasu as k

class Test(unittest.TestCase):
    
    def setUp(self):
        self.a = k.array(10)
        for i in range(10):
            self.a[i] = i

    def test(self):
        b = self.a * 2.0
        print "b is", b
        for i in range(10):
            assert_equal(b[i], i*2)
            assert_equal(self.a[i], i)

        assert_equal(type(b), k.array)
            
    def test2(self):
        b = ((self.a * 2.0) * 2.0) * 2.0
        print "b is", b
        for i in range(10):
            assert_equal(b[i], i*8)
            assert_equal(self.a[i], i)

        assert_equal(type(b), k.array)
            
