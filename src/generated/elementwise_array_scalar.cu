//
//
// this is a generated file
//
//

#include <resophonic/kamasu/config.hpp>
#include <kernel.h>

// bah bah bah
__global__ void
kamasu_elementwise_array_scalar_1_knl
(Op op,
 float* data,
 unsigned linear_size,
 const std::size_t factor0,
 const int stride0,
 float scalar)
{
  if (INDEX >= linear_size)
    return;

  unsigned actual_index = 
    INDEX/factor0*stride0;

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

void 
kamasu_elementwise_array_scalar_1(Op op,
				      float* data, 
				      std::size_t linear_size,
				      const std::size_t* factors, 
				      const int* strides,
				      float scalar)
{
  bd_t bd = gridsize(linear_size);

  kamasu_elementwise_array_scalar_1_knl<<<bd.first, bd.second>>>
    (op, 
     data,
     linear_size,
     factors[0],
     strides[0],
     scalar);
}


#include <resophonic/kamasu/config.hpp>
#include <kernel.h>

// bah bah bah
__global__ void
kamasu_elementwise_array_scalar_2_knl
(Op op,
 float* data,
 unsigned linear_size,
 const std::size_t factor0, const std::size_t factor1,
 const int stride0, const int stride1,
 float scalar)
{
  if (INDEX >= linear_size)
    return;

  unsigned actual_index = 
    INDEX/factor1*stride1 +  unsigned(INDEX % factor1)/factor0*stride0;

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

void 
kamasu_elementwise_array_scalar_2(Op op,
				      float* data, 
				      std::size_t linear_size,
				      const std::size_t* factors, 
				      const int* strides,
				      float scalar)
{
  bd_t bd = gridsize(linear_size);

  kamasu_elementwise_array_scalar_2_knl<<<bd.first, bd.second>>>
    (op, 
     data,
     linear_size,
     factors[0],factors[1],
     strides[0],strides[1],
     scalar);
}


#include <resophonic/kamasu/config.hpp>
#include <kernel.h>

// bah bah bah
__global__ void
kamasu_elementwise_array_scalar_3_knl
(Op op,
 float* data,
 unsigned linear_size,
 const std::size_t factor0, const std::size_t factor1, const std::size_t factor2,
 const int stride0, const int stride1, const int stride2,
 float scalar)
{
  if (INDEX >= linear_size)
    return;

  unsigned actual_index = 
    INDEX/factor2*stride2 +  unsigned(INDEX % factor1)/factor0*stride0 +  unsigned(INDEX % factor2)/factor1*stride1;

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

void 
kamasu_elementwise_array_scalar_3(Op op,
				      float* data, 
				      std::size_t linear_size,
				      const std::size_t* factors, 
				      const int* strides,
				      float scalar)
{
  bd_t bd = gridsize(linear_size);

  kamasu_elementwise_array_scalar_3_knl<<<bd.first, bd.second>>>
    (op, 
     data,
     linear_size,
     factors[0],factors[1],factors[2],
     strides[0],strides[1],strides[2],
     scalar);
}


#include <resophonic/kamasu/config.hpp>
#include <kernel.h>

// bah bah bah
__global__ void
kamasu_elementwise_array_scalar_4_knl
(Op op,
 float* data,
 unsigned linear_size,
 const std::size_t factor0, const std::size_t factor1, const std::size_t factor2, const std::size_t factor3,
 const int stride0, const int stride1, const int stride2, const int stride3,
 float scalar)
{
  if (INDEX >= linear_size)
    return;

  unsigned actual_index = 
    INDEX/factor3*stride3 +  unsigned(INDEX % factor1)/factor0*stride0 +  unsigned(INDEX % factor2)/factor1*stride1 +  unsigned(INDEX % factor3)/factor2*stride2;

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

void 
kamasu_elementwise_array_scalar_4(Op op,
				      float* data, 
				      std::size_t linear_size,
				      const std::size_t* factors, 
				      const int* strides,
				      float scalar)
{
  bd_t bd = gridsize(linear_size);

  kamasu_elementwise_array_scalar_4_knl<<<bd.first, bd.second>>>
    (op, 
     data,
     linear_size,
     factors[0],factors[1],factors[2],factors[3],
     strides[0],strides[1],strides[2],strides[3],
     scalar);
}


#include <resophonic/kamasu/config.hpp>
#include <kernel.h>

// bah bah bah
__global__ void
kamasu_elementwise_array_scalar_5_knl
(Op op,
 float* data,
 unsigned linear_size,
 const std::size_t factor0, const std::size_t factor1, const std::size_t factor2, const std::size_t factor3, const std::size_t factor4,
 const int stride0, const int stride1, const int stride2, const int stride3, const int stride4,
 float scalar)
{
  if (INDEX >= linear_size)
    return;

  unsigned actual_index = 
    INDEX/factor4*stride4 +  unsigned(INDEX % factor1)/factor0*stride0 +  unsigned(INDEX % factor2)/factor1*stride1 +  unsigned(INDEX % factor3)/factor2*stride2 +  unsigned(INDEX % factor4)/factor3*stride3;

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

void 
kamasu_elementwise_array_scalar_5(Op op,
				      float* data, 
				      std::size_t linear_size,
				      const std::size_t* factors, 
				      const int* strides,
				      float scalar)
{
  bd_t bd = gridsize(linear_size);

  kamasu_elementwise_array_scalar_5_knl<<<bd.first, bd.second>>>
    (op, 
     data,
     linear_size,
     factors[0],factors[1],factors[2],factors[3],factors[4],
     strides[0],strides[1],strides[2],strides[3],strides[4],
     scalar);
}


