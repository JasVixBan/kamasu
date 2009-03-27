#include <resophonic/kamasu.hpp>
#include <resophonic/kamasu/config.hpp>
#include <resophonic/kamasu/logging.hpp>
#include <resophonic/kamasu/make_vector.hpp>

#include "opmap.hpp"

#include <boost/mpl/map.hpp>

#include <cublas.h>
#include <cutil.h>

namespace resophonic {
  namespace kamasu {

    namespace detail {

      struct dispatch
      {

	template <typename LhsIsRVal, typename RhsIsRVal>
	rk::array_impl<float, boost::mpl::true_>
	operator()(bp::tag::multiplies,
		   const rk::array_impl<float, LhsIsRVal>& lhs, 
		   const rk::array_impl<float, RhsIsRVal>& rhs,
		   const stream_impl& si)
	{
	  BOOST_ASSERT(lhs.nd == 2);
	  BOOST_ASSERT(rhs.nd == 2);
	  std::size_t lhs_rows = lhs.dim(0);
	  std::size_t lhs_cols = lhs.dim(1);
	  std::size_t rhs_rows = rhs.dim(0);
	  std::size_t rhs_cols = rhs.dim(1);

	  BOOST_ASSERT(lhs_cols == rhs_rows);

	  std::vector<std::size_t> shp = make_vector(lhs_rows, rhs_cols);
	  rk::array_impl<float, boost::mpl::true_> rv;
	  rv.reshape(shp);

	  //   C = alpha * op(A) * op(B) + beta * C
	  
	  cublasSgemm('n', // transa, no trans 
		      'n', // transb, no trans
		      lhs_rows, // rows of lhs and rows of result
		      rhs_cols, // cols of rhs and cols of result
		      lhs_cols, // number columns of op(A) and rows of op(B)
		      1.0, // alpha 
		      lhs.data(), // data of lhs
		      lhs_rows, // leading dimension of lhs
		      rhs.data(), // data of rhs
		      rhs_rows, // leading dimension of rhs
		      0, // beta.  if zero, C just gets overwritten
		      rv.data(), // pointer to C
		      lhs_rows // leading dim of C
		      );
	  
	  cublasStatus s = cublasGetError();
	  if (s != CUBLAS_STATUS_SUCCESS)
	    throw cublas_exception(s);
	  return rv;
	}

	// 
	//    +=
	//

	template <typename LhsIsRVal, typename RhsIsRVal>
	rk::array_impl<float, boost::mpl::true_>
	operator()(bp::tag::plus_assign,
		   const rk::array_impl<float, LhsIsRVal>& lhs, 
		   const rk::array_impl<float, RhsIsRVal>& rhs,
		   const stream_impl& s)
	{
	  RESOPHONIC_KAMASU_THROW(lhs.nd != rhs.nd, dimensions_dont_match());
	  
	  for (int i=0; i<lhs.nd; i++)
	    RESOPHONIC_KAMASU_THROW(lhs.dim(i) != rhs.dim(i), 
				    dimensions_dont_match());

	  log_trace("%s", "*** DISPATCH TO ARRAY-ARRAY KERNEL ***");

	  log_trace("a.nd==%u", lhs.nd);

	  switch (lhs.nd) {
#define DISPATCH_CASE(Z, N, DATA) case N:				\
	    log_trace("firing with nd=%u", lhs.nd);\
             BOOST_PP_CAT(kamasu_elementwise_array_array_,N) \
	      (op_map<bp::tag::plus>::value,				\
	       lhs.linear_size,						\
	       lhs.data() + lhs.offset,					\
	       rhs.data() + rhs.offset,					\
	       lhs.factors,						\
	       rhs.factors,						\
	       lhs.strides,						\
	       rhs.strides,						\
	       s.value);						\
	    break;

	    BOOST_PP_REPEAT_FROM_TO(1, KAMASU_MAX_ARRAY_DIM, DISPATCH_CASE, ~);

	  default:
	    throw std::runtime_error("kamasu internal error");
	  }

#undef DISPATCH_CASE
	  
	  log_trace("%s", "*** DONE DISPATCH TO AA KERNEL ***");
	  return rk::array_impl<float, boost::mpl::true_>();
	}

