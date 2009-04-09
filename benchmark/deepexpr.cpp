#include <resophonic/kamasu.hpp>
#include "benchmark.hpp"

using resophonic::kamasu::array;

struct deepexpr 
{
  static void usage() { 
    std::cout << "\nno options.\n";
  }

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
    int main() 
    { 
      e = a * 2.0f; 
      e += (d * 2.0f);
      e += (b * 2.0f) / (c * 2.0f);
      return 0;
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
    int main() 
    { 
      for (unsigned i=0; i<n; i++)
	e[i] = (a[i] * 2.0f) + (b[i] * 2.0f) / (c[i] * 2.0f) + (d[i] * 2.0f);
      return 0;
    }
  };
};

MAIN(1);


