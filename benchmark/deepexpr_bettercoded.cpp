#include <resophonic/kamasu.hpp>
#include "benchmark.hpp"

using resophonic::kamasu::array;
namespace t = resophonic::kamasu::testing;

struct deepexpr_bettercoded : suite<deepexpr_bettercoded>
{
  static void usage() { 
    std::cout << "\nno options.\n";
  }

  struct kamasu : benchmark<kamasu>
  {
    unsigned n, x;
    array<float> a, b, c, d, e;
    std::vector<float> randvec;

    kamasu(unsigned n_, unsigned x_) : n(n_), x(x_) 
    { 
      t::rng.seed(13);
      randvec.resize(n);
      for (unsigned i=0; i<n; i++)
	randvec[i] = t::uniform();
    }

    void start() 
    { 
      a << randvec;
      b << randvec;
      c << randvec;
      d << randvec;
    }
    void stop() 
    { 
    }
    int main() 
    { 
      for (unsigned i=0; i<x; i++)
	{
	  e = a * 2.0f;
	  e += b / 2.0f;
	  e += c * 2.0f;
	  e += d / 2.0f;
	}
      return 0;
    }
    int verify(const std::vector<float>& r)
    {
      std::vector<float> v;
      e >> v;
      for (unsigned i=0; i<n; i++)
	ENSURE_DISTANCE(v[i], r[i], 1.0e-5);
    }
  };

  struct cpu : benchmark<cpu>
  {
    unsigned n, x;
    std::vector<float> a, b, c, d, result, randvec;

    cpu(unsigned n_, unsigned x_) : n(n_), x(x_)
    {
      t::rng.seed(13);
      a.resize(n);
      for (unsigned i=0; i<n; i++)
	a[i] = t::uniform();
    }

    void start() 
    { 
      b = a;
      c = a;
      d = a;
      result.resize(n);
    }
    void stop() 
    { 
    }
    int main() 
    { 
      for (unsigned i=0; i<x; i++)
	for (unsigned i=0; i<n; i++)
	  result[i] = a[i] * 2.0f + b[i] / 2.0f + c[i] * 2.0f + d[i] / 2.0f;
      return 0;
    }
  };
};

MAIN();


