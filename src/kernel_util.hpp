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

//
// helpers
// 

namespace resophonic {
  namespace kamasu {
    enum Op { MULTIPLIES, PLUS, MINUS, DIVIDES, POW };

    const static unsigned threads_per_block = 512;

    typedef std::pair<unsigned, unsigned> bd_t;
    static bd_t gridsize(unsigned size)
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

    template <int N>
    __device__ unsigned actual_index(const argpack<std::size_t, N> &factors,
				     const argpack<int, N> &strides)
    {
      unsigned x = INDEX/factors[N-1] * strides[N-1];
							//      for (unsigned i=I-1; i<=0; i++)
#pragma unroll 10
      for (int i = N-1; i>0; i--)
	x += unsigned(INDEX % factors[i]) / factors[i-1] * strides[i-1];

      return x;

    }

#endif


  }
}
#endif

