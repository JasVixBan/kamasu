#ifndef RESOPHONIC_KAMASU_TESTING_HPP_INCLUDED
#define RESOPHONIC_KAMASU_TESTING_HPP_INCLUDED

#include <boost/noncopyable.hpp>

namespace resophonic {
  namespace kamasu {
    namespace testing {

      extern unsigned n_clones, host_to_device, device_to_host, gpu_malloc;

    }
  }
}

#ifdef RESOPHONIC_KAMASU_DEBUG
#define RESOPHONIC_KAMASU_WHITEBOX(thing) thing
#else
#define RESOPHONIC_KAMASU_WHITEBOX(thing) 
#endif

#endif

