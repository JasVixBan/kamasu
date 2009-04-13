#include <iostream>
#include <cassert>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using std::cout;

#include <resophonic/kamasu/logging.hpp>
#include <resophonic/kamasu/array.hpp>
#include <resophonic/kamasu/dot.hpp>

#include <boost/timer.hpp>

namespace rk = resophonic::kamasu;
namespace bnu = boost::numeric::ublas;

int main(int argc, char** argv)
{
  unsigned n = atoi(argv[1]);
  unsigned times = argc == 3 ? atoi(argv[2]) : 1;
  
  boost::timer total, math;
  total.restart();
  
  rk::array<float> a(n), b(n);

  std::cout << "taking dot product of two " << n << " element vectors (" << times << " times).\n";
  math.restart();
  for (unsigned i=0; i<times; i++)
    rk::dot(a,b);

  std::cout << "mathtime: " << math.elapsed() << "\n";
  std::cout << "w/ data transfer: " << total.elapsed() << "\n";

}
