#include <iostream>
#include <cassert>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using std::cout;

#include <resophonic/kamasu/logging.hpp>
#include <resophonic/kamasu/array.hpp>

namespace rk = resophonic::kamasu;

const float sr = 48000.0;
const unsigned winlen = sr/70;

rk::array<float> autocorrelate(rk::array<float>& signal)
{
  rk::array<float> freqs(signal.dim(0) - winlen);
  return freqs;
}


int main(int argc, char** argv)
{
  log_warn("%s") % __PRETTY_FUNCTION__;
  std::string fname = argv[1];
  unsigned nsamples = atoi(argv[2]);
  cout << "Reading " << nsamples << " floats from " << fname << "\n";
  
  int fd = open(fname.c_str(), O_RDONLY);
  assert(fd);
  
  std::vector<float> signal(nsamples);
  
  read(fd, signal.data(), nsamples*sizeof(float));

  rk::array<float> a(nsamples);

  for (unsigned i=0; i<signal.size(); i++)
    {
      a(i) = signal[i];
      cout << signal[i] << "\n";
    }


}
