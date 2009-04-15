//
//  Forces an init of cudaland.
//
#include <resophonic/kamasu.hpp>


namespace resophonic {
  namespace kamasu {
    struct cuda_init {

      void init() {
	
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

	cublasInit();

      }

      cuda_init() { 
	//init(); 
      }

    };

    static cuda_init initter;

  }
}
