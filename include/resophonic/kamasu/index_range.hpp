/**
 *  $Id$
 *  
 *  Copyright (C) 2009
 *  Troy D. Straszheim  <troy@icecube.umd.edu>
 *  
 *  This file is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 *  
 */
#ifndef RESOPHONIC_KAMASU_INDEX_RANGE_HPP_INCLUDED
#define RESOPHONIC_KAMASU_INDEX_RANGE_HPP_INCLUDED

#include <iostream>
#include <boost/array.hpp>
#include <boost/static_assert.hpp>
#include <boost/shared_array.hpp>
#include <resophonic/kamasu/logging.hpp>

namespace resophonic {
  namespace kamasu {

    struct slice_nil { };
    static const slice_nil _ = slice_nil();

    class index_range 
    {
    public:
      typedef int64_t index;
      typedef int64_t size_type;

      static index from_start()
      { return (std::numeric_limits<index>::min)(); }

      static index to_end()
      { return (std::numeric_limits<index>::max)(); }

    public:

      index_range()
      {
	start_ = from_start();
	finish_ = to_end();
	stride_ = 1;
	degenerate_ = false;
      }

      explicit index_range(index pos)
      {
	start_ = pos;
	finish_ = pos+1;
	stride_ = 1;
	degenerate_ = true;
      }

      explicit index_range(index start, index finish, index stride=1)
	: start_(start), finish_(finish), stride_(stride),
	  degenerate_(false)
      { }

      explicit index_range(slice_nil, index finish, index stride=1)
      {
	degenerate_ = false;
	stride_ = stride;

	if (stride < 0)
	  {
	    start_ = finish;
	    finish_ = from_start();
	  }
	else
	  {
	    start_ = from_start();
	    finish_ = finish;
	  }
      }

      explicit index_range(index start, slice_nil, index stride=1)
      {
	degenerate_ = false;
	stride_ = stride;

	BOOST_ASSERT(stride != 0);

	if (stride > 0)
	  {
	    start_ = start;
	    finish_ = to_end();
	  }
	else
	  {
	    start_ = start;
	    finish_ = from_start();
	  }
      }

      explicit index_range(slice_nil, slice_nil, index stride=1)
      {
	log_trace("(_,_,%ld)", stride);
	degenerate_ = false;
	stride_ = stride;

	if (stride < 0)
	  {
	    start_ = to_end();
	    finish_ = from_start();
	  }
	else
	  {
	    start_ = from_start();
	    finish_ = to_end();
	  }
      }

      // These are for chaining assignments to an index_range
      index_range& start(index s) {
	start_ = s;
	degenerate_ = false;
	return *this;
      }

      index_range& finish(index f) {
	finish_ = f;
	degenerate_ = false;
	return *this;
      }

      index_range& stride(index s) { stride_ = s; return *this; }

      index start() const
      { 
	return start_; 
      }

      index get_start(index low_index_range = index_range::from_start()) const
      { 
	if (start_ == from_start())
	  return low_index_range;
	return start_; 
      }

      index finish() const
      {
	return finish_;
      }

      index get_finish(index high_index_range = index_range::to_end()) const
      {
	if (finish_ == to_end())
	  return high_index_range;
	return finish_;
      }

      index stride() const { return stride_; }

      void set_index_range(index start, index finish, index stride=1)
      {
	start_ = start;
	finish_ = finish;
	stride_ = stride;
      }

      static index_range all() 
      { return index_range(from_start(), to_end(), 1); }

      bool is_degenerate() const { return degenerate_; }

      index_range operator-(index shift) const
      { 
	return index_range(start_ - shift, finish_ - shift, stride_); 
      }

      index_range operator+(index shift) const
      { 
	return index_range(start_ + shift, finish_ + shift, stride_); 
      }

      index operator[](unsigned i) const
      {
	return start_ + i * stride_;
      }

      index operator()(unsigned i) const
      {
	return start_ + i * stride_;
      }

      // add conversion to std::slice?

    public:

      index start_, finish_, stride_;
      bool degenerate_;

    };

  }
}

#endif
