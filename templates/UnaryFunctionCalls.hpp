#ifndef RESOPHONIC_KAMASU_UNARY_FUNCTION_CALLS_HPP_INCLUDED
#define RESOPHONIC_KAMASU_UNARY_FUNCTION_CALLS_HPP_INCLUDED

#include <resophonic/kamasu/generated/UnaryFunctionTags.hpp>
#include <resophonic/kamasu/policy_switch.hpp>

namespace resophonic {
  namespace kamasu {

    namespace detail {
      template <typename Expr>
      struct fncall2fntag 
      {
	typedef typename Expr::proto_child0 child0;
	typedef typename boost::proto::result_of::value<child0>::type value;
	typedef typename boost::remove_reference<value>::type noref;
	typedef typename boost::remove_const<noref>::type noconst;
	typedef noconst type;
      };
    }

    struct UnaryFunctionDispatch : bp::callable
    {
      typedef rk::array_impl<float, boost::mpl::true_> result_type;

      template <typename Op, typename IsRVal>
      result_type 
      operator()(Op, const rk::array_impl<float, IsRVal>& v);
    };

    struct UnaryFunctionCases
    {
      template <typename Tag, int _=0>
      struct case_ : boost::proto::not_<boost::proto::_>
      { };

      /*'\n'.join(['''
	template <int _> struct case_<tag::%s,_> 
	: boost::proto::when<boost::proto::function<boost::proto::terminal<tag::%s>, Array>, 
	UnaryFunctionDispatch(tag::%s(), Array(boost::proto::_child1))> { };
	''' % (fn, fn, fn) for fn in functions])*/
    };

    struct UnaryFunctionCalls 
      : boost::proto::policy_switch<UnaryFunctionCases, detail::fncall2fntag> 
    { };

  }
}

#endif
