#include <resophonic/kamasu/config.hpp>
#include "kernel_util.hpp"

namespace resophonic {
  namespace kamasu {

    void eas_/*N*/(resophonic::kamasu::Op op,
		   /*T*/* data,
		   std::size_t linear_size,
		   const std::size_t* factors,
		   const int* strides,
		   /*T*/ scalar,
		   cudaStream_t stream);
  }
}
