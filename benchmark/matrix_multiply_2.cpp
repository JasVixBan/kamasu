#include <resophonic/kamasu.hpp>
#include "benchmark.hpp"

#include <boost/numeric/ublas/matrix.hpp>

using resophonic::kamasu::array;
namespace ublas = boost::numeric::ublas;

struct matrix_multiply_2 
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
    int main() 
    { 
      for (unsigned i = 0; i<x; i++)
	c = (a / 3.0f) * (b / 7.0f);
      return 0;
    }

    void verify(const ublas::matrix<ublas::column_major>& v) { }

  };

  struct cpu : benchmark<cpu>
  {
    unsigned n, x;
    cpu(unsigned n_, unsigned x_) : n(n_), x(x_) { }

    ublas::matrix<float> a, b, result;

    void start() 
    { 
      a = ublas::matrix<float>(n,n);
      b = ublas::matrix<float>(n,n);
    }
    void stop() 
    { 
    }
    int main() 
    { 
      for (unsigned i=0; i<x; i++)
	result = prod(a * 3.0f, b * 7.0f);
      if (result.size1() != n || result.size2() != n)
	throw std::runtime_error("wrong size");
      return 0;
    }
  };
};

MAIN();

