#include <boost/fusion/sequence.hpp>
#include <boost/format.hpp>
#include <boost/proto/proto.hpp>
#include <boost/ref.hpp>
#include <vector>
#include <cassert>

namespace bp = boost::proto;

struct ToString : bp::callable
{
  typedef std::string result_type;
  template <typename T>
  result_type operator()(const T& t)
  {
    return str(boost::format("%s @ %p") % t % &t);
  }

  result_type operator()(bp::tag::plus, const std::string& lhs, const std::string& rhs)
  {
    return str(boost::format("%s PLUS %s") % lhs % rhs );
  }
};

struct array_impl 
{ 
  friend std::ostream& operator<<(std::ostream& os, array_impl) { return os << "array_impl"; }
};

struct FloatTerminal
  : bp::when<bp::terminal<float>, ToString(bp::_value)>
{ };

struct ArrayTerminal
  : bp::when<bp::terminal<array_impl>, ToString(bp::_value)>
{ };

struct data
{
  unsigned curdepth;
  unsigned maxdepth;
};

struct Grammar
  : bp::or_<ArrayTerminal,
	    FloatTerminal,
	    bp::when<bp::plus<Grammar, Grammar>,
		     ToString(bp::tag::plus(),
			      Grammar(bp::_left),
			      Grammar(bp::_right))>
	    >
{ };

struct array : bp::terminal<array_impl>::type { };

int main(int, char**)
{
  //  bp::terminal<float>::type f = {3.14};
  array a;
  std::cout << Grammar()(a + 777.0f);
}
