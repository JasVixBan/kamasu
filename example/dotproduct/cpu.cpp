#include <iostream>
#include <cassert>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>

#include <iostream>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/timer.hpp>
 
//g++ bench.cc -o test -I/usr/local/lib/boost_1_29_0/ -O3 -DNDEBUG

namespace ublas = boost::numeric::ublas;

using namespace std;
//using namespace ublas;

int main(int argc, char *argv[]) {
        
  unsigned n = atoi(argv[1]);
  unsigned times = argc == 3 ? atoi(argv[2]) : 1;
        
  boost::timer t;
  double time;
        
  ublas::vector<float> A(n), B(n);
  for (unsigned i=0; i<n; i++)
    {
      A(i) = i;
      B(i) = i;
    }
  std::cout << "taking dot product of two " << n << " element vectors (" << times << " times).\n";
  t.restart();
  for (int i=0; i<times; i++)
    {    
      A(0) = i;
      float f = ublas::inner_prod(A, B);
    }

  time = t.elapsed();
  cout << "elapsed time - " << time << "s" << endl << endl;
        
  return 0;
} 

