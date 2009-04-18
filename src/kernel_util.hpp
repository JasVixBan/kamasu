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

namespace resophonic {
  namespace kamasu {

    typedef std::pair<unsigned, unsigned> bd_t;
    static bd_t gridsize(unsigned size, unsigned threads_per_block = 64)
    {
      std::cout << "yeh";
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

    template <int N>
    __device__ unsigned actual_index(const argpack<std::size_t, N> &factors,
				     const argpack<int, N> &strides)
    {
      unsigned x = INDEX/factors[N-1] * strides[N-1];
							//      for (unsigned i=I-1; i<=0; i++)
      for (int i = N-1; i>0; i--)
	x += unsigned(INDEX % factors[i]) / factors[i-1] * strides[i-1];

      return x;

    }

    __device__ unsigned actual_index(unsigned nd,
				     const std::size_t* factors,
				     const int* strides)
    {
      unsigned x = INDEX/factors[nd-1] * strides[nd-1];
							//      for (unsigned i=I-1; i<=0; i++)
      for (int i = nd-1; i>0; i--)
	x += unsigned(INDEX % factors[i]) / factors[i-1] * strides[i-1];

      return x;

    }

#endif


  }
}
#endif

