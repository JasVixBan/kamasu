#ifndef RESOPHONIC_KAMASU_MIRROR_HPP_INCLUDED
#define RESOPHONIC_KAMASU_MIRROR_HPP_INCLUDED

/**
 *  $Id$
 *  
 *  Copyright (C) 200*
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

#include <resophonic/kamasu/config.hpp>
#include <resophonic/kamasu/exception.hpp>

// #include <boost/shared_ptr.hpp>
// #include <boost/array.hpp>

#include <vector>

namespace resophonic {
  namespace kamasu {

    template <typename T>
    class mirror
    {
      T cpu_[KAMASU_MAX_ARRAY_DIM];
      //      mutable T*   gpu_;
      //      mutable bool dirty;

      //      T* gpu_malloc() const;


      void set_impl(const T* hdata, std::size_t s);

      void sync() const;

    public:

      ~mirror();

      mirror();

      /*
      T* gpu_data();
      const T* gpu_data() const;
      */

      void clone(const mirror& rhs);

      mirror* clone() const;

      void set(const std::vector<T>& hdata);

      void set(unsigned i, T value)
      {
	RESOPHONIC_KAMASU_THROW(i >= KAMASU_MAX_ARRAY_DIM, bad_index());
	cpu_[i] = value;
	//	dirty = true;
      }

      T get(unsigned i) const
      {
	RESOPHONIC_KAMASU_THROW(i >= KAMASU_MAX_ARRAY_DIM, bad_index());
	return cpu_[i];
      }

      void reset();
    };
  }
}

#endif
