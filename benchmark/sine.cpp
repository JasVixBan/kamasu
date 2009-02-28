#include <resophonic/kamasu.hpp>
#include "benchmark.hpp"

using resophonic::kamasu::array;

struct sine
{
  struct kamasu : benchmark<kamasu>
  {
    unsigned n;
    kamasu(unsigned n_) : n(n_) { }

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
      a = resophonic::kamasu::sin(a);
    }
  };

  struct cpu : benchmark<cpu>
  {
    unsigned n;
    cpu(unsigned n_) : n(n_) { }

    std::vector<float> a;

    void start() 
    { 
      a.resize(n);
    }
    void stop() 
    { 
    }
    void main() 
    { 
      for (unsigned i=0; i<n; i++)
	a[i] = ::sin(a[i]);
    }
  };
};

MAIN(1);

