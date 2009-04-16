#include <iostream>
#include <stdexcept>
// #include <resophonic/kamasu.hpp>

int main(int, char**)
{
  std::cout << "hi\n";
  throw std::runtime_error("EEK");
}
