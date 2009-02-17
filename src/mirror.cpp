// #define I3_PRINTF_LOGGING_LEVEL LOG_DEBUG
#include <resophonic/kamasu.hpp>
#include <resophonic/kamasu/mirror.hpp>
#include <resophonic/kamasu/logging.hpp>
#include <iostream>
#include <boost/shared_ptr.hpp>

#include <cutil.h>
#include <cublas.h>
#include <cuda_runtime.h>

#include <boost/pool/singleton_pool.hpp>

namespace resophonic {
  namespace kamasu {

    template<typename T>
    mirror<T>::mirror() /*: gpu_(0), dirty(false)*/
    { 
      log_trace("%s", __PRETTY_FUNCTION__);
    }

    template <typename T>
    void
    mirror<T>::reset()
    {
      /*
      if (gpu_)
	{
	  KAMASU_SAFE_CALL(cudaFree(gpu_));
	  gpu_ = 0;
	}
      BOOST_ASSERT(gpu_ == 0);
      dirty = false;
      */
    }

    template <typename T>
    mirror<T>::~mirror() 
    {
      /*
      log_trace("%s", __PRETTY_FUNCTION__);
      if (gpu_)
	{
	  KAMASU_SAFE_CALL(cudaFree(gpu_));
	  gpu_ = 0;
	}
      */
    }

    /*
    template <typename T>
    T* 
    mirror<T>::gpu_malloc() const
    {

      T* devmem;
      KAMASU_SAFE_CALL(cudaMalloc((void**) &devmem,  KAMASU_MAX_ARRAY_DIM* sizeof(T)));
      log_trace ("malloc %u = %x", (KAMASU_MAX_ARRAY_DIM * sizeof(T)) % devmem);
      KAMASU_SAFE_CALL(cudaMemset(devmem, 0, KAMASU_MAX_ARRAY_DIM * sizeof(T)));
      return devmem;
    }
    */

    template <typename T>
    mirror<T>*
    mirror<T>::clone() const
    {
      mirror* new_p = new mirror;
      new_p->clone(*this);
      return new_p;
    }

    template <typename T>
    void
    mirror<T>::clone(const mirror& rhs)
    {
      if (this == &rhs)
	return;

      reset();
      memcpy(cpu_, rhs.cpu_, KAMASU_MAX_ARRAY_DIM*sizeof(T));
      //dirty = true;
    }

    template <typename T>
    void
    mirror<T>::set(const std::vector<T>& v)
    {
      set_impl(v.data(), v.size());
    }

    template <typename T>
    void
    mirror<T>::set_impl(const T* hdata, std::size_t s)
    {
      reset();
      if (s == 0)
	return;
      memcpy(cpu_, hdata, sizeof(T) * s);
      //dirty = true;
    }

    template <typename T>
    void
    mirror<T>::sync() const
    {
      /*
      dirty = false;
      /*
      if (! gpu_)
	gpu_ = gpu_malloc();
      KAMASU_SAFE_CALL( cudaMemcpy( gpu_,  cpu_, KAMASU_MAX_ARRAY_DIM * sizeof(T),
				  cudaMemcpyHostToDevice) );
      */
    }

    /*
    template <typename T>
    const T*
    mirror<T>::gpu_data() const
    {
      if (dirty) sync();
      return gpu_;
    }

    template <typename T>
    T*
    mirror<T>::gpu_data()
    {
      if (dirty) sync();
      return gpu_;
    }
    */
    template class mirror<unsigned>;
    template class mirror<int>;

  }
}
