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

      log_trace("%s",  __PRETTY_FUNCTION__);
      //      log_trace("the type is: %s") % name_of(lrv);
      RESOPHONIC_KAMASU_THROW(lrv.nd() == 1, dimensions_dont_match());
      RESOPHONIC_KAMASU_THROW(rrv.nd() == 1, dimensions_dont_match());

      return cublasSdot(lrv.dim(0),
			lrv.data() + lrv.offset(),
			lrv.stride(0),
			rrv.data() + rrv.offset(),
			rrv.stride(0));
    }
  }
}

#endif



