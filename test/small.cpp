#include <boost/proto/proto.hpp>
#include <boost/ref.hpp>
#include <resophonic/kamasu/name_of.hpp>

namespace bp = boost::proto;
using resophonic::name_of;
template <typename T>
struct nameable {
  friend std::ostream& operator<<(std::ostream& os, T)
  {
    return os << name_of<T>();
  }
};

struct pow_tag : nameable<pow_tag> { };

struct dot_tag : nameable<dot_tag> { };


struct UnaryFnCall : bp::callable
{
  typedef float result_type;
  
  template <typename Tag, typename T>
  result_type
  operator()(Tag, const T& t, float& state)
  {
    std::cout << __PRETTY_FUNCTION__ << " state=" << state << "\n";
    state += 100;
    return state;
  }

};

struct BinaryFnCall : bp::callable
{
  typedef float result_type;
  
  template <typename Tag, typename T, typename U>
  result_type
  operator()(Tag, const T& t, const U& u, float& state)
  {
    std::cout << __PRETTY_FUNCTION__ << " state=" << state << "\n";
    state += 10;
    return state;
  }
};

struct Grammar;

struct Cases
{
  template <typename Tag, int i=0>
  struct case_ : bp::not_<bp::_> { };

  template <int i>
  struct case_<pow_tag, i>
    : bp::when<bp::unary_expr<pow_tag, Grammar>, 
	       UnaryFnCall(pow_tag(), 
			   Grammar(bp::_child0, bp::_state, bp::_data), 
			   bp::_data)>
  { };

  template <int i>
  struct case_<dot_tag, i>
    : bp::when<bp::binary_expr<dot_tag, Grammar, Grammar>,
	       BinaryFnCall(dot_tag(), 
			    Grammar(bp::_child0, bp::_state, bp::_data), 
			    Grammar(bp::_child1, bp::_state, bp::_data),
			    bp::_data)>
  { };
};

struct Switch : bp::switch_<Cases> { };

struct Grammar :
    bp::or_<bp::when<bp::terminal<float>, bp::_value>
	    , Switch
	    >
{ };

template <typename T>
struct Expression;

struct Domain
  : bp::domain<bp::pod_generator<Expression>, Grammar>
{ };

template <typename Expr>
struct Expression
{
  BOOST_PROTO_EXTENDS(Expr, Expression<Expr>, Domain);
};


template<class T>
typename bp::result_of::make_expr<
  pow_tag,
  Domain,
  T const &
  >::type
pow (T const &t)
{
  return bp::make_expr<pow_tag, Domain>(boost::ref(t));
}

template<class T, class U>
typename bp::result_of::make_expr<
  dot_tag,
  Domain,
  T const &,
  U const &
  >::type
dot (T const& t, U const& u)
{
  return bp::make_expr<dot_tag, Domain>(boost::ref(t), boost::ref(u));
}

template <typename Expr>
void 
matchit(Expr const& expr)
{
  std::cout << "\n\n" << name_of(expr) << "\n\n";
  bp::display_expr(expr, std::cout);
  BOOST_MPL_ASSERT(( bp::matches<Expr, Grammar> ));

  float state = 0, data = 0;

  typename boost::result_of<Grammar(Expr const&, float&, float&)>::type 
    thingy = Grammar()(expr, state, data);

  std::cout << "RESULT:" << data;

}


int main(int, char**)
{
  float f = 3.14;

  std::cout << "\n";

  matchit(pow(3.1415f));
  matchit(dot(3.1415f, 4.444f));
  matchit(
  	  pow(dot(3.1415f, 3.11f))
  	  );
}
