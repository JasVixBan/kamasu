#ifndef RESOPHONIC_KAMASU_HOLDER_HPP_INCLUDED
#define RESOPHONIC_KAMASU_HOLDER_HPP_INCLUDED

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

#include <resophonic/kamasu/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <vector>

namespace resophonic {
  namespace kamasu {

    template <typename T>
    class holder : boost::noncopyable
    {
      T* data_;
      std::size_t size_;
      
      holder(const holder& rhs); // not implemented

    public:

      ~holder();

      holder();
      holder(std::size_t);
      std::size_t size() const;
      T* data();
      const T* data() const;

      T* gpu_mallocn(unsigned n);

      void resize(std::size_t s);

      boost::shared_ptr<holder> clone() const;

      void clone(const holder& rhs);

      void host_to_device(const std::vector<T>& hdata);

      void host_to_device(const T* hdata, std::size_t s);

      void device_to_host(T* hdata);
      
      T get(unsigned i) const;
      
      void set(unsigned i, T value);

      void reset();

    };
  }
}

#endif
