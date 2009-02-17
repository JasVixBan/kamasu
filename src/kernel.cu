#define BOOST_NO_EXCEPTIONS

#include <resophonic/kamasu/config.hpp>
#include <resophonic/kamasu/mirror.hpp>
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

  for (int i = n_dims-1; i>=0; i--)
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
  else if (op == POW)
    data[actual_index] = pow(data[actual_index], scalar);
}

#define BOOST_PP_ITERATION_LIMITS (1, KAMASU_MAX_ARRAY_DIM-1)
#define BOOST_PP_FILENAME_1 "kernel.ipp"
#include BOOST_PP_ITERATE()


void kamasu_testy_knl(Op op,
		      float* data, 
		      std::size_t linear_size,
		      unsigned n_dims, 
		      unsigned* factors, int* strides, 
		      float scalar)
{
  bd_t bd = gridsize(linear_size);
  //printf("%s with gridsize %u %u\n", __PRETTY_FUNCTION__, bd.first, bd.second);
  //printf("n_dims=%u linear_size=%zu", n_dims, linear_size);
  
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


