#include <resophonic/kamasu/grammar.hpp>
#include <resophonic/kamasu/make_vector.hpp>
#include "transform.hpp"

namespace resophonic 
{
  namespace kamasu 
  {

    template <typename T, typename Tag>
    typename ArrayArrayOp::result_type
    ArrayArrayOp::operator()(Tag,
			     const rk::array_impl<T>& lhs, 
			     const rk::array_impl<T>& rhs,
			     const state_t& state,
			     data_t& data)
    {
      log_trace("%s",  __PRETTY_FUNCTION__);
      
      RESOPHONIC_KAMASU_THROW(lhs.nd != rhs.nd, dimensions_dont_match());
	  
      const rk::array_impl<float> rv(lhs);

      for (unsigned i=0; i<lhs.nd(); i++)
	RESOPHONIC_KAMASU_THROW(lhs.dim(i) != rhs.dim(i), 
				dimensions_dont_match());

      log_trace("%s", "*** DISPATCH TO ARRAY-ARRAY KERNEL ***");
      
      log_trace("a.nd==%u", rv.nd);

      transform<float, Tag>(rv.data(), rv.view_p(),
			    rhs.data(), rhs.view_p());

      return rv;
    }

#define INST(TYPE, TAG)							\
    template array_impl<TYPE>						\
    ArrayArrayOp::operator()<TYPE, TAG>					\
      (TAG,								\
       array_impl<TYPE> const&, array_impl<TYPE> const&,		\
       state_t const&, data_t&);

    INST(float, boost::proto::tag::plus);
    INST(float, boost::proto::tag::minus);
    INST(float, boost::proto::tag::divides);

    template <typename T, typename Tag>
    class instantiate
    {
      instantiate() {
	array_impl<T> rv;
	state_t s;
	data_t data;
	ArrayArrayOp()(Tag(), rv, rv, s, data);
      }
    };
    
    template struct instantiate<float, boost::proto::tag::plus>;
    template struct instantiate<float, boost::proto::tag::minus>;
    template struct instantiate<float, boost::proto::tag::divides>;

    template <>
    ArrayArrayOp::result_type
    ArrayArrayOp::operator()(boost::proto::tag::multiplies,
			     const rk::array_impl<float>& lhs, 
			     const rk::array_impl<float>& rhs,
			     const state_t&,
			     data_t& data)
    {
      BOOST_ASSERT(lhs.nd == 2);
      BOOST_ASSERT(rhs.nd == 2);
      std::size_t lhs_rows = lhs.dim(0);
      std::size_t lhs_cols = lhs.dim(1);
      std::size_t rhs_rows = rhs.dim(0);
      std::size_t rhs_cols = rhs.dim(1);

      BOOST_ASSERT(lhs_cols == rhs_rows);

      std::vector<std::size_t> shp = make_vector(lhs_rows, rhs_cols);

      rk::array_impl<float> rv;
      if (data.tmp)
	{
	  rv = *data.tmp;
	  data.tmp = 0;
	}
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

    template <>
    ArrayArrayOp::result_type
    ArrayArrayOp::operator()(boost::proto::tag::plus_assign,
			     const rk::array_impl<float>& lhs, 
			     const rk::array_impl<float>& rhs,
			     const state_t& state,
			     data_t& data)
    {
      return ArrayArrayOp()(boost::proto::tag::plus(),
			    lhs, rhs, state, data);
    }


  }
}
