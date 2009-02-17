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
		   const rk::array_impl<float, RhsIsRVal>& rhs)
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

	template <typename LhsIsRVal, typename RhsIsRVal>
	rk::array_impl<float, boost::mpl::true_>
	operator()(bp::tag::plus_assign,
		   const rk::array_impl<float, LhsIsRVal>& lhs, 
		   const rk::array_impl<float, RhsIsRVal>& rhs)
	{
	  RESOPHONIC_KAMASU_THROW(lhs.nd != rhs.nd, dimensions_dont_match());
	  
	  for (int i=0; i<lhs.nd; i++)
	    RESOPHONIC_KAMASU_THROW(lhs.dim(i) != rhs.dim(i), 
				    dimensions_dont_match());

	  log_trace("%s", "*** DISPATCH TO ARRAY-ARRAY KERNEL ***");

	  switch (lhs.nd) {
	    std::cout<< "a.nd==" << lhs.nd << "\n";
#define DISPATCH_CASE(Z, N, DATA) case N:				\
             BOOST_PP_CAT(kamasu_elementwise_array_array_,N) \
	      (op_map<bp::tag::plus>::value,				\
	       lhs.linear_size,						\
	       lhs.data() + lhs.offset,					\
	       rhs.data() + rhs.offset,					\
	       lhs.factors,						\
	       rhs.factors,						\
	       lhs.strides,						\
	       rhs.strides);						\
	    break;

	    BOOST_PP_REPEAT_FROM_TO(1, KAMASU_MAX_ARRAY_DIM, DISPATCH_CASE, ~);

	  default:
	    throw std::runtime_error("kamasu internal error");
	  }

#undef DISPATCH_CASE
	  
	  log_trace("%s", "*** DONE DISPATCH TO AA KERNEL ***");
	  return rk::array_impl<float, boost::mpl::true_>();
	}

	void operator()(bp::tag::divides, 
			float* lhs, float * rhs, unsigned size)
	{
	  BOOST_ASSERT(size > 0);
	  kamasu_vector_vector_div(size, lhs, 1, rhs, 1);
	}
	void operator()(bp::tag::minus, 
			float* lhs, float * rhs, unsigned size)
	{
	  BOOST_ASSERT(size > 0);
	  kamasu_vector_vector_sub(size, lhs, 1, rhs, 1);
	}
	template <typename Op, typename T, typename IsRVal>
	void operator()(Op, 
			const rk::array_impl<T, IsRVal>& a,
			T scalar) 
	{
	  log_trace("%s", __PRETTY_FUNCTION__);
	  switch (a.nd) {
	    std::cout<< "a.nd==" << a.nd << "\n";
#define DISPATCH_CASE(Z, N, DATA)					\
	    case N:							\
	      log_trace("Case %d", N); \
	    BOOST_PP_CAT(kamasu_elementwise_array_scalar_,N)		\
	    (op_map<Op>::value,						\
	     a.data() + a.offset,					\
	     a.linear_size,						\
	     a.factors,							\
	     a.strides,							\
	     scalar);							\
	    break;

	    BOOST_PP_REPEAT_FROM_TO(1, KAMASU_MAX_ARRAY_DIM, DISPATCH_CASE, ~);

	  default:
	    throw std::runtime_error("kamasu internal error");
	  }

#undef DISPATCH_CASE

	}
      };
    }

    template <typename Op, typename IsRVal>
    typename ArrayScalarOp::result_type
    ArrayScalarOp::operator()(Op, 
			      const rk::array_impl<float, IsRVal>& v, 
			      const float& f)
    {
      log_trace("%s", "*** CREATE TEMPORARY ***");
      rk::array_impl<float, boost::mpl::true_> rv(v);
      log_trace("%s", "*** DONE CREATE TEMPORARY ***");
      v.show();
      rv.show();

      BOOST_ASSERT(rv.nd > 0);

      BOOST_ASSERT(v.linear_size == rv.linear_size);
      
      //      int* eff = rv.impl_->strides.gpu_data();
      //      BOOST_ASSERT(eff);

      detail::dispatch()(Op(), rv, f);
      
      return rv;
    }

#define INST_ARRAYSCALAR(OP, TF)					\
    template ArrayScalarOp::result_type					\
    ArrayScalarOp::operator()(OP, const rk::array_impl<float, boost::mpl:: TF > &, \
			      const float&);
    
    INST_ARRAYSCALAR(boost::proto::tag::plus, true_);
    INST_ARRAYSCALAR(boost::proto::tag::plus, false_);
    INST_ARRAYSCALAR(boost::proto::tag::minus, true_);
    INST_ARRAYSCALAR(boost::proto::tag::minus, false_);
    INST_ARRAYSCALAR(boost::proto::tag::divides, true_);
    INST_ARRAYSCALAR(boost::proto::tag::divides, false_);
    INST_ARRAYSCALAR(boost::proto::tag::multiplies, true_);
    INST_ARRAYSCALAR(boost::proto::tag::multiplies, false_);
    INST_ARRAYSCALAR(resophonic::kamasu::tag::pow, true_);
    INST_ARRAYSCALAR(resophonic::kamasu::tag::pow, false_);

    template <typename Op, typename LhsIsRVal, typename RhsIsRVal>
    typename ArrayArrayOp::result_type
    ArrayArrayOp::operator()(Op,
			       const rk::array_impl<float, LhsIsRVal>& lhs, 
			       const rk::array_impl<float, RhsIsRVal>& rhs)
    {
      log_trace("%s",  __PRETTY_FUNCTION__);
      
      return detail::dispatch()(Op(), lhs, rhs);
    }

#define INSTANTIATE_ARRAYARRAY_OP_IMPL(OP, LRV, RRV) template		\
    ArrayArrayOp::result_type						\
    ArrayArrayOp::operator()(OP,					\
			     const rk::array_impl<float, boost::mpl:: LRV>&, \
			     const rk::array_impl<float, boost::mpl:: RRV>&);
    
#define INSTANTIATE_ARRAYARRAY_OP(OP)					\
    INSTANTIATE_ARRAYARRAY_OP_IMPL(OP, false_, false_);			\
	INSTANTIATE_ARRAYARRAY_OP_IMPL(OP, false_, true_);		\
	INSTANTIATE_ARRAYARRAY_OP_IMPL(OP, true_, false_);		\
	INSTANTIATE_ARRAYARRAY_OP_IMPL(OP, true_, true_);

    //INSTANTIATE_ARRAYARRAY_OP(boost::proto::tag::plus);
    INSTANTIATE_ARRAYARRAY_OP(boost::proto::tag::multiplies);
    INSTANTIATE_ARRAYARRAY_OP(boost::proto::tag::plus_assign);
    //INSTANTIATE_ARRAYARRAY_OP(tag::dot);
    //INSTANTIATE_ARRAYARRAY_OP(boost::proto::tag::divides);
    //INSTANTIATE_ARRAYARRAY_OP(boost::proto::tag::minus);


  }
}
