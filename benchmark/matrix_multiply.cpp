#include <resophonic/kamasu.hpp>
#include "benchmark.hpp"
#include <test/I3Test.h>
#include <boost/numeric/ublas/matrix.hpp>

using resophonic::kamasu::array;
namespace ublas = boost::numeric::ublas;

struct matrix_multiply : suite<matrix_multiply>
{
  static void usage() 
  {
    std::cout << "n x\nn = size of a(n,n) and b(n,n)\nx = number of times to multiply\n";
  }

  struct kamasu : benchmark<kamasu>
  {
    array<float> a, b, c;
    ublas::matrix<float, ublas::column_major> myres;

    unsigned n, x;
    kamasu(unsigned n_, unsigned x_) : n(n_), x(x_) { }

    void start() 
    { 
      rng.seed(13);
      ublas::matrix<float, ublas::column_major> indata(n,n);
      for (unsigned i=0; i<n; i++)
	for (unsigned j=0; j<n; j++)
	  indata(i,j) = rand();

      a = array<float>(n,n); 
      a << indata;

      for (unsigned i=0; i<n; i++)
	for (unsigned j=0; j<n; j++)
	  indata(i,j) = rand();

      b = array<float>(n,n); 
      b << indata;
    }

    int main() 
    { 
      for (unsigned i = 0; i<x; i++)
	c = a * b;
      return 0;
    }

    void stop() 
    { 
      c >> myres;
      cudaThreadSynchronize();
    }

    void verify(const ublas::matrix<float, ublas::column_major>& ub)
    {
      //      for (unsigned i=0; i<n; i++)
      //	for (unsigned j=0; j<n; j++)
      //	  ENSURE_DISTANCE(ub(i,j), myres(i,j), 1.0e-01);
    }
  };

  struct cpu : benchmark<cpu>
  {
    ublas::matrix<float> a, b, result;

    unsigned n, x;
    cpu(unsigned n_, unsigned x_) : n(n_), x(x_) { }

    void start() 
    { 
      rng.seed(13);
      a = ublas::matrix<float>(n,n);
      for (unsigned i=0; i<n; i++)
	for (unsigned j=0; j<n; j++)
	  a(i,j) = rand();

      b = ublas::matrix<float>(n,n);
      for (unsigned i=0; i<n; i++)
	for (unsigned j=0; j<n; j++)
	  b(i,j) = rand();
    }
    void stop() 
    { 
    }
    int main() 
    { 
      for (unsigned i=0; i<x; i++)
      	result = prod(a,b);
      return 0;
    }
  };
};

MAIN();




// externally

// number of arguments
// types of arguments


// internally cpu vs kamasu

// type of result
// verify function
