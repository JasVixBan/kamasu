#ifndef RESOPHONIC_KAMASU_POOL_HPP_INCLUDED
#define RESOPHONIC_KAMASU_POOL_HPP_INCLUDED

#include <resophonic/kamasu.hpp>
#include <resophonic/kamasu/testing.hpp>
#include <boost/pool/singleton_pool.hpp>
#include <cuda_runtime.h>


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
	  RESOPHONIC_CUDAMALLOC_DEBUG(std::cerr << "mallocHost " << bytes << "\n");
	  cuda_check(cudaMallocHost(&ptr, bytes));
	  RESOPHONIC_CUDAMALLOC_DEBUG(std::cerr << " @ " << ptr << "\n");
	  return (char*)ptr;
	}

	static void free(char* const block)
	{
	  RESOPHONIC_CUDAMALLOC_DEBUG(std::cerr << "free " << block << "\n");
	  cuda_check(cudaFreeHost(block));
	}

      };

      typedef boost::singleton_pool<tag, sizeof(holder<float>)> holder_pool;

    }
  }
}

#endif
