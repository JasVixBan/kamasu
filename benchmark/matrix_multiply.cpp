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
    ublas::matrix<float, ublas::column_major> indata;
    ublas::matrix<float, ublas::column_major> myres;
    unsigned n, x;

    kamasu(unsigned n_, unsigned x_) 
      : n(n_), x(x_), indata(n_, n_) 
    { 
      rng.seed(13);
      for (unsigned i=0; i<n; i++)
	for (unsigned j=0; j<n; j++)
	  indata(i,j) = rand();
    }

    void start() 
    { 
      a << indata;
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
    ublas::matrix<float, ublas::column_major> indata;
    unsigned n, x;

    cpu(unsigned n_, unsigned x_) 
      : n(n_), x(x_), indata(n_, n_) 
    { 
      rng.seed(13);
      for (unsigned i=0; i<n; i++)
	for (unsigned j=0; j<n; j++)
	  indata(i,j) = rand();
    }

    void start() 
    { 
      rng.seed(13);
      a = indata;
      b = indata;
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
