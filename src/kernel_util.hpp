#ifndef RESOPHONIC_KAMASU_KERNEL_UTIL_HPP_INCLUDED
#define RESOPHONIC_KAMASU_KERNEL_UTIL_HPP_INCLUDED

#define X      threadIdx.x  
#define XSIZE  blockDim.x
#define Y      blockIdx.x
#define YSIZE  gridDim.x
#define Z      blockIdx.y
#define ZSIZE  gridDim.y

#define INDEX (Z * YSIZE * XSIZE + Y * XSIZE + X)

#include <map>

//
// helpers
// 

namespace resophonic {
  namespace kamasu {
    enum Op { MULTIPLIES, PLUS, MINUS, DIVIDES, POW };
  }
}

const static unsigned threads_per_block = 512;

typedef std::pair<unsigned, unsigned> bd_t;
static bd_t gridsize(unsigned size)
{
  bd_t pr;
  if (size <= threads_per_block)
    return std::make_pair(1, size);
  else
    return std::make_pair(ceil(double(size) / threads_per_block), threads_per_block);
}

#endif

