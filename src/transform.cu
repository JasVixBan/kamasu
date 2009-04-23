
#include "transform.hpp"
#include "kernel_util.hpp"

#include <iostream>
#include <proto_tags_fwd.hpp>
#include <resophonic/kamasu/tag.hpp>
#include "primitives.hpp"

#include <resophonic/kamasu/array.hpp>
#include <resophonic/kamasu/exception.hpp>


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

      unsigned thisthread_offset = actual_index(INDEX, vp.nd, vp.factors, vp.strides);

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
      cuda_check();
    }

#define INST(TYPE, TAG)							\
    template void transform<TYPE, TAG>(TYPE*, const view_params&, TYPE);

    INST(float, boost::proto::tag::plus);
    INST(float, boost::proto::tag::minus);
    INST(float, boost::proto::tag::multiplies);
    INST(float, boost::proto::tag::divides);
    INST(float, boost::proto::tag::assign);
    INST(float, resophonic::kamasu::tag::pow);

#undef INST

    //
    // array-array
    //
    template <typename T, typename Tag>
    __global__ void 
    transform_knl(T* data_l, view_params vp_l,
		  T* data_r, view_params vp_r)
    {
      if (INDEX >= vp_l.linear_size)
	return;

      unsigned lhs_off = actual_index(INDEX, vp_l.nd, vp_l.factors, vp_l.strides);
      unsigned rhs_off = actual_index(INDEX, vp_r.nd, vp_r.factors, vp_r.strides);

      op_impl_<T, Tag>::impl(data_l + lhs_off, data_r + rhs_off); 
    }

    template <typename T, typename Tag>
    void 
    transform(T* data_l, const view_params& vp_l,
	      T* data_r, const view_params& vp_r)
    {
      bd_t bd = gridsize(vp_l.linear_size, 16);
      
      transform_knl<T, Tag><<<bd.first, bd.second>>>(data_l + vp_l.offset, vp_l, 
						     data_r + vp_r.offset, vp_r); 
      cuda_check();
    }

#define INST(TYPE, TAG)							\
    template void transform<TYPE, TAG>(TYPE*, const view_params&,	\
				       TYPE*, const view_params&);

    INST(float, boost::proto::tag::plus);
    INST(float, boost::proto::tag::minus);
    INST(float, boost::proto::tag::divides);

#undef INST




  }
}


