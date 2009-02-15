// #define I3_PRINTF_LOGGING_LEVEL LOG_INFO

#include <cassert>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
// includes, project
#include <boost/multi_array.hpp>
#include <boost/foreach.hpp>

#include "cutil.h"
#include <resophonic/kamasu/config.hpp>
#include <resophonic/kamasu/array.hpp>
#include <resophonic/kamasu/config.hpp>
#include <resophonic/kamasu/holder.hpp>
#include <resophonic/kamasu/rval.hpp>
#include <resophonic/kamasu/make_vector.hpp>
#include <resophonic/kamasu/exception.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>

#include "kernel.h"

namespace resophonic {
  namespace kamasu {

    template <typename T, typename RVal>
    array<T, RVal>::array() 
      : /*base_t(*this),*/
	self_(boost::proto::value(*this))
    {

    }

    template <typename T, typename RVal>
    array<T, RVal>::~array()
    {
      
    }

    template <typename T, typename RVal>
    array<T, RVal>::array(const std::vector<std::size_t>& shape) 
      : self_(boost::proto::value(*this))
    { 
      self().reshape(shape);
    }

    template <typename T, typename RVal>
    std::size_t
    array<T, RVal>::linear_size() const
    {
      return self().linear_size;
    }

    template <typename T, typename RVal>
    void 
    array<T, RVal>::take(const array_impl<T, boost::mpl::true_>& rhs)
    {
      log_trace("%s",  "TAKING");
#ifdef RESOPHONIC_KAMASU_DEBUG
      rhs.show();
#endif
      BOOST_ASSERT(rhs.nd);
      BOOST_ASSERT(rhs.linear_size);
      self().copy_from(rhs);
    }

    template <typename T, typename RVal>
    void 
    array<T, RVal>::take(const array_impl<T, boost::mpl::false_>& rhs)
    {
      log_trace("%s",  __PRETTY_FUNCTION__);
#ifdef RESOPHONIC_KAMASU_DEBUG
      rhs.show();
#endif
      BOOST_ASSERT(rhs.nd);
      self().copy_from(rhs);
    }

    template <typename T, typename RVal>
    array<T, RVal>&
    array<T, RVal>::operator<<(const boost::numeric::ublas::matrix<T,boost::numeric::ublas::column_major>& m)
    {
      std::vector<std::size_t> newshape = make_vector(m.size1(), m.size2());
      self().reshape(newshape, true);
      self().data_->host_to_device(&(m.data()[0]), m.size1() * m.size2());
    }

    template <typename T, typename RVal>
    void
    array<T, RVal>::operator>>(boost::numeric::ublas::matrix<T,boost::numeric::ublas::column_major>& m)
    {
      m.resize(this->dim(0), this->dim(1));
      self().data_->device_to_host(&(m.data()[0]));
    }

    template <typename T, typename RVal>
    void 
    array<T, RVal>::show() const
    {
      self().show();
    }

    template <typename T, typename RVal>
    array<T, RVal>
    array<T, RVal>:: copy() const
    {
      array newarray;
      self().copy_into(newarray.self());
      return newarray;
    }

    template <typename T, typename RVal>
    array<T, RVal>& 
    array<T, RVal>::operator=(const array<T, RVal>& rhs) 
    {
      log_trace("%s",  __PRETTY_FUNCTION__);
      this->take(rhs.self());
      return *this;
    };

    template <typename T, typename RVal>				
    std::size_t								
    array<T, RVal>::index_of(const std::vector<std::size_t>& indexes) const
    {									
      std::size_t index = 0;
      for (unsigned i=0; i<indexes.size(); i++)
	index += indexes[i] * self().impl_->strides.get(i);

      return index;
    }

