//
//
// this is a generated file
//
//

#include <resophonic/kamasu/config.hpp>
#include <resophonic/kamasu/grammar.hpp>
#include <resophonic/kamasu/exception.hpp>

#include "transform.hpp"

namespace resophonic {
  namespace kamasu {


    template <typename Tag, typename T>
    ArrayScalarOp::result_type
    ArrayScalarOp::operator()(Tag,
			      const rk::array_impl<T>& rv, 
			      T scalar,
			      const state_t&,
			      data_t& data)
    {
      transform<float, Tag>(rv.data(), rv.view_p(), scalar);
      cuda_check();

      return rv;
    }

#define INSTANTIATE(TYPE, TAG)						\
    template array_impl<TYPE>						\
    ArrayScalarOp::operator()<TAG,					\
      TYPE>(TAG,							\
	    resophonic::kamasu::array_impl<TYPE> const&,		\
	    TYPE,							\
	    resophonic::kamasu::state_t const&,				\
	    resophonic::kamasu::data_t&);

    INSTANTIATE(float, boost::proto::tag::multiplies);
    INSTANTIATE(float, boost::proto::tag::assign);
    INSTANTIATE(float, boost::proto::tag::plus);
    INSTANTIATE(float, boost::proto::tag::minus);
    INSTANTIATE(float, boost::proto::tag::divides);
    INSTANTIATE(float, resophonic::kamasu::tag::pow);


  }
}

