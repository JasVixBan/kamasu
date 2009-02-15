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

#define CHECK_DIM(Z, N, DATA) RESOPHONIC_KAMASU_THROW(DATA##N == 0, zero_dim(N));
    

#define VARARG_CONSTRUCTOR_DEFN(Z, N, DATA)				\
    template <typename T, typename RVal>				\
    array<T, RVal>::array(BOOST_PP_ENUM_PARAMS(N, std::size_t Arg)) :	\
    self_(boost::proto::value(*this))					\
    {									\
      BOOST_PP_REPEAT(N, CHECK_DIM, Arg);				\
      std::vector<std::size_t> shape = KAMASU_MAKE_VECTOR(N, Arg);	\
      self().reshape(shape);						\
    }						

    BOOST_PP_REPEAT_FROM_TO(1, KAMASU_MAX_ARRAY_DIM, VARARG_CONSTRUCTOR_DEFN, ~);

#undef VARARG_CONSTRUCTOR_DEFN

    template <typename T, typename RVal>
    array<T, RVal>::array(const std::vector<std::size_t>& shape) : self_(boost::proto::value(*this))
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

#define INDEX_OF_TERM(Z, N, DATA) + (Arg##N * strides.get(N))

#define INDEX_OF_DEFN(Z, N, DATA)					\
    template <typename T, typename RVal>				\
    std::size_t								\
    array<T, RVal>::index_of(BOOST_PP_ENUM_PARAMS(N, std::size_t Arg)) const \
    {									\
      const mirror<int>& strides(self().impl_->strides);		\
      return 0 BOOST_PP_REPEAT(N, INDEX_OF_TERM, ~);			\
    }
    BOOST_PP_REPEAT_FROM_TO(1, KAMASU_MAX_ARRAY_DIM, INDEX_OF_DEFN, Arg);

#undef INDEX_OF_TERM
#undef INDEX_OF_DEFN

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

#define SLICE_DEFN(Z, N, DATA)						\
    template <typename T, typename RVal>				\
    array<T, RVal>							\
    array<T, RVal>::slice(BOOST_PP_ENUM_PARAMS(N, const index_range& Arg)) const \
    {									\
      return slice(KAMASU_MAKE_VECTOR(N, Arg));				\
    }

    BOOST_PP_REPEAT_FROM_TO(2, KAMASU_MAX_ARRAY_DIM, SLICE_DEFN, ~);

#undef SLICE_DEFN

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
    //  these could go via std::vector
    //

#ifdef RESOPHONIC_KAMASU_DEBUG
#define DIM_CHECK(Z, N, DATA) RESOPHONIC_KAMASU_THROW(DATA##N >= self().impl_->dims.get(N), \
						      bad_index());
#else
#define DIM_CHECK(Z, N, DATA) ;
#endif

#define STRIDE_TERM(Z, N, DATA)	+ DATA ## N * self().impl_->strides.get(N)

#define FNCALL_LVALUE_OPERATOR_DEFN(Z, N, DATA)				\
    template <typename T, typename RVal>				\
    T									\
    array<T, RVal>::operator()(BOOST_PP_ENUM_PARAMS(N, std::size_t Arg)) const \
    {									\
      RESOPHONIC_KAMASU_THROW(N != self().nd, dimensions_dont_match());	\
      BOOST_PP_REPEAT(N, DIM_CHECK, Arg);				\
      int index = 0 BOOST_PP_REPEAT(N, STRIDE_TERM, Arg);		\
      log_trace("getting lvalue from offset %d",  (self().offset + index)); \
      return self().data_->get(index);					\
    }


    BOOST_PP_REPEAT_FROM_TO(1, KAMASU_MAX_ARRAY_DIM, FNCALL_LVALUE_OPERATOR_DEFN, ~);


#define FNCALL_RVALUE_OPERATOR_DEFN(Z, N, DATA)				\
    template <typename T, typename RVal>				\
    rval<T>								\
    array<T, RVal>::operator()(BOOST_PP_ENUM_PARAMS(N, std::size_t Arg)) \
    {									\
      RESOPHONIC_KAMASU_THROW(N != self().nd, dimensions_dont_match());	\
      BOOST_PP_REPEAT(N, DIM_CHECK, Arg);				\
      int index = 0 BOOST_PP_REPEAT(N, STRIDE_TERM, Arg);		\
      log_trace("getting rvalue offset=%u index=%d",  self().offset % index); \
      return rval<T>(self().data_, index + self().offset);		\
    }

    BOOST_PP_REPEAT_FROM_TO(1, KAMASU_MAX_ARRAY_DIM, FNCALL_RVALUE_OPERATOR_DEFN, ~);

    template class array<float, boost::mpl::true_>;
    template class array<float, boost::mpl::false_>;
  }
}