    template <typename T, typename RVal>				
    array<T, RVal>							
    array<T, RVal>::slice(const std::vector<index_range>& ranges) const
    {									
      log_trace("slicing!");						
      BOOST_ASSERT(ranges.size() == self().nd);				

      std::vector<std::size_t> newshape;				
      for (unsigned i=0; i< ranges.size(); i++)
	{
	  const index_range& ir = ranges[i];
	  if (! ir.is_degenerate())
	    {								
	      int finish, start, diff;

	      if (ir.stride() > 0)
		{
		  if (ir.start() != ir.from_start())
		    start = ir.start();
		  else
		    start = 0;

		  if (ir.finish() != ir.to_end())
		    finish = ir.finish();
		  else
		    finish = self().impl_->dims.get(i);
		}
	      else
		{
		  if (ir.start() != ir.to_end())
		    start = ir.start();
		  else
		    start = self().impl_->dims.get(i)-1;

		  if (ir.finish() != ir.from_start())
		    finish = ir.finish();
		  else
		    finish = -1;
		}

	      diff = finish - start;		
	    
	      diff += diff % ir.stride();				
	      log_trace("diff %d - %d is %d",  finish % start % diff); 
	      unsigned newdim = std::abs(diff/ir.stride());		
	      newshape.push_back(newdim);					
	      log_trace("newdim is %u",  newdim);
	    }
	}
      log_trace("make new array");
      array new_array;
      new_array.self().reshape(newshape, false);
      log_trace("done make new array");
      new_array.self().data_ = self().data_;
      std::vector<std::size_t> starts;
      for (unsigned i=0; i< ranges.size(); i++)
	{
	  const index_range& ir = ranges[i];
	  if (!ir.is_degenerate())
	    {
	      if (ir.stride() > 0)
		starts.push_back(ir.start() == ir.from_start() 
				 ? 0 : ir.start());
	      else 
		starts.push_back(ir.start() == ir.to_end() 
				 ? self().impl_->dims.get(i)-1 : ir.start());
	    }
	  else
	    {
	      starts.push_back(ir.start());
	    }
	}
      new_array.self().offset = index_of(starts);
      log_trace("offset is %d",  new_array.self().offset);

      std::vector<int> new_strides;

      for (unsigned i=0; i<ranges.size(); i++)
	{
	  if (!ranges[i].is_degenerate())
	    new_strides.push_back(self().impl_->strides.get(i) * ranges[i].stride());
	}

      new_array.self().impl_->strides.set(new_strides);
      new_array.self().calculate_factors();
      return new_array;	
    }

    template <typename T, typename RVal>				
    array<T, RVal>							
    array<T, RVal>::slice(const index_range& ir) const
    {									
      log_trace("slicing!");						
      BOOST_ASSERT(1  == self().nd);				

      if (ir.is_degenerate())
	throw std::runtime_error("degenerate slice of 1d array");

      int finish, start, diff;

      if (ir.stride() > 0)
	{
	  if (ir.start() != ir.from_start())
	    start = ir.start();
	  else
	    start = 0;

	  if (ir.finish() != ir.to_end())
	    finish = ir.finish();
	  else
	    finish = self().impl_->dims.get(0);
	}
      else
	{
	  if (ir.start() != ir.to_end())
	    start = ir.start();
	  else
	    start = self().impl_->dims.get(0)-1;

	  if (ir.finish() != ir.from_start())
	    finish = ir.finish();
	  else
	    finish = -1;
	}

      diff = finish - start;		
	    
      diff += diff % ir.stride();				
      log_trace("diff %d - %d is %d",  finish % start % diff); 
      unsigned newdim = std::abs(diff/ir.stride());		
      log_trace("newdim is %u",  newdim);

      log_trace("make new array");
      array new_array;
      new_array.self().reshape(newdim, false);
      log_trace("done make new array");
      new_array.self().data_ = self().data_;

      std::size_t newstart; 
      if (ir.stride() > 0)
	newstart = (ir.start() == ir.from_start()) ? 0 : ir.start();
      else 
	newstart = (ir.start() == ir.to_end()) ? self().impl_->dims.get(0)-1 : ir.start();

      new_array.self().offset = index_of(newstart);
      log_trace("offset is %d",  new_array.self().offset);

      new_array.self().impl_->strides.set(0, self().impl_->strides.get(0) * ir.stride());
      new_array.self().calculate_factors();
      return new_array;	
    }
    
    //
    //  "vararg" defns expanded here
    //
#define BOOST_PP_ITERATION_LIMITS (1, KAMASU_MAX_ARRAY_DIM-1)
#define BOOST_PP_FILENAME_1 "array.ipp"
#include BOOST_PP_ITERATE()

    template class array<float, boost::mpl::true_>;
    template class array<float, boost::mpl::false_>;
  }
}



