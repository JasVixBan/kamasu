#include "kernel_util.hpp"

namespace resophonic {
  namespace kamasu {

    __global__ void
    kamasu_elementwise_array_array_knl_/*N*/(Op op,
					     std::size_t linear_size,
					     float* data_l,
					     float* data_r,
					     /*enum('const std::size_t factor_l%d', N)*/,
					     /*enum('const std::size_t factor_r%d', N)*/,
					     /*enum('const int stride_l%d', N)*/,
					     /*enum('const int stride_r%d', N)*/)
    {
      if (INDEX >= linear_size)
	return;

      unsigned actual_index_l = /* ' + '.join(['INDEX/factor_l%d*stride_l%d' % (N-1, N-1)]+[' unsigned(INDEX %% factor_l%d)/factor_l%d*stride_l%d' % (n+1,n,n) for n in range(N-1)]) */;
      unsigned actual_index_r = /* ' + '.join(['INDEX/factor_r%d*stride_r%d' % (N-1, N-1)]+[' unsigned(INDEX %% factor_r%d)/factor_r%d*stride_r%d' % (n+1,n,n) for n in range(N-1)]) */;

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
    kamasu_elementwise_array_array_/*N*/(Op op,
					 std::size_t linear_size,
					 float* data_l,
					 float* data_r,
					 const std::size_t* factors_l,
					 const std::size_t* factors_r,
					 const int* strides_l,
					 const int* strides_r,
					 cudaStream_t stream)
    {
      bd_t bd = gridsize(linear_size);
  
      kamasu_elementwise_array_array_knl_/*N*/<<<bd.first, bd.second, 0, stream>>>
	(op, 
	 linear_size,
	 data_l,
	 data_r,
	 /*enum('factors_l[%d]', N)*/,
	 /*enum('factors_r[%d]', N)*/,
	 /*enum('strides_l[%d]', N)*/,
	 /*enum('strides_r[%d]', N)*/);
    }

  }
}
