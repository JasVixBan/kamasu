#ifndef RESOPHONIC_KAMASU_TESTING_HPP_INCLUDED
#define RESOPHONIC_KAMASU_TESTING_HPP_INCLUDED

#include <boost/noncopyable.hpp>

#define RESOPHONIC_CUDAMALLOC_DEBUG(X) resophonic::kamasu::testing::cudamalloc_bp(), X

namespace resophonic {
  namespace kamasu {
    namespace testing {

      extern unsigned n_clones, host_to_device, device_to_host, gpu_malloc;

      inline void cudamalloc_bp() { }
    }
  }
}

#ifdef RESOPHONIC_WHITEBOX_TESTING
#define RESOPHONIC_KAMASU_WHITEBOX(thing) thing
#else
#define RESOPHONIC_KAMASU_WHITEBOX(thing) 
#endif

#endif

