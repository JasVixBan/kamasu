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

#include "cuda_runtime_api.h"
#include "cutil.h"

#include <vector>
#include <cassert>

namespace ks = resophonic::kamasu;
namespace bnu = boost::numeric::ublas;

using namespace resophonic::kamasu;

TEST_GROUP();

void from_gpu_test(unsigned n, unsigned m, unsigned seed)
{
  array<float> a(n, m);
  
  for (int i=0; i<n; i++)
    for (int j=0; j<m; j++)
      a(i,j) = i * m + j;

  bnu::matrix<float> fetched;
  a >> fetched;

  ENSURE_EQUAL(a.n_dims(), 2);
  ENSURE_EQUAL(a.dim(0), fetched.size1());
  ENSURE_EQUAL(a.dim(1), fetched.size2());

  for (int i=0; i<n; i++)
    for (int j=0; j<m; j++)
      ENSURE_EQUAL(fetched(i,j), i * m + j);
    
}

void to_gpu_test(unsigned n, unsigned m, unsigned seed)
{
  bnu::matrix<float> a(n, m);

  for (int i=0; i<n; i++)
    for (int j=0; j<m; j++)
      a(i,j) = i * m + j;

  array<float> put;

  put << a;

  ENSURE_EQUAL(put.n_dims(), 2);
  ENSURE_EQUAL(put.dim(0), a.size1());
  ENSURE_EQUAL(put.dim(1), a.size2());

  for (int i=0; i<n; i++)
    for (int j=0; j<m; j++)
      ENSURE_EQUAL(put(i,j), i * m + j);
}

#define MAKE_TEST(M, N, SEED) \
  TEST(ublas_to_kamasu_##M##x##N##_seed##SEED)				\
  {									\
    to_gpu_test(M, N, SEED);						\
  }									\
  TEST(kamasu_to_ublas_##M##x##N##_seed##SEED)				\
  {									\
    from_gpu_test(M, N, SEED);						\
  }									\

MAKE_TEST(1,1,1);
MAKE_TEST(1,2,1);
MAKE_TEST(2,1,1);
MAKE_TEST(2,2,1);
MAKE_TEST(3,7,1);
MAKE_TEST(2,2,2);
MAKE_TEST(3,3,3);
MAKE_TEST(17,3,17);
MAKE_TEST(51,3,0);
MAKE_TEST(19,47,0);
MAKE_TEST(419,247,0);

