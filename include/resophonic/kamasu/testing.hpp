#ifndef RESOPHONIC_KAMASU_TESTING_HPP_INCLUDED
#define RESOPHONIC_KAMASU_TESTING_HPP_INCLUDED

#include <boost/random.hpp>

// #define RESOPHONIC_CUDAMALLOC_DEBUG(X) resophonic::kamasu::testing::cudamalloc_bp(), X
#define RESOPHONIC_CUDAMALLOC_DEBUG(X)

namespace resophonic {
  namespace kamasu {
    namespace testing {

      extern unsigned n_clones, host_to_device, device_to_host, gpu_malloc;

      inline void cudamalloc_bp() { }

      extern boost::mt19937 rng;
      extern boost::uniform_real<float> uniform_distribution;
      extern boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > uniform;

    }
  }
}

#ifdef RESOPHONIC_WHITEBOX_TESTING
#define RESOPHONIC_KAMASU_WHITEBOX(thing) thing
#else
#define RESOPHONIC_KAMASU_WHITEBOX(thing) 
#endif

#endif

