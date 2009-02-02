#include <resophonic/kamasu/logging.hpp>
#include <resophonic/kamasu/holder.hpp>
#include <resophonic/kamasu/dumper_context.hpp>
#include <resophonic/kamasu/array_impl.hpp>

#include "cutil.h"
#include <cassert>

namespace resophonic 
{
  namespace kamasu 
  {
    template<typename T, typename RVal>
    array_impl<T, RVal>::array_impl() 
      : impl(new holder<T>), 
	dims(new holder<unsigned>), 
	factors(new holder<unsigned>), 
	strides(new holder<int>),
	linear_size(0),
	offset(0)
    { 
    }

    namespace
    {
      template <typename T>
      void 
      construct(array_impl<T, boost::mpl::true_>& lhs, 
		const array_impl<T, boost::mpl::true_ >& rhs)
      {
	lhs.impl = rhs.impl;
	lhs.dims = rhs.dims;
	lhs.strides = rhs.strides;
	lhs.factors = rhs.factors;

	lhs.offset = rhs.offset;
	lhs.linear_size = rhs.linear_size;
      }

      template <typename T>
      void 
      construct(array_impl<T,  boost::mpl::false_>& lhs, 
		const array_impl <T, boost::mpl::true_ >& rhs)
      {
	lhs.impl = rhs.impl;
	lhs.dims = rhs.dims;
	lhs.strides = rhs.strides;
	lhs.factors = rhs.factors;

	lhs.offset = rhs.offset;
	lhs.linear_size = rhs.linear_size;
      }

      template <typename T>
      void 
      construct(array_impl<T, boost::mpl::false_>& lhs,
		const array_impl<T, boost::mpl::false_>& rhs)
      {
	lhs.impl = rhs.impl->clone();
	lhs.dims = rhs.dims->clone();
	lhs.strides = rhs.strides->clone();
	lhs.factors = rhs.factors->clone();

	lhs.offset = rhs.offset;
	lhs.linear_size = rhs.linear_size;
      }

      template <typename T>
      void 
      construct(array_impl<T, boost::mpl::true_>& lhs,
		const array_impl<T, boost::mpl::false_>& rhs)
      {
	lhs.impl = rhs.impl->clone();
	lhs.dims = rhs.dims->clone();
	lhs.strides = rhs.strides->clone();
	lhs.factors = rhs.factors->clone();

	lhs.offset = rhs.offset;
	lhs.linear_size = rhs.linear_size;
      }
    }

    template <typename T, typename RVal>
    void
    array_impl<T, RVal>::show() const
    {
      log_trace("____ Array ____");
      log_trace("ndim %u  / stride %u / offset %u") % dims->size() % strides->size() % offset;
      for (unsigned i=0; i < dims->size(); i++)
	log_trace("dims[%u]      %u") % i % dims->get(i);
      for (unsigned i=0; i < factors->size(); i++)
	log_trace("factors[%u]   %u") % i % factors->get(i);
      for (unsigned i=0; i < strides->size(); i++)
	log_trace("stride[%u]   %u") % i % strides->get(i);
      log_trace("off      %lu") % offset;
      log_trace("last     %lu") % linear_size;
    }

    template<typename T, typename RVal>
    array_impl<T, RVal>::array_impl(const array_impl<T, RVal>& rhs)
    {
      log_trace("%s") % __PRETTY_FUNCTION__;
      construct(*this, rhs);
    }

    template<typename T, typename RVal>
    array_impl<T, RVal>::array_impl(const array_impl<T, other_t>& rhs)
    {
      log_trace("%s") % __PRETTY_FUNCTION__;
      construct(*this, rhs);
    }

    template <typename T, typename RVal>
    void
    array_impl<T, RVal>::reshape(const std::vector<std::size_t>& shape)
    {
      log_trace("reshape");
      dims->resize(shape.size());
      strides->resize(shape.size());
      factors->resize(shape.size());
      offset = 0;
      for (int i=0; i<shape.size(); i++)
	dims->set(i, shape[i]);
      std::size_t newsize = calculate_strides();
      calculate_factors();
      impl->resize(newsize);
    }

