#include <resophonic/kamasu/dumper_context.hpp>
#include <resophonic/kamasu/matrix_impl.hpp>
#include "cutil.h"
#include "holder.hpp"
#include <cassert>

namespace resophonic 
{
  namespace kamasu 
  {
    template<typename T, typename RVal>
    matrix_impl<T, RVal>::matrix_impl() : impl(new holder<T>), size1(0), size2(0)
    {
      SHOW();
    }

    namespace 
    {
      template <typename T>
      void 
      construct(matrix_impl<T,  boost::mpl::true_>& lhs, 
		const matrix_impl <T, boost::mpl::true_ >& rhs)
      {
	lhs.impl = rhs.impl;
      }

      template <typename T>
      void 
      construct(matrix_impl<T,  boost::mpl::false_>& lhs, 
		const matrix_impl <T, boost::mpl::true_ >& rhs)
      {
	lhs.impl = rhs.impl;
      }

      template <typename T>
      void 
      construct(matrix_impl<T, boost::mpl::false_>& lhs,
		const matrix_impl<T, boost::mpl::false_>& rhs)
      {
	lhs.impl = rhs.impl->clone();
      }

      template <typename T>
      void 
      construct(matrix_impl<T, boost::mpl::true_>& lhs,
		const matrix_impl<T, boost::mpl::false_>& rhs)
      {
	lhs.impl = rhs.impl->clone();
      }
    }

    template<typename T, typename RVal>
    matrix_impl<T, RVal>::matrix_impl(const matrix_impl<T, RVal>& rhs)
    {
      SHOW();
      construct(*this, rhs);
      size1 = rhs.size1;
      size2 = rhs.size2;
    }

    template<typename T, typename RVal>
    matrix_impl<T, RVal>::matrix_impl(const matrix_impl<T, other_t>& rhs)
    {
      SHOW();
      construct(*this, rhs);
    }

    template <typename T, typename RVal>
    void matrix_impl<T, RVal>::reset()
    {
      impl.reset();
      size1 = size2 = 0;
    }

    template<typename T, typename RVal>
    void matrix_impl<T, RVal>::resize(std::size_t s1, std::size_t s2)
    {
      size1 = s1;
      size2 = s2;
      impl->resize(size1 * size1);
    }

    template<typename T, typename RVal>
    matrix_impl<T, RVal>::~matrix_impl()
    {
      SHOW();
    }

    template<typename T, typename RVal>
    void 
    matrix_impl<T, RVal>::copy_from(const matrix_impl<T, boost::mpl::true_>& rhs)
    {
      SHOW();
      impl = rhs.impl;
      size1 = rhs.size1;
      size2 = rhs.size2;
    }

    template<typename T, typename RVal>
    void
    matrix_impl<T, RVal>::copy_from(const matrix_impl<T, boost::mpl::false_>& rhs)
    {
      size1 = rhs.size1;
      size1 = rhs.size2;
      impl = rhs.impl->clone();
    }

    template class matrix_impl<float, boost::mpl::false_>;
    template class matrix_impl<float, boost::mpl::true_>;
  }
}

