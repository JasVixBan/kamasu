#ifndef RESOPHONIC_KAMASU_ARRAY_IMPL_HPP_INCLUDED
#define RESOPHONIC_KAMASU_ARRAY_IMPL_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/not.hpp>
#include <boost/shared_ptr.hpp>
//#include <resophonic/kamasu/holder.hpp>
#include <resophonic/kamasu/exception.hpp>

#include <vector>

namespace resophonic {
  namespace kamasu {

    template <typename T>
    class holder;

    template <typename T, 
	      typename RVal = boost::mpl::false_>
    struct array_impl 
    {
      typedef array_impl<T, RVal> this_t;
      typedef array_impl<T, typename boost::mpl::not_<RVal>::type> other_t;
      
      typedef uint64_t offset_t;
      std::size_t dims[KAMASU_MAX_ARRAY_DIM];
      std::size_t factors[KAMASU_MAX_ARRAY_DIM];
      int strides[KAMASU_MAX_ARRAY_DIM];

      offset_t offset;
      std::size_t linear_size;
      unsigned nd;

      boost::shared_ptr<holder<T> > data_;

      array_impl();
      template <typename OtherRVal>
      array_impl(const array_impl<T, OtherRVal>&);

      ~array_impl();

      //      void reset();
      void copy_from(const array_impl<T, boost::mpl::false_>& rhs);
      void copy_from(const array_impl<T, boost::mpl::true_>& rhs);
      void copy_into(this_t& thing) const;
      void copy_into(other_t& thing) const;

      void swap(array_impl& rhs);

      void show() const;
      std::size_t size() const;
      T* data() const;

      void reshape(const std::vector<std::size_t>& shape, bool realloc = true);
      void reshape(std::size_t shape, bool realloc = true);
      std::size_t calculate_strides();
      void calculate_factors();

      void alloc();

      std::size_t& dim(std::size_t index) 
      { 
	RESOPHONIC_KAMASU_THROW(index >= nd, bad_index());
	return dims[index]; 
      }
      std::size_t dim(std::size_t index) const 
      { 
	RESOPHONIC_KAMASU_THROW(index >= nd, bad_index());
	return dims[index]; 
      }

      int& stride(std::size_t index)
      { 
	RESOPHONIC_KAMASU_THROW(index >= nd, bad_index());
	return strides[index]; 
      }
      int stride(std::size_t index) const 
      { 
	RESOPHONIC_KAMASU_THROW(index >= nd, bad_index());
	return strides[index]; 
      }

      std::size_t& factor(std::size_t index)
      { 
	RESOPHONIC_KAMASU_THROW(index >= nd, bad_index());
	return factors[index]; 
      }
      std::size_t factor(std::size_t index) const 
      { 
	RESOPHONIC_KAMASU_THROW(index >= nd, bad_index());
	return factors[index]; 
      }
    };

  }
}


#endif
