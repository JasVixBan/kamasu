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

void from_gpu_test(unsigned n, unsigned m)
{
  array<float> a(n, m);
  
  for (unsigned i=0; i<n; i++)
    for (unsigned j=0; j<m; j++)
      a(i,j) = i * m + j;

  bnu::matrix<float, bnu::column_major> fetched;
  a >> fetched;

  ENSURE_EQUAL(a.nd(), 2u);
  ENSURE_EQUAL(a.dim(0), fetched.size1());
  ENSURE_EQUAL(a.dim(1), fetched.size2());

  for (unsigned i=0; i<n; i++)
    for (unsigned j=0; j<m; j++)
      ENSURE_EQUAL(fetched(i,j), i * m + j);
    
}

void to_gpu_test(unsigned n, unsigned m)
{
  bnu::matrix<float, bnu::column_major> a(n, m);

  for (unsigned i=0; i<n; i++)
    for (unsigned j=0; j<m; j++)
      a(i,j) = i * m + j;

  array<float> put;

  put << a;

  ENSURE_EQUAL(put.nd(), 2u);
  ENSURE_EQUAL(put.dim(0), a.size1());
  ENSURE_EQUAL(put.dim(1), a.size2());

  for (unsigned i=0; i<n; i++)
    for (unsigned j=0; j<m; j++)
      //std::cout << i << "," << j << " == " << put(i,j) << " should be " << i*m+j << "\n";
      ENSURE_EQUAL(put(i,j), i * m + j);
}

#define MAKE_TEST(M, N)				\
  TEST(ublas_to_kamasu_##M##x##N)		\
  {						\
    to_gpu_test(M, N);				\
  }						\
  TEST(kamasu_to_ublas_##M##x##N)		\
  {						\
    from_gpu_test(M, N);			\
  }						\

MAKE_TEST(1,1);
MAKE_TEST(1,2);
MAKE_TEST(2,1);
MAKE_TEST(2,2);
MAKE_TEST(3,3);
MAKE_TEST(3,7);
MAKE_TEST(17,3);
MAKE_TEST(51,3);
MAKE_TEST(19,47);
MAKE_TEST(419,247);

