#ifndef RESOPHONIC_GPUMATH_KERNEL_H_INCLUDED
#define RESOPHONIC_GPUMATH_KERNEL_H_INCLUDED

#include <boost/preprocessor.hpp>
#include <map>

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




void gpu_mul_scalar(float* data, unsigned size, float scalar);
void gpu_add_scalar(float* data, unsigned size, float scalar);
void gpu_sub_scalar(float* data, unsigned size, float scalar);
void gpu_div_scalar(float* data, unsigned size, float scalar);

void gpu_mul_vector(float* lhs, float* rhs,  unsigned size);
void gpu_add_vector(float* lhs, float* rhs,  unsigned size);
void gpu_sub_vector(float* lhs, float* rhs,  unsigned size);
void gpu_div_vector(float* lhs, float* rhs,  unsigned size);

void kamasu_vector_scalar_add(int n, float alpha, float *x, int incx);
void kamasu_vector_scalar_sub(int n, float alpha, float *x, int incx);
void kamasu_vector_scalar_mul(int n, float alpha, float *x, int incx);
void kamasu_vector_scalar_div(int n, float alpha, float *x, int incx);

void kamasu_vector_vector_add(int n, float* lhs, int inclhs, const float* rhs, int incrhs);
void kamasu_vector_vector_sub(int n, float* lhs, int inclhs, const float* rhs, int incrhs);
void kamasu_vector_vector_mul(int n, float* lhs, int inclhs, const float* rhs, int incrhs);
void kamasu_vector_vector_div(int n, float* lhs, int inclhs, const float* rhs, int incrhs);

enum Op { MULTIPLIES, PLUS, MINUS, DIVIDES, POW } ;

void kamasu_testy_knl(Op op, 
		      float* data, 
		      std::size_t n_entries,
		      unsigned n_dims, 
		      unsigned* factors, int* strides, 
		      float scalar);

void kamasu_aa_knl(Op op,
		   unsigned n_dims,
		   float* data_l,
		   float* data_r,
		   std::size_t factor_l1,
		   std::size_t factor_l2,
		   std::size_t factor_r1,
		   std::size_t factor_r2,
		   int stride_l1,
		   int stride_l2,
		   int stride_r1,
		   int stride_r2,
		   unsigned linear_size);

#define ENUMERATED_DECLS(Z, N, DATA)					\
  void BOOST_PP_CAT(kamasu_elementwise_array_scalar_,N)			\
    (Op op,								\
     float* data,							\
     std::size_t linear_size,						\
     const std::size_t* factors,					\
     const int* strides,						\
     float scalar);							\
  void BOOST_PP_CAT(kamasu_elementwise_array_array_,N)			\
    (Op op,								\
     std::size_t linear_size_l,						\
     float* data_l,							\
     float* data_r,							\
     const std::size_t* factors_l,					\
     const std::size_t* factors_r,					\
     const int* strides_l,						\
     const int* strides_r);


BOOST_PP_REPEAT_FROM_TO(1, KAMASU_MAX_ARRAY_DIM, ENUMERATED_DECLS, ~);

#endif
