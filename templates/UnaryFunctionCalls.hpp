#ifndef RESOPHONIC_KAMASU_UNARY_FUNCTION_CALLS_HPP_INCLUDED
#define RESOPHONIC_gKAMASU_UNARY_FUNCTION_CALLS_HPP_INCLUDED

#include <resophonic/kamasu/state.hpp>
#include <resophonic/kamasu/data.hpp>
#include <resophonic/kamasu/generated/UnaryFunctionTags.hpp>

namespace resophonic {
  namespace kamasu {

    struct UnaryFunctionDispatch : bp::callable
    {
      typedef rk::array_impl<float> result_type;

      template <typename Op>
      result_type 
      operator()(Op, 
		 const rk::array_impl<float>& v,
		 const state_t&,
		 data_t&);
    };

    struct UnaryFunctionCases
    {
      template <typename Tag, int _=0>
      struct case_ : boost::proto::not_<boost::proto::_>
      { };

      /*'\n'.join(['''
	template <int _> struct case_<%s_tag,_> 
	: boost::proto::when<boost::proto::unary_expr<%s_tag, Array>, 
	UnaryFunctionDispatch(%s_tag(), 
	                      Array(boost::proto::_child0, 
                                    boost::proto::_state, boost::proto::_data), 
                              boost::proto::_state, boost::proto::_data)> { };
	''' % (fn, fn, fn) for fn in functions])*/
    };

    struct UnaryFunctionCalls 
      : boost::proto::switch_<UnaryFunctionCases> 
    { };

  }
}

#endif
