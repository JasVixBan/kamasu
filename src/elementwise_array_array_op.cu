
#include "elementwise_array_scalar_op.hpp"
#include "kernel_util.hpp"

#include <proto_tags_fwd.hpp>
#include <resophonic/kamasu/tag.hpp>
#include <stdexcept>

namespace resophonic {
  namespace kamasu {

    template <typename T>
    __device__ void 
    op_impl(T* l, T* r, ::boost::proto::tag::plus)
    {
      *l += *r;
    }

    template <typename T>
    __device__ void 
    op_impl(T* l, T* r, ::boost::proto::tag::minus)
    {
      (*l) -= *r;
    }

    template <typename T>
    __device__ void 
    op_impl(T* l, T* r, ::boost::proto::tag::multiplies)
    {
      (*l) *= *r;
    }

    template <typename T>
    __device__ void 
    op_impl(T* l, T* r, ::boost::proto::tag::divides)
    {
      (*l) /= *r;
    }

    template <typename T, int N, typename Tag>
    __global__ void 
    eaa_knl(std::size_t linear_size,
	    T* data_l,
	    T* data_r,
	    argpack<std::size_t, N> factors_l,
	    argpack<std::size_t, N> factors_r,
	    argpack<int, N> strides_l,
	    argpack<int, N> strides_r)
    {
      if (INDEX >= linear_size)
	return;

      unsigned lhs_off = actual_index<N>(factors_l, strides_l);
      unsigned rhs_off = actual_index<N>(factors_r, strides_r);

      op_impl(data_l + lhs_off, data_r + rhs_off, Tag()); 
    }

    template <typename T, int N, typename Tag>
    void 
    elementwise_array_array_op(std::size_t linear_size,
			       T* data_l,
			       T* data_r,
			       const std::size_t* factors_l,
			       const std::size_t* factors_r,
			       const int* strides_l,
			       const int* strides_r,
			       cudaStream_t stream)
    {
      bd_t bd = gridsize(linear_size);
      
      argpack<std::size_t, N> factors_l_(factors_l);
      argpack<int, N> strides_l_(strides_l);
      
      argpack<std::size_t, N> factors_r_(factors_r);
      argpack<int, N> strides_r_(strides_r);
      
      eaa_knl<T, N, Tag><<<bd.first, bd.second, 0, stream>>>(linear_size, 
							     data_l, data_r, 
							     factors_l_, factors_r_,
							     strides_l_, strides_r_);
    }

    namespace inst 
    {
      template <typename T, typename Tag>
      struct iaao
      {
	iaao()
	{
	  cudaStream_t s;
	  elementwise_array_array_op<T, 1, Tag>(0U, 0, 0, 0, 0, 0, 0, s);
	  elementwise_array_array_op<T, 2, Tag>(0, 0, 0, 0, 0, 0, 0, s);
	  elementwise_array_array_op<T, 3, Tag>(0, 0, 0, 0, 0, 0, 0, s);
	  elementwise_array_array_op<T, 4, Tag>(0, 0, 0, 0, 0, 0, 0, s);
	  elementwise_array_array_op<T, 5, Tag>(0, 0, 0, 0, 0, 0, 0, s);
	}
      };

      template struct iaao<float, boost::proto::tag::plus>;
      template struct iaao<float, boost::proto::tag::minus>;
      template struct iaao<float, boost::proto::tag::divides>;

    }
    template void elementwise_array_array_op<float, 5, boost::proto::tag::minus>(unsigned long, float*, float*, unsigned long const*, unsigned long const*, int const*, int const*, int);
  }
}

