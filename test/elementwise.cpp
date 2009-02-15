#include <I3Test.h>
#include "testing_util.hpp"

#include <iostream>

// includes, project

#include <resophonic/kamasu.hpp>

#include <vector>
#include <cassert>

using namespace resophonic::kamasu;

TEST_GROUP();

TEST(pow_2)
{
  unsigned n = 100;
  array<float> a = make_1d(n), b;

  b = rk::pow(a, 2.0f);

  ENSURE_EQUAL(b.linear_size(), n);
  ENSURE_EQUAL(b.n_dims(), 1);
  ENSURE_EQUAL(b.dim(0), n);

  for (float i=0; i<n; i++)
    {
      ENSURE_EQUAL(a(i), i);
      ENSURE_DISTANCE(b(i), i*i, i *i * 0.000001);
    }
}
