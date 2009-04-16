#include <resophonic/kamasu.hpp>
#include <resophonic/kamasu/sort.hpp>
#include "benchmark.hpp"
#include <test/I3Test.h>
#include <boost/numeric/ublas/matrix.hpp>

using resophonic::kamasu::array;
namespace ublas = boost::numeric::ublas;
namespace t = resophonic::kamasu::testing;

struct sort : suite<sort>
{
  static void usage() 
  {
    std::cout << "n x\nn = size of a(n,n) and b(n,n)\nx = number of times to multiply\n";
  }


  struct kamasu : benchmark<kamasu>
  {
    array<float> a;
    std::vector<float> indata, myres;
    unsigned n, x;

    kamasu(unsigned n_, unsigned x_) 
      : n(n_), x(x_), indata(n_)
    { 
      t::rng.seed(13);
      for (unsigned i=0; i<n; i++)
	{
	  indata[i] = t::uniform();
	}
    }

    void start() 
    { 
      a << indata;
    }

    int main() 
    { 
      resophonic::kamasu::sort(a);
      return 0;
    }

    void stop() 
    { 
      a >> myres;
    }

    void verify(const std::vector<float>& v)
    {
      for (int i=0; i<n-1; i++)
	{
	  ENSURE_DISTANCE(myres[i], v[i], 10e-06);
	}
    }
  };

  struct cpu : benchmark<cpu>
  {
    std::vector<float> result;
    unsigned n, x;

    cpu(unsigned n_, unsigned x_) 
      : n(n_), x(x_), result(n_)
    { 
      t::rng.seed(13);
      for (unsigned i=0; i<n; i++)
	{
	  result[i] = t::uniform();
	}
    }

    void start() 
    { 
    }
    void stop() 
    { 
    }
    int main() 
    { 
      std::sort(result.begin(), result.end());
      return 0;
    }
  };
};

MAIN();




// externally

// number of arguments
// types of arguments


// internally cpu vs kamasu

// type of result
// verify function
