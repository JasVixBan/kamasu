#include <iostream>
#include <resophonic/kamasu.hpp>
#include "benchmark.hpp"


using resophonic::kamasu::array;

int main(int argc, char** argv)
{
  /*

  cuInit(0);

  CUdevice dev;
  int nGPUs;
  cuDeviceGetCount(&nGPUs);
  printf("Device Info: %d GPUs found in system.\n", nGPUs);

  CUcontext ctx;
  cuDeviceGet(&dev,0);       // use 1st CUDA device
  cuCtxCreate(&ctx, 0, dev); // create context for it

  CUresult memres;
  unsigned int free, total;
  memres = cuMemGetInfo(&free, &total);
  printf("After all allocation(%d):     free %d     total %d \n", memres, free, total);

  cuCtxDetach(ctx);
  */


  unsigned len = boost::lexical_cast<unsigned>(argv[1]);
  std::cout << "creating array<float>(" << len << ")\n";

  array<float> a(len);

}




