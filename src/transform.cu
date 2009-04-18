
#include "transform.hpp"
#include "kernel_util.hpp"

#include <iostream>
#include <proto_tags_fwd.hpp>
#include <resophonic/kamasu/tag.hpp>
#include "primitives.hpp"

#include <resophonic/kamasu/array.hpp>


namespace resophonic {
  namespace kamasu {

    //
    // array-scalar
    //  
    template <typename T, typename Tag>
    __global__ void 
    transform_knl(T* data, view_params vp, T scalar)
    {
      if (INDEX >= vp.linear_size)
	return;

      unsigned thisthread_offset = actual_index(vp.nd, vp.factors, vp.strides);

      op_impl_<T, Tag>::impl(data + thisthread_offset, scalar); 
    }

    template <typename T, typename Tag>
    void 
    transform(T* data, const view_params& vp,
	      T scalar)
    {
      bd_t bd = gridsize(vp.linear_size);
      
      std::cout << "launch: " << bd.first << " " << bd.second << "\n"
		<< "nd = " << vp.nd << " factor0=" << vp.factors[0]
		<< " stride0 = " << vp.strides[0] << "\n";
      
      transform_knl<T, Tag><<<bd.first, bd.second>>>(data + vp.offset, vp, scalar);
    }

    namespace inst {
      template <typename T, typename Tag>
      struct eas 
      {
	eas()
	{
	  view_params vp;
	  transform<T, Tag>(0, vp, 0.0f);
	}
      };

      template struct eas<float, boost::proto::tag::plus>;
      template struct eas<float, boost::proto::tag::minus>;
      template struct eas<float, boost::proto::tag::multiplies>;
      template struct eas<float, boost::proto::tag::divides>;
      template struct eas<float, boost::proto::tag::assign>;
      template struct eas<float, resophonic::kamasu::tag::pow>;
    }

    //
    // array-array
    //
    template <typename T, int N, typename Tag>
    __global__ void 
    transform_knl(std::size_t linear_size,
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

      op_impl_<T, Tag>::impl(data_l + lhs_off, data_r + rhs_off); 
    }

    template <typename T, int N, typename Tag>
    void 
    transform(std::size_t linear_size,
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
      
      transform_knl<T, N, Tag><<<bd.first, bd.second, 0, stream>>>(linear_size, 
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
	  transform<T, 1, Tag>(0, 0, 0, 0, 0, 0, 0, 0);
	  transform<T, 2, Tag>(0, 0, 0, 0, 0, 0, 0, 0);
	  transform<T, 3, Tag>(0, 0, 0, 0, 0, 0, 0, 0);
	  transform<T, 4, Tag>(0, 0, 0, 0, 0, 0, 0, 0);
	  transform<T, 5, Tag>(0, 0, 0, 0, 0, 0, 0, 0);
	}
      };

      template struct iaao<float, boost::proto::tag::plus>;
      template struct iaao<float, boost::proto::tag::minus>;
      template struct iaao<float, boost::proto::tag::divides>;

    }



  }
}


