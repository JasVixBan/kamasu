//
//
// this is a generated file
//
//

#include <resophonic/kamasu/config.hpp>
#include "kernel.h"

__global__ void
kamasu_elementwise_array_array_knl_1(Op op,
					 std::size_t linear_size,
					 float* data_l,
					 float* data_r,
					 const std::size_t factor_l0,
					 const std::size_t factor_r0,
					 const int stride_l0,
					 const int stride_r0)
{
  if (INDEX >= linear_size)
    return;

  unsigned actual_index_l = INDEX/factor_l0*stride_l0;
  unsigned actual_index_r = INDEX/factor_r0*stride_r0;

  if (op == MULTIPLIES)
    data_l[actual_index_l] *= data_r[actual_index_r];
  else if (op == DIVIDES)
    data_l[actual_index_l] /= data_r[actual_index_r];
  else if (op == PLUS)
    data_l[actual_index_l] += data_r[actual_index_r];
  else if (op == MINUS)
    data_l[actual_index_l] -= data_r[actual_index_r];
}

void 
kamasu_elementwise_array_array_1(Op op,
				     std::size_t linear_size,
				     float* data_l,
				     float* data_r,
				     const std::size_t* factors_l,
				     const std::size_t* factors_r,
				     const int* strides_l,
				     const int* strides_r)
{
  bd_t bd = gridsize(linear_size);
  
  kamasu_elementwise_array_array_knl_1<<<bd.first, bd.second>>>
    (op, 
     linear_size,
     data_l,
     data_r,
     factors_l[0],
     factors_r[0],
     strides_l[0],
     strides_r[0]);
}

#include <resophonic/kamasu/config.hpp>
#include "kernel.h"

__global__ void
kamasu_elementwise_array_array_knl_2(Op op,
					 std::size_t linear_size,
					 float* data_l,
					 float* data_r,
					 const std::size_t factor_l0,const std::size_t factor_l1,
					 const std::size_t factor_r0,const std::size_t factor_r1,
					 const int stride_l0,const int stride_l1,
					 const int stride_r0,const int stride_r1)
{
  if (INDEX >= linear_size)
    return;

  unsigned actual_index_l = INDEX/factor_l1*stride_l1 +  unsigned(INDEX % factor_l1)/factor_l0*stride_l0;
  unsigned actual_index_r = INDEX/factor_r1*stride_r1 +  unsigned(INDEX % factor_r1)/factor_r0*stride_r0;

  if (op == MULTIPLIES)
    data_l[actual_index_l] *= data_r[actual_index_r];
  else if (op == DIVIDES)
    data_l[actual_index_l] /= data_r[actual_index_r];
  else if (op == PLUS)
    data_l[actual_index_l] += data_r[actual_index_r];
  else if (op == MINUS)
    data_l[actual_index_l] -= data_r[actual_index_r];
}

void 
kamasu_elementwise_array_array_2(Op op,
				     std::size_t linear_size,
				     float* data_l,
				     float* data_r,
				     const std::size_t* factors_l,
				     const std::size_t* factors_r,
				     const int* strides_l,
				     const int* strides_r)
{
  bd_t bd = gridsize(linear_size);
  
  kamasu_elementwise_array_array_knl_2<<<bd.first, bd.second>>>
    (op, 
     linear_size,
     data_l,
     data_r,
     factors_l[0],factors_l[1],
     factors_r[0],factors_r[1],
     strides_l[0],strides_l[1],
     strides_r[0],strides_r[1]);
}

#include <resophonic/kamasu/config.hpp>
#include "kernel.h"

__global__ void
kamasu_elementwise_array_array_knl_3(Op op,
					 std::size_t linear_size,
					 float* data_l,
					 float* data_r,
					 const std::size_t factor_l0,const std::size_t factor_l1,const std::size_t factor_l2,
					 const std::size_t factor_r0,const std::size_t factor_r1,const std::size_t factor_r2,
					 const int stride_l0,const int stride_l1,const int stride_l2,
					 const int stride_r0,const int stride_r1,const int stride_r2)
{
  if (INDEX >= linear_size)
    return;

  unsigned actual_index_l = INDEX/factor_l2*stride_l2 +  unsigned(INDEX % factor_l1)/factor_l0*stride_l0 +  unsigned(INDEX % factor_l2)/factor_l1*stride_l1;
  unsigned actual_index_r = INDEX/factor_r2*stride_r2 +  unsigned(INDEX % factor_r1)/factor_r0*stride_r0 +  unsigned(INDEX % factor_r2)/factor_r1*stride_r1;

  if (op == MULTIPLIES)
    data_l[actual_index_l] *= data_r[actual_index_r];
  else if (op == DIVIDES)
    data_l[actual_index_l] /= data_r[actual_index_r];
  else if (op == PLUS)
    data_l[actual_index_l] += data_r[actual_index_r];
  else if (op == MINUS)
    data_l[actual_index_l] -= data_r[actual_index_r];
}

void 
kamasu_elementwise_array_array_3(Op op,
				     std::size_t linear_size,
				     float* data_l,
				     float* data_r,
				     const std::size_t* factors_l,
				     const std::size_t* factors_r,
				     const int* strides_l,
				     const int* strides_r)
{
  bd_t bd = gridsize(linear_size);
  
  kamasu_elementwise_array_array_knl_3<<<bd.first, bd.second>>>
    (op, 
     linear_size,
     data_l,
     data_r,
     factors_l[0],factors_l[1],factors_l[2],
     factors_r[0],factors_r[1],factors_r[2],
     strides_l[0],strides_l[1],strides_l[2],
     strides_r[0],strides_r[1],strides_r[2]);
}

