#include <boost/numeric/ublas/matrix.hpp>
#include <resophonic/kamasu.hpp>
#include "benchmark.hpp"

using namespace resophonic::kamasu;

struct deepexpr_streamed
{
  struct kamasu : benchmark<kamasu>
  {
    unsigned n;
    kamasu(unsigned n_) : n(n_) { }

    array<float> a;

    void start() 
    { 
      a = array<float>(n, n); 
    }
    void stop() 
    { 
    }
    void main() 
    { 
      {
	for (unsigned i=0; i<n; i++)
	  {
	    array<float, boost::mpl::true_> slice = a.slice(index_range(i), index_range(_,_));
	    slice = rk::pow(slice, 2.0f);
	  }
      }
    }
  };

  struct cpu : benchmark<cpu>
  {
    const unsigned n;
    cpu(unsigned n_) : n(n_), m(n,n) { }

    boost::numeric::ublas::matrix<float> m;

    void start() 
    { 
    }
    void stop() 
    { 
    }
    void main() 
    { 
      for (unsigned i=0; i<n; i++)
	{
	  for (unsigned j=0; j<n; j++)
	    m(i,j) = ::pow(m(i,j), 2);
	}
    }
  };
};

MAIN(1);


