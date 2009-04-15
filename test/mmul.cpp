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

#if 0

TEST(matrix_mul)
{
  array<float> a(2,2);

  array<float> b(2,2);
  array<float> c(2,2);

  a(0,0) = 0;
  a(0,1) = 1;
  a(1,0) = 2;
  a(1,1) = 3;

  b(0,0) = 6;
  b(0,1) = 7;
  b(1,0) = 4;
  b(1,1) = 5;


  //         0  2
  //         1  3
  //
  // 6  4    4 24
  // 7  5    5 27

  bnu::matrix<float, bnu::column_major> A, B, C;
  a >> A;
  b >> B;
  C = prod(A, B);

  /*
  ENSURE_EQUAL(C(0,0), 14.0f);
  ENSURE_EQUAL(C(0,1), 27.0f);
  ENSURE_EQUAL(C(1,0), 10.0f);
  ENSURE_EQUAL(C(1,1), 19.0f);
  */
  c = a * b;

  ENSURE_EQUAL(a(0,0), 0.0f);
  ENSURE_EQUAL(a(0,1), 1.0f);
  ENSURE_EQUAL(a(1,0), 2.0f);
  ENSURE_EQUAL(a(1,1), 3.0f);

  ENSURE_EQUAL(b(0,0), 6.0f);
  ENSURE_EQUAL(b(0,1), 7.0f);
  ENSURE_EQUAL(b(1,0), 4.0f);
  ENSURE_EQUAL(b(1,1), 5.0f);

  for (int i=0; i<2; i++)
    for (int j=0; j<2; j++)
      std::cout << "c(" << i << "," << j << ") = " << c(i,j) << " boost:" << C(i,j) << "\n";

  ENSURE_EQUAL(c(0,0), C(0,0));
  ENSURE_EQUAL(c(0,1), C(0,1));
  ENSURE_EQUAL(c(1,0), 10.0f);
  ENSURE_EQUAL(c(1,1), 19.0f);



}


