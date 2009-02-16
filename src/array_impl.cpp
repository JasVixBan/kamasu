#include <resophonic/kamasu/logging.hpp>
#include <resophonic/kamasu/holder.hpp>
#include <resophonic/kamasu/dumper_context.hpp>
#include <resophonic/kamasu/array_impl.hpp>

#include "pool.hpp"
#include "cutil.h"
#include <cuda_runtime.h>
#include <cassert>

#include <boost/bind.hpp>

namespace resophonic 
{
  namespace kamasu 
  {

    template<typename T, typename RVal>
    void
    array_impl<T, RVal>::alloc() 
    {
      data_ = boost::shared_ptr<holder<T> >(new (holder_pool::malloc()) holder<T>,
					    (void (*)(void*))holder_pool::free);
      impl_ = boost::shared_ptr<detail::impl_t>(new (impl_pool::malloc()) detail::impl_t,
					       (void (*)(void*))impl_pool::free);
    } 

    template<typename T, typename RVal>
    array_impl<T, RVal>::array_impl() 
      : /*data_(new (holder_pool::malloc()) holder<float>,
	      (void (*)(void*))holder_pool::free),
	      impl_(new (impl_pool::malloc()) detail::impl_t,
	      (void (*)(void*))impl_pool::free),*/
	linear_size(0),
	offset(0)
    { }

    namespace
    {
      template <typename T>
      void 
      construct(array_impl<T, boost::mpl::true_>& lhs, 
		const array_impl<T, boost::mpl::true_ >& rhs)
      {
	lhs.nd = rhs.nd;
	lhs.data_ = rhs.data_;
	lhs.impl_ = rhs.impl_;

	lhs.offset = rhs.offset;
	lhs.linear_size = rhs.linear_size;
      }

      template <typename T>
      void 
      construct(array_impl<T,  boost::mpl::false_>& lhs, 
		const array_impl <T, boost::mpl::true_ >& rhs)
      {
	lhs.nd = rhs.nd;
	lhs.data_ = rhs.data_;
	lhs.impl_ = rhs.impl_;

	lhs.offset = rhs.offset;
	lhs.linear_size = rhs.linear_size;
      }

      template <typename T>
      void 
      construct(array_impl<T, boost::mpl::false_>& lhs,
		const array_impl<T, boost::mpl::false_>& rhs)
      {
	lhs.nd = rhs.nd;
	lhs.impl_ = rhs.impl_ ? rhs.impl_->clone() : rhs.impl_;
	lhs.data_ = rhs.data_ ? rhs.data_->clone() : rhs.data_;

	lhs.offset = rhs.offset;
	lhs.linear_size = rhs.linear_size;
      }

      template <typename T>
      void 
      construct(array_impl<T, boost::mpl::true_>& lhs,
		const array_impl<T, boost::mpl::false_>& rhs)
      {
	lhs.nd = rhs.nd;
	lhs.impl_ = rhs.impl_ ? rhs.impl_->clone() : rhs.impl_;
	lhs.data_ = rhs.data_ ? rhs.data_->clone() : rhs.data_;

	lhs.offset = rhs.offset;
	lhs.linear_size = rhs.linear_size;
      }
    }

    template<typename T, typename RVal>
    array_impl<T, RVal>::array_impl(const this_t& rhs)
    {
      log_trace("%s",  __PRETTY_FUNCTION__);
      construct(*this, rhs);
    }

    template<typename T, typename RVal>
    array_impl<T, RVal>::array_impl(const other_t& rhs)
    {
      log_trace("%s",  __PRETTY_FUNCTION__);
      construct(*this, rhs);
    }

    template <typename T, typename RVal>
    void
    array_impl<T, RVal>::reshape(const std::vector<std::size_t>& shape, bool realloc)
    {
      log_trace("%s", "reshape");
      if (!impl_) alloc();
      detail::impl_t& impl = *impl_;
      offset = 0;
      nd = 0;
      for (int i=0; i<shape.size(); i++)
	{
	  if (shape[i] != 0)
	    {
	      impl.dims.set(nd, shape[i]);
	      nd++;
	    }
	}

      std::size_t newsize = calculate_strides();
      calculate_factors();
      if (realloc)
	data_->resize(newsize);
    }

    template <typename T, typename RVal>
    void
    array_impl<T, RVal>::reshape(std::size_t shape, bool realloc)
    {
      if (!impl_) alloc();
      detail::impl_t& impl = *impl_;
      log_trace("%s", "reshape");
      offset = 0;
      nd = 1;
      impl.dims.set(0u, shape);
      impl.strides.set(0u, 1);
      impl.factors.set(0u, 1);
      linear_size = shape;
      if (realloc)
	data_->resize(shape);
    }

