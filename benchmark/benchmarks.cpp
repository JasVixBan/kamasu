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

#include <vector>
#include <cassert>

namespace ks = resophonic::kamasu;

using namespace resophonic::kamasu;

TEST_GROUP();

TEST(1d_slice)
{
  unsigned n = 10000;

  array<float> a(n);

  for (int j=0; j<100; j++)
    {
      std::cout << j << "% \r";
      for (int i=0; i<n/2 -1 ; i++)
	{
	  std::cout.flush();
	  array<float> b = a.slice(index_range(i, i+n/2));
	}
    }
	
}


void matrix_multiply(unsigned n)
{

  array<float> a(n,n), b(n,n), c;

  //  c = a * b;

}


void ublas_multiply(unsigned n)
{
  

}


TEST(matrix_multiply)
{
  matrix_multiply(1024);
}


template <typename Expr>
void fleh(Expr const& e)
{
  log_trace("fn is %s", __PRETTY_FUNCTION__);
  //  BOOST_MPL_ASSERT(( boost::proto::matches<Expr, StreamedGrammar> ));
}

TEST(vector_ops_serial)
{
  unsigned n = 10;
  array<float> a(n,n), b(n,n), c;

  //  std::cout << name_of((stream(), a * b));
  // std::cout << "it is:" << name_of((stream(), a * b)) << "\n";
  //  fleh f;

  // cudaStream_t s;
  stream s;

  fleh((s, a));

  c = (s, a * b);

  //  whatsit(stream(), a*b);
  //  c = (stream(), a * b);
}
