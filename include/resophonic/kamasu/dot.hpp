#ifndef RESOPHONIC_KAMASU_DOT_HPP_INCLUDED
#define RESOPHONIC_KAMASU_DOT_HPP_INCLUDED

#include "cublas.h"

#include <resophonic/kamasu/array_impl.hpp>
#include <resophonic/kamasu/grammar.hpp>

namespace resophonic {
  namespace kamasu {

    template <typename LExpr, typename RExpr>
    float dot(LExpr const& lhs, RExpr const& rhs)
    {
      array_impl<float, boost::mpl::true_> lrv, rrv;
      lrv = Grammar()(lhs);
      rrv = Grammar()(rhs);
      

      log_trace("%s") % __PRETTY_FUNCTION__;
      log_trace("the type is: %s") % name_of(lrv);
      BOOST_ASSERT(lrv.dims->size() == 1);
      BOOST_ASSERT(rrv.dims->size() == 1);

      return cublasSdot(lrv.dims->get(0),
			lrv.data() + lrv.offset,
			lrv.strides->get(0),
			rrv.data() + rrv.offset,
			rrv.strides->get(0));
    }
  }
}

#endif
