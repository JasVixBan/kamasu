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
  
  bnu::matrix<float, bnu::column_major> asrc(n,n), bsrc(n,n), cdst(n,n);
  rk::array<float> a(n,n), b(n,n), c;

  a << asrc;
  b << bsrc;

  std::cout << "multiplying NxN array by NxN array where N=" << n << " (" << times << " times).\n";
  math.restart();
  for (int i=0; i<times; i++)
    c = a * b;

  c >> cdst;

  std::cout << "mathtime: " << math.elapsed() << "\n";
  std::cout << "w/ data transfer: " << total.elapsed() << "\n";

}
