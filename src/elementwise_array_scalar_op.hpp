#include <resophonic/kamasu/config.hpp>
#include "kernel_util.hpp"

namespace resophonic {
  namespace kamasu {

    template <typename T, int N, typename Tag>
    void 
    elementwise_array_scalar_op(T* data, 
				std::size_t linear_size, 
				const std::size_t* factors,
				const int* strides,
				T scalar);

  }
}