    template <typename T, typename RVal>
    std::size_t
    array_impl<T, RVal>::calculate_strides()
    {
      detail::impl_t& impl = *impl_;
      // this also calculates size but do we need this here...
      unsigned stride = 1;
      impl.strides.set(0, stride);

      for(unsigned i=1; i<nd; i++)
	{
	  stride *= impl.dims.get(i-1);
	  impl.strides.set(i, stride);
	}

      for (unsigned i=0; i<nd; i++)
	log_trace("dim %u is %u, stride %u",  i % impl.dims.get(i) % impl.strides.get(i));

      std::size_t size = 1;
      for (int i=0; i<nd; i++)
	size *= impl.dims.get(i);
      return size;
    }

    template <typename T, typename RVal>
    void 
    array_impl<T, RVal>::calculate_factors()
    {
      BOOST_ASSERT(nd > 0);
      detail::impl_t& impl = *impl_;
      linear_size = 1;
      impl.factors.set(0, 1);
      unsigned prev_factor = 1;
      linear_size = impl.dims.get(0);
      for(unsigned i=1; i<nd; i++)
	{
	  unsigned dim_left = impl.dims.get(i-1);
	  unsigned newfactor = dim_left * prev_factor;
	  impl.factors.set(i, newfactor);
	  prev_factor = newfactor;

	  linear_size *= impl.dims.get(i);
	}


      for (unsigned i=0; i<nd; i++)
	log_trace("dim %u is %u, factor %u", 
		  i % impl.dims.get(i) % impl.factors.get(i));
      log_trace("linear size is %u", linear_size); 
    }

    template <typename T, typename RVal>
    void array_impl<T, RVal>::reset()
    {
      impl_.reset();
    }


    template<typename T, typename RVal>
    void 
    array_impl<T, RVal>::copy_from(const array_impl<T, boost::mpl::true_>& rhs)
    {
#if RESOPHONIC_KAMASU_DEBUG
      log_trace("%s",  __PRETTY_FUNCTION__);
      rhs.show();
#endif
      nd = rhs.nd;
      impl_ = rhs.impl_;
      data_ = rhs.data_;
      offset = rhs.offset;
      linear_size = rhs.linear_size;
    }

    template<typename T, typename RVal>
    void
    array_impl<T, RVal>::copy_from(const array_impl<T, boost::mpl::false_>& rhs)
    {
#if RESOPHONIC_KAMASU_DEBUG
      log_trace("%s",  __PRETTY_FUNCTION__);
      rhs.show();
#endif
      nd = rhs.nd;
      impl_ = rhs.impl_;
      data_ = rhs.data_;

      offset = rhs.offset;
      linear_size = rhs.linear_size;
    }

    template<typename T, typename RVal>
    void
    array_impl<T, RVal>::copy_into(this_t& rhs) const
    {
      log_trace("%s",  __PRETTY_FUNCTION__);
      rhs.nd = nd;
      rhs.data_ = data_->clone();
      rhs.impl_ = impl_->clone();

      rhs.offset = offset;
      rhs.linear_size = linear_size;
    }

    template<typename T, typename RVal>
    void
    array_impl<T, RVal>::copy_into(other_t& rhs) const
    {
      log_trace("%s",  __PRETTY_FUNCTION__);
      rhs.nd = nd;
      rhs.data_ = data_->clone();
      rhs.impl_ = impl_->clone();

      rhs.offset = offset;
      rhs.linear_size = linear_size;
    }

    template<typename T, typename RVal>
    std::size_t
    array_impl<T, RVal>::size() const
    {
      return data_->size();
    }

    template<typename T, typename RVal>
    T*
    array_impl<T, RVal>::data() const
    {
      return data_->data();
    }

    template<typename T, typename RVal>
    array_impl<T, RVal>::~array_impl()
    { 
    }

    template <typename T, typename RVal>
    void
    array_impl<T, RVal>::show() const
    {
      log_trace("%s", "____ Array ____");
      log_trace("offset %u,  nd %u",  offset % nd);
      for (unsigned i=0; i < nd; i++)
	log_trace("dims[%u]      %u",  i % impl_->dims.get(i));
      for (unsigned i=0; i < nd; i++)
	log_trace("factors[%u]   %u",  i % impl_->factors.get(i));
      for (unsigned i=0; i < nd; i++)
	log_trace("stride[%u]   %u",  i % impl_->strides.get(i));
      log_trace("off      %lu",  offset);
      log_trace("last     %lu",  linear_size);
    }

    template class array_impl<float, boost::mpl::false_>;
    template class array_impl<float, boost::mpl::true_>;

  }
}

