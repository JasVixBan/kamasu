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

int main(int argc, char *argv[]) 
{
  unsigned data_len = atoi(argv[1]);
  const unsigned N = atoi(argv[2]);
  
  boost::timer total, math;
  total.restart();
  
  std::vector<float> a(data_len), filtered(data_len-N);
  std::vector<float> coeff(N);
  math.restart();

  for (int n=0; n<N; n++)
    for (int x=0; x<data_len-N; x++)
      filtered[x] += a[x+n] * coeff[n];

  std::cout << "mathtime: " << math.elapsed() << "\n";
} 

