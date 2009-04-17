#include "kernel_util.hpp"

namespace resophonic 
{
  namespace kamasu 
  {

    template <typename T>
    __global__ void
    linspace_knl(T* data,
			unsigned linear_size,
			const int stride,
			T start,
			T stop)
    {
      if (INDEX >= linear_size)
	return;

      unsigned actual_index =  INDEX*stride;

      data[actual_index] = start + INDEX * (stop - start) / (linear_size - 1);
    }

    template <typename T>
    void 
    linspace(T* data, 
		    std::size_t linear_size,
		    const int stride,
		    T start,
		    T stop)
    {
      bd_t bd = gridsize(linear_size);

      linspace_knl<<<bd.first, bd.second>>>
	(data,
	 linear_size,
	 stride,
	 start,
	 stop);
    }

    template void linspace<float>(float*, std::size_t, const int, float, float);
  }
}
