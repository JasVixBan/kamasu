#ifndef RESOPHONIC_KAMASU_ARRAY_IMPL_HPP_INCLUDED
#define RESOPHONIC_KAMASU_ARRAY_IMPL_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/not.hpp>
#include <boost/shared_ptr.hpp>
#include <resophonic/kamasu/holder.hpp>
#include <resophonic/kamasu/mirror.hpp>

#include <vector>

namespace resophonic {
  namespace kamasu {

    namespace detail {
      struct impl_t {
	mirror<unsigned> dims;
	mirror<unsigned> factors;
	mirror<int>      strides;

	boost::shared_ptr<impl_t> clone()
	{
	  boost::shared_ptr<impl_t> newimpl(new impl_t);
	  impl_t& i(*newimpl);
	  i.dims.clone(dims);
	  i.factors.clone(factors);
	  i.strides.clone(strides);
	  return newimpl;
	}
      };
    }

    template <typename T, 
	      typename RVal = boost::mpl::false_>
    struct array_impl 
    {
      typedef typename boost::mpl::not_<RVal>::type other_t;

      mutable boost::shared_ptr<detail::impl_t> impl_;

      typedef uint64_t offset_t;
      offset_t offset;
      std::size_t linear_size;
      unsigned nd;

      boost::shared_ptr<holder<T> > data_;

      array_impl();
      array_impl(const array_impl<T, RVal>&);

      explicit array_impl(const array_impl<T, other_t>&);
      ~array_impl();

      void reset();
      void copy_from(const array_impl<T, boost::mpl::false_>& rhs);
      void copy_from(const array_impl<T, boost::mpl::true_>& rhs);
      void copy_into(array_impl<T, RVal>& thing) const;

      void swap(array_impl& rhs);

      void show() const;
      std::size_t size() const;
      T* data() const;

      void reshape(const std::vector<std::size_t>& shape, bool realloc = true);
      void reshape(std::size_t shape, bool realloc = true);
      std::size_t calculate_strides();
      void calculate_factors();

    };

  }
}


#endif
