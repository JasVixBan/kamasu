#include <resophonic/kamasu.hpp>
#include "benchmark.hpp"

using resophonic::kamasu::array;
namespace t = resophonic::kamasu::testing;

struct sine
{
  static void usage()
  {
    std::cout << "m n\n"
	      << "m = size of array to sin()\n"
	      << "n = number of times\n";
  }

  struct kamasu : benchmark<kamasu>
  {
    unsigned m, n;
    kamasu(unsigned m_, unsigned n_) : m(m_), n(n_) { }

    array<float> result;
    std::vector<float> v;
    void start() 
    { 
      v.resize(m);
      t::rng.seed(13);
      for (unsigned i=0; i<m; i++)
	v[i] = t::rand();
    }
    void stop() 
    { 
    }
    void main() 
    { 
      result << v;
      for (unsigned i=0; i<n; i++)
	result = resophonic::kamasu::sin(result);
      result >> v;
    }
    void verify(const std::vector<float>& ublas) 
    { 
      for(unsigned i=0; i<m; i++)
	ENSURE_DISTANCE(ublas[i], v[i], 1.0e-04);
    }
  };

  struct cpu : benchmark<cpu>
  {
    unsigned m,n;
    cpu(unsigned m_, unsigned n_) : m(m_), n(n_) { }

    std::vector<float> result;

    void start() 
    { 
      result.resize(m);
      t::rng.seed(13);
      for (unsigned i=0; i<m; i++)
	result[i] = t::rand();
    }
    void stop() 
    { 
    }
    void main() 
    { 
      for (unsigned j=0; j<n; j++)
	for (unsigned i=0; i<m; i++)
	  result[i] = ::sin(result[i]);
    }
  };
};

MAIN(2);


