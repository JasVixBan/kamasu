#include <resophonic/kamasu/config.hpp>
#include "kernel_util.hpp"

namespace resophonic {
  namespace kamasu {

    // array-scalar
    template <typename T, int N, typename Tag>
    void 
    transform(T* data, 
	      std::size_t linear_size, 
	      const std::size_t* factors,
	      const int* strides,
	      T scalar);

    // array-array
    template <typename T, int N, typename Tag>
    void 
    transform(std::size_t linear_size,
	      T* data_l,
	      T* data_r,
	      const std::size_t* factors_l,
	      const std::size_t* factors_r,
	      const int* strides_l,
	      const int* strides_r,
	      cudaStream_t stream);

  }
}

