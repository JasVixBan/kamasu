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

#include <boost/proto/proto.hpp>
#include "kernel.h"

namespace resophonic {
  namespace kamasu {

    template <typename T>
    struct op_map
    { };

#define KAMASU_OPMAP_SPECIALIZATION(PROTO_OP, KAMASU_OPCODE)	\
    template <> struct op_map<boost::proto::tag::PROTO_OP> {	\
      const static Op value = KAMASU_OPCODE;			\
    }

    KAMASU_OPMAP_SPECIALIZATION(plus, PLUS);
    KAMASU_OPMAP_SPECIALIZATION(minus, MINUS);
    KAMASU_OPMAP_SPECIALIZATION(multiplies, MULTIPLIES);
    KAMASU_OPMAP_SPECIALIZATION(divides, DIVIDES);

    template <> struct op_map<tag::pow> {
      const static Op value = POW;
    };
  }
}
