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


/*! \file adjacent_difference.inl
 *  \brief Inline file for adjacent_difference.h
 */

#include <komrade/adjacent_difference.h>
#include <komrade/functional.h>
#include <komrade/detail/dispatch/adjacent_difference.h>

namespace komrade
{

template <class InputIterator, class OutputIterator, class BinaryFunction>
OutputIterator adjacent_difference(InputIterator first, InputIterator last,
                                   OutputIterator result,
                                   BinaryFunction binary_op)
{
  // dispatch on category
  return komrade::detail::dispatch::adjacent_difference(first, last, result, binary_op,
    typename komrade::iterator_traits<InputIterator>::iterator_category());
} // end adjacent_difference()

template <class InputIterator, class OutputIterator>
OutputIterator adjacent_difference(InputIterator first, InputIterator last, 
                                   OutputIterator result)
{
  typedef typename komrade::iterator_traits<InputIterator>::value_type InputType;

  komrade::minus<InputType> binary_op;
  return komrade::adjacent_difference(first, last, result, binary_op);
} // end adjacent_difference()

} // end namespace komrade

