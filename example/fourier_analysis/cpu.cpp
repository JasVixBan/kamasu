#include <iostream>
#include <cassert>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include "fourier_analysis.hpp"

using std::cout;

#include <fftw3.h>

hann_window hann(fftsize);

int main(int argc, char** argv)
{
  struct stat sb;

  stat(argv[1], &sb);
  unsigned nsamples = sb.st_size / 4;

  if (argv[3])
    nsamples = atoi(argv[3]);

  cout << "Reading " << nsamples << " samples from " << argv[1] << "\n";
  
  int fd = open(argv[1], O_RDONLY);
  assert(fd);

  float* indata = (float*) fftw_malloc(nsamples * sizeof(float));
  fftwf_complex* outdata = (fftwf_complex*) fftw_malloc(fftsize * sizeof(fftwf_complex));

  int i = read(fd, indata, nsamples * sizeof(float));

  cout << "Writing to " << argv[2] << "\n";
  unlink(argv[2]);

  int outfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR|S_IWUSR);
  float nsteps = div(nsamples-fftsize, stepsize).quot + 1;
  write(outfd, &nsteps, sizeof(float));
  float writefreqs = nfreqs;
  write(outfd, &writefreqs, sizeof(float));

  fftwf_plan plan;

  int j=0;
  for (unsigned i=0; i<nsamples-fftsize; i+=stepsize, j++)
    {
      if (i%1000 == 0)
	{
	  std::cout << i << "      \r";
	  std::cout.flush();
	}
      plan = fftwf_plan_dft_r2c_1d(fftsize, indata+i, outdata, FFTW_ESTIMATE);
      fftwf_execute(plan);

      /*
      for (int i=nfreqs-1; i>=0; i--)
	{
	  float amp = 10 * log10(std::sqrt(outdata[i][0] * outdata[i][0] + outdata[i][1] * outdata[i][1]));
	  write(outfd, &amp, sizeof(float));
	}
      */
    }

  cout << "Performed " << j << " steps.\n";
  close(outfd);

}
