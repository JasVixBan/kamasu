#ifndef RESOPHONIC_KAMASU_ARRAY_IMPL_HPP_INCLUDED
#define RESOPHONIC_KAMASU_ARRAY_IMPL_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/mpl/not.hpp>
#include <resophonic/kamasu/shared_ptr.hpp>
#include <resophonic/kamasu/exception.hpp>
#include <resophonic/kamasu/view_params.hpp>

#include <vector>

namespace resophonic {
  namespace kamasu {

    template <typename T>
    class holder;

    template <typename T>
    class array;

    template <typename T>
    struct array_impl 
    {
      typedef std::size_t offset_t;

      friend class array<T>;

      array_impl(const array_impl& rhs);
      array_impl();

      ~array_impl();

      array_impl clone() const;

      //      void reset();
      void copy_from(const array_impl<T>& rhs, bool clone = false);

      void swap(array_impl& rhs);

      

      void show() const;
      std::size_t size() const;
      T* data() const;
      T get(std::size_t index) const { return data_->get(index); }
      void reshape(const std::vector<std::size_t>& shape, bool realloc = true);
      void reshape(std::size_t shape, bool realloc = true);
      dim_t& dim(std::size_t index) 
      { 
	RESOPHONIC_KAMASU_THROW(index >= nd, bad_index());
	return impl.dims[index]; 
      }
      dim_t dim(std::size_t index) const 
      { 
	RESOPHONIC_KAMASU_THROW(index >= nd, bad_index());
	return impl.dims[index]; 
      }

      int& stride(std::size_t index)
      { 
	RESOPHONIC_KAMASU_THROW(index >= nd, bad_index());
	return impl.strides[index]; 
      }

      int stride(std::size_t index) const 
      { 
	RESOPHONIC_KAMASU_THROW(index >= nd, bad_index());
	return impl.strides[index]; 
      }

      factor_t& factor(std::size_t index)
      { 
	RESOPHONIC_KAMASU_THROW(index >= nd, bad_index());
	return impl.factors[index]; 
      }
      factor_t factor(std::size_t index) const 
      { 
	RESOPHONIC_KAMASU_THROW(index >= nd, bad_index());
	return impl.factors[index]; 
      }
      offset_t offset() const { return impl.offset; }

      const dim_t* dims() const { return impl.dims; }
      const factor_t* factors() const { return impl.factors; }
      const stride_t* strides() const { return impl.strides; }
      unsigned nd() const { return impl.nd; }
      unsigned linear_size() const { return impl.linear_size; }

      const view_params& view_p() const { return impl;}

    private:

      std::size_t calculate_strides();
      void calculate_factors();
      
      void alloc();

      view_params impl;

      boost::shared_ptr<holder<T> > data_;

    };

  }
}


#endif
