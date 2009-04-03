#include <iostream>
#include <boost/proto/proto.hpp>
#include <boost/proto/transform.hpp>
namespace proto = boost::proto;

struct times2
{
  typedef int result_type;

  //  times2(){ }

  times2(const int& i){ std::cout << __PRETTY_FUNCTION__ << "\n"; }
  times2(){ std::cout << __PRETTY_FUNCTION__ << "\n"; }

  int operator()(int i, const int& state) const
  {
    std::cout << "Called times2() state=" << state << "\n";
    return i * 2;
  }
};

struct plus2
{
  typedef double result_type;

  double operator()(double i) const
  {
    std::cout << "Called plus2()\n";
    return i * 2;
  }
};

typedef proto::when<proto::terminal<proto::_>, times2> chooser_t;

struct IntTimes2 : proto::when<proto::terminal<proto::_>,
			       proto::lazy<chooser_t(proto::_value, proto::_state) >
			       >
{ };

int main()
{
  int dummy = 777;
  proto::terminal<int>::type i = {1};
  proto::terminal<double>::type d = {1.111};

  IntTimes2()(i, dummy, dummy);
}
