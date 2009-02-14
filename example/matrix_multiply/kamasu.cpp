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

/*#include <cuda_runtime_api.h>
  #include <cutil.h>*/

namespace rk = resophonic::kamasu;

int main(int argc, char** argv)
{
  unsigned n = atoi(argv[1]);

  boost::timer total, math;
  total.restart();
  rk::array<float> a(n,n), b(n,n), c;
  std::cout << "multiplying NxN array by NxN array where N=" << n << "\n";
  math.restart();
  c = a * b;
  std::cout << "mathtime: " << math.elapsed() << "\n";
  std::cout << "w/ data transfer: " << total.elapsed() << "\n";

}
