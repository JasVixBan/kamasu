#include <resophonic/kamasu/config.hpp>
#include <resophonic/kamasu/logging.hpp>
#include <resophonic/kamasu/grammar.hpp>

#include <resophonic/pfeilhecht.h>

namespace resophonic {
  namespace kamasu {
  
    template <>
    ArrayScalarOp::result_type
    UnaryFunctionDispatch::operator()(resophonic::kamasu::/*OP*/_tag, 
				      const rk::array_impl</*T*/>& v,
				      const state_t&,
				      data_t& data)
    {
      rk::array_impl</*T*/> rv(v);
  
      log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

      switch (rv.nd) {					     
	/*'\n'.join(['''case %u: kamasu_unary_array_%s_%d(rv.data() + rv.offset, 
	  rv.linear_size, rv.factors, rv.strides, data.si.value); break;''' % (n, OP, n) for n in one_to_n])*/
      
      default:							
	throw std::runtime_error("kamasu internal error");		
      }								

      return rv;
    }
  }
}
