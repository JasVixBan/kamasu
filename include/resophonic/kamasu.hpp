#ifndef RESOPHONIC_KAMASU_HPP_INCLUDED
#define RESOPHONIC_KAMASU_HPP_INCLUDED

#include <resophonic/kamasu/state.hpp>
#include <resophonic/kamasu/data.hpp>
#include <resophonic/kamasu/config.hpp>
#include <resophonic/kamasu/logging.hpp>

#include <boost/shared_ptr.hpp>

#define BOOST_PROTO_NO_DEBUG

#include <boost/proto/proto.hpp>

namespace std {
  class exception;
}

#include <stdio.h>
#include <cassert>

#include <resophonic/kamasu/array.hpp>
#include <resophonic/kamasu/grammar.hpp>
#include <resophonic/kamasu/exception.hpp>

#define KAMASU_SAFE_CALL( call ) do {					\
    cudaError err = call;						\
    if( cudaSuccess != err) {						\
      throw resophonic::kamasu::cuda_exception(err, __FILE__, __LINE__); \
    } } while (false)


#endif
