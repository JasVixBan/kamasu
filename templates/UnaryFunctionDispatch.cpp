#include <resophonic/kamasu/config.hpp>
#include <resophonic/kamasu/logging.hpp>
#include <resophonic/kamasu/grammar.hpp>

#include "generated/unary_array_op.h"

namespace resophonic {
  namespace kamasu {
  
    template <>
    ArrayScalarOp::result_type
    UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::/*OP*/, 
				      const rk::array_impl</*T*/, /*RVAL*/>& v,
				      const rk::stream_impl& si) 
    {
      rk::array_impl</*T*/, boost::mpl::true_> rv(v);
  
      log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

      switch (rv.nd) {					     
	/*'\n'.join(['''case %u: kamasu_unary_array_%s_%d(rv.data() + rv.offset, 
	  rv.linear_size, rv.factors, rv.strides, si.value); break;''' % (n, OP, n) for n in one_to_n])*/
      
      default:							
	throw std::runtime_error("kamasu internal error");		
      }								

      return rv;
    }
  }
}
