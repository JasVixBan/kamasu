#ifndef RESOPHONIC_KAMASU_DOT_HPP_INCLUDED
#define RESOPHONIC_KAMASU_DOT_HPP_INCLUDED

#include "cublas.h"

#include <resophonic/kamasu/array.hpp>
#include <resophonic/kamasu/array_impl.hpp>
#include <resophonic/kamasu/grammar.hpp>

namespace resophonic {
  namespace kamasu {

    template <typename LExpr, typename RExpr>
    float
    dot(LExpr const& lhs, RExpr const& rhs) {

      array<float, boost::mpl::true_> lrv, rrv;

      lrv = lhs; // force evaluation of lhs, rhs
      rrv = rhs;

      log_trace("%s") % __PRETTY_FUNCTION__;
      log_trace("the type is: %s") % name_of(lrv);
      BOOST_ASSERT(lrv.dims->size() == 1);
      BOOST_ASSERT(rrv.dims->size() == 1);

      return cublasSdot(lrv.self().dims->get(0),
			lrv.self().data() + lrv.self().offset,
			lrv.self().strides->get(0),
			rrv.self().data() + rrv.self().offset,
			rrv.self().strides->get(0));
    }
  }
}

#endif



