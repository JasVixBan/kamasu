#include <resophonic/kamasu.hpp>
#include "benchmark.hpp"

using resophonic::kamasu::array;

struct deepexpr 
{
  struct kamasu : benchmark<kamasu>
  {
    unsigned n;
    kamasu(unsigned n_) : n(n_) { }

    array<float> a, b, c, d, e;

    void start() 
    { 
      a = array<float>(n); 
      b = array<float>(n); 
      c = array<float>(n); 
      d = array<float>(n); 
    }
    void stop() 
    { 
    }
    void main() 
    { 
      e = (a * 2.0f) + (b * 2.0f) / (c * 2.0f) + (d * 2.0f);
    }
  };

  struct cpu : benchmark<cpu>
  {
    unsigned n;
    cpu(unsigned n_) : n(n_) { }

    std::vector<float> a, b, c, d, e;

    void start() 
    { 
      a.resize(n);
      b.resize(n);
      c.resize(n);
      d.resize(n);
      e.resize(n);
    }
    void stop() 
    { 
    }
    void main() 
    { 
      for (unsigned i=0; i<n; i++)
	e[i] = (a[i] * 2.0f) + (b[i] * 2.0f) / (c[i] * 2.0f) + (d[i] * 2.0f);
    }
  };
};

MAIN(1);


