#ifndef RESOPHONIC_KAMASU_PRIMITIVES_HPP_INCLUDED
#define RESOPHONIC_KAMASU_PRIMITIVES_HPP_INCLUDED

#include "proto_tags_fwd.hpp"
#include <resophonic/kamasu/tag.hpp>

namespace resophonic
{
  namespace kamasu
  {

    template <typename T, typename Op>
    struct op_impl_;

    template <typename T>
    struct op_impl_<T, boost::proto::tag::plus>
    {
      static void impl(T* t, const T& scalar)
      {
	*t += scalar;
      }
      static void impl(T* t, T* s)
      {
	*t += *s;
      }
    };

    template <typename T>
    struct op_impl_<T, boost::proto::tag::minus>
    {
      static void impl(T* t, const T& scalar)
      {
	*t -= scalar;
      }
      static void impl(T* t, T* s)
      {
	*t -= *s;
      }
    };

    template <typename T>
    struct op_impl_<T, boost::proto::tag::divides>
    {
      static void impl(T* t, const T& scalar)
      {
	*t /= scalar;
      }
      static void impl(T* t, T* s)
      {
	*t /= *s;
      }
    };

    template <typename T>
    struct op_impl_<T, boost::proto::tag::multiplies>
    {
      static void impl(T* t, const T& scalar)
      {
	*t *= scalar;
      }
      static void impl(T* t, T* s)
      {
	*t *= *s;
      }
    };

    template <typename T>
    struct op_impl_<T, boost::proto::tag::assign>
    {
      static void impl(T* t, const T& scalar)
      {
	*t = scalar;
      }
      static void impl(T* t, T* s)
      {
	*t = *s;
      }
    };

    template <typename T>
    struct op_impl_<T, tag::pow>
    {
      static void impl(T* t, const T& scalar)
      {
	*t = pow(*t, scalar);
      }
    };
  }
}

#endif
