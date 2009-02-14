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
        
  boost::timer t;
  double time;
        
  ublas::matrix<float> A(n,n), B(n,n), C(n, n);
  
  cout << "computing X = A*B" << endl;
  t.restart();
  C = prod(A,B);
  time = t.elapsed();
  cout << "elapsed time - " << time << "s" << endl << endl;
        
#if 0
        
  // A*B*C
  cout << "computing X = A*B*C" << endl;
  t.restart();
  //X = prod(A, prod(B,C)); // - !!!!!!!!!!!
  X = prod(A, ublas::matrix<double> (prod(B,C)));
  time = t.elapsed();
  cout << "elapsed time - " << time << "s" << endl << endl;
        
        
  // A*B*C*D
  cout << "computing X = A*B*C*D" << endl;
  t.restart();
  //B = prod(A ,prod(B, prod(C,D))); // !!!!!!!!!
  X = prod(A, ublas::matrix<double> (prod(B, ublas::matrix<d
					  ouble> (prod(C,D)))));
  time = t.elapsed();
  cout << "elapsed time - " << time << "s" << endl;
                
        
  cout << "end" << endl;
#endif
  return 0;
} 

