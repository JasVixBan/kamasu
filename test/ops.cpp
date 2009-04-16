#include <I3Test.h>
#include "testing_util.hpp"

#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

// includes, project

#include <resophonic/kamasu.hpp>
#include <resophonic/kamasu/dot.hpp>
#include <resophonic/kamasu/linspace.hpp>

#include "cuda_runtime_api.h"

#include <vector>
#include <cassert>

namespace ks = resophonic::kamasu;
namespace bu = boost::numeric::ublas;

using namespace resophonic::kamasu;

TEST_GROUP();


void test_multiplies(unsigned n)
{
  array<float> a = make_1d(n), b;
  ENSURE_EQUAL(a.linear_size(), n);
  ENSURE_EQUAL(a.nd(), 1u);
  ENSURE_EQUAL(a.dim(0), n);

  b = a * 2.0f;

  ENSURE_EQUAL(b.linear_size(), n);
  ENSURE_EQUAL(b.nd(), 1u);
  ENSURE_EQUAL(b.dim(0), n);

  for (unsigned i=0; i<n; i++)
    {
      ENSURE_EQUAL(a(i), i);
      ENSURE_EQUAL(b(i), i*2.0f);
    }
}

#define TEST_MULT_N(N) TEST(1d_multiplies_##N) { test_multiplies(N); }

TEST_MULT_N(1);
TEST_MULT_N(2);
TEST_MULT_N(127);
TEST_MULT_N(128);
TEST_MULT_N(129);
TEST_MULT_N(447);
TEST_MULT_N(511);
TEST_MULT_N(512);
TEST_MULT_N(513);
TEST_MULT_N(1023);
TEST_MULT_N(1024);
TEST_MULT_N(1025);
TEST_MULT_N(2047);
TEST_MULT_N(2048);
TEST_MULT_N(2049);
TEST_MULT_N(4100);
//TEST_MULT_N(100000);
//TEST_MULT_N(1000000);


TEST(m1_plus)
{
  array<float> a = make_1d(10), b;

  b = a + 2.0f;

  for (unsigned i=0; i<10; i++)
    ENSURE_EQUAL(b(i), i+2.0f);
}

TEST(m1_minus)
{
  array<float> a = make_1d(10), b;

  b = a - 2.0f;

  for (unsigned i=0; i<10; i++)
    ENSURE_EQUAL(b(i), i-2.0f);
}

TEST(m1_divides)
{
  array<float> a = make_1d(10), b;

  b = a / 2.0f;

  for (unsigned i=0; i<10; i++)
    ENSURE_EQUAL(b(i), i/2.0f);
}

void test_stride(unsigned length, int stride)
{
  array<float> a = make_1d(length), b, c;

  b = a(index_range(0, length, stride));

  ENSURE_EQUAL(b.nd(), 1u);
  ENSURE_EQUAL(b.stride(0), stride);
  //  ENSURE_EQUAL(b.dim(0), slicedim);

  unsigned slicedim = b.dim(0);

  float factor = 0.5;

  c = b + factor;

  ENSURE_EQUAL(c.nd(), 1u);
  ENSURE_EQUAL(c.stride(0), stride);

  for (unsigned i=0; i<length; i++)
    ENSURE_EQUAL(a(i), i);

  for (unsigned i=0; i<slicedim; i++)
    ENSURE_EQUAL(b(i), i*stride);

  for (unsigned i=0; i<slicedim; i++)
    ENSURE_EQUAL(c(i), b(i)+factor);
}

#define TEST_STRIDE(LEN, STRIDE)					\
  TEST(test_len_##LEN##_stride_##STRIDE) {				\
    test_stride(LEN, STRIDE);						\
  }

TEST_STRIDE(22,2);
TEST_STRIDE(151,5);
TEST_STRIDE(8111,3);
TEST_STRIDE(1997,5);
TEST_STRIDE(5563,5);
TEST_STRIDE(8111,5);
TEST_STRIDE(2269,11);
TEST_STRIDE(14947, 7);
TEST_STRIDE(51487, 11);