    template <typename T, typename RVal>
    std::size_t
    array_impl<T, RVal>::calculate_strides()
    {
      // this also calculates size but do we need this here...
      std::size_t size = 1;
      strides->resize(dims->size());
      for(unsigned i=0; i<dims->size(); i++)
	{
	  BOOST_ASSERT(dims->get(i) != 0);
	  size *= dims->get(i);
	  strides->set(i, 1);
	  for (unsigned j=i+1; j<dims->size(); j++)
	    {
	      int s = strides->get(i);
	      s *= dims->get(j);
	      strides->set(i, s);
	    }
	}

      log_trace("size=%u") % size;
      for (unsigned i=0; i<dims->size(); i++)
	log_trace("dim %u is %u, stride %u") % i % dims->get(i) % strides->get(i);
      return size;
    }

    template <typename T, typename RVal>
    void 
    array_impl<T, RVal>::calculate_factors()
    {
      factors->resize(dims->size());
      BOOST_ASSERT(dims->size() > 0);
      linear_size = 1;
      for(unsigned i=0; i<dims->size(); i++)
	{
	  unsigned dim = dims->get(i);
	  BOOST_ASSERT(dim != 0);
	  factors->set(i, 1);
	  linear_size *= dim;
	  for (unsigned j=i+1; j<dims->size(); j++)
	    {
	      unsigned f = factors->get(i);
	      f *= dims->get(j);
	      factors->set(i, f);
	    }
	}

      for (unsigned i=0; i<dims->size(); i++)
	log_trace("dim %u is %u, factor %u") 
	  % i % dims->get(i) % factors->get(i);
      log_trace("linear size is %u") % linear_size; 
    }

    template <typename T, typename RVal>
    void array_impl<T, RVal>::reset()
    {
      impl.reset();
    }

    template<typename T, typename RVal>
    void 
    array_impl<T, RVal>::copy_from(const array_impl<T, boost::mpl::true_>& rhs)
    {
      log_trace("%s") % __PRETTY_FUNCTION__;
      rhs.show();

      impl = rhs.impl;

      dims = rhs.dims;
      BOOST_ASSERT(rhs.dims->size());
      BOOST_ASSERT(dims->size() == rhs.dims->size());

      strides = rhs.strides;
      BOOST_ASSERT(rhs.dims->size());
      BOOST_ASSERT(strides->size() == rhs.strides->size());

      factors = rhs.factors;
      BOOST_ASSERT(rhs.factors->size());
      BOOST_ASSERT(factors->size() == rhs.factors->size());

      offset = rhs.offset;
      linear_size = rhs.linear_size;
    }

    template<typename T, typename RVal>
    void
    array_impl<T, RVal>::copy_from(const array_impl<T, boost::mpl::false_>& rhs)
    {
      log_trace("%s") % __PRETTY_FUNCTION__;
      rhs.show();
      impl = rhs.impl->clone();

      dims = rhs.dims->clone();
      BOOST_ASSERT(dims->size());
      BOOST_ASSERT(dims->size() == rhs.dims->size());

      strides = rhs.strides->clone();
      BOOST_ASSERT(strides->size());
      BOOST_ASSERT(strides->size() == rhs.strides->size());

      factors = rhs.factors->clone();
      BOOST_ASSERT(rhs.factors->size());
      BOOST_ASSERT(factors->size() == rhs.factors->size());

      offset = rhs.offset;
      linear_size = rhs.linear_size;
    }

    template<typename T, typename RVal>
    std::size_t
    array_impl<T, RVal>::size() const
    {
      return impl->size();
    }

    template<typename T, typename RVal>
    T*
    array_impl<T, RVal>::data() const
    {
      return impl->data();
    }

    template<typename T, typename RVal>
    array_impl<T, RVal>::~array_impl()
    { 
    }

    template class array_impl<float, boost::mpl::false_>;
    template class array_impl<float, boost::mpl::true_>;

  }
}

