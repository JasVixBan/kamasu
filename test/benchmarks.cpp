#include <I3Test.h>
#include "testing_util.hpp"

#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

// includes, project

#include <resophonic/kamasu.hpp>
#include <resophonic/kamasu/mirror.hpp>

#include <vector>
#include <cassert>

namespace ks = resophonic::kamasu;

using namespace resophonic::kamasu;

TEST_GROUP();

TEST(1d_slice)
{
  unsigned n = 2500;

  array<float> a(n);

  for (int j=0; j<100; j++)
    {
      std::cout << j << "% \r";
      for (int i=0; i<n/2 -1 ; i++)
	{
	  std::cout.flush();
	  a.slice(index_range(i, i+n/2));
	}
    }
	
}