TEST(m2_stride)
{
  array<float> a = make_4x5(), b, c;

  // slice last row   [ 4 12 20 ]
  b = a(index_range(3), index_range(0, 5, 2));

  ENSURE_EQUAL(b(0), 4.0f);
  ENSURE_EQUAL(b(1), 12.0f);
  ENSURE_EQUAL(b(2), 20.0f);

  c = b + 19.5f;

  check_unchanged_4x5(a);

  ENSURE_EQUAL(b(0), 4.0f);
  ENSURE_EQUAL(b(1), 12.0f);
  ENSURE_EQUAL(b(2), 20.0f);

  ENSURE_EQUAL(c(0), 23.5f);
  ENSURE_EQUAL(c(1), 31.5f);
  ENSURE_EQUAL(c(2), 39.5f);

}

TEST(m2_2d_stride)
{
  array<float> a = make_4x5(), b, c;

  // slice to
  // 1 9 17
  // 3 11 19
  b = a(index_range(0,4,2), index_range(0, 5, 2));

  for (unsigned i=0; i<b.dim(0); i++)
    for (unsigned j=0; j<b.dim(1); j++)
      {
	log_trace("b(%d,%d) = %f", i % j % b(i,j));
	ENSURE_EQUAL(b(i,j), a(i*2, j*2));
      }

  float trm = 100.0f;

  c = b + trm;

  ENSURE_EQUAL(c.nd(), b.nd());
  ENSURE_EQUAL(c.factor(0), b.factor(0));
  ENSURE_EQUAL(c.factor(1), b.factor(1));

  ENSURE_EQUAL(c.dim(0), b.dim(0));
  ENSURE_EQUAL(c.dim(1), b.dim(1));

  ENSURE_EQUAL(c.stride(0), b.stride(0));
  ENSURE_EQUAL(c.stride(1), b.stride(1));

  ENSURE_NOT_EQUAL(c.data(), b.data());

  check_unchanged_4x5(a);

  for (unsigned i=0; i<c.dim(0); i++)
    for (unsigned j=0; j<c.dim(1); j++)
      log_trace("c(%d,%d) = %f", i % j % c(i,j));


  ENSURE_EQUAL(b(0,0), 1.0f);
  ENSURE_EQUAL(b(0,1), 9.0f);
  ENSURE_EQUAL(b(0,2), 17.0f);
  ENSURE_EQUAL(b(1,0), 3.0f);
  ENSURE_EQUAL(b(1,1), 11.0f);
  ENSURE_EQUAL(b(1,2), 19.0f);

  ENSURE_EQUAL(c(0,0), b(0,0) + trm);
  ENSURE_EQUAL(c(1,0), b(1,0) + trm);
  ENSURE_EQUAL(c(1,1), b(1,1) + trm);
  ENSURE_EQUAL(c(1,2), b(1,2) + trm);

  ENSURE_EQUAL(c(0,1), b(0,1) + trm);
  ENSURE_EQUAL(c(0,2), b(0,2) + trm);
}


TEST(multiplies)
{
  array<float> a = make_4x5();

  array<float> b;
  b = a * 2.0f;

  ENSURE_EQUAL(a(0,0), 1.0f);
  ENSURE_EQUAL(a(1,2), 10.0f);
  ENSURE_EQUAL(a(3,0), 4.0f);
  ENSURE_EQUAL(a(0,4), 17.0f);
  ENSURE_EQUAL(a(3,4), 20.0f);

  ENSURE_EQUAL(b(0,0), 2.0f);
  ENSURE_EQUAL(b(1,2), 20.0f);
  ENSURE_EQUAL(b(3,0), 8.0f);
  ENSURE_EQUAL(b(0,4), 34.0f);
  ENSURE_EQUAL(b(3,4), 40.0f);
}

TEST(plus)
{
  array<float> a = make_4x5();

  array<float> b;

  b = a + 2.5f;

  ENSURE_EQUAL(a(0,0), 1.0f);
  ENSURE_EQUAL(a(1,2), 10.0f);
  ENSURE_EQUAL(a(3,0), 4.0f);
  ENSURE_EQUAL(a(0,4), 17.0f);
  ENSURE_EQUAL(a(3,4), 20.0f);

  ENSURE_EQUAL(b(0,0), 3.5f);
  ENSURE_EQUAL(b(1,2), 12.5f);
  ENSURE_EQUAL(b(3,0), 6.5f);
  ENSURE_EQUAL(b(0,4), 19.5f);
  ENSURE_EQUAL(b(3,4), 22.5f);
}

