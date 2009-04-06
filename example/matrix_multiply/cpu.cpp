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
        
  ublas::matrix<float> A(n,n), B(n,n), C(n, n);
  
  std::cout << "multiplying NxN array by NxN array where N=" << n << " (" << times << " times).\n";
  t.restart();
  for (unsigned i=0; i<times; i++)
    C = prod(A,B);

  time = t.elapsed();
  cout << "elapsed time - " << time << "s" << endl << endl;
        
  return 0;
} 

