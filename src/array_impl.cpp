#include <resophonic/kamasu/logging.hpp>
#include <resophonic/kamasu/holder.hpp>
#include <resophonic/kamasu/dumper_context.hpp>
#include <resophonic/kamasu/array_impl.hpp>
// #include <resophonic/cuda/assign.h>

#include "pool.hpp"
#include <cuda_runtime.h>
#include <cassert>
#include <string.h>
#include <cstring>
#include <boost/bind.hpp>

namespace resophonic 
{
  namespace kamasu 
  {

    template<typename T>
    void
    array_impl<T>::alloc() 
    {
      data_ = boost::shared_ptr<holder<T> >(new (holder_pool::malloc()) holder<T>,
					    (void (*)(void*))holder_pool::free);
    } 

    template<typename T>
    array_impl<T>::array_impl() 
    { 
      impl.offset = 0;
      impl.linear_size = 0;
    }

    template <typename T>
    array_impl<T>::array_impl(const array_impl<T>& rhs) :
      impl(rhs.impl),
      data_(rhs.data_)
    {
      log_trace("%s",  __PRETTY_FUNCTION__);
    }

    template <typename T>
    array_impl<T>
    array_impl<T>::clone() const
    {
      array_impl<T> newarray(*this);
      newarray.data_ = data_->clone();
      return std::move(newarray);
    }

    template <typename T>
    void
    array_impl<T>::reshape(const std::vector<std::size_t>& shape, bool realloc)
    {
      log_trace("%s", "reshape");
      impl.offset = 0;
      impl.nd = 0;
      for (unsigned i=0; i<shape.size(); i++)
	{
	  if (shape[i] != 0)
	    {
	      impl.nd++;
	      dim(impl.nd-1) = shape[i];
	    }
	}

      std::size_t newsize = calculate_strides();
      calculate_factors();
      if (realloc)
	{
	  if (!data_)
	    data_ = boost::shared_ptr<holder<T> >(new holder<T>(newsize));
	  else
	    data_->resize(newsize);
	}
    }

    template <typename T>
    void
    array_impl<T>::reshape(std::size_t shape, bool realloc)
    {
      log_trace("%s", "reshape");
      impl.offset = 0;
      impl.nd = 1;
      dim(0) = shape;
      stride(0) = 1;
      factor(0) = 1; 
      impl.linear_size = shape;
      if (realloc)
	data_->resize(shape);
    }

    template <typename T>
    std::size_t
    array_impl<T>::calculate_strides()
    {
      unsigned s = 1;
      stride(0) = s;

      for(unsigned i=1; i<nd(); i++)
	{
	  s *= dim(i-1);
	  stride(i) = s;
	}

      for (unsigned i=0; i<nd(); i++)
	log_trace("dim %u is %u, stride %u",  i % dim(i) % stride(i));

      std::size_t size = 1;
      for (unsigned i=0; i<nd(); i++)
	size *= dim(i);
      return size;
    }

    template <typename T>
    void 
    array_impl<T>::calculate_factors()
    {
      BOOST_ASSERT(nd() > 0);

      impl.linear_size = 1;
      factor(0) = 1;
      unsigned prev_factor = 1;
      impl.linear_size = dim(0);
      for(unsigned i=1; i<nd(); i++)
	{
	  unsigned dim_left = dim(i-1);
	  unsigned newfactor = dim_left * prev_factor;
	  factor(i) = newfactor;
	  prev_factor = newfactor;

	  impl.linear_size *= dim(i);
	}


      for (unsigned i=0; i<nd(); i++)
	log_trace("dim %u is %u, factor %u", 
		  i % dim(i) % factor(i));
      log_trace("linear size is %u", linear_size); 
    }

    template<typename T>
    void 
    array_impl<T>::copy_from(const array_impl<T>& rhs, bool clone)
    {
      if (&rhs == this)
	return;
#if RESOPHONIC_KAMASU_DEBUG
      log_trace("%s",  __PRETTY_FUNCTION__);
      //      rhs.show();
#endif
      impl = rhs.impl;
      data_ = clone ? rhs.data_->clone() : rhs.data_;
    }

    template<typename T>
    std::size_t
    array_impl<T>::size() const
    {
      return data_->size();
    }

    template<typename T>
    T*
    array_impl<T>::data() const
    {
      return data_ ? data_->data() : 0;
    }

    template<typename T>
    array_impl<T>::~array_impl()
    { 
    }

    template <typename T>
    void
    array_impl<T>::show() const
    {
      /*
      log_trace("%s", "____ Array ____");
      log_trace("offset %u,  nd %u",  offset % nd);
      for (unsigned i=0; i < nd; i++)
	log_trace("dims[%u]      %u",  i % dim(i));
      for (unsigned i=0; i < nd; i++)
	log_trace("factors[%u]   %u",  i % factor(i));
      for (unsigned i=0; i < nd; i++)
	log_trace("stride[%u]   %u",  i % stride(i));
      log_trace("off      %lu",  offset);
      log_trace("last     %lu",  linear_size);
      */
    }

    template class array_impl<float>;
  }
}

