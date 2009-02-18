#include "kernel.h"
#include "cutil.h"

//
//
//  ops
//
//  

__global__ void
kamasu_elementwise_array_/*OP*/_/*N*/_knl
(float* data,
 unsigned linear_size,
 /*', '.join(['const std::size_t factor%d' % x for x in range(N)])*/,
 /*', '.join(['const int stride%d' % x for x in range(N)])*/)
{
  if (INDEX >= linear_size)
    return;

  unsigned actual_index = /* ' + '.join([' unsigned(INDEX/factor%d)*stride%d' % (n,n) for n in range(N)]) */;

  data[actual_index] = /*OP*/(data[actual_index]);
}

void 
BOOST_PP_CAT(kamasu_elementwise_array_/*OP*/_/*N*/(float* data, 
							std::size_t linear_size,
							const std::size_t* factors, 
							const int* strides)
{
  bd_t bd = gridsize(linear_size);

  kamasu_elementwise_array_/*OP*/_/*N*/_knl<<<bd.first, bd.second>>>
    (data,
     linear_size,
     /*','.join(['factors[%d]' % x for x in range(N)])*/,
     /*','.join(['strides[%d]' % x for x in range(N)])*/);
}

