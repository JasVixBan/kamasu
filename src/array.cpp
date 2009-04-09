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

#include <resophonic/pfeilhecht.h>

namespace resophonic {
  namespace kamasu {

    template <typename T>
    array<T>::array() 
      : self_(boost::proto::value(*this))
    {
    }

    template <typename T>
    array<T>::array(const std::vector<std::size_t>& shape) 
      : self_(boost::proto::value(*this))
    { 
      self_.reshape(shape);
    }

    template <typename T>
    array<T>::array(const array<T>& rhs) 
      : self_(boost::proto::value(*this))
    { 
      self().copy_from(rhs.self());
    }

    template <typename T>
    array<T>::~array()
    {
      
    }

    template <typename T>
    array<T>&
    array<T>::operator<<(const boost::numeric::ublas::matrix<T,boost::numeric::ublas::column_major>& m)
    {
      std::vector<std::size_t> newshape = make_vector(m.size1(), m.size2());
      self_.reshape(newshape, true);
      self_.data_->host_to_device(&(m.data()[0]), m.size1() * m.size2());
      return *this;
    }

    template <typename T>
    void
    array<T>::operator>>(boost::numeric::ublas::matrix<T,boost::numeric::ublas::column_major>& m)
    {
      m.resize(this->dim(0), this->dim(1));
      self_.data_->device_to_host(&(m.data()[0]));
    }

    template <typename T>
    void 
    array<T>::show() const
    {
      //      self_.show();
    }

    template <typename T>
    array<T>
    array<T>::clone() const
    {
      array<T> newarray;
      newarray.self() = self().clone();

      return std::move(newarray);
    }

    template <typename T>
    array<T>& 
    array<T>::operator=(const array<T>& rhs) 
    {
      log_trace("%s",  __PRETTY_FUNCTION__);
      self_.copy_from(rhs.self_);
      return *this;
    };

    template <typename T>			
    std::size_t								
    array<T>::index_of(const std::vector<std::size_t>& indexes) const
    {									
      std::size_t index = 0;
      for (unsigned i=0; i<indexes.size(); i++)
	index += indexes[i] * stride(i);

      return index;
    }

    template <typename T>				
    array<T>							
    array<T>::slice(const std::vector<index_range>& ranges) const
    {									
      BOOST_ASSERT(ranges.size() == self_.nd);				

      std::vector<std::size_t> newshape, starts;				

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
		    finish = dim(i);

		  starts.push_back(ir.start() == ir.from_start() 
				   ? 0 : ir.start());
		}
	      else
		{
		  if (ir.start() != ir.to_end())
		    start = ir.start();
		  else
		    start = dim(i)-1;

		  if (ir.finish() != ir.from_start())
		    finish = ir.finish();
		  else
		    finish = -1;
		  starts.push_back(ir.start() == ir.to_end() 
				   ? dim(i)-1 : ir.start());

		}

	      diff = finish - start;		
	    
	      diff += diff % ir.stride();				
	      log_trace("diff %d - %d is %d",  finish % start % diff); 
	      unsigned newdim = std::abs(diff/ir.stride());		
	      newshape.push_back(newdim);					
	      log_trace("newdim is %u",  newdim);

	    }
	  else
	    {
	      starts.push_back(ir.start());
	      newshape.push_back(0);
	    }
	}
      array<T> new_array;
      new_array.self().reshape(newshape, false);
      new_array.self().data_ = self_.data_;
      new_array.self().offset = index_of(starts);

      for (unsigned i=0, j=0; i<ranges.size(); i++)
	{
	  if (!ranges[i].is_degenerate())
	    new_array.stride(j++) = stride(i) * ranges[i].stride();
	}
      new_array.self().calculate_factors();
      return new_array;	
    }

    template <typename T>				
    array<T>							
    array<T>::operator()(const index_range& ir) const
    {									
      RESOPHONIC_KAMASU_THROW(1 != self_.nd, dimensions_dont_match());				

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
	    finish = dim(0);
	}
      else
	{
	  if (ir.start() != ir.to_end())
	    start = ir.start();
	  else
	    start = dim(0)-1;

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

      array<T> new_array;
      new_array.self().reshape(newdim, false);
      RESOPHONIC_KAMASU_THROW(new_array.nd() != 1, std::runtime_error("internal error"));
      new_array.self().data_ = self_.data_;

      std::size_t newstart; 
      if (ir.stride() > 0)
	newstart = (ir.start() == ir.from_start()) ? 0 : ir.start();
      else 
	newstart = (ir.start() == ir.to_end()) ? dim(0)-1 : ir.start();

      new_array.self().offset = index_of(newstart);
      log_trace("offset is %d",  new_array.self().offset);

      new_array.stride(0) = stride(0) * ir.stride();
      new_array.self().calculate_factors();
      return new_array;	
    }
    
    //
    //  "vararg" defns expanded here
    //
#define BOOST_PP_ITERATION_LIMITS (1, KAMASU_MAX_ARRAY_DIM-1)
#define BOOST_PP_FILENAME_1 "array.ipp"
#include BOOST_PP_ITERATE()

    template class array<float>;
  }
}



