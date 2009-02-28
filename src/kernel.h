#ifndef RESOPHONIC_GPUMATH_KERNEL_H_INCLUDED
#define RESOPHONIC_GPUMATH_KERNEL_H_INCLUDED

#include <boost/preprocessor.hpp>

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


enum Op { MULTIPLIES, PLUS, MINUS, DIVIDES, POW };


#define FN_NAME(NAME,TAG,N) NAME##_##TAG##_##N

#define ENUMERATED_DECLS(Z, N, DATA)					\
  void BOOST_PP_CAT(kamasu_elementwise_array_op_,N)			\
    (Op op,								\
     float* data,							\
     std::size_t linear_size,						\
     const std::size_t* factors,					\
     const int* strides,						\
     cudaStream_t s);							\
  void BOOST_PP_CAT(kamasu_elementwise_array_scalar_,N)			\
    (Op op,								\
     float* data,							\
     std::size_t linear_size,						\
     const std::size_t* factors,					\
     const int* strides,						\
     float scalar,							\
     cudaStream_t s);							\
  void BOOST_PP_CAT(kamasu_elementwise_array_array_,N)			\
    (Op op,								\
     std::size_t linear_size_l,						\
     float* data_l,							\
     float* data_r,							\
     const std::size_t* factors_l,					\
     const std::size_t* factors_r,					\
     const int* strides_l,						\
     const int* strides_r,						\
     cudaStream_t s);


BOOST_PP_REPEAT_FROM_TO(1, KAMASU_MAX_ARRAY_DIM, ENUMERATED_DECLS, ~);

#undef FN_NAME

#endif
