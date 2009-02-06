// #define I3_PRINTF_LOGGING_LEVEL LOG_DEBUG
#include <resophonic/kamasu.hpp>
#include <resophonic/kamasu/mirror.hpp>
#include <resophonic/kamasu/logging.hpp>
#include <iostream>
#include <boost/shared_ptr.hpp>

#include <cutil.h>
#include <cublas.h>
#include <cuda_runtime.h>

namespace resophonic {
  namespace kamasu {

    template<typename T>
    mirror<T>::mirror() : gpu_(0), cpu_(0), dirty(false)
    { 
      log_trace("%s") % __PRETTY_FUNCTION__;
    }

    template <typename T>
    void
    mirror<T>::reset()
    {
      BOOST_ASSERT ((gpu_ == 0 && size() == 0) 
		    || (gpu_ != 0 && size() != 0));
      if (size() > 0)
	BOOST_ASSERT(gpu_);
      if (gpu_)
	BOOST_ASSERT(size());
      dirty = false;

      if (gpu_)
	{
	  CUDA_SAFE_CALL(cudaFree(gpu_));
	  gpu_ = 0;
	  cpu_.resize(0);
	}
      BOOST_ASSERT(size() == 0);
      BOOST_ASSERT(gpu_ == 0);
    }

    template <typename T>
    mirror<T>::~mirror() 
    {
      log_trace("%s") % __PRETTY_FUNCTION__;
      reset();
    }

    template <typename T>
    T* mirror<T>::gpu_mallocn(unsigned n) const
    {
      T* devmem;
      CUDA_SAFE_CALL( cublasAlloc( n, sizeof(T), (void**) &devmem));
      log_trace ("malloc %u = %x") % (n * sizeof(T)) % devmem;
      cudaMemset(devmem, 0, n * sizeof(T));
      return devmem;
    }

    template <typename T>
    void
    mirror<T>::resize(std::size_t s)
    {
      if (size() == s)
	return;
      reset();
      if (s == 0)
	return;
      gpu_ = gpu_mallocn(s);
      cudaMemset(gpu_, 0, s);
      std::vector<T>(s, 0).swap(cpu_);
    }

    template <typename T>
    boost::shared_ptr<mirror<T> >
    mirror<T>::clone() const
    {
      boost::shared_ptr<mirror> new_p(new mirror);
      new_p->clone(*this);
      return new_p;
    }

    template <typename T>
    void
    mirror<T>::clone(const mirror& rhs)
    {
      reset();
      if (rhs.size() == 0)
	return;
      cpu_ = rhs.cpu_;
      gpu_ = gpu_mallocn(rhs.size());
      CUDA_SAFE_CALL( cudaMemcpy( gpu_, rhs.gpu_, 
				  sizeof(T) * size(),
				  cudaMemcpyDeviceToDevice) );
      log_debug("*** CLONED RHS %u bytes @%p***") % gpu_ % size();
    }

    template <typename T>
    void
    mirror<T>::set(const std::vector<T>& v)
    {
      set(v.data(), v.size());
    }

    template <typename T>
    void
    mirror<T>::sync() const
    {
      dirty = false;
      gpu_ = gpu_mallocn(cpu_.size() * sizeof(T));
      CUDA_SAFE_CALL( cudaMemcpy( gpu_,  cpu_.data(), cpu_.size() * sizeof(T),
				  cudaMemcpyHostToDevice) );
    }

    template <typename T>
    void
    mirror<T>::set(const T* hdata, std::size_t s)
    {
      reset();
      if (s == 0)
	return;
      cpu_.resize(s);
      memcpy(cpu_.data(), hdata, sizeof(T) * size());
      dirty = true;
    }

    template <typename T>
    void
    mirror<T>::set(unsigned i, T value)
    {
      BOOST_ASSERT(i < size());
      cpu_[i] = value;
      log_trace("Set %s at %u of %u") % value % i % size();
      dirty = true;
    }

    template <typename T>
    std::size_t
    mirror<T>::size() const
    {
      return cpu_.size();
    }

    template <typename T>
    const T*
    mirror<T>::gpu_data() const
    {
      return gpu_;
    }


    template <typename T>
    T*
    mirror<T>::gpu_data()
    {
      return gpu_;
    }

    template <typename T>
    T
    mirror<T>::get(unsigned i) const
    {
      if (not (i < size()))
	log_error("egh, trying to get %u from block of size %u") % i % size();

      return cpu_[i];
    }
      
    template class mirror<unsigned>;
    template class mirror<int>;

  }
}
