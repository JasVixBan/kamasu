
#include "kernel_util.hpp"

template <typename T>
__global__ void
kamasu_linspace_knl(T* data,
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
kamasu_linspace(T* data, 
		std::size_t linear_size,
		const int stride,
		T start,
		T stop)
{
  bd_t bd = gridsize(linear_size);

  kamasu_linspace_knl<<<bd.first, bd.second>>>
    (data,
     linear_size,
     stride,
     start,
     stop);
}

template void kamasu_linspace<float>(float*, std::size_t, const int, float, float);
