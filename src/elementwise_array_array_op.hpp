#include <resophonic/kamasu/config.hpp>
#include "kernel_util.hpp"

namespace resophonic {
  namespace kamasu {

    template <typename T, int N, typename Tag>
    void 
    elementwise_array_array_op(std::size_t linear_size,
			       T* data_l,
			       T* data_r,
			       const std::size_t* factors_l,
			       const std::size_t* factors_r,
			       const int* strides_l,
			       const int* strides_r,
			       cudaStream_t stream);
  }
}

