#include <resophonic/kamasu/testing.hpp>

namespace resophonic {
  namespace kamasu {
    namespace testing {

      unsigned n_clones;
      unsigned host_to_device;
      unsigned device_to_host;
      unsigned gpu_malloc;

      boost::mt19937 rng;
      boost::uniform_real<float> uniform_distribution(-10,10);
      boost::variate_generator<boost::mt19937&, 
			       boost::uniform_real<float> > uniform(rng, uniform_distribution);

    }
  }
}
