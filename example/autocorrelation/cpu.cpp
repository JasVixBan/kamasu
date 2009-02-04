#include <iostream>
#include <cassert>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using std::cout;

const float sr = 48000.0;
const unsigned winlen = sr/70;

std::vector<float> autocorrelate(std::vector<float>& signal)
{
  std::vector<float> freqs(signal.size() - winlen),
    corr_coeff(winlen), delta_corr(winlen-1);

  for(unsigned outer = 0; outer< signal.size() - winlen*2; outer++)
    {
      cout << outer * 100 / signal.size() << "%\r";
      cout.flush();
      for (unsigned inner = 0; inner < winlen; inner++)
	{
	  float sum = 0;
	  for (unsigned i = 0; i<winlen; i++)
	    sum += signal[outer+i] * signal[outer+inner+i];
	  corr_coeff[inner] = sum / winlen;
	}
      for (unsigned inner = 0; inner < winlen-1; inner++)
	delta_corr[inner] = corr_coeff[inner+1] - corr_coeff[inner];
      
      
      for (unsigned i = (sr/200)/4; // start a little way into the wave
	   i< delta_corr.size()-1;
	   i++)
	{
	  if (delta_corr[i] >= 0 and delta_corr[i+1] < 0)
	    {
	      freqs[outer] = sr/(i+2);
	      break;
	    }
	}
    }

  return freqs;
}


int main(int argc, char** argv)
{
  std::string fname = argv[1];
  unsigned nsamples = atoi(argv[2]);
  cout << "Reading " << nsamples << " floats from " << fname << "\n";
  
  int fd = open(fname.c_str(), O_RDONLY);
  assert(fd);
  
  std::vector<float> signal(nsamples);
  
  read(fd, signal.data(), nsamples*sizeof(float));

  std::vector<float> freqs = autocorrelate(signal);
  
  for (unsigned i=0; i<freqs.size(); i++)
    {
      cout << freqs[i] << "\n";
    }
  /*
  log_warn("%s") % __PRETTY_FUNCTION__;
  rk::array<float> a(nsamples);

  for (unsigned i=0; i<signal.size(); i++)
    {
      a(i) = signal[i];
      cout << signal[i] << "\n";
    }
  */

}
