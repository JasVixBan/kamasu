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

int main(int argc, char** argv)
{
  unsigned data_len = atoi(argv[1]);
  const unsigned N = atoi(argv[2]);
  unsigned times = argc == 3 ? atoi(argv[2]) : 1;
  
  boost::timer total, math;
  total.restart();
  
  rk::array<float> a(data_len), filtered(data_len-N);
  std::vector<float> coeff(N);
  math.restart();

  for (int n=0; n<N; n++)
    {
      filtered += a.slice(rk::index_range(n,data_len-N+n)) * coeff[n];
    }

  std::cout << "mathtime: " << math.elapsed() << "\n";
  std::cout << "w/ data transfer: " << total.elapsed() << "\n";
}
