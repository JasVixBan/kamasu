#define SHOW() std::cout << __PRETTY_FUNCTION__ << "\n"
#include <iostream>

struct S {
  S() { SHOW(); }
  ~S() { SHOW(); }
};

struct R 
{
  R() { SHOW(); }

  R(const R&) { SHOW(); }
  R(R&&) { SHOW(); }
  ~R() { SHOW(); }
};

R&& maker() 
{
  R r;
  return r;
}




int main()
{
  S(), R(), std::cout << "thingy at the end\n";
  
  return 0;
}