TEST(basic)
{
  bnu::matrix<float> A(4,2), B(2,3);
  array<float> a, b;

  //  a
  //  1 2
  //  3 4 
  //  5 6 
  //  7 8
  A(0,0) = 1;
  A(0,1) = 2;
  A(1,0) = 3;
  A(1,1) = 4;
  A(2,0) = 5;
  A(2,1) = 6;
  A(3,0) = 7;
  A(3,1) = 8;

  a << A;
  
  ENSURE_EQUAL(a.n_dims(), 2);
  ENSURE_EQUAL(a.dim(0), 4);
  ENSURE_EQUAL(a.dim(1), 2);

  ENSURE_EQUAL(a(0,0), 1);
  ENSURE_EQUAL(a(0,1), 2);
  ENSURE_EQUAL(a(1,0), 3);
  ENSURE_EQUAL(a(1,1), 4);
  ENSURE_EQUAL(a(2,0), 5);
  ENSURE_EQUAL(a(2,1), 6);
  ENSURE_EQUAL(a(3,0), 7);
  ENSURE_EQUAL(a(3,1), 8);

  ENSURE_EQUAL(A.size1(), 4);
  ENSURE_EQUAL(A.size2(), 2);

  ENSURE_EQUAL(A(0,0), 1);
  ENSURE_EQUAL(A(0,1), 2);
  ENSURE_EQUAL(A(1,0), 3);
  ENSURE_EQUAL(A(1,1), 4);
  ENSURE_EQUAL(A(2,0), 5);
  ENSURE_EQUAL(A(2,1), 6);
  ENSURE_EQUAL(A(3,0), 7);
  ENSURE_EQUAL(A(3,1), 8);

  // b
  //   9  10  11
  //  12  13  14
  B(0,0) = 9;
  B(0,1) = 10;
  B(0,2) = 11;
  B(1,0) = 12;
  B(1,1) = 13;
  B(1,2) = 14;

  b << B;

  ENSURE_EQUAL(b.n_dims(), 2);
  ENSURE_EQUAL(b.dim(0), 2);
  ENSURE_EQUAL(b.dim(1), 3);

  ENSURE_EQUAL(b(0,0), 9);
  ENSURE_EQUAL(b(0,1), 10);
  ENSURE_EQUAL(b(0,2), 11);
  ENSURE_EQUAL(b(1,0), 12);
  ENSURE_EQUAL(b(1,1), 13);
  ENSURE_EQUAL(b(1,2), 14);

  ENSURE_EQUAL(B.size1(), 2);
  ENSURE_EQUAL(B.size2(), 3);
  ENSURE_EQUAL(B(0,0), 9);
  ENSURE_EQUAL(B(0,1), 10);
  ENSURE_EQUAL(B(0,2), 11);
  ENSURE_EQUAL(B(1,0), 12);
  ENSURE_EQUAL(B(1,1), 13);
  ENSURE_EQUAL(B(1,2), 14);

  array<float> c;

  c = a * b;

  ENSURE_EQUAL(c.n_dims(), 2);
  ENSURE_EQUAL(c.dim(0), 4);
  ENSURE_EQUAL(c.dim(1), 3);

  bnu::matrix<float, bnu::column_major> C, boost_c;
  
  c >> C;

  ENSURE_EQUAL(C.size1(), 4);
  ENSURE_EQUAL(C.size2(), 3);

  boost_c = bnu::prod(A, B);

  ENSURE_EQUAL(boost_c.size1(), 4);
  ENSURE_EQUAL(boost_c.size2(), 3);

  for (int i=0; i<boost_c.size1(); i++)
    for (int j=0; j<boost_c.size2(); j++)
      {
	std::cout << i << ", " << j << " [c: "<< c(i,j) << " C:" << C(i,j) << " boost_c:" << boost_c(i,j) << "]\n";
	ENSURE_EQUAL(c(i,j), C(i,j));
	ENSURE_EQUAL(boost_c(i,j), C(i,j));
      }
}

#endif

void mmul_test(const unsigned M, const unsigned N, const unsigned K)
{
  bnu::matrix<float, bnu::column_major> A(M,N), B(N,K);
  array<float> a, b;

  for (unsigned m = 0; m<M; m++)
    for (unsigned n = 0; n<N; n++)
      A(m,n) = n*M + m;

  for (unsigned n = 0; n<N; n++)
    for (unsigned k = 0; k<K; k++)
      B(n,k) = k*N + k;

  // move to gpu
  a << A;
  b << B;

  array<float> c;

  c = a * b;

  std::cout << "multiply " << a.dim(0) << "x" << a.dim(1) << " * " 
	    << b.dim(0) << "x" << b.dim(1) << " matrices ==> " 
	    << c.dim(0) << "x" << c.dim(1) << "\n";

  ENSURE_EQUAL(c.nd(), 2u);
  ENSURE_EQUAL(c.dim(0), M);
  ENSURE_EQUAL(c.dim(1), K);

  bnu::matrix<float, bnu::column_major> C;
  C = prod(A, B);
  
  ENSURE_EQUAL(C.size1(), M);
  ENSURE_EQUAL(C.size2(), K);

  bnu::matrix<float, bnu::column_major> kamasu_c;
  c >> kamasu_c;

  for (unsigned m=0; m<M; m++)
    for (unsigned k=0; k<K; k++)
      {
	ENSURE_DISTANCE(C(m,k), kamasu_c(m,k), C(m,k)*1.0e-07);
      }
}

#define MMUL_TEST(M,N,K) TEST( M ## x ## N ## x ## K) { mmul_test(M,N,K); }

MMUL_TEST(3,4,5);
MMUL_TEST(13,14,15);
MMUL_TEST(1,1,1);
MMUL_TEST(1,17,1);
MMUL_TEST(101,102,103);


