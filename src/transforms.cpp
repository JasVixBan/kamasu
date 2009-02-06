#include <resophonic/kamasu.hpp>
#include <resophonic/kamasu/logging.hpp>
#include "opmap.hpp"

#include <boost/mpl/map.hpp>

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
	  BOOST_ASSERT(lhs.dims->size() == 2);
	  BOOST_ASSERT(rhs.dims->size() == 2);
	  BOOST_ASSERT(lhs.dims->get(1) == rhs.dims->get(0));
	  
	  rk::array_impl<float, boost::mpl::true_> rv;
	  std::vector<std::size_t> shape;
	  shape.push_back(lhs.dims->get(0));
	  shape.push_back(rhs.dims->get(1));

	  BOOST_ASSERT(0);
	  rv.reshape(shape);
	  return rv;
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
	template <typename T>
	void operator()(T, 
			float* lhs, 
			std::size_t ndims,
			std::size_t last_index,
			unsigned* factors,
			int* strides,
			float scalar)
	{
	  log_trace("*** DISPATCH TO KERNEL ***");
	  BOOST_ASSERT(lhs);
	  BOOST_ASSERT(ndims);
	  BOOST_ASSERT(factors);
	  BOOST_ASSERT(last_index);
	  kamasu_testy_knl(op_map<T>::value, lhs, ndims, last_index, factors, strides, scalar);
	  log_trace("*** DONE DISPATCH TO KERNEL ***");
	  BOOST_ASSERT(lhs);
	  BOOST_ASSERT(ndims);
	  BOOST_ASSERT(factors);
	  BOOST_ASSERT(last_index);
	}
      };
    }

    template <typename Op, typename IsRVal>
    typename ArrayScalarOp::result_type
    ArrayScalarOp::operator()(Op, 
			      const rk::array_impl<float, IsRVal>& v, 
			      const float& f)
    {
      log_trace("*** CREATE TEMPORARY ***");
      rk::array_impl<float, boost::mpl::true_> rv(v);
      log_trace("*** DONE CREATE TEMPORARY ***");
      v.show();
      rv.show();

      BOOST_ASSERT(rv.dims->size());
      BOOST_ASSERT(v.dims->size());
      BOOST_ASSERT(rv.dims->get(0) > 0);
      BOOST_ASSERT(v.dims->get(0) > 0);

      BOOST_ASSERT(v.factors->size());
      BOOST_ASSERT(rv.factors->size());

      BOOST_ASSERT(v.dims->size() == rv.dims->size());
      BOOST_ASSERT(v.linear_size == rv.linear_size);
      
      v.factors->sync();
      v.strides->sync();
      detail::dispatch()(Op(), 
			 rv.data() + rv.offset,  
			 rv.linear_size,
			 rv.dims->size(), 
			 rv.factors->gpu_data(),
			 rv.strides->gpu_data(),
			 f);
      
      BOOST_ASSERT(rv.dims->size());
      BOOST_ASSERT(rv.dims->get(0) > 0);

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
      log_trace("%s") % __PRETTY_FUNCTION__;
      
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
    //INSTANTIATE_ARRAYARRAY_OP(tag::dot);
    //INSTANTIATE_ARRAYARRAY_OP(boost::proto::tag::divides);
    //INSTANTIATE_ARRAYARRAY_OP(boost::proto::tag::minus);


  }
}
