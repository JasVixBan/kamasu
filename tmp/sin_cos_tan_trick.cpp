#include <boost/fusion/sequence.hpp>

#include <boost/proto/proto.hpp>
#include <boost/ref.hpp>
#include <vector>
#include <cassert>

namespace bp = boost::proto;

//
// Tag for calls to exp() in our DSEL
//
#define MAKE_TAG(T)							\
  struct T##_tag { };							\
  std::ostream& operator<<(std::ostream& os, T ## _tag)			\
  {									\
    return os << BOOST_PP_STRINGIZE(T) "_tag";				\
  }									\

MAKE_TAG(exp);
MAKE_TAG(sin);
MAKE_TAG(cos);
MAKE_TAG(tan);

std::ostream& operator<<(std::ostream& os, bp::tag::divides)
{
  return os << "divides";
}


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

  //
  //  not called
  //

  array_impl& operator=(array_impl& rhs)
  {
    assert(0); // just to be sure what is and isn't getting called
  }

  array_impl& operator=(const array_impl& rhs)
  {
    assert(0); // just to be sure what is and isn't getting called
  }

  array_impl& operator=(const array_impl&& rhs)
  {
    assert(0); // just to be sure what is and isn't getting called
  }

  friend std::ostream& operator<<(std::ostream& os, 
				  const array_impl&)
  {
    return os << "array_impl";
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
    std::cout << "unary_fn " << Tag() << "\n";
    array_impl tmp(t);
    return std::move(tmp);
  }
};

struct copy_lvalue : bp::callable
{
  typedef array_impl result_type;

  result_type
  operator()(const array_impl& a)
  {
    std::cout << "copy yerself an lvalue\n";
    return a;
  }
};

//
//  The transform for calls to exp.  You'd like to be able to see if
//  this is getting called with a movable object.  
//
struct BinaryFnCall : bp::callable
{
  typedef array_impl result_type;
  
  template <typename Op>
  result_type
  operator()(Op, const array_impl& lhs, const array_impl& rhs)
  {
    std::cout << "binary_fn " << Op() << "\n";
    array_impl tmp(lhs);
    return std::move(tmp);
  }
};

struct RuntimeArgsAreSame : bp::callable
{
  typedef bool result_type;
  
  result_type
  operator()(const array_impl& lhs, const array_impl& rhs)
  {
    bool answer = (&lhs == &rhs);
    std::cout << "RuntimeArgsAreSame == " << answer << "\n";
    return answer;
  }
};

struct Grammar;

struct ArrayTerminal :
  bp::when<bp::terminal<array_impl>, copy_lvalue(bp::_value)>
{ };

struct TrigIdentity 
{ 
  struct call : bp::callable
  {
    typedef array_impl result_type;
  
    result_type
    operator()(const array_impl& lhs, const array_impl& rhs) const
    {
      std::cout << "TrigIdentity\n";
      if (&lhs == &rhs)
	return BinaryFnCall()(tan_tag(), lhs, rhs);
      else
	{
	  std::cout << "NOOOOO\n";
	  return BinaryFnCall()(bp::tag::divides(),
				UnaryFnCall()(sin_tag(), lhs),
				UnaryFnCall()(cos_tag(), rhs));
	}
    }
  };

  typedef bp::when<bp::divides<bp::unary_expr<sin_tag, bp::terminal<array_impl> >,
			       bp::unary_expr<cos_tag, bp::terminal<array_impl> > >,
		   call(bp::_value(bp::_value(bp::_child0)),
			bp::_value(bp::_value(bp::_child1)))>
  impl;
};

struct Grammar :
  bp::or_<TrigIdentity::impl,
	  ArrayTerminal,
	  bp::when<bp::terminal<double>, bp::_value>,
	  bp::when<bp::unary_expr<exp_tag, Grammar>,
		   UnaryFnCall(exp_tag(),
			       Grammar(bp::_child0))>,
	  bp::when<bp::unary_expr<sin_tag, Grammar>,
		   UnaryFnCall(sin_tag(),
			       Grammar(bp::_child0))>s,
	  bp::when<bp::unary_expr<cos_tag, Grammar>,
		   UnaryFnCall(cos_tag(),
			       Grammar(bp::_child0))>,
	  bp::when<bp::multiplies<Grammar, Grammar>,
		   BinaryFnCall(Grammar(bp::_child0),
				Grammar(bp::_child1))>,
	  bp::when<bp::divides<Grammar, Grammar>,
		   BinaryFnCall(bp::tag::divides(), 
				Grammar(bp::_child0),
				Grammar(bp::_child1))>
	  >
{ };



