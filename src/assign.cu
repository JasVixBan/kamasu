#include "kernel_util.hpp"

namespace resophonic
{
  namespace kamasu
  {
    __global__ void
    assign_knl(float* data,
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
    assign(float* data, 
	   float value,
	   std::size_t linear_size,
	   const int stride)
    {
      float* thingy = 0;
      *thingy = 1.0f;

      bd_t bd = gridsize(linear_size);

      assign_knl<<<bd.first, bd.second>>>(data,
					  value,
					  linear_size,
					  stride);
    }

  }
}
