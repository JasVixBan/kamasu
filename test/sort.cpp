#include <I3Test.h>
#include "testing_util.hpp"

#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <resophonic/kamasu.hpp>
#include <resophonic/kamasu/dot.hpp>
#include <resophonic/kamasu/linspace.hpp>
#include <resophonic/kamasu/testing.hpp>
#include <resophonic/kamasu/sort.hpp>

namespace rk = resophonic::kamasu;

TEST_GROUP();

TEST(sort)
{
  const unsigned n = 15;
  rk::array<float> a(n);

  for (unsigned i=0; i<n; i++)
    a(i) = n-i;

  rk::sort(a);

  for (unsigned i=0; i<n-1; i++)
    {
      //      ENSURE(a(i) <= a(i+1));
      std::cout << a(i) << " ";
    }
}