	//
	//  general elementwise case
	//
	template <typename Op, typename LhsIsRVal, typename RhsIsRVal>
	rk::array_impl<float, boost::mpl::true_>
	operator()(Op,
		   const rk::array_impl<float, LhsIsRVal>& lhs, 
		   const rk::array_impl<float, RhsIsRVal>& rhs,
		   const stream_impl& s)
	{
	  RESOPHONIC_KAMASU_THROW(lhs.nd != rhs.nd, dimensions_dont_match());
	  
	  const rk::array_impl<float, boost::mpl::true_> rv(lhs);

	  for (int i=0; i<lhs.nd; i++)
	    RESOPHONIC_KAMASU_THROW(lhs.dim(i) != rhs.dim(i), 
				    dimensions_dont_match());

	  log_trace("%s", "*** DISPATCH TO ARRAY-ARRAY KERNEL ***");

	  log_trace("a.nd==%u", rv.nd);

	  switch (rv.nd) {
#define DISPATCH_CASE(Z, N, DATA) case N:				\
	    log_trace("firing with nd=%u", rv.nd);\
	    BOOST_PP_CAT(kamasu_elementwise_array_array_,N)		\
	      (op_map<Op>::value,					\
	       rv.linear_size,						\
	       rv.data() + rv.offset,					\
	       rhs.data() + rhs.offset,					\
	       rv.factors,						\
	       rhs.factors,						\
	       rv.strides,						\
	       rhs.strides,						\
	       s.value);						\
	    break;

	    BOOST_PP_REPEAT_FROM_TO(1, KAMASU_MAX_ARRAY_DIM, DISPATCH_CASE, ~);

	  default:
	    throw std::runtime_error("kamasu internal error");
	  }

#undef DISPATCH_CASE
	  
	  log_trace("%s", "*** DONE DISPATCH TO AA KERNEL ***");
	  return rv;
	}

      };
    }

    template <typename Op, typename LhsIsRVal, typename RhsIsRVal>
    typename ArrayArrayOp::result_type
    ArrayArrayOp::operator()(Op,
			     const rk::array_impl<float, LhsIsRVal>& lhs, 
			     const rk::array_impl<float, RhsIsRVal>& rhs,
			     const state_t&,
			     data_t& data)
    {
      log_trace("%s",  __PRETTY_FUNCTION__);
      
      return detail::dispatch()(Op(), lhs, rhs, data.si);
    }

#define INSTANTIATE_ARRAYARRAY_OP_IMPL(OP, LRV, RRV) template		\
    ArrayArrayOp::result_type						\
    ArrayArrayOp::operator()(OP,					\
			     const rk::array_impl<float, boost::mpl:: LRV>&, \
			     const rk::array_impl<float, boost::mpl:: RRV>&, \
			     const state_t&, data_t&);
    
#define INSTANTIATE_ARRAYARRAY_OP(OP)					\
    INSTANTIATE_ARRAYARRAY_OP_IMPL(OP, false_, false_);			\
	INSTANTIATE_ARRAYARRAY_OP_IMPL(OP, false_, true_);		\
	INSTANTIATE_ARRAYARRAY_OP_IMPL(OP, true_, false_);		\
	INSTANTIATE_ARRAYARRAY_OP_IMPL(OP, true_, true_);
    
    INSTANTIATE_ARRAYARRAY_OP(boost::proto::tag::plus);
    INSTANTIATE_ARRAYARRAY_OP(boost::proto::tag::minus);
    INSTANTIATE_ARRAYARRAY_OP(boost::proto::tag::multiplies);
    INSTANTIATE_ARRAYARRAY_OP(boost::proto::tag::divides);
    INSTANTIATE_ARRAYARRAY_OP(boost::proto::tag::plus_assign);
    //INSTANTIATE_ARRAYARRAY_OP(tag::dot);
    //INSTANTIATE_ARRAYARRAY_OP(boost::proto::tag::divides);
    //INSTANTIATE_ARRAYARRAY_OP(boost::proto::tag::minus);

  }
}
