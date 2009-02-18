#ifndef RESOPHONIC_KAMASU_KERNEL_UTIL_H_INCLUDED
#define RESOPHONIC_KAMASU_KERNEL_UTIL_H_INCLUDED

#define X      threadIdx.x  
#define XSIZE  blockDim.x
#define Y      blockIdx.x
#define YSIZE  gridDim.x
#define Z      blockIdx.y
#define ZSIZE  gridDim.y

#define INDEX (Z * YSIZE * XSIZE + Y * XSIZE + X)

//
// helpers
// 

const static unsigned threads_per_block = 64;

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
