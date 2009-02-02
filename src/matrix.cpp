#include <cassert>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
// includes, project

#include "cutil.h"
//#include <resophonic/kamasu.hpp>
#include <resophonic/kamasu/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "kernel.h"
#include "holder.hpp"

namespace resophonic {
  namespace kamasu {

    template <typename T, typename RVal>
    matrix<T, RVal>::matrix()
    {
      SHOW();
    }

    template <typename T, typename RVal>
    matrix<T, RVal>::~matrix()
    {
      SHOW();
    }

    template<typename T, typename RVal>
    void matrix<T, RVal>::take(const blas_matrix_t& rhs)
    {
      self().size1 = rhs.size1();
      self().size2 = rhs.size2();
      LOG("Taking blas matrix") << rhs << "\n";
      const T* rawdata = &(rhs.data()[0]);
      
      LOG("before, dev ptr is") << self().impl->data;
      self().impl->host_to_device(rawdata, self().size1 * self().size2);

      assert(self().impl->size == self().size1 * self().size2);
    }

    template <typename T, typename RVal>
    T
    matrix<T, RVal>::operator()(std::size_t i, std::size_t j) const
    {
      assert(self().impl->size == self().size1 * self().size2);
      assert(i < self().size1);
      assert(j < self().size2);

      unsigned ix = size1() * j + i;
      LOG("idx==") << ix;
      return kamasu_get_elem(self().impl->data, ix);
    }

    template <typename T, typename RVal>
    matrix<T, RVal>::matrix(std::size_t size1, std::size_t size2)
    {
      self().resize(size1, size2);
      assert(self().impl->size == self().size1 * self().size2);
    }

    template <typename T, typename RVal>
    void
    matrix<T, RVal>::operator>>(blas_matrix_t& rhs) const
    {
      assert(self().impl->size == self().size1 * self().size2);

      SHOW();
      LOG("sizes are") << size1() << " " << size2();
      blas_matrix_t bmt(size1(), size2());
      typename blas_matrix_t::array_type& arr = bmt.data();
      LOG("size is") << arr.size();
      T* t = &(bmt.data()[0]);

      CUDA_SAFE_CALL( cudaMemcpy(& (bmt.data()[0]), self().impl->data, 
				 sizeof(T) * self().impl->size,
				 cudaMemcpyDeviceToHost) );
      rhs.assign_temporary(bmt);

    }

    template class matrix<float, boost::mpl::true_>;
    template class matrix<float, boost::mpl::false_>;
  }
}



