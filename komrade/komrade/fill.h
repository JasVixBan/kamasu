/*
 *  Copyright 2008-2009 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */


/*! \file fill.h
 *  \brief Defines the interface to some
 *         methods for filling a device array
 *         with an exemplar.
 */

#pragma once

#include <komrade/detail/config.h>

namespace komrade
{

/*! \addtogroup transformations
 *  \addtogroup filling
 *  \ingroup transformations
 *  \{
 */

/*! \p fill assigns the value \p value to every element in
 *  the range <tt>[first, last)</tt>. That is, for every
 *  iterator \c i in <tt>[first, last)</tt>, it performs
 *  the assignment <tt>*i = value</tt>.
 *
 *  \param first The beginning of the sequence.
 *  \param last The end of the sequence.
 *  \param value The value to be copied.
 *
 *  \tparam ForwardIterator is a model of <a href="http://www.sgi.com/tech/stl/ForwardIterator.html">Forward Iterator</a>,
 *          and \p ForwardIterator is mutable.
 *  \tparam T is a model of <a href="http://www.sgi.com/tech/stl/Assignable.html">Assignable</a>,
 *          and \p T's \c value_type is convertible to \p ForwardIterator's \c value_type.
 *
 *  The following code snippet demonstrates how to use \p fill to set a komrade::device_vector's
 *  elements to a given value.
 *
 *  \code
 *  #include <komrade/fill.h>
 *  #include <komrade/device_vector.h>
 *  ...
 *  komrade::device_vector<int> v(4);
 *  komrade::fill(v.begin(), v.end(), 137);
 *
 *  // v[0] == 137, v[1] == 137, v[2] == 137, v[3] == 137
 *  \endcode
 *
 *  \see http://www.sgi.com/tech/stl/fill.html
 *  \see \c uninitialized_fill
 */
template<typename ForwardIterator, typename T>
  void fill(ForwardIterator first,
            ForwardIterator last,
            const T &value);

/*! \} // end filling
 *  \} // transformations
 */

} // end namespace komrade

#include <komrade/detail/fill.inl>

