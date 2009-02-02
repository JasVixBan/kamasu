#ifndef RESOPHONIC_KAMASU_ARRAY_IMPL_HPP_INCLUDED
#define RESOPHONIC_KAMASU_ARRAY_IMPL_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/not.hpp>
#include <boost/shared_ptr.hpp>
#include <resophonic/kamasu/holder.hpp>
#include <vector>

namespace resophonic 
{
  namespace kamasu
  {
    template <typename T, 
	      typename RVal = boost::mpl::false_>
    struct array_impl 
    {
      typedef typename boost::mpl::not_<RVal>::type other_t;

      boost::shared_ptr<holder<unsigned> > dims;
      boost::shared_ptr<holder<unsigned> > factors;

      boost::shared_ptr<holder<int> > strides;

      typedef uint64_t offset_t;
      offset_t offset;
      std::size_t linear_size;
      boost::shared_ptr<holder<T> > impl;

      array_impl();
      array_impl(const array_impl<T, RVal>&);

      explicit array_impl(const array_impl<T, other_t>&);
      ~array_impl();

      void reset();
      void copy_from(const array_impl<T, boost::mpl::false_>& rhs);
      void copy_from(const array_impl<T, boost::mpl::true_>& rhs);

      void swap(array_impl& rhs);

      void show() const;
      std::size_t size() const;
      T* data() const;

      void reshape(const std::vector<std::size_t>& shape);
      unsigned calculate_strides();
      void calculate_factors();

    };

  }
}


#endif
