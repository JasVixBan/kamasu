
#include "kernel_util.hpp"

__global__ void
kamasu_linspace_knl(float* data,
		    unsigned linear_size,
		    const int stride,
		    float start,
		    float stop)
{
  if (INDEX >= linear_size)
    return;

  unsigned actual_index =  INDEX*stride;

  data[actual_index] = start + INDEX * (stop - start) / (linear_size - 1);
}

void 
kamasu_linspace(float* data, 
		std::size_t linear_size,
		const int stride,
		float start,
		float stop)
{
  bd_t bd = gridsize(linear_size);

  kamasu_linspace_knl<<<bd.first, bd.second>>>
    (data,
     linear_size,
     stride,
     start,
     stop);
}

