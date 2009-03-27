#include <I3Test.h>
#include "testing_util.hpp"

#include <iostream>

// includes, project

#include <resophonic/kamasu.hpp>

#include <vector>
#include <cassert>

using namespace resophonic::kamasu;

TEST_GROUP();

TEST(sin)
{
  unsigned n = 1000;
  array<float> a = make_1d(n), b;

  b = rk::sin(a);

  for (float i=0; i<n; i++)
    {
      ENSURE_EQUAL(a(i), i);
      ENSURE_DISTANCE(b(i), ::sin(i), ::sin(i) * 10e-07);
    }
}


TEST(plus)
{
  unsigned n = 10000;
  array<float> a = make_1d(n), b;

  b = a + 2.0f;

  ENSURE_EQUAL(b.linear_size(), n);
  ENSURE_EQUAL(b.nd(), 1);
  ENSURE_EQUAL(b.dim(0), n);

  for (float i=0; i<n; i++)
    {
      ENSURE_EQUAL(a(i), i);
      ENSURE_EQUAL(b(i), i+2);
    }
}

TEST(minus)
{
  unsigned n = 10000;
  array<float> a = make_1d(n), b;

  b = a - 2.0f;

  ENSURE_EQUAL(b.linear_size(), n);
  ENSURE_EQUAL(b.nd(), 1);
  ENSURE_EQUAL(b.dim(0), n);

  for (float i=0; i<n; i++)
    {
      ENSURE_EQUAL(a(i), i);
      ENSURE_EQUAL(b(i), i-2);
    }
}

TEST(multiplies)
{
  unsigned n = 10000;
  array<float> a = make_1d(n), b;

  b = a * 2.0f;

  ENSURE_EQUAL(b.linear_size(), n);
  ENSURE_EQUAL(b.nd(), 1);
  ENSURE_EQUAL(b.dim(0), n);

  for (float i=0; i<n; i++)
    {
      ENSURE_EQUAL(a(i), i);
      ENSURE_EQUAL(b(i), i*2);
    }
}

TEST(divides)
{
  unsigned n = 10000;
  array<float> a = make_1d(n), b;

  b = a / 2.0f;

  ENSURE_EQUAL(b.linear_size(), n);
  ENSURE_EQUAL(b.nd(), 1);
  ENSURE_EQUAL(b.dim(0), n);

  for (float i=0; i<n; i++)
    {
      ENSURE_EQUAL(a(i), i);
      ENSURE_EQUAL(b(i), i/2.0f);
    }
}

TEST(pow_2)
{
  unsigned n = 10000;
  array<float> a = make_1d(n), b;

  b = rk::pow(a, 2.0f);

  ENSURE_EQUAL(b.linear_size(), n);
  ENSURE_EQUAL(b.nd(), 1);
  ENSURE_EQUAL(b.dim(0), n);

  for (float i=0; i<n; i++)
    {
      ENSURE_EQUAL(a(i), i);
      ENSURE_DISTANCE(b(i), i*i, i *i * 10e-07);
    }
}

TEST(exp)
{
  unsigned n = 10000;
  array<float> a = make_1d(n), b;

  b = rk::exp(a);

  ENSURE_EQUAL(b.linear_size(), n);
  ENSURE_EQUAL(b.nd(), 1);
  ENSURE_EQUAL(b.dim(0), n);

  for (float i=0; i<n; i++)
    {
      ENSURE_EQUAL(a(i), i);
      ENSURE_DISTANCE(b(i), expf(i), b(i) * 10e-07);
    }
}

TEST(exp2)
{
  unsigned n = 10000;
  array<float> a = make_1d(n), b;

  b = rk::exp2(a);

  ENSURE_EQUAL(b.linear_size(), n);
  ENSURE_EQUAL(b.nd(), 1);
  ENSURE_EQUAL(b.dim(0), n);

  for (float i=0; i<n; i++)
    {
      ENSURE_EQUAL(a(i), i);
      ENSURE_DISTANCE(b(i), exp2f(i), exp2f(i) * 10e-07);
    }
}

TEST(log10)
{
  unsigned n = 1000;
  array<float> a = make_1d(n), b;

  b = rk::log10(a);

  for (float i=0; i<n; i++)
    {
      ENSURE_EQUAL(a(i), i);
      ENSURE_DISTANCE(b(i), log10f(i), log10f(i) * 10e-07);
    }
}

TEST(wontcompile)
{
  int n= 10;
  array<float> a = make_1d(n);
  //  a = rk::erf(a*3.0f, 4.0f);
}

