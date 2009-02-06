// #define I3_PRINTF_LOGGING_LEVEL LOG_DEBUG
#include <resophonic/kamasu.hpp>
#include <resophonic/kamasu/holder.hpp>
#include <resophonic/kamasu/logging.hpp>
#include <iostream>
#include <boost/shared_ptr.hpp>

#include <cutil.h>
#include <cublas.h>
#include <cuda_runtime.h>

namespace resophonic {
  namespace kamasu {

    template<typename T>
    holder<T>::holder() : data_(0), size_(0) 
    { 
      log_trace("%s") % __PRETTY_FUNCTION__;
    }

    template <typename T>
    void
    holder<T>::reset()
    {
      BOOST_ASSERT ((data_ == 0 && size_ == 0) 
		    || (data_ != 0 && size_ != 0));
      if (size_ > 0)
	BOOST_ASSERT(data_);
      if (data_)
	BOOST_ASSERT(size_);

      if (data_)
	{
	  CUDA_SAFE_CALL(cudaFree(data_));
	  data_ = 0;
	  size_ = 0;
	}
    }

    template <typename T>
    holder<T>::~holder() 
    {
      log_trace("%s") % __PRETTY_FUNCTION__;
      reset();
    }

    template <typename T>
    T* holder<T>::gpu_mallocn(unsigned n)
    {
      T* devmem;
      CUDA_SAFE_CALL( cublasAlloc( n, sizeof(T), (void**) &devmem));
      log_trace ("malloc %u = %x") % (n * sizeof(T)) % devmem;
      cudaMemset(devmem, 0, n * sizeof(T));
      return devmem;
    }

    template <typename T>
    void
    holder<T>::resize(std::size_t s)
    {
      if (size_ == s)
	return;
      reset();
      if (s == 0)
	return;
      data_ = gpu_mallocn(s);
      cudaMemset(data_, 0, s);
      size_ = s;
    }

    template <typename T>
    boost::shared_ptr<holder<T> >
    holder<T>::clone() const
    {
      boost::shared_ptr<holder> new_p(new holder);
      new_p->clone(*this);
      return new_p;
    }

    template <typename T>
    void
    holder<T>::clone(const holder& rhs)
    {
      reset();
      if (rhs.size_ == 0)
	return;
      size_ = rhs.size_;
      data_ = gpu_mallocn(rhs.size_);
      CUDA_SAFE_CALL( cudaMemcpy( data_, rhs.data_, 
				  sizeof(T) * size_,
				  cudaMemcpyDeviceToDevice) );
      log_debug("*** CLONED RHS %u bytes @%p***") % size_ % data_;
    }

    template <typename T>
    void
    holder<T>::host_to_device(const std::vector<T>& v)
    {
      host_to_device(v.data(), v.size());
    }

    template <typename T>
    void
    holder<T>::host_to_device(const T* hdata, std::size_t s)
    {
      reset();
      if (s == 0)
	return;
      size_ = s;
      data_ = gpu_mallocn(size_ * sizeof(T));
      CUDA_SAFE_CALL( cudaMemcpy( data_,  hdata, size_ * sizeof(T),
				  cudaMemcpyHostToDevice) );
    }

    template <typename T>
    void
    holder<T>::device_to_host(T* hdata)
    {
      if (size_ == 0)
	return;
      CUDA_SAFE_CALL( cudaMemcpy( hdata, data_, size_ * sizeof(T),
				  cudaMemcpyDeviceToHost) );
    }

    template <typename T>
    std::size_t
    holder<T>::size() const
    {
      return size_;
    }

    template <typename T>
    const T*
    holder<T>::data() const
    {
      return data_;
    }


    template <typename T>
    T*
    holder<T>::data()
    {
      return data_;
    }

    template <typename T>
    T
    holder<T>::get(unsigned i) const
    {
      if (not (i < size_))
	log_error("egh, trying to get %u from block of size %u") % i % size_;
      BOOST_ASSERT(i < size_);

      T value;
      const T* addy = data_ + i;
      CUDA_SAFE_CALL( cudaMemcpy(&value, addy, sizeof(T), cudaMemcpyDeviceToHost) );
      log_trace("Got %s from [%u] of %u ") % value % i % size_;
      return value;
    }
      
    template <typename T>
    void
    holder<T>::set(unsigned i, T value)
    {
      BOOST_ASSERT(i < size_);
      T* addy = data_ + i;
      CUDA_SAFE_CALL( cudaMemcpy(addy, &value, sizeof(T), cudaMemcpyHostToDevice) );
      log_trace("Set %s at %u of %u") % value % i % size_;
    }

    template class holder<float>;
    template class holder<unsigned>;
    template class holder<int>;

  }
}
