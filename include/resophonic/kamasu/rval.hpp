/**
 *  $Id$
 *  
 *  Copyright (C) 2008
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

#ifndef RESOPHONIC_KAMASU_GPU_RVAL_HPP_INCLUDED
#define RESOPHONIC_KAMASU_GPU_RVAL_HPP_INCLUDED

#include <resophonic/kamasu/holder.hpp>

namespace resophonic {
  namespace kamasu {
    //
    // little holder type that can get back to us if we assign to it
    //
    template <typename T>
    class rval 
    {
      boost::shared_ptr<holder<T> > hldr_;
      unsigned index_;

      rval(); 

    public:

      rval(boost::shared_ptr<holder<T> > device_mem, unsigned index);
      //      rval(const rval& rhs);

      operator T() const;
      rval& operator=(T);

      friend std::ostream& operator<<(std::ostream& os, const rval& rv)
      {
	return os << rv.operator T();
      }

      friend bool operator==(const rval& lhs, const rval& rhs)
      {
	return lhs.operator T() == rhs.operator T();
      }
      friend bool operator<=(const rval& lhs, const rval& rhs)
      {
	return lhs.operator T() <= rhs.operator T();
      }

    };

  }
}
#endif
