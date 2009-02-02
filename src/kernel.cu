#include "kernel.h"
#include "cutil.h"
#include <stdio.h>
#include <cublas.h>
#include <map>

#define SDATA( index)      CUT_BANK_CHECKER(sdata, index)

#include <boost/preprocessor.hpp>

////////////////////////////////////////////////////////////////////////////////
//! Simple test kernel for device functionality
//! @param g_idata  input data in global memory
//! @param g_odata  output data in global memory
////////////////////////////////////////////////////////////////////////////////
__device__ float doit(float f)
{
  return f + 1.0f;
}

__global__ void
testKernel( float* g_idata, float* g_odata) 
{
  // shared memory
  // the size is determined by the host application
  extern  __shared__  float sdata[];

  // access thread id
  const unsigned int tid = threadIdx.x +
    + threadIdx.y * blockDim.x 
    + threadIdx.z * blockDim.y * blockDim.x; 

  // read in input data from global memory
  // use the bank checker macro to check for bank conflicts during host
  // emulation
  sdata[tid] = g_idata[tid];
  //__syncthreads();

  // perform some computations
  sdata[tid] = doit(sdata[tid]);
  //__syncthreads();

  // write data to global memory
  g_odata[tid] = sdata[tid];
}

#define X      threadIdx.x  
#define XSIZE  blockDim.x
#define Y      blockIdx.x
#define YSIZE  gridDim.x
#define Z      blockIdx.y
#define ZSIZE  gridDim.y

#define INDEX (Z * YSIZE * XSIZE + Y * XSIZE + X)

__global__ void
gpu_add_elem_knl(float* g_idata1, float* g_idata2, float* g_odata) 
{
  g_odata[INDEX] = g_idata1[INDEX] + g_idata2[INDEX];
}

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


//
//  vector-scalar knls
//

__global__ void
gpu_add_scalar_k(float* data, float scalar) 
{
  data[INDEX] += scalar;
}

__global__ void
gpu_sub_scalar_k(float* data, float scalar) 
{
  data[INDEX] -= scalar;
}

__global__ void
gpu_mul_scalar_k(float* data, float scalar) 
{
  data[INDEX] *= scalar;
}

__global__ void
gpu_div_scalar_k(float* data, float scalar) 
{
  data[INDEX] /= scalar;
}


//
//  c-iface scalar
//

void gpu_mul_scalar(float* data, unsigned size, float scalar)
{
  cublasSscal(size, scalar, data, 1);
  //  gpu_mul_scalar_k<<<gridsize(size), threads_per_block>>>(data, scalar);
}

void gpu_add_scalar(float* data, unsigned size, float scalar)
{
  bd_t bd = gridsize(size);
  gpu_add_scalar_k<<<bd.first, bd.second>>>(data, scalar);
}

void gpu_sub_scalar(float* data, unsigned size, float scalar)
{
  bd_t bd = gridsize(size);
  gpu_sub_scalar_k<<<bd.first, bd.second>>>(data, scalar);
}

void gpu_div_scalar(float* data, unsigned size, float scalar)
{
  cublasSscal(size, 1.0f/scalar, data, 1);
}





//
//  vector-vector knls
//

__global__ void
gpu_add_vector_k(float* lhs, float* rhs) 
{
  lhs[INDEX] += rhs[INDEX];
}

__global__ void
gpu_sub_vector_k(float* lhs, float* rhs) 
{
  lhs[INDEX] -= rhs[INDEX];
}

__global__ void
gpu_mul_vector_k(float* lhs, float* rhs) 
{
  lhs[INDEX] *= rhs[INDEX];
}

__global__ void
gpu_div_vector_k(float* lhs, float* rhs) 
{
  lhs[INDEX] /= rhs[INDEX];
}

/*
//
//  c-iface vector
//
void gpu_mul_vector(float* lhs, float* rhs, unsigned size)
{
  printf(">>> gpu_mul_vector %u %u\n", gridsize(size), threads_per_block);
  gpu_mul_vector_k<<<gridsize(size), threads_per_block>>>(lhs, rhs);
}

void gpu_add_vector(float* lhs, float* rhs, unsigned size)
{
  gpu_add_vector_k<<<gridsize(size), threads_per_block>>>(lhs, rhs);
}

void gpu_sub_vector(float* lhs, float* rhs, unsigned size)
{
  gpu_sub_vector_k<<<gridsize(size), threads_per_block>>>(lhs, rhs);
}

void gpu_div_vector(float* lhs, float* rhs, unsigned size)
{
  gpu_div_vector_k<<<gridsize(size), threads_per_block>>>(lhs, rhs);
}
*/
//
//  testing:  add to matrix
//
                                                            
__global__ void
kamasu_testy_knl_thunk(Op op,
		       float* data,
		       unsigned linear_size,
		       unsigned n_dims,
		       unsigned* factors,
		       int* strides,
		       float scalar)
{
  unsigned index = INDEX;
  unsigned actual_index = 0;

  if (INDEX >= linear_size)
    return;

  for (unsigned i = 0; i<n_dims; i++)
    {
      unsigned this_component = index / factors[i];
      actual_index += this_component * strides[i];
      index -= this_component * factors[i];
    }

  if (op == MULTIPLIES)
    data[actual_index] *= scalar;
  else if (op == DIVIDES)
    data[actual_index] /= scalar;
  else if (op == PLUS)
    data[actual_index] += scalar;
  else if (op == MINUS)
    data[actual_index] -= scalar;
}


void kamasu_testy_knl(Op op,
		      float* data, 
		      std::size_t linear_size,
		      unsigned n_dims, 
		      unsigned* factors, int* strides, 
		      float scalar)
{
  bd_t bd = gridsize(linear_size);
  printf("%s with gridsize %u %u\n", __PRETTY_FUNCTION__, bd.first, bd.second);
  kamasu_testy_knl_thunk<<<bd.first, bd.second>>>(op, 
						  data,
						  linear_size,
						  n_dims,
						  factors,
						  strides,
						  scalar);
}


#define SCALAR_KNL(Z, N, DATA)						\
  __global__ void							\
  gpu_add_scalar_knl_ ## N						\
  (float* data, unsigned offset,					\
   BOOST_PP_ENUM_PARAMS(N, unsigned dim),				\
   BOOST_PP_ENUM_PARAMS(N, unsigned factor),				\
   BOOST_PP_ENUM_PARAMS(N, unsigned stride),				\
   float scalar)							\
  {									\
    unsigned index = INDEX;						\
    unsigned r = 0;							\
  }

//SCALAR_KNL(~, 1, ~)
//SCALAR_KNL(~, 2, ~)
//SCALAR_KNL(~, 3, ~)

/*
void gpu_mul_scalar(float* data, unsigned size, float scalar)
{
  cublasSscal(size, scalar, data, 1);
  //  gpu_mul_scalar_k<<<gridsize(size), threads_per_block>>>(data, scalar);
}
*/


//
//  3x4
//
//  0,0 0,1 0,2 0,3     1,0 1,1 1,2 1,3     2,0 2,1 2,2 2,3
//
//  1  2  3  4
//  5  6  7  8
//  9  10 11 12
//

// take index 11:  (should be (2,3))
// 11 % 4 = 3,    11-3 = 8


// index 4:  1,0  == 1*4 + 0*1
// index 5:  1,1  == 1*4 + 1,1
