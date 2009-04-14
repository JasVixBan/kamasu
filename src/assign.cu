#include "kernel_util.hpp"

__global__ void
kamasu_linspace_knl(float* data,
		    float value,
		    unsigned linear_size,
		    const int stride)
{
  if (INDEX >= linear_size)
    return;

  unsigned actual_index =  INDEX*stride;

  data[actual_index] = value;
}

void 
kamasu_assign(float* data, 
	      float value,
	      std::size_t linear_size,
	      const int stride)
{
  bd_t bd = gridsize(linear_size);

  kamasu_linspace_knl<<<bd.first, bd.second>>>
    (data,
     value,
     linear_size,
     stride);
}

