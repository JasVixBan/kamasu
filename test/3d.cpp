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
namespace bu = boost::numeric::ublas;

using namespace resophonic::kamasu;

TEST_GROUP();

TEST(check_ed)
{
  array<float> a = make_3d(10);
  check_3d(a, 10);
}

TEST(slice0)
{
  unsigned n = 13;
  array<float> a = make_3d(n);
  for (unsigned slicedim = 0; slicedim < n; slicedim++)
    {
      array<float> b = a.slice(index_range(_,_), index_range(_,_), index_range(slicedim));
  
      b.show();

      ENSURE_EQUAL(b.n_dims(), 2);
      ENSURE_EQUAL(b.dim(0), n);
      ENSURE_EQUAL(b.dim(1), n);

      for (unsigned j=0; j<n; j++)
	for (unsigned i=0; i<n; i++)
	  ENSURE_EQUAL(b(i,j), a(i,j,slicedim));
    }
}

TEST(slice0_reverse)
{
  unsigned n = 13;
  array<float> a = make_3d(n);
  for (unsigned slicedim = 0; slicedim < n; slicedim++)
    {
      array<float> b = a.slice(index_range(_,_,-1), index_range(_,_), index_range(slicedim));
  
      b.show();

      ENSURE_EQUAL(b.n_dims(), 2);
      ENSURE_EQUAL(b.dim(0), n);
      ENSURE_EQUAL(b.dim(1), n);

      for (unsigned j=0; j<n; j++)
	for (unsigned i=0; i<n; i++)
	  ENSURE_EQUAL(b(n-i-1,j), a(i,j,slicedim));
    }
}

TEST(slice1)
{
  unsigned n = 11;
  array<float> a = make_3d(n);
  for (unsigned slicedim = 0; slicedim < n; slicedim++)
    {
      array<float> b = a.slice(index_range(_,_), index_range(slicedim), index_range(_,_));
  
      b.show();

      ENSURE_EQUAL(b.n_dims(), 2);
      ENSURE_EQUAL(b.dim(0), n);
      ENSURE_EQUAL(b.dim(1), n);

      for (unsigned j=0; j<n; j++)
	for (unsigned i=0; i<n; i++)
	  ENSURE_EQUAL(b(i,j), a(i, slicedim, j));
    }
}

TEST(slice1_reverse)
{
  unsigned n = 11;
  array<float> a = make_3d(n);
  for (unsigned slicedim = 0; slicedim < n; slicedim++)
    {
      array<float> b = a.slice(index_range(_,_), index_range(slicedim), index_range(_,_,-1));
  
      b.show();

      ENSURE_EQUAL(b.n_dims(), 2);
      ENSURE_EQUAL(b.dim(0), n);
      ENSURE_EQUAL(b.dim(1), n);

      for (unsigned j=0; j<n; j++)
	for (unsigned i=0; i<n; i++)
	  ENSURE_EQUAL(b(i,n-j-1), a(i, slicedim, j));
    }
}

TEST(slice2)
{
  unsigned n = 17;
  array<float> a = make_3d(n);
  for (unsigned slicedim = 0; slicedim < n; slicedim++)
    {
      array<float> b = a.slice(index_range(slicedim), index_range(_,_), index_range(_,_));
  
      b.show();

      ENSURE_EQUAL(b.n_dims(), 2);
      ENSURE_EQUAL(b.dim(0), n);
      ENSURE_EQUAL(b.dim(1), n);

      for (unsigned j=0; j<n; j++)
	for (unsigned i=0; i<n; i++)
	  ENSURE_EQUAL(b(i,j), a(slicedim, i, j));
    }
}

TEST(slice2_reverse)
{
  unsigned n = 17;
  array<float> a = make_3d(n);
  for (unsigned slicedim = 0; slicedim < n; slicedim++)
    {
      array<float> b = a.slice(index_range(slicedim), index_range(_,_,-1), index_range(_,_));
  
      b.show();

      ENSURE_EQUAL(b.n_dims(), 2);
      ENSURE_EQUAL(b.dim(0), n);
      ENSURE_EQUAL(b.dim(1), n);

      for (unsigned j=0; j<n; j++)
	for (unsigned i=0; i<n; i++)
	  ENSURE_EQUAL(b(n-i-1,j), a(slicedim, i, j));
    }
}

TEST(double_reverse)
{
  unsigned n = 17;
  array<float> a = make_3d(n);
  for (unsigned slicedim = 0; slicedim < n; slicedim++)
    {
      array<float> b = a.slice(index_range(slicedim), index_range(_,_,-1), index_range(_,_,-1));
  
      b.show();

      ENSURE_EQUAL(b.n_dims(), 2);
      ENSURE_EQUAL(b.dim(0), n);
      ENSURE_EQUAL(b.dim(1), n);

      for (unsigned j=0; j<n; j++)
	for (unsigned i=0; i<n; i++)
	  ENSURE_EQUAL(b(n-i-1,n-j-1), a(slicedim, i, j));
    }
}
