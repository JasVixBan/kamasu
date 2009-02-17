#ifndef RESOPHONIC_KAMASU_POOL_HPP_INCLUDED
#define RESOPHONIC_KAMASU_POOL_HPP_INCLUDED

#include <resophonic/kamasu.hpp>
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
	  KAMASU_SAFE_CALL(cudaMallocHost(&ptr, bytes));
	  return (char*)ptr;
	}

	static void free(char* const block)
	{
	  KAMASU_SAFE_CALL(cudaFreeHost(block));
	}

      };

      typedef boost::singleton_pool<tag, sizeof(holder<float>)> holder_pool;

    }
  }
}

#endif
