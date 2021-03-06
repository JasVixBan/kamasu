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


/*! \file range.h
 *  \brief Defines the interface to the
 *         dispatch layer of the range function.
 */

#pragma once

#include <komrade/iterator/iterator_categories.h>
#include <komrade/iterator/iterator_traits.h>

#include <komrade/detail/device/cuda/vectorize.h>

namespace komrade
{

namespace detail
{

namespace dispatch
{

namespace detail
{

template <typename OutputType, typename RangeType>
struct range_functor
{
        OutputType * ptr;
  const RangeType init;
  const RangeType step;

  range_functor(OutputType * _ptr, const RangeType _init, const RangeType _step) 
      : ptr(_ptr), init(_init), step(_step) {}
  
  template <typename IntegerType>
      __host__ __device__
  void operator()(const IntegerType i) const { ptr[i] = init + step * i; }
}; // end range_functor

} // end detail


///////////////    
// Host Path //
///////////////    
template<typename ForwardIterator, typename T>
  void range(ForwardIterator first,
             ForwardIterator last,
             T init,
             T step,
             komrade::forward_host_iterator_tag)
{
    for(size_t i = 0; first != last; i++, first++)
        *first = init + step * i;
}


/////////////////    
// Device Path //
/////////////////    

template<typename ForwardIterator, typename T>
  void range(ForwardIterator first,
             ForwardIterator last,
             T init,
             T step,
             komrade::random_access_device_iterator_tag)
{
    typedef typename komrade::iterator_traits<ForwardIterator>::value_type OutputType;

    // XXX use make_device_dereferenceable here instead of assuming &*first is device_ptr
    komrade::detail::device::cuda::vectorize(last - first, detail::range_functor<OutputType,T>((&*first).get(), init, step));
}

} // end dispatch

} // end detail

} // komrade

