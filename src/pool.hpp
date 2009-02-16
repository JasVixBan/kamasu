#ifndef RESOPHONIC_KAMASU_POOL_HPP_INCLUDED
#define RESOPHONIC_KAMASU_POOL_HPP_INCLUDED

#include <boost/pool/singleton_pool.hpp>
#include <cuda_runtime.h>
#include "cutil.h"


namespace resophonic {
  namespace kamasu {
    namespace {

      struct tag { };

      struct cuda_host_alloc
      {
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;

	static char* malloc(const size_type bytes)
	{
	  void *ptr;
	  CUDA_SAFE_CALL(cudaMallocHost(&ptr, bytes));
	  return (char*)ptr;
	}

	static void free(char* const block)
	{
	  CUDA_SAFE_CALL(cudaFreeHost(block));
	}

      };

      typedef boost::singleton_pool<tag, sizeof(holder<float>), cuda_host_alloc> holder_pool;
      typedef boost::singleton_pool<tag, sizeof(detail::impl_t), cuda_host_alloc> impl_pool;

    }
  }
}

#endif
