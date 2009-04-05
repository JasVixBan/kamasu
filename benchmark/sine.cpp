#include <resophonic/kamasu.hpp>
#include "benchmark.hpp"

using resophonic::kamasu::array;

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

    array<float> a;

    void start() 
    { 
      a = array<float>(m); 
    }
    void stop() 
    { 
    }
    void main() 
    { 
      for (unsigned i=0; i<n; i++)
	a = resophonic::kamasu::sin(a);
    }
  };

  struct cpu : benchmark<cpu>
  {
    unsigned m,n;
    cpu(unsigned m_, unsigned n_) : m(m_), n(n_) { }

    std::vector<float> a;

    void start() 
    { 
      a.resize(m);
    }
    void stop() 
    { 
    }
    void main() 
    { 
      for (unsigned j=0; j<n; j++)
	for (unsigned i=0; i<m; i++)
	  a[i] = ::sin(a[i]);
    }
  };
};

MAIN(2);


