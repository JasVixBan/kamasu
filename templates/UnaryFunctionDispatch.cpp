#include <resophonic/kamasu/config.hpp>
#include <resophonic/kamasu/logging.hpp>
#include <resophonic/kamasu/grammar.hpp>

#include "unary_array_op.h"

namespace resophonic {
  namespace kamasu {
  
    template <>
    UnaryFunctionDispatch::result_type
    UnaryFunctionDispatch::operator()(resophonic::kamasu::/*OP*/_tag, 
				      const rk::array_impl</*T*/>& v,
				      const state_t&,
				      data_t& data)
    {
      log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

      switch (v.nd()) {					     
	/*'\n'.join(['''case %u: unary_array_%s_%d(v.data() + v.offset(), 
	  v.linear_size(), v.factors(), v.strides(), data.si.value); break;''' % (n, OP, n) for n in one_to_n])*/
      
      default:							
	throw std::runtime_error("kamasu internal error");		
      }								

      return v;
    }
  }
}
