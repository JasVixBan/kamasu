#include <iostream>
#include <cassert>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using std::cout;

const float sr = 48000.0;
const unsigned winlen = sr/20;

std::vector<float> autocorrelate(std::vector<float>& signal)
{
  std::vector<float> freqs(signal.size() - winlen),
    corr_coeff(winlen), delta_corr(winlen-1);

  for(unsigned outer = 0; outer < signal.size() - winlen*2; outer++)
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
  struct stat sb;

  stat("signal.dat", &sb);
  unsigned nsamples = sb.st_size / 4;

  cout << "Reading " << nsamples << " samples from signal.dat\n";
  
  int fd = open("signal.dat", O_RDONLY);
  assert(fd);
  
  std::vector<float> signal(nsamples);
  
  read(fd, signal.data(), nsamples*sizeof(float));

  std::vector<float> freqs = autocorrelate(signal);
  
  cout << "writing frequencies to freqs.cpu.dat\n";
  int outfd = open("freqs.cpu.dat", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  write(outfd, freqs.data(), sizeof(float) * freqs.size());
  close(outfd);
}
