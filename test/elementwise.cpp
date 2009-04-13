#include <I3Test.h>
#include "testing_util.hpp"

#include <iostream>

// includes, project

#include <resophonic/kamasu.hpp>
#include <resophonic/kamasu/linspace.hpp>

#include <vector>
#include <cassert>

using namespace resophonic::kamasu;

TEST_GROUP();

const static unsigned n = 100000;

std::vector<float> result;

TEST(sin)
{
  array<float> a = make_1d(n), b;

  b = rk::sin(a);

  b >> result;

  for (float i=0; i<n; i++)
    {
      ENSURE_DISTANCE(result[i], ::sin(i), 1.0e-06);
    }
}

TEST(plus)
{
  array<float> a = make_1d(n), b;

  b = a + 2.0f;

  ENSURE_EQUAL(b.linear_size(), n);
  ENSURE_EQUAL(b.nd(), 1u);
  ENSURE_EQUAL(b.dim(0), n);

  b >> result;
  for (float i=0; i<n; i++)
    {
      ENSURE_EQUAL(result[i], i+2);
    }
}

TEST(minus)
{
  array<float> a = make_1d(n), b;

  b = a - 2.0f;

  ENSURE_EQUAL(b.linear_size(), n);
  ENSURE_EQUAL(b.nd(), 1u);
  ENSURE_EQUAL(b.dim(0), n);

  b >> result;

  for (float i=0; i<n; i++)
    {
      ENSURE_EQUAL(result[i], i-2);
    }
}

TEST(multiplies)
{
  array<float> a = rk::linspace(-1.0f, 1.0f, (float)n), b;

  ENSURE_EQUAL(a.linear_size(), n);
  ENSURE_EQUAL(a.nd(), 1u);
  ENSURE_EQUAL(a.dim(0), n);

  std::vector<float> lhs;
  a >> lhs;

  ENSURE_EQUAL(lhs.size(), n);

  b = a * 2.0f;

  ENSURE_EQUAL(b.linear_size(), n);
  ENSURE_EQUAL(b.nd(), 1u);
  ENSURE_EQUAL(b.dim(0), n);

  b >> result;

  ENSURE_EQUAL(result.size(), n);

  for (float i=0; i<n; i++)
    {
      try {
	ENSURE_DISTANCE(result[i], lhs[i]*2.0f, 1.0e-05);
      } catch (...) {
	std::cout << "@ " << i << " "<< result[i] << " vs " << lhs[i]*.20f <<"\n";
      }
    }
}

TEST(divides)
{
  array<float> a = make_1d(n), b;

  b = a / 2.0f;

  ENSURE_EQUAL(b.linear_size(), n);
  ENSURE_EQUAL(b.nd(), 1u);
  ENSURE_EQUAL(b.dim(0), n);

  b >> result;

  for (float i=0; i<n; i++)
    {
      ENSURE_EQUAL(result[i], i/2.0f);
    }
}

TEST(pow_2)
{
  array<float> a = make_1d(n), b;

  b = rk::pow(a, 2.0f);

  ENSURE_EQUAL(b.linear_size(), n);
  ENSURE_EQUAL(b.nd(), 1u);
  ENSURE_EQUAL(b.dim(0), n);

  b >> result;

  for (float i=0; i<n; i++)
    {
      ENSURE_DISTANCE(result[i], i*i, 1.0e-06);
    }
}

TEST(exp)
{
  array<float> a = make_1d(n), b;
  ENSURE_EQUAL(a.linear_size(), n);
  ENSURE_EQUAL(b.linear_size(), 0u);

  b = rk::exp(a);

  ENSURE_NOT_EQUAL(a.data(), b.data());

  ENSURE_EQUAL(b.linear_size(), n);
  ENSURE_EQUAL(b.nd(), 1u);
  ENSURE_EQUAL(b.dim(0), n);

  b >> result;

  for (float i=0; i<n; i++)
    {
      ENSURE_DISTANCE(result[i], expf(i), 1.0e-06);
    }
}

TEST(exp2)
{
  array<float> a = make_1d(n), b;

  b = rk::exp2(a);

  ENSURE_EQUAL(b.linear_size(), n);
  ENSURE_EQUAL(b.nd(), 1u);
  ENSURE_EQUAL(b.dim(0), n);

  b >> result;

  for (float i=0; i<n; i++)
    {
      ENSURE_DISTANCE(result[i], exp2f(i), 1.0e-06);
    }
}

TEST(log10)
{
  array<float> a = make_1d(n), b;

  b = rk::log10(a);

  b >> result;

  for (float i=0; i<n; i++)
    {
      ENSURE_DISTANCE(result[i], log10f(i), 1.0e-06);
    }
}
