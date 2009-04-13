#include <iostream>
#include <resophonic/kamasu.hpp>
#include <boost/lexical_cast.hpp>

using resophonic::kamasu::array;

int main(int argc, char** argv)
{
  if (argc < 1)
    {
      std::cout << "usage: create X\nX == size of (1d) matrix to create\n";
      return 1;
    }
  unsigned len = boost::lexical_cast<unsigned>(argv[1]);
  std::cout << "creating array<float>(" << len << ")\n";

  array<float> a(len);

}




