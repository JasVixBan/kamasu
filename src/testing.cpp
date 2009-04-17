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


      namespace ublas = boost::numeric::ublas;

      template <typename T>
      ublas::matrix<T, ublas::column_major> 
      rand_matrix (unsigned n, unsigned m)
      {
	ublas::matrix<T, ublas::column_major> mat(n, m);
	for (int i=0; i<n; i++)
	  for (int j=0; j<m; j++)
	    mat(i,j) = uniform();
	return mat;
      }

      template ublas::matrix<float, ublas::column_major> rand_matrix(unsigned, unsigned);


    }
  }
}
