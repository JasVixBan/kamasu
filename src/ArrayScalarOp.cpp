//
//
// this is a generated file
//
//

#include <resophonic/kamasu/config.hpp>
#include <resophonic/kamasu/grammar.hpp>
#include <resophonic/kamasu/exception.hpp>

#include "elementwise_array_scalar_op.hpp"

namespace resophonic {
  namespace kamasu {


    template <typename Tag>
    ArrayScalarOp::result_type
    ArrayScalarOp::operator()(Tag,
			      const rk::array_impl<float>& rv, 
			      const float& scalar,
			      const state_t&,
			      data_t& data)
    {
      switch (rv.nd) {
      case 1:  transform<float, 1, Tag>(rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
      case 2:  transform<float, 2, Tag>(rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
      case 3:  transform<float, 3, Tag>(rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
      case 4:  transform<float, 4, Tag>(rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
      case 5:  transform<float, 5, Tag>(rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;

      default:
	throw std::runtime_error("kamasu internal error");
      }

      cuda_check();

      return rv;
    }

    //    namespace {
      template <typename T, typename Tag>
      struct instantiate
      {
	instantiate() {
	  array_impl<T> rv;
	  float scalar;
	  state_t s;
	  data_t data;
	  ArrayScalarOp()(Tag(), rv, scalar, s, data);
	}
      };
    
      template struct instantiate<float, boost::proto::tag::plus>;
      template struct instantiate<float, boost::proto::tag::minus>;
      template struct instantiate<float, boost::proto::tag::multiplies>;
      template struct instantiate<float, boost::proto::tag::divides>;
      template struct instantiate<float, boost::proto::tag::assign>;
      template struct instantiate<float, resophonic::kamasu::tag::pow>;
    //    }
  }
}

