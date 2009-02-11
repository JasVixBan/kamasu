#include <iostream>
#include <cassert>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using std::cout;

#include <resophonic/kamasu/logging.hpp>
#include <resophonic/kamasu/array.hpp>
#include <resophonic/kamasu/dot.hpp>

namespace rk = resophonic::kamasu;

const float sr = 48000.0;
const unsigned winlen = sr/70;

int main(int argc, char** argv)
{
  struct stat sb;

  stat(argv[1], &sb);
  unsigned nsamples = sb.st_size / 4;

  if (argv[2])
    nsamples = atoi(argv[2]);

  cout << "Reading " << nsamples << " samples from " << argv[1] << "\n";
  
  int fd = open(argv[1], O_RDONLY);
  assert(fd);
  
  std::vector<float> signal(nsamples);
  
  read(fd, signal.data(), nsamples*sizeof(float));

  rk::array<float> a(nsamples);

  std::cout << "moving (slowly) to gpu\n";

  for (unsigned i=0; i<signal.size(); i++)
    a(i) = signal[i];


  


}
