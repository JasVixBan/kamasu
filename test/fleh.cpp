#include <iostream>
#include <boost/proto/proto.hpp>
#include <boost/proto/transform.hpp>

#include <boost/mpl/if.hpp>
#include <boost/function.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <resophonic/kamasu/name_of.hpp>



template <typename T, std::size_t N>
void f(T(&)[N])
{
  std::cout << "array has length " << N << "\n";
}

int main() 
{
  int a[17];  
  f(a);
}