#include <resophonic/kamasu/config.hpp>
#include "kernel.h"

__global__ void
kamasu_elementwise_array_array_knl_4(Op op,
					 std::size_t linear_size,
					 float* data_l,
					 float* data_r,
					 const std::size_t factor_l0,const std::size_t factor_l1,const std::size_t factor_l2,const std::size_t factor_l3,
					 const std::size_t factor_r0,const std::size_t factor_r1,const std::size_t factor_r2,const std::size_t factor_r3,
					 const int stride_l0,const int stride_l1,const int stride_l2,const int stride_l3,
					 const int stride_r0,const int stride_r1,const int stride_r2,const int stride_r3)
{
  if (INDEX >= linear_size)
    return;

  unsigned actual_index_l = INDEX/factor_l3*stride_l3 +  unsigned(INDEX % factor_l1)/factor_l0*stride_l0 +  unsigned(INDEX % factor_l2)/factor_l1*stride_l1 +  unsigned(INDEX % factor_l3)/factor_l2*stride_l2;
  unsigned actual_index_r = INDEX/factor_r3*stride_r3 +  unsigned(INDEX % factor_r1)/factor_r0*stride_r0 +  unsigned(INDEX % factor_r2)/factor_r1*stride_r1 +  unsigned(INDEX % factor_r3)/factor_r2*stride_r2;

  if (op == MULTIPLIES)
    data_l[actual_index_l] *= data_r[actual_index_r];
  else if (op == DIVIDES)
    data_l[actual_index_l] /= data_r[actual_index_r];
  else if (op == PLUS)
    data_l[actual_index_l] += data_r[actual_index_r];
  else if (op == MINUS)
    data_l[actual_index_l] -= data_r[actual_index_r];
}

void 
kamasu_elementwise_array_array_4(Op op,
				     std::size_t linear_size,
				     float* data_l,
				     float* data_r,
				     const std::size_t* factors_l,
				     const std::size_t* factors_r,
				     const int* strides_l,
				     const int* strides_r)
{
  bd_t bd = gridsize(linear_size);
  
  kamasu_elementwise_array_array_knl_4<<<bd.first, bd.second>>>
    (op, 
     linear_size,
     data_l,
     data_r,
     factors_l[0],factors_l[1],factors_l[2],factors_l[3],
     factors_r[0],factors_r[1],factors_r[2],factors_r[3],
     strides_l[0],strides_l[1],strides_l[2],strides_l[3],
     strides_r[0],strides_r[1],strides_r[2],strides_r[3]);
}

#include <resophonic/kamasu/config.hpp>
#include "kernel.h"

__global__ void
kamasu_elementwise_array_array_knl_5(Op op,
					 std::size_t linear_size,
					 float* data_l,
					 float* data_r,
					 const std::size_t factor_l0,const std::size_t factor_l1,const std::size_t factor_l2,const std::size_t factor_l3,const std::size_t factor_l4,
					 const std::size_t factor_r0,const std::size_t factor_r1,const std::size_t factor_r2,const std::size_t factor_r3,const std::size_t factor_r4,
					 const int stride_l0,const int stride_l1,const int stride_l2,const int stride_l3,const int stride_l4,
					 const int stride_r0,const int stride_r1,const int stride_r2,const int stride_r3,const int stride_r4)
{
  if (INDEX >= linear_size)
    return;

  unsigned actual_index_l = INDEX/factor_l4*stride_l4 +  unsigned(INDEX % factor_l1)/factor_l0*stride_l0 +  unsigned(INDEX % factor_l2)/factor_l1*stride_l1 +  unsigned(INDEX % factor_l3)/factor_l2*stride_l2 +  unsigned(INDEX % factor_l4)/factor_l3*stride_l3;
  unsigned actual_index_r = INDEX/factor_r4*stride_r4 +  unsigned(INDEX % factor_r1)/factor_r0*stride_r0 +  unsigned(INDEX % factor_r2)/factor_r1*stride_r1 +  unsigned(INDEX % factor_r3)/factor_r2*stride_r2 +  unsigned(INDEX % factor_r4)/factor_r3*stride_r3;

  if (op == MULTIPLIES)
    data_l[actual_index_l] *= data_r[actual_index_r];
  else if (op == DIVIDES)
    data_l[actual_index_l] /= data_r[actual_index_r];
  else if (op == PLUS)
    data_l[actual_index_l] += data_r[actual_index_r];
  else if (op == MINUS)
    data_l[actual_index_l] -= data_r[actual_index_r];
}

void 
kamasu_elementwise_array_array_5(Op op,
				     std::size_t linear_size,
				     float* data_l,
				     float* data_r,
				     const std::size_t* factors_l,
				     const std::size_t* factors_r,
				     const int* strides_l,
				     const int* strides_r)
{
  bd_t bd = gridsize(linear_size);
  
  kamasu_elementwise_array_array_knl_5<<<bd.first, bd.second>>>
    (op, 
     linear_size,
     data_l,
     data_r,
     factors_l[0],factors_l[1],factors_l[2],factors_l[3],factors_l[4],
     factors_r[0],factors_r[1],factors_r[2],factors_r[3],factors_r[4],
     strides_l[0],strides_l[1],strides_l[2],strides_l[3],strides_l[4],
     strides_r[0],strides_r[1],strides_r[2],strides_r[3],strides_r[4]);
}

