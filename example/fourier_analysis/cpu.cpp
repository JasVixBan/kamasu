#include <iostream>
#include <cassert>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
#include "hann_window.hpp"

using std::cout;

const float sr = 48000.0;
const unsigned winlen = sr/70;

#include <fftw3.h>


int main(int argc, char** argv)
{
  struct stat sb;

  stat(argv[1], &sb);
  unsigned nsamples = sb.st_size / 4;

  if (argv[3])
    nsamples = atoi(argv[2]);

  cout << "Reading " << nsamples << " samples from " << argv[1] << "\n";
  
  int fd = open(argv[1], O_RDONLY);
  assert(fd);

  const unsigned fftsize = 512;
  const unsigned stepsize = 256;
  const unsigned nfreqs = div(512, 2).quot + 1;
  
  float* indata = (float*) fftw_malloc(nsamples * sizeof(float));
  fftwf_complex* outdata = (fftwf_complex*) fftw_malloc(fftsize * sizeof(fftwf_complex));

  read(fd, indata, nsamples * sizeof(float));

  cout << "Writing to " << argv[2] << "\n";
  int outfd = open(argv[2], O_WRONLY | O_CREAT);
  float writefreqs = nfreqs;
  write(outfd, &writefreqs, sizeof(float));

  float nsteps = div(nsamples, stepsize).quot;
  write(outfd, &nsteps, sizeof(float));

  fftwf_plan plan;

  int j=0;
  for (int i=0; i<nsamples-fftsize; i+=stepsize)
    {
      j++;
      if (i%1000 == 0)
	{
	  std::cout << i << "      \r";
	  std::cout.flush();
	}
      plan = fftwf_plan_dft_r2c_1d(fftsize, indata+i, outdata, FFTW_ESTIMATE);
      fftwf_execute(plan);

      for (int i=0; i<nfreqs; i++)
	{
	  float amp = std::sqrt(outdata[i][0] * outdata[i][0] + outdata[i][1] * outdata[i][1]);
	  write(outfd, &amp, sizeof(float));
	}
    }

  cout << "Performed " << j << " steps.\n";
  close(outfd);

}