TEST(dot_with_mul)
{
  //    0   1   2   3   4   5   6   7   8   9
  // *  9   8   7   6   5   4   3   2   1   0
  // ----------------------------------------------
  //    0   8  14  18  20  20  18  14   8   0 == 120
  unsigned n = 10;
  array<float> a(n), b(n);
  for (unsigned i=0; i<n; i++)
    {
      a(i) = i;
      b(i) = n-1-i;
    }
  for (unsigned i=0; i<n; i++)
    {
      ENSURE_EQUAL(a(i), i);
      ENSURE_EQUAL(b(i), n-i-1);
    }

  float r = rk::dot(a*-1.0f, b*-1.0f);
  log_trace("dot prod is %f",  r);
  ENSURE_EQUAL(r, 120.0f);
}

TEST(dot_half_mul)
{
  //    0   1   2   3   4   5   6   7   8   9
  // *  9   8   7   6   5   4   3   2   1   0
  // ----------------------------------------------
  //    0   8  14  18  20  20  18  14   8   0 == 120
  unsigned n = 10;
  array<float> a(n), b(n);
  for (unsigned i=0; i<n; i++)
    {
      a(i) = i;
      b(i) = n-1-i;
    }
  for (unsigned i=0; i<n; i++)
    {
      ENSURE_EQUAL(a(i), i);
      ENSURE_EQUAL(b(i), n-i-1);
    }

  float r = rk::dot(a, b*-1.0f);
  log_trace("dot prod is %f",  r);
  ENSURE_EQUAL(r, -120.0f);
}


TEST(dot)
{
  //    0   1   2   3   4   5   6   7   8   9
  // *  9   8   7   6   5   4   3   2   1   0
  // ----------------------------------------------
  //    0   8  14  18  20  20  18  14   8   0 == 120
  unsigned n = 10;
  array<float> a(n), b(n);
  for (unsigned i=0; i<n; i++)
    {
      a(i) = i;
      b(i) = n-1-i;
    }
  for (unsigned i=0; i<n; i++)
    {
      ENSURE_EQUAL(a(i), i);
      ENSURE_EQUAL(b(i), n-i-1);
    }

  float dp = rk::dot(a, b);
  log_trace("dot prod is %f",  dp);
  ENSURE_EQUAL(dp, 120.0f);
}

TEST(plus_assign)
{
  array<float> a = make_4x5();

  array<float> b = make_4x5();
  b += a;

  ENSURE_NOT_EQUAL(b.data(), a.data());
  ENSURE_EQUAL(a(0,0), 1.0f);
  ENSURE_EQUAL(a(1,2), 10.0f);
  ENSURE_EQUAL(a(3,0), 4.0f);
  ENSURE_EQUAL(a(0,4), 17.0f);
  ENSURE_EQUAL(a(3,4), 20.0f);

  ENSURE_EQUAL(b(3,4), 40.0f);
  ENSURE_EQUAL(b(0,0), 2.0f);
  ENSURE_EQUAL(b(1,2), 20.0f);
  ENSURE_EQUAL(b(3,0), 8.0f);
  ENSURE_EQUAL(b(0,4), 34.0f);
}

TEST(plus_assign_slice)
{
  array<float> a = linspace<float>(0,99,100);
  array<float> a2 = linspace<float>(0,9,10);

  array<float> b = a(index_range(10,20));
  b += a2;

  for (int i=0; i<99; i++)
    {
      if (i>=10 && i<20)
	{
	  ENSURE_EQUAL(a(i), i + i-10);
	}
      else
	{
	  ENSURE_EQUAL(a(i), i);
	}
    }
}

template <typename Expr>
void checkexpr(Expr const &expr)
{
  BOOST_MPL_ASSERT((boost::proto::matches<Expr, resophonic::kamasu::UnaryFunctionCalls>));
}

TEST(shits_and_giggles)
{
  array<float> a;
  checkexpr(rk::sin(a));
}
