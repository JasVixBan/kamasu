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

rk::array<float> autocorrelate(rk::array<float>& signal)
{
  rk::array<float> freqs(signal.dim(0) - winlen);

  for (unsigned outer = 0; outer < 10/*signal.dim(0) - winlen*2*/; outer++)
    {
      cout << "[" << outer << "] " << outer * 100 / signal.dim(0) << "%\r";
      cout.flush();
      std::vector<float> corr_coeff(winlen);
      rk::array<float> lhs = signal.slice(rk::index_range(outer, outer+winlen));
      for (unsigned inner = 0; inner < winlen; inner++)
	{
	  float periodic_autocorr = 
	    rk::dot(lhs, signal.slice(rk::index_range(outer+inner, outer+inner+winlen)));
	  corr_coeff[inner] = periodic_autocorr;
	}
      
    }
  return freqs;
}


int main(int argc, char** argv)
{
  struct stat sb;

  stat("signal.dat", &sb);
  unsigned nsamples = sb.st_size / 4;

  cout << "Reading " << nsamples << " samples from signal.dat\n";
  
  int fd = open("signal.dat", O_RDONLY);
  assert(fd);
  
  std::vector<float> signal(nsamples);
  
  read(fd, signal.data(), nsamples*sizeof(float));

  rk::array<float> a(nsamples);

  for (unsigned i=0; i<signal.size(); i++)
    a(i) = signal[i];

  rk::array<float> freqs = autocorrelate(a);
  
}
