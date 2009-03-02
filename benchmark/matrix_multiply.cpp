#include <resophonic/kamasu.hpp>
#include "benchmark.hpp"

#include <boost/numeric/ublas/matrix.hpp>

using resophonic::kamasu::array;
namespace ublas = boost::numeric::ublas;

struct matrix_multiply 
{
  struct kamasu : benchmark<kamasu>
  {
    unsigned n;
    kamasu(unsigned n_) : n(n_) { }

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
      c = a * b;
    }
  };

  struct cpu : benchmark<cpu>
  {
    unsigned n;
    cpu(unsigned n_) : n(n_) { }

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
      c = prod(a,b);
    }
  };
};

MAIN(1);


