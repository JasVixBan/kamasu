#include <iostream>
#include <cassert>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using std::cout;

#include <resophonic/kamasu/logging.hpp>
#include <resophonic/kamasu/array.hpp>
#include <resophonic/kamasu/linspace.hpp>
#include <resophonic/kamasu/dot.hpp>

namespace rk = resophonic::kamasu;

#include "audio_synthesis.hpp"

int main(int argc, char** argv)
{
  int fd = open("signal.dat", O_RDONLY);
  assert(fd);
  
  rk::array<float> signal(nchan, nsamp);
  rk::array<float> linear = rk::linspace<float>(0, 2*M_PI, sr);
  
  for (int i=0; i<9; i++)
    {
      float freq = 200 + i * 50;
      rk::array<float> sl = signal.slice(rk::index_range(i*sr, i*sr + sr));
      sl += rk::sin(linear) * 0.5f;
    }
}
