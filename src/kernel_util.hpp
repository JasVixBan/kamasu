#ifndef RESOPHONIC_KAMASU_KERNEL_UTIL_HPP_INCLUDED
#define RESOPHONIC_KAMASU_KERNEL_UTIL_HPP_INCLUDED

#define X      threadIdx.x  
#define XSIZE  blockDim.x
#define Y      blockIdx.x
#define YSIZE  gridDim.x
#define Z      blockIdx.y
#define ZSIZE  gridDim.y

#define INDEX (Z * YSIZE * XSIZE + Y * XSIZE + X)

#include <utility>
#include <iostream>
#include <resophonic/kamasu/view_params.hpp>

namespace resophonic {
  namespace kamasu {

    typedef std::pair<unsigned, unsigned> bd_t;
    static bd_t gridsize(unsigned size, unsigned threads_per_block = 64)
    {
      bd_t pr;
      if (size <= threads_per_block)
	return std::make_pair(1, size);
      else
	return std::make_pair(::ceil(double(size) / threads_per_block), threads_per_block);
    }


#ifdef __CUDACC__

    template <typename T, int Length>
    struct argpack
    {
      T data[Length];
      argpack(const T* d)
      {
	memcpy(data, d, Length * sizeof(T));
      }
      T& operator[](unsigned index)
      {
	return data[index];
      }
      const T& operator[](unsigned index) const
      {
	return data[index];
      }
      void touchme() { }
    };

    __device__ unsigned actual_index(unsigned linear_index,
				     unsigned nd,
				     const factor_t* factors,
				     const stride_t* strides)
    {
      unsigned x = linear_index/factors[nd-1] * strides[nd-1];
							//      for (unsigned i=I-1; i<=0; i++)
      for (int i = nd-1; i>0; i--)
	x += unsigned(linear_index % factors[i]) / factors[i-1] * strides[i-1];

      return x;

    }

#endif


  }
}
#endif

