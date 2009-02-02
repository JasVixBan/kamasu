import unittest
from nose.tools import *
from resophonic import kamasu as k

class Test_1d(unittest.TestCase):
    
    def setUp(self):
        self.a = k.array(10)
        for i in range(10):
            self.a[i] = i

    def test(self):
        b = self.a[1:9]
        assert_equal(b.n_dims(), 1)
        assert_equal(b.dim(0), 8)

        for i in range(8):
            assert_equal(b[i], i + 1.0)

    def test_reverse(self):
        b = self.a[8:0:-1]
        assert_equal(b.n_dims(), 1)
        assert_equal(b.dim(0), 8)

        for i in range(8):
            print ">>>", i, b[i]
            assert_equal(b[i], 8.0 - i)

    def test_reverse2(self):
        b = self.a[::-1]
        assert_equal(b.n_dims(), 1)
        assert_equal(b.dim(0), 10)

        for i in range(10):
            assert_equal(b[i], 9.0 - i)

    def test_half_reverse(self):
        b = self.a[5::-1]
        assert_equal(b.n_dims(), 1)
        assert_equal(b.dim(0), 6)

        for i in range(6):
            print ">>>", i, b[i]
            assert_equal(b[i], 5.0 - i)

    def test_half(self):
        b = self.a[5:]
        assert_equal(b.n_dims(), 1)
        assert_equal(b.dim(0), 5)

        for i in range(5):
            print "test_half >>>", i, b[i]
            assert_equal(b[i], 5.0 + i)

    def test_half2(self):
        b = self.a[:5]
        assert_equal(b.n_dims(), 1)
        assert_equal(b.dim(0), 5)

        for i in range(5):
            print __name__, i, b[i]
            assert_equal(b[i], i)

    def test_reverse_doublestep(self):
        b = self.a[::-2]
        assert_equal(b.n_dims(), 1)
        assert_equal(b.dim(0), 5)

        for i in range(5):
            print "test_reverse_doublestep >>>", i, b[i]
            assert_equal(b[i], 9.0 - 2*i)

class Test2d(unittest.TestCase):
    
    def setUp(self):
        n = 10
        a = k.array(n,n)
        counter = 0
        assert_equal(a.n_dims(), 2)
        assert_equal(a.dim(0), n)
        assert_equal(a.dim(1), n)
        for j in range(n):
            for i in range(n):
                a[i,j] = counter
                assert_equal(j*10 + i, counter)
                counter += 1
        self.n = n
        self.a = a
        
    def test(self):
        b = self.a[1:9, 1:9]
        assert_equal(b.n_dims(), 2)
        assert_equal(b.dim(0), 8)
        assert_equal(b.dim(1), 8)
 
        for j in range(8):
            for i in range(8):
                assert_equal(b[i,j], self.a[i+1, j+1])

    def test_copyslice(self):
        b = self.a[:,:]
        assert_equal(b.n_dims(), 2)
        assert_equal(b.dim(0), 10)
        assert_equal(b.dim(1), 10)
 
        for j in range(10):
            for i in range(10):
                assert_equal(b[i,j], self.a[i,j])

    def test_reverse(self):
        b = self.a[4,:]
        assert_equal(b.n_dims(), 1)
        assert_equal(b.dim(0), 10)
         
        for i in range(10):
            print ">>>", i, b[i]
            assert_equal(b[i], self.a[4,i])
             
    def test_reverse2(self):
        b = self.a[5,::-1]
        assert_equal(b.n_dims(), 1)
        assert_equal(b.dim(0), 10)
 
        for i in range(10):
            assert_equal(b[i], self.a[5, 9-i])

    def test_reverse2b(self):
        b = self.a[::-1,5]
        assert_equal(b.n_dims(), 1)
        assert_equal(b.dim(0), 10)
 
        for i in range(10):
            assert_equal(b[i], self.a[9-i,5])

    def test_double_reverse(self):
        b = self.a[::-1,::-1]
        assert_equal(b.n_dims(), 2)
        assert_equal(b.dim(0), 10)
        assert_equal(b.dim(1), 10)
 
        for i in range(10):
            for j in range(10):
                assert_equal(b[i,j], self.a[9-i, 9-j])

    def test_double_reverse2(self):
        b = self.a[::-2,::-2]
        assert_equal(b.n_dims(), 2)
        assert_equal(b.dim(0), 5)
        assert_equal(b.dim(1), 5)
 
        for i in range(5):
            for j in range(5):
                print "%d,%d => %d,%d" % (i,j,9-i*2,9-j*2)
                assert_equal(b[i,j], self.a[9-i*2, 9-j*2])
 
#     def test_half_reverse(self):
#         b = self.a[5::-1]
#         assert_equal(b.n_dims(), 1)
#         assert_equal(b.dim(0), 6)
# 
#         for i in range(6):
#             print ">>>", i, b[i]
#             assert_equal(b[i], 5.0 - i)
# 
#     def test_half(self):
#         b = self.a[5:]
#         assert_equal(b.n_dims(), 1)
#         assert_equal(b.dim(0), 5)
# 
#         for i in range(5):
#             print "test_half >>>", i, b[i]
#             assert_equal(b[i], 5.0 + i)
# 
#     def test_half2(self):
#         b = self.a[:5]
#         assert_equal(b.n_dims(), 1)
#         assert_equal(b.dim(0), 5)
# 
#         for i in range(5):
#             print __name__, i, b[i]
#             assert_equal(b[i], i)
# 
#     def test_reverse_doublestep(self):
#         b = self.a[::-2]
#         assert_equal(b.n_dims(), 1)
#         assert_equal(b.dim(0), 5)
# 
#         for i in range(5):
#             print "test_reverse_doublestep >>>", i, b[i]
#             assert_equal(b[i], 9.0 - 2*i)








