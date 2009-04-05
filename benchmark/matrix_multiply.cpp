#include <resophonic/kamasu.hpp>
#include "benchmark.hpp"

#include <boost/numeric/ublas/matrix.hpp>

using resophonic::kamasu::array;
namespace ublas = boost::numeric::ublas;

struct matrix_multiply 
{
  static void usage() {
    std::cout << "n x\nn = size of a(n,n) and b(n,n)\nx = number of times to multiply\n";
  }

  struct kamasu : benchmark<kamasu>
  {
    unsigned n, x;
    kamasu(unsigned n_, unsigned x_) : n(n_), x(x_) { }

    array<float> a, b, c;

    void start() 
    { 
      a = array<float>(n,n); 
      b = array<float>(n,n); 
    }
    void stop() 
    { 
    }
    void main() 
    { 
      for (int i = 0; i<x; i++)
	c = a * b;
    }
  };

  struct cpu : benchmark<cpu>
  {
    unsigned n, x;
    cpu(unsigned n_, unsigned x_) : n(n_), x(x_) { }

    ublas::matrix<float> a, b, c;

    void start() 
    { 
      a = ublas::matrix<float>(n,n);
      b = ublas::matrix<float>(n,n);
    }
    void stop() 
    { 
    }
    void main() 
    { 
      for (unsigned i=0; i<x; i++)
	c = prod(a,b);
    }
  };
};

MAIN(2);