template <typename T>
struct Expression;

struct Domain
  : bp::domain<bp::generator<Expression>, Grammar>
{ };

template <typename Expr>
struct Expression 
  : proto::extends<Expr, Expression<Expr>, Domain>
{
  //  BOOST_PROTO_EXTENDS(Expr, Expression<Expr>, Domain);
};

#define MAKE_LAZYFN(Tag)					\
  template<class T>						\
  typename bp::result_of::make_expr<Tag ## _tag,		\
				    Domain,			\
				    const T&			\
				    >::type			\
  Tag (const T&& t)						\
  {								\
    return bp::make_expr<Tag ## _tag, Domain>(boost::ref(t));	\
  }

MAKE_LAZYFN(exp);
MAKE_LAZYFN(sin);
MAKE_LAZYFN(cos);
MAKE_LAZYFN(tan);

struct happy_context
  : bp::callable_context<happy_context const>
{
  typedef array_impl result_type;

  std::vector<unsigned>& internal_at_depth;
  unsigned& current_depth;

  happy_context(std::vector<unsigned>& depths, unsigned &d) 
    : internal_at_depth(depths), 
      current_depth(d) { }

  struct inc 
  {
    unsigned& what;
    inc(unsigned& what_) : what(what_) { ++what; }

    ~inc() { --what; }
  };

  result_type operator()(bp::tag::terminal, const array_impl&) const
  {
    std::cout << "***** " << __PRETTY_FUNCTION__ << "\n";
    return array_impl();
  }

  result_type operator()(bp::tag::terminal, const double&) const
  {
    std::cout << "***** " << __PRETTY_FUNCTION__ << "\n";
    return array_impl();
  }

  template <typename Tag, typename Lhs>
  result_type operator()(Tag, const Lhs& lhs) const
  {
    std::cout << __PRETTY_FUNCTION__ << "\n";

    internal_at_depth[current_depth]++;

    inc i(current_depth);
    bp::eval(lhs, *this);

    return array_impl();
  }

  template <typename Tag, typename Lhs, typename Rhs>
  result_type operator()(Tag, const Lhs& lhs, const Rhs& rhs) const
  {
    std::cout << __PRETTY_FUNCTION__ << "\n";

    internal_at_depth[current_depth]++;

    inc i(current_depth);
    bp::eval(lhs, *this);
    bp::eval(rhs, *this);
    return array_impl();
  }

};

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
  array& operator=(Expr&& expr)
  {
    unsigned depth  = 0;
    std::vector<unsigned> nodes(10);
    happy_context yay(nodes, depth);
    bp::eval(expr, yay);
    for (unsigned i=0; nodes[i] > 0; i++)
      std::cout << "Depth " << i << " internal nodes:" << nodes[i] << "\n";

    bp::display_expr(expr, std::cout);
    BOOST_MPL_ASSERT(( bp::matches<Expr, Grammar> ));

    typedef typename boost::result_of<Grammar(Expr&&)>::type result_t;

    result_t r = Grammar()(expr);

    self().operator=(std::move(r));

    return *this;
  }
};

#define SHOW std::cout << __PRETTY_FUNCTION__

template <typename T, typename what = void>
struct foo
{
  static void go() { SHOW << " one\n"; }
};

template <typename T>
struct foo<T, typename T::has_something>
{
  static void go() { SHOW << "two\n"; }
};

template <typename T>
struct foo<T, typename T::has_something_else>
{
  static void go() { SHOW << "three\n"; }
};

struct Blah
{
  typedef int has_something;
};

struct Else
{
  typedef int has_something_else;
};

int main(int, char**)
{
  array a("a"), b("b");

  foo<Else>::go();
  foo<Else, Else::has_something_else>::go();
  foo<Blah>::go();
  foo<int>::go();
  // Here, only one copy is made
  //  a = exp(exp(b));
  //  std::cout << "a's name:" << a.self().name << "\n\n";

  // Here, two copies are made
  //  a = exp(exp(exp(b) * exp(b)));
  //  std::cout << "a's name:" << a.self().name << "\n";

  a = sin(a) / cos(b);

}

