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

TEST(zero_dim_is_illegal)
{
  ks::array<float> a(3,3,0,3);
}

#define VALUE(Z, N, TEXT) TEXT
#define LOOPVAR(Z, N, LOOPEND) for (unsigned var##N = 0; var##N < LOOPEND; var##N++)

#define NDIM_SHAPE_CONSTRUCTOR_TEST(Z, N, DATA)				\
  TEST(vararg_basics_test_ ## N ## d_x_## DATA ##d)			\
  {									\
    ks::array<float> a(BOOST_PP_ENUM(N, VALUE, DATA));			\
    float val = 0.5;							\
    BOOST_PP_REPEAT(N, LOOPVAR, DATA)					\
      {									\
	a(BOOST_PP_ENUM_PARAMS(N, var)) = ++val;			\
      }									\
    val = 0.5;								\
    BOOST_PP_REPEAT(N, LOOPVAR, DATA)					\
      {									\
	ENSURE_EQUAL(a(BOOST_PP_ENUM_PARAMS(N, var)), ++val);		\
      }									\
    ks::array<float> b;							\
    b = a.copy();							\
    val = 0.5;								\
    BOOST_PP_REPEAT(N, LOOPVAR, DATA)					\
      {									\
	ENSURE_EQUAL(b(BOOST_PP_ENUM_PARAMS(N, var)), ++val);		\
      }									\
    val = 1.5;								\
    BOOST_PP_REPEAT(N, LOOPVAR, DATA)					\
      {									\
	b(BOOST_PP_ENUM_PARAMS(N, var)) = ++val;			\
      }									\
    val = 0.5;								\
    BOOST_PP_REPEAT(N, LOOPVAR, DATA)					\
      {									\
	ENSURE_EQUAL(a(BOOST_PP_ENUM_PARAMS(N, var)), ++val);		\
      }									\
  }

// BOOST_PP_REPEAT_FROM_TO(1, KAMASU_MAX_ARRAY_DIM, NDIM_SHAPE_CONSTRUCTOR_TEST, 2);
// BOOST_PP_REPEAT_FROM_TO(1, KAMASU_MAX_ARRAY_DIM, NDIM_SHAPE_CONSTRUCTOR_TEST, 3);

NDIM_SHAPE_CONSTRUCTOR_TEST(~, 1, 100);
NDIM_SHAPE_CONSTRUCTOR_TEST(~, 4, 10);
//NDIM_SHAPE_CONSTRUCTOR_TEST(~, 7, 3);

#define PUSHBACK(Z, N, DATA) shape.push_back(DATA);

#define NDIM_STDVECTOR_CONSTRUCTOR_TEST(Z, N, DATA)			\
  TEST(stdvector_basics_test_ ## N ## d_x_## DATA ##d)			\
  {									\
    std::vector<std::size_t> shape;					\
    BOOST_PP_REPEAT(N, PUSHBACK, DATA);					\
    ks::array<float> a(shape);						\
    float val = 0.5;							\
    BOOST_PP_REPEAT(N, LOOPVAR, DATA)					\
      {									\
	a(BOOST_PP_ENUM_PARAMS(N, var)) = ++val;			\
      }									\
    val = 0.5;								\
    BOOST_PP_REPEAT(N, LOOPVAR, DATA)					\
      {									\
	ENSURE_EQUAL(a(BOOST_PP_ENUM_PARAMS(N, var)), ++val);		\
      }									\
    									\
    ks::array<float> b;							\
    b = a.copy();							\
    val = 0.5;								\
    BOOST_PP_REPEAT(N, LOOPVAR, DATA)					\
      {									\
	ENSURE_EQUAL(b(BOOST_PP_ENUM_PARAMS(N, var)), ++val);		\
      }									\
    val = 1.5;								\
    BOOST_PP_REPEAT(N, LOOPVAR, DATA)					\
      {									\
	b(BOOST_PP_ENUM_PARAMS(N, var)) = ++val;			\
      }									\
    val = 0.5;								\
    BOOST_PP_REPEAT(N, LOOPVAR, DATA)					\
      {									\
	ENSURE_EQUAL(a(BOOST_PP_ENUM_PARAMS(N, var)), ++val);		\
      }									\
  }

NDIM_STDVECTOR_CONSTRUCTOR_TEST(~, 1, 10);
NDIM_STDVECTOR_CONSTRUCTOR_TEST(~, 1, 100);
NDIM_STDVECTOR_CONSTRUCTOR_TEST(~, 4, 10);
//NDIM_STDVECTOR_CONSTRUCTOR_TEST(~, 7, 3);

TEST(make_4x5)
{
  array<float> a = make_4x5();
  ENSURE_EQUAL(a(0,0), 1);
  ENSURE_EQUAL(a(1,1), 6);
  ENSURE_EQUAL(a(2,2), 11);
  ENSURE_EQUAL(a(3,3), 16);
}

TEST(slice_2d_reduce)
{
  array<float> a = make_4x5();
  // slice to

  // 2 6 10 14 18
  array<float> sliced = a.slice(index_range(1), index_range(0, 5));

  ENSURE_EQUAL(sliced.n_dims(), 1);
  ENSURE_EQUAL(sliced.dim(0), 5);

  for (unsigned i=0; i<5; i++)
    log_trace("[%u] == %f",  i % sliced(i));
  ENSURE_EQUAL(sliced(0), 2.0);
  ENSURE_EQUAL(sliced(1), 6.0);
  ENSURE_EQUAL(sliced(2), 10.0);
  ENSURE_EQUAL(sliced(3), 14.0);
  ENSURE_EQUAL(sliced(4), 18.0);
}

TEST(slice_2d)
{
  array<float> a = make_4x5();

  {
    // slice to
    //    6  10  14
    //    7  11  15

    array<float> sliced = a.slice(index_range(1,3), index_range(1,4));
    ENSURE_EQUAL(sliced.n_dims(), 2);
    ENSURE_EQUAL(sliced.dim(0), 2);
    ENSURE_EQUAL(sliced.dim(1), 3);

    // verify they contain what they should
    ENSURE_EQUAL(sliced(0,0), 6.0);
    ENSURE_EQUAL(sliced(1,1), 11.0);
    ENSURE_EQUAL(sliced(1,2), 15.0);
  }


  {
    // slice to
    // 5 6 7 8

    array<float> sliced = a.slice(index_range(0,4), index_range(1));
    ENSURE_EQUAL(sliced.n_dims(), 1);
    ENSURE_EQUAL(sliced.dim(0), 4);

    log_trace("[0] == %f",  sliced(0));
    ENSURE_EQUAL(sliced(0), 5.0);
    ENSURE_EQUAL(sliced(1), 6.0);
    ENSURE_EQUAL(sliced(2), 7.0);
    ENSURE_EQUAL(sliced(3), 8.0);
  }

  {
    // slice to
    // 5 6 7 8

    array<float> sliced = a.slice(index_range(_,_), index_range(1));
    ENSURE_EQUAL(sliced.n_dims(), 1);
    ENSURE_EQUAL(sliced.dim(0), 4);

    log_trace("[0] == %f",  sliced(0));
    ENSURE_EQUAL(sliced(0), 5.0);
    ENSURE_EQUAL(sliced(1), 6.0);
    ENSURE_EQUAL(sliced(2), 7.0);
    ENSURE_EQUAL(sliced(3), 8.0);
  }

  {
    // slice to
    // 8 7 6 5 

    array<float> sliced = a.slice(index_range(_,_,-1), index_range(1));
    ENSURE_EQUAL(sliced.n_dims(), 1);
    ENSURE_EQUAL(sliced.dim(0), 4);

    log_trace("[0] == %f",  sliced(0));
    ENSURE_EQUAL(sliced(0), 8.0);
    ENSURE_EQUAL(sliced(1), 7.0);
    ENSURE_EQUAL(sliced(2), 6.0);
    ENSURE_EQUAL(sliced(3), 5.0);
  }

  {
    // slice to
    // 8 7 6 5
    array<float> sliced = a.slice(index_range(3, -1, -1), index_range(1));
    ENSURE_EQUAL(sliced.n_dims(), 1);
    ENSURE_EQUAL(sliced.dim(0), 4);

    log_trace("[0] == %f",  sliced(0));
    ENSURE_EQUAL(sliced(0), 8.0);
    ENSURE_EQUAL(sliced(1), 7.0);
    ENSURE_EQUAL(sliced(2), 6.0);
    ENSURE_EQUAL(sliced(3), 5.0);
  }

  {
    // slice to
    // 4 8 12 16 20
    array<float> sliced = a.slice(index_range(3), index_range(_,_));
    ENSURE_EQUAL(sliced.n_dims(), 1);
    ENSURE_EQUAL(sliced.dim(0), 5);

    log_trace("[0] == %f",  sliced(0));
    ENSURE_EQUAL(sliced(0), 4.0);
    ENSURE_EQUAL(sliced(1), 8.0);
    ENSURE_EQUAL(sliced(2), 12.0);
    ENSURE_EQUAL(sliced(3), 16.0);
    ENSURE_EQUAL(sliced(4), 20.0);
  }

  {
    // slice to
    // 20 16 12 8 4
    array<float> sliced = a.slice(index_range(3), index_range(_,_,-1));
    ENSURE_EQUAL(sliced.n_dims(), 1);
    ENSURE_EQUAL(sliced.dim(0), 5);

    log_trace("[0] == %f",  sliced(0));
    ENSURE_EQUAL(sliced(0), 20.0);
    ENSURE_EQUAL(sliced(1), 16.0);
    ENSURE_EQUAL(sliced(2), 12.0);
    ENSURE_EQUAL(sliced(3), 8.0);
    ENSURE_EQUAL(sliced(4), 4.0);
  }

  {
    // slice to
    // 15 11 7
    // 14 10 6
    array<float> sliced = a.slice(index_range(2, 0, -1), index_range(3, 0, -1));
    ENSURE_EQUAL(sliced.n_dims(), 2);
    ENSURE_EQUAL(sliced.dim(0), 2);
    ENSURE_EQUAL(sliced.dim(1), 3);


    ENSURE_EQUAL(sliced(0,0), 15.0);
    ENSURE_EQUAL(sliced(0,1), 11.0);
    ENSURE_EQUAL(sliced(0,2),  7.0);

    ENSURE_EQUAL(sliced(1,0), 14.0);
    ENSURE_EQUAL(sliced(1,1), 10.0);
    ENSURE_EQUAL(sliced(1,2),  6.0);
  }

  {
    // slice to
    // 1 9 17
    // 3 11 19
    array<float> sliced = a.slice(index_range(0, 3, 2), index_range(0, 5, 2));
    ENSURE_EQUAL(sliced.n_dims(), 2);
    ENSURE_EQUAL(sliced.dim(0), 2);
    ENSURE_EQUAL(sliced.dim(1), 3);

    ENSURE_EQUAL(sliced(0,0), 1.0);
    ENSURE_EQUAL(sliced(0,1), 9.0);
    ENSURE_EQUAL(sliced(0,2), 17.0);

    ENSURE_EQUAL(sliced(1,0), 3.0);
    ENSURE_EQUAL(sliced(1,1), 11.0);
    ENSURE_EQUAL(sliced(1,2), 19.0);
  }

  {
    // slice to
    // 17 9 1
    // 19 11 3
    array<float> sliced = a.slice(index_range(0, 3, 2), index_range(4, -1, -2));
    ENSURE_EQUAL(sliced.n_dims(), 2);
    ENSURE_EQUAL(sliced.dim(0), 2);
    ENSURE_EQUAL(sliced.dim(1), 3);


    ENSURE_EQUAL(sliced(0,0), 17.0);
    ENSURE_EQUAL(sliced(0,1), 9.0);
    ENSURE_EQUAL(sliced(0,2), 1.0);

    ENSURE_EQUAL(sliced(1,0), 19.0);
    ENSURE_EQUAL(sliced(1,1), 11.0);
    ENSURE_EQUAL(sliced(1,2), 3.0);
  }
}

TEST(slice_1d)
{
  std::vector<std::size_t> shp;
  shp.push_back(10);

  array<float> a(shp);
  ENSURE_EQUAL(a.linear_size(), 10);

  // array is    0 1 2 3 4 5 6 7 8 9

  for (unsigned i=0; i<10; i++)
    a(i) = i;

  ENSURE_EQUAL(a(2), 2.0);
  ENSURE_EQUAL(a(9), 9.0);

  {
    // identical array
    array<float> sliced = a.slice(index_range(0,10));
    ENSURE_EQUAL(sliced.linear_size(), 10);
    ENSURE_EQUAL(sliced(0), 0.0);
    ENSURE_EQUAL(sliced(9), 9.0);
  }

  {
    // from null index range
    array<float> sliced = a.slice(index_range(9,-1,-1));
    ENSURE_EQUAL(sliced.linear_size(), 10);
    ENSURE_EQUAL(sliced(0), 9.0);
    ENSURE_EQUAL(sliced(1), 8.0);
    ENSURE_EQUAL(sliced(8), 1.0);
    ENSURE_EQUAL(sliced(9), 0.0);
  }

  {
    // 0 2 4 6 8
    array<float> sliced = a.slice(index_range(0,10, 2));
    ENSURE_EQUAL(sliced.linear_size(), 5);
    for (unsigned i=0; i<5; i++)
      ENSURE_EQUAL(sliced(i), i * 2.0); 
  }

  {
    // 9 7 5 3 1
    array<float> sliced = a.slice(index_range(9,-1, -2));
    ENSURE_EQUAL(sliced.linear_size(), 5);
    for (unsigned i=0; i<5; i++)
      ENSURE_EQUAL(sliced(i), 9.0 - i * 2.0); 
  }
}

TEST(linspace)
{
  array<float> onetoten = linspace(0, 10, 11);
  ENSURE_EQUAL(onetoten.linear_size(), 11);
  for (unsigned i=0; i<11; i++)
    ENSURE_EQUAL(onetoten(i), i); 

  array<float> tentoone = linspace(10, 0, 11);
  ENSURE_EQUAL(tentoone.linear_size(), 11);
  for (unsigned i=0; i<11; i++)
    ENSURE_EQUAL(tentoone(i), 10.-i); 
}

using resophonic::kamasu::_;

TEST(1d_slice)
{
  array<float> a = linspace(0, 9, 10);
  
  log_trace("about to slice");
  index_range ir(0,10,1);
  array<float> sliced = a.slice(ir);
  ENSURE_EQUAL(sliced.linear_size(), 10);
  for (unsigned i=0; i<9; i++)
    ENSURE_EQUAL(sliced(i), i); 
}

TEST(1d_slice_rev)
{
  array<float> a = linspace(0, 9, 10);
  
  log_trace("about to slice");
  index_range ir(9,-1,-1);
  array<float> sliced = a.slice(ir);
  ENSURE_EQUAL(sliced.linear_size(), 10);
  for (unsigned i=0; i<9; i++)
    ENSURE_EQUAL(sliced(i), 9.0f - i); 
}

TEST(1d_slice_underscore)
{
  array<float> a = linspace(0, 9, 10);
  
  log_trace("about to slice");
  index_range ir(_,_);
  array<float> sliced = a.slice(ir);
  ENSURE_EQUAL(sliced.n_dims(), 1);
  ENSURE_EQUAL(sliced.dim(0), 10);
  ENSURE_EQUAL(sliced.linear_size(), 10);
  for (unsigned i=0; i<9; i++)
    ENSURE_EQUAL(sliced(i), i); 
}

TEST(1d_slice_from_left)
{
  array<float> a = linspace(0, 9, 10);
  
  log_trace("about to slice");
  index_range ir(5,_);
  array<float> sliced = a.slice(ir);
  ENSURE_EQUAL(sliced.n_dims(), 1);
  ENSURE_EQUAL(sliced.dim(0), 5);
  ENSURE_EQUAL(sliced.linear_size(), 5);
  for (unsigned i=0; i<5; i++)
    {
      ENSURE_EQUAL(sliced(i), i+5); 
    }
}

TEST(1d_slice_from_right)
{
  array<float> a = linspace(0, 9, 10);
  
  log_trace("about to slice");
  index_range ir(_,5);
  array<float> sliced = a.slice(ir);
  ENSURE_EQUAL(sliced.n_dims(), 1);
  ENSURE_EQUAL(sliced.dim(0), 5);
  ENSURE_EQUAL(sliced.linear_size(), 5);
  for (unsigned i=0; i<5; i++)
    {
      ENSURE_EQUAL(sliced(i), i); 
    }
}

TEST(1d_underscore_reverse)
{
  array<float> a = linspace(0, 9, 10);
  
  log_trace("about to slice");
  index_range ir(_, _, -1);
  array<float> sliced = a.slice(ir);
  ENSURE_EQUAL(sliced.n_dims(), 1);
  ENSURE_EQUAL(sliced.dim(0), 10);
  ENSURE_EQUAL(sliced.linear_size(), 10);
  ENSURE_EQUAL(sliced.stride(0), -1);

  for (unsigned i=0; i<10; i++)
    {
      ENSURE_EQUAL(sliced(i), 9.0f - i); 
    }
}

TEST(1d_underscore_reverse_2)
{
  array<float> a = linspace(0, 9, 10);
  
  log_trace("about to slice");
  // slice to 9 7 5 3 1
  index_range ir(_, _, -2);
  array<float> sliced = a.slice(ir);
  ENSURE_EQUAL(sliced.n_dims(), 1);
  ENSURE_EQUAL(sliced.dim(0), 5);
  ENSURE_EQUAL(sliced.linear_size(), 5);
  ENSURE_EQUAL(sliced.stride(0), -2);

  for (unsigned i=0; i<5; i++)
    {
      ENSURE_EQUAL(sliced(i), 9.0f - (i*2)); 
    }
}

TEST(assignment)
{
  // shared semantics
  array<float> a(3,4,5);
  ENSURE_EQUAL(a.linear_size(), 60);
  ENSURE_EQUAL(a.n_dims(), 3);
  ENSURE_EQUAL(a.dim(0), 3);
  ENSURE_EQUAL(a.dim(1), 4);
  ENSURE_EQUAL(a.dim(2), 5);
  array<float> b;
  b = a;
  ENSURE_EQUAL(b.linear_size(), 60);
  ENSURE_EQUAL(b.n_dims(), 3);
  ENSURE_EQUAL(b.dim(0), 3);
  ENSURE_EQUAL(b.dim(1), 4);
  ENSURE_EQUAL(b.dim(2), 5);
}


TEST(copy_construct)
{
  array<float> a(3,4,5);
  ENSURE_EQUAL(a.linear_size(), 60);
  ENSURE_EQUAL(a.n_dims(), 3);
  ENSURE_EQUAL(a.dim(0), 3);
  ENSURE_EQUAL(a.dim(1), 4);
  ENSURE_EQUAL(a.dim(2), 5);
  array<float> b(a);

  ENSURE_EQUAL(b.linear_size(), 60);
  ENSURE_EQUAL(b.n_dims(), 3);
  ENSURE_EQUAL(b.dim(0), 3);
  ENSURE_EQUAL(b.dim(1), 4);
  ENSURE_EQUAL(b.dim(2), 5);
  ENSURE_NOT_EQUAL(a.self().data(), b.self().data());

  a(0,0,0) = 17.5;
  b(0,0,0) = 33.5;
  ENSURE_EQUAL(a(0,0,0), 17.5);
  ENSURE_EQUAL(b(0,0,0), 33.5);
}


TEST(construct)
{
  std::vector<std::size_t> shape;
  shape.push_back(7);
  shape.push_back(3);
  shape.push_back(9);

  array<float> arr(shape);
}


TEST(copy_semantics)
{
  array<float> a(1);
  ENSURE_EQUAL(a.linear_size(), 1);
  ENSURE_EQUAL(a.n_dims(), 1);
  ENSURE_EQUAL(a.dim(0), 1);
  array<float> b;
  b = a.copy();
  
  ENSURE_EQUAL(b.linear_size(), 1);
  ENSURE_EQUAL(b.n_dims(), 1);
  ENSURE_EQUAL(b.dim(0), 1);

  ENSURE_NOT_EQUAL(a.self().data(), b.self().data());

  b(0) = 33.5;
  ENSURE_EQUAL(b(0), 33.5);
  a(0) = 17.5;
  ENSURE_EQUAL(a(0), 17.5);
  ENSURE_EQUAL(b(0), 33.5);
}

TEST(copy_semantics_on_assign_2)
{
  array<float> a(2,2);
  ENSURE_EQUAL(a.linear_size(), 4);
  ENSURE_EQUAL(a.n_dims(), 2);
  ENSURE_EQUAL(a.dim(0), 2);
  ENSURE_EQUAL(a.dim(1), 2);
  array<float> b;
  b = a.copy();

  ENSURE_EQUAL(b.linear_size(), 4);
  ENSURE_EQUAL(b.n_dims(), 2);
  ENSURE_EQUAL(b.dim(0), 2);
  ENSURE_EQUAL(b.dim(1), 2);

  ENSURE_NOT_EQUAL(a.self().data(), b.self().data());

  b(0,0) = 33.5;
  ENSURE_EQUAL(b(0,0), 33.5);
  a(0,0) = 17.5;
  ENSURE_EQUAL(a(0,0), 17.5);
  ENSURE_EQUAL(b(0,0), 33.5);

  b(1,0) = 34.5;
  ENSURE_EQUAL(b(1,0), 34.5);
  a(1,0) = 16.5;
  ENSURE_EQUAL(a(1,0), 16.5);
  ENSURE_EQUAL(b(1,0), 34.5);
}

void test_slice_sizes(unsigned len, unsigned stride, unsigned sliced_dim)
{
  array<float> a(len);
  ENSURE_EQUAL(a.dim(0), len);
  ENSURE_EQUAL(a.stride(0), 1);
 
  array<float> b;

  b = a.slice(index_range(0, len, stride));

  ENSURE_EQUAL(a.dim(0), len);
  ENSURE_EQUAL(a.stride(0), 1);
  ENSURE_EQUAL(b.dim(0), sliced_dim);
  ENSURE_EQUAL(b.stride(0), stride);
}

#define SLICETEST(LEN, STRIDE, DIM)		\
  TEST(slice_1d_##LEN##_by_stride_##STRIDE) {	\
    test_slice_sizes(LEN, STRIDE, DIM);		\
  }


SLICETEST(1,1,1);
SLICETEST(1,2,1);
SLICETEST(10, 1, 10);
SLICETEST(10, 2, 5);
SLICETEST(11, 2, 6);
SLICETEST(12, 2, 6);
SLICETEST(13, 2, 7);
SLICETEST(5563, 5, 1113);
SLICETEST(8111, 3, 2704);

