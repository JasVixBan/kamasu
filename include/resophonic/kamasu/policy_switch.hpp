#ifndef RESOPHONIC_KAMASU_POLICY_SWITCH_HPP_INCLUDED
#define RESOPHONIC_KAMASU_POLICY_SWITCH_HPP_INCLUDED

#include <boost/proto/proto.hpp>

namespace boost {
  namespace proto {
    
    template<typename Cases, 
	     template <class> class Policy = boost::proto::tag_of>
    struct policy_switch 
      : boost::proto::transform<policy_switch<Cases, Policy> >
    {
      typedef policy_switch<Cases, Policy> proto_base_expr;

      template<typename Expr, typename State, typename Data>
      struct impl
	: Cases::template case_<

	typename Policy<Expr>::type

	>::template impl<Expr, State, Data>
      { };

      template<typename Expr, typename State, typename Data>
      struct impl<Expr &, State, Data>
	: Cases::template case_<
	
	typename Policy<Expr>::type
	
	>::template impl<Expr &, State, Data>
      { };
    };

    namespace detail {
      
      // if you don't specialize matches_, it won't match and you will
      // pull your hair and wring your hands.

      template<typename Expr, typename Cases, template <class> class Policy>
      struct matches_<Expr, policy_switch<Cases, Policy> >
	: matches_<
	Expr
	, typename Cases::template case_<typename Policy<Expr>::type>::proto_base_expr
	>
      { };
    }
  }
}

#endif
