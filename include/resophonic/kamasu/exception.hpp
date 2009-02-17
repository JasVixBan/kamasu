#ifndef RESOPHONIC_KAMASU_EXCEPTION_HPP_INCLUDED
#define RESOPHONIC_KAMASU_EXCEPTION_HPP_INCLUDED

#include <exception>
#include <cassert>
#include <resophonic/kamasu/config.hpp>
#include <cuda.h>
#include <cublas.h>
#include <cutil.h>
#include <cuda_runtime.h>

namespace resophonic {
  namespace kamasu {

    struct bad_index : virtual std::exception
    {
      bad_index() { }

      virtual const char* what() const throw()
      {
	return "resophonic::kamasu error: bad index";
      }
    };

    struct zero_dim : virtual std::exception
    {
      std::size_t which_dim;
      zero_dim(std::size_t which) : which_dim(which) { }

      virtual const char* what() const throw()
      {
	return "resophonic::kamasu error:"
	  "illegal zero dimension (minimum is 1 for a degenerate slice)";
      }
    };

    struct dimensions_dont_match : virtual std::exception
    {
      dimensions_dont_match() { }

      virtual const char* what() const throw()
      {
	return "resophonic::kamasu error: wrong number of dimensions";
      }
    };

    struct cublas_exception : virtual std::exception
    {
      cublasStatus s;
      cublas_exception(cublasStatus s_) : s(s_) { }
      virtual const char* what() const throw()
      {
	return "resophonic::kamasu error: cublas is unhappy";
      }
    };

    struct cuda_exception : virtual std::exception
    {
      cudaError_t e;
      const char *file, *msg;
      unsigned line;

      cuda_exception(cudaError_t e_, const char* file_, unsigned line_) 
	: e(e_), file(file_), msg(cudaGetErrorString(e_)), line(line_)  
      { }
      virtual const char* what() const throw()
      {
	return msg;
      }
    };


  }
}

#endif
