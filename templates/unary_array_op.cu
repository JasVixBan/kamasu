#include "kernel_util.hpp"
#include <resophonic/kamasu/view_params.hpp>

namespace resophonic {
  namespace kamasu {

    __global__ void
    unary_array_/*OP*/_/*N*/_knl
    (float* data,
     unsigned linear_size,
     /*', '.join(['const factor_t factor%d' % x for x in range(N)])*/,
     /*', '.join(['const stride_t stride%d' % x for x in range(N)])*/)
    {
      if (INDEX >= linear_size)
	return;

      unsigned actual_index = /* ' + '.join([' unsigned(INDEX/factor%d)*stride%d' % (n,n) for n in range(N)]) */;

      data[actual_index] = /*OP*/(data[actual_index]);
    }

    void 
    unary_array_/*OP*/_/*N*/(float* data, 
				    std::size_t linear_size,
				    const factor_t* factors, 
				    const stride_t* strides,
				    cudaStream_t stream)
    {
      bd_t bd = gridsize(linear_size);

      unary_array_/*OP*/_/*N*/_knl<<<bd.first, bd.second, 0, stream>>>
	(data,
	 linear_size,
	 /*','.join(['factors[%d]' % x for x in range(N)])*/,
	 /*','.join(['strides[%d]' % x for x in range(N)])*/);
    }

  }
}
