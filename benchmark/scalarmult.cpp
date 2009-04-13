#include <resophonic/kamasu.hpp>
#include "benchmark.hpp"

using resophonic::kamasu::array;

struct scalarmult 
{

  static void usage()
  {
    std::cout << "n m\n"
	      << "n = Length of 1d array to multiply by 2.0f\n"
	      << "m = number of times to do that\n";
  }

  struct kamasu : benchmark<kamasu>
  {
    unsigned n, m;
    kamasu(unsigned n_, unsigned m_) : n(n_), m(m_) { }

    array<float> a;
    
    void start() 
    { 
      a = array<float>(n); 
    }
    void stop() 
    { 
    }
    void main() 
    { 
      for (unsigned i=0; i<m; i++)
	a = a * 2.0f;
    }

    void verify(const std::vector<float>&)
    {
    }

  };

  struct cpu : benchmark<cpu>
  {
    unsigned n, m;
    cpu(unsigned n_, unsigned m_) : n(n_), m(m_) { }

    std::vector<float> result;

    void start() 
    { 
      result = std::vector<float>(n);
    }
    void stop() 
    { 
    }
    void main() 
    { 
      for (unsigned j=0; j<m; j++)
	for (unsigned i=0; i<n; i++)
	  result[i] *= 2.0f;
    }
  };
};

MAIN();


