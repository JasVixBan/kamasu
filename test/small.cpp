#include <boost/fusion/sequence.hpp>

#include <boost/proto/proto.hpp>
#include <boost/ref.hpp>
#include <cassert>
#include <resophonic/kamasu/name_of.hpp>

namespace bp = boost::proto;
using resophonic::name_of;

//
// Tag for calls to exp() in our DSEL
//
struct exp_tag 
{ 
  friend std::ostream& operator<<(std::ostream& os, exp_tag) 
  { 
    return os << "exp_tag"; 
  }
};

//
//  The terminal.  Assume this thing is very heavy.  Some construtors
//  have assert(0) in them to verify they aren't called.
//
//
struct array_impl 
{
  std::string name;

  array_impl() 
    : name("NONAME") 
  { }

  array_impl(const std::string& name_) 
    : name(name_) 
  { 
    std::cout << "name=" << name << "\n";
  }

  //
  //  constructors
  //

  array_impl(array_impl& rhs) 
    : name(rhs.name + "_copied")
  { }

  array_impl(const array_impl& rhs) 
    : name(rhs.name+ "_copied")
  { }

  array_impl(array_impl&& rhs) 
  { 
    name.swap(rhs.name);
    name += "_moved";
  }

  array_impl& operator=(array_impl&& rhs)
  {
    name.swap(rhs.name);
    name += "_moved";
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, 
				  const array_impl&)
  {
    return os << "array_impl";
  }
};

struct UnaryFnCall;
struct array;

struct Grammar :
  bp::or_<bp::when<bp::terminal<array_impl>, bp::_value>,
	  bp::when<bp::unary_expr<exp_tag, Grammar>, 
		   UnaryFnCall(exp_tag(), 
			       Grammar(bp::_child0))> 
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
  exp_tag,
  Domain,
  const T&
  >::type
exp (const T& t)
{
  return bp::make_expr<exp_tag, Domain>(boost::ref(t));
}

//
//  Our expression type that 
//
struct array : public Expression<bp::terminal<array_impl>::type>
{
  typedef array_impl impl_t;

  impl_t& self() { return boost::proto::value(*this); }

  array() { assert(0); }

  array(const std::string& name)
  {
    self().name = name;
  }

  array(const array&) { assert(0); }

  array(array&&) { assert(0); }
  
  template <typename Expr>
  array& operator=(Expr const& expr)
  {
    bp::display_expr(expr, std::cout);
    BOOST_MPL_ASSERT(( bp::matches<Expr, Grammar> ));

    typedef typename boost::result_of<Grammar(Expr const&)>::type result_t;

    std::cout << "result_t = " << name_of<result_t>() << "\n";

    return *this;
  }
};

//
//  The transform for calls to exp.  You'd like to be able to see if
//  this is getting called with a movable object.  
//
struct UnaryFnCall : bp::callable
{
  typedef array_impl result_type;
  
  template <typename Tag>
  result_type
  operator()(Tag, const array_impl& t)
  {
    std::cout << "transform a const ref\n";
    array_impl tmp(t);
    return tmp;
  }
};


int main(int, char**)
{
  array a("a"), b("b");

  // Here, only one copy is made
  a = exp(b);
  std::cout << "a's name:" << a.self().name << "\n\n";

  // Here, two copies are made
  //  a = exp(exp(exp(b)));
  //  std::cout << "a's name:" << a.self().name << "\n";




}
