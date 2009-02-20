#include <resophonic/kamasu/config.hpp>
#include <resophonic/kamasu/grammar.hpp>
#include "opmap.hpp"
#include "generated/elementwise_array_scalar.h"

namespace resophonic {
  namespace kamasu {


    template <>
    ArrayScalarOp::result_type
    ArrayScalarOp::operator()(/*OP*/, 
			      const rk::array_impl</*T*/, /*RVAL*/>& v, 
			      const /*T*/& scalar)
    {
      rk::array_impl</*T*/, boost::mpl::true_> rv(v);

      switch (rv.nd) {
	/*'\n'.join(['case %u:  kamasu_elementwise_array_scalar_%d(op_map<%s>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;' % (this_n, this_n, OP) for this_n in one_to_n])*/

      default:
	throw std::runtime_error("kamasu internal error");
      }

      
      return rv;
    }
  }

}


