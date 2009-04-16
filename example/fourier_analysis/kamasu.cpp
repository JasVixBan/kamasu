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

#include "fourier_analysis.hpp"

#include <cufft.h>
#include <cuda_runtime_api.h>
#include <cutil.h>

namespace rk = resophonic::kamasu;

int main(int argc, char** argv)
{
  struct stat sb;

  stat(argv[1], &sb);
  unsigned nsamples = sb.st_size / 4;

  if (argv[3])
    nsamples = atoi(argv[3]);

  cout << "Reading " << nsamples << " samples from " << argv[1] << "\n";
  
  // open file

  int fd = open(argv[1], O_RDONLY);
  assert(fd);
  
  // alloc/fill host input memory

  float* hostdata;
  KAMASU_SAFE_CALL( cudaMallocHost((void**)&hostdata, sizeof(float) * nsamples) );

  int i =read(fd, hostdata, sizeof(float) * nsamples);
  i ++;
  // alloc/fill device input memory

  float* gpu_indata;
  cout << "malloc" << sizeof(float) * nsamples << " device mem for data\n";
  KAMASU_SAFE_CALL( cudaMalloc((void**)&gpu_indata, sizeof(float) * nsamples) );

  KAMASU_SAFE_CALL( cudaMemcpy(gpu_indata, hostdata, sizeof(float) * nsamples, cudaMemcpyHostToDevice) );

  // write header to output file

  cout << "Writing to " << argv[2] << "\n";
  unlink(argv[2]);
  int outfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  float nsteps = div(nsamples-fftsize, stepsize).quot + 1;
  i = write(outfd, &nsteps, sizeof(float));

  float writefreqs = nfreqs;
  i = write(outfd, &writefreqs, sizeof(float));

  // create device output memory

  cufftComplex *gpu_outdata;
  KAMASU_SAFE_CALL(cudaMalloc((void**)&gpu_outdata, sizeof(cufftComplex)*nfreqs));

  // create host output memory
  cufftComplex *host_outdata;
  KAMASU_SAFE_CALL(cudaMallocHost((void**)&host_outdata, sizeof(cufftComplex)*nfreqs * nsteps));

  // loop through input data calling ffts
  int j=0;
  for (unsigned i=0; i<nsamples-fftsize; i+=stepsize, j++)
    {
      if (i%1000 == 0)
	{
	  std::cout << i << "      \r";
	  std::cout.flush();
	}
      // create plan
      cufftHandle plan;
      CUFFT_SAFE_CALL(cufftPlan1d(&plan, fftsize, CUFFT_R2C, 1));

      CUFFT_SAFE_CALL( cufftExecR2C(plan, gpu_indata+i, gpu_outdata) );

      CUFFT_SAFE_CALL( cufftDestroy(plan) );
      
      /*
      CUDA_SAFE_CALL( cudaMemcpy(host_outdata+ nfreqs*j, gpu_outdata, 
	sizeof(cufftComplex) * nfreqs, cudaMemcpyDeviceToHost) );

      for (int k=nfreqs-1; k>=0; k--)
	{
	  cufftComplex& thingy = host_outdata[k];

	  float amp = 10 * log10(cuCabsf(thingy));

	  write(outfd, &amp, sizeof(float));
	}
      */
    }

  cout << "Performed " << j << " steps.\n";
  close(outfd);
}
