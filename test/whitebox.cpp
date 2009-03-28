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

#include "cuda_runtime_api.h"
#include "cutil.h"

#include <vector>
#include <cassert>

namespace rk = resophonic::kamasu;

using namespace resophonic::kamasu;

#ifdef RESOPHONIC_KAMASU_DEBUG

TEST_GROUP();

TEST(copy_construct)
{
  testing::n_clones = 0;
  array<float> a(10);

  ENSURE_EQUAL(testing::n_clones, 0);

  array<float> b(a);

  ENSURE_EQUAL(testing::n_clones, 0);
  ENSURE_EQUAL(a.data(), b.data());
}

// question:
// semantics of b = a * 2;
// vs
// b = a;
// 

TEST(assign_op)
{
  testing::n_clones = 0;
  array<float> a(10);

  ENSURE_EQUAL(testing::n_clones, 0);

  array<float> b = a;

  ENSURE_EQUAL(testing::n_clones, 0);
  ENSURE_EQUAL(a.data(), b.data());
}

array<float> return_by_value()
{
  return array<float>(14, 7);
}

TEST(return_by_value)
{
  testing::n_clones = 0;
  array<float> a = return_by_value();
  ENSURE_EQUAL(testing::n_clones, 0);
}

TEST(assign_from_expression)
{
  testing::n_clones = 0;
  array<float> b = linspace<float>(0,10,11);
  ENSURE_EQUAL(b.rvalue(), false);
  ENSURE_EQUAL(testing::n_clones, 0);
  array<float> a = b * 2.0f;
  ENSURE_EQUAL(a.rvalue(), false);
  ENSURE_EQUAL(b.rvalue(), false);
  ENSURE_EQUAL(testing::n_clones, 1);
}

TEST(assign_from_expression_2)
{
  testing::n_clones = 0;
  array<float> b(2,2);
  array<float> c(2,2);
  ENSURE_EQUAL(testing::n_clones, 0);
  array<float> a = (b * 2.0f) * (c * 2.0f);
  ENSURE_EQUAL(testing::n_clones, 2);
}
 
TEST(slice_doesnt_copy)
{
  testing::n_clones = 0;
  testing::gpu_malloc = 0;
  array<float> a(2,2);
  
  ENSURE_EQUAL(testing::n_clones, 0);
  ENSURE_EQUAL(testing::gpu_malloc, 1);

  array<float> b = a.slice(index_range(_,_), index_range(0));

  ENSURE_EQUAL(testing::n_clones, 0);
  ENSURE_EQUAL(testing::gpu_malloc, 1);
}
 
TEST(forward_a_temp)
{
  testing::n_clones = 0;
  testing::gpu_malloc = 0;
  array<float> a(2), b(2);
  
  a = b * 2;

  ENSURE_EQUAL(testing::n_clones, 0);
  ENSURE_EQUAL(testing::gpu_malloc, 2);
}
 
TEST(linspace_rvalueref)
{
  array<float> a = linspace(0.0f, 10.0f, 11.0f);

}


#endif
