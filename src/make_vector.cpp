/**
 *  $Id$
 *  
 *  Copyright (C) 2008, 2009
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
#include <resophonic/kamasu/make_vector.hpp>

#include <resophonic/kamasu/index_range.hpp>

#define PUSHBACK(Z, N, DATA) \
  val.push_back(DATA##N);

#define MAKE_VECTOR_IMPL(Z, N, DATA)			\
  template <typename T>					\
  typename std::vector<T>				\
  make_vector(BOOST_PP_ENUM_PARAMS(N, T Arg))		\
  {							\
    std::vector<T> val;					\
    BOOST_PP_REPEAT_FROM_TO(0, N, PUSHBACK, Arg);	\
    return val;						\
  }
  
#define MAKE_VECTOR_INST(Z, N, T)		\
  template std::vector<T>			\
  make_vector(BOOST_PP_ENUM_PARAMS(N, T Arg));

namespace resophonic {
  namespace kamasu {
    BOOST_PP_REPEAT_FROM_TO(1, KAMASU_MAX_ARRAY_DIM, MAKE_VECTOR_IMPL, ~);

    BOOST_PP_REPEAT_FROM_TO(1, KAMASU_MAX_ARRAY_DIM, MAKE_VECTOR_INST, std::size_t);
    BOOST_PP_REPEAT_FROM_TO(1, KAMASU_MAX_ARRAY_DIM, MAKE_VECTOR_INST, unsigned);
    BOOST_PP_REPEAT_FROM_TO(1, KAMASU_MAX_ARRAY_DIM, MAKE_VECTOR_INST, int);
    BOOST_PP_REPEAT_FROM_TO(1, KAMASU_MAX_ARRAY_DIM, MAKE_VECTOR_INST, index_range);
  }
}


