#ifndef RESOPHONIC_KAMASU_HPP_INCLUDED
#define RESOPHONIC_KAMASU_HPP_INCLUDED

#include <resophonic/kamasu/config.hpp>
#include <resophonic/kamasu/logging.hpp>

#define BOOST_SP_NO_ATOMIC_ACCESS
#define BOOST_SP_DISABLE_THREADS
#include <boost/shared_ptr.hpp>

#define BOOST_PROTO_NO_DEBUG
// hmm.  will this work?
#ifndef __CUDACC__
#include <boost/proto/proto.hpp>
#endif

namespace std {
  class exception;
}

const unsigned threads_per_block = 512;

#include <stdio.h>
#include <cassert>
namespace boost {
  inline void throw_exception(std::exception const& e)
  {
    printf("oh noes, exception.\n");
    assert(false);
  }
}

#include <resophonic/kamasu/array.hpp>
#include <resophonic/kamasu/grammar.hpp>

#endif
