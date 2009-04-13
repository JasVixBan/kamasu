#include <iostream>
#include <vector>
#include <array>
#include <boost/proto/proto.hpp>
#include <boost/proto/transform.hpp>
#include <boost/mpl/print.hpp>
#include <boost/mpl/vector.hpp>
#include <tuple>

#include <boost/mpl/if.hpp>
#include <boost/function.hpp>
#include <boost/array.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/lambda/lambda.hpp>
#include <resophonic/kamasu/name_of.hpp>
#include "cuda.h"


namespace bp = boost::proto;
using resophonic::name_of;

template <typename T, T... Args> struct product;

template <typename T, T Head, T... Tail>
struct product<T, Head, Tail...> : private product<T, Tail...>
{
  typedef product<T, Tail...> base_t;
  const static T value = Head * base_t::value;
};

template <typename T, T Head>
struct product<T, Head>
{
  const static T value = Head;
};

template <template <typename> class Trait, 
	  typename... Args> struct all;

template <template <typename> class Trait, 
	  typename Head, 
	  typename... Tail>
struct all<Trait, Head, Tail...> : private all<Trait, Tail...>
{
  typedef all<Trait, Tail...> base_t;

  const static bool value = Trait<Head>::value && base_t::value;
};

template <template <typename> class Trait,
	  typename Head>
struct all<Trait, Head>
{
  const static bool value = Trait<Head>::value;
};



template <typename T, unsigned... Dims>
struct array_impl
{
  const static unsigned linear_size = product<unsigned, Dims...>::value;
  const static unsigned dimensionality = sizeof...(Dims);
  T data[linear_size];

  array_impl() { std::cout << "create array with " << linear_size << " entries.\n"; }

  template <typename... Args>
  T& operator()(Args... values) 
  { 
    static_assert(sizeof...(Args) == dimensionality, 
		  "Number of arguments does not match matrix dimensionality");
    static_assert(all<boost::is_integral, Args...>::value, "Not all args are integral");
    //    unsigned args[dimensionality] = {values...};
  }

};

/*
template <typename T, unsigned... Dims>
array<T, Dims...> 
operator*(const array<T, Dims...>& lhs, T rhs)
{
  return array<T, Dims...>();
}
*/

struct Array 
  : bp::when<bp::terminal<array_impl<bp::_, bp::N, bp::N> >, 
	     bp::_value> 
{ };

struct Float : bp::when<bp::terminal<float>, bp::_value> { };

struct _linearsize : bp::transform<_linearsize>
{
  template <typename Expr, typename State, typename Data>
  struct impl : bp::transform_impl<Expr, State, Data>
  {
    typedef unsigned result_type;
    
    result_type operator()(typename impl::expr_param expr,
			   typename impl::state_param state,
			   typename impl::data_param data) const
    {
      return impl::expr::linear_size;
    }
  };
};

namespace boost {
  namespace proto {
    template <>
    struct is_callable<_linearsize> : boost::mpl::true_ { };
  }
}

/*
struct Multiply : bp::callable
{
  typedef array_impl result_type;
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

struct Grammar
  : bp::or_<Array,
	    Float,
	    bp::when<bp::multiplies<Array, Float>
		     Multiply(Array(bp::_left), Float(bp::_right))>
	    >
{ };

*/

template <typename T, unsigned... Dims>
struct array : bp::terminal<array_impl<T, Dims...> >::type
{ 
  template <typename Expr>
  array& operator=(const Expr& expr)
  {
    BOOST_MPL_ASSERT((bp::matches<Expr, Array>));
    std::cout << name_of<Expr>() << "\n";
  }
};

std::string kernel = "\
__global__ void add_to (float* data, float scalar)\
{\
  data[INDEX] += scalar;\
}\
";

int main() 
{
  array<float, 3,4> a;
  //  array<float, 4,3> b;

  //  std::cout << "matches:"
  //	    << bp::matches<bp::terminal<array_impl<float, 3, 7> >::type, Array>::type << "\n";

  //  a * 7.0f;

  //  a(2,3);

  CUmodule module;
  CUresult res = cuModuleLoadDataEx(&module,  // CuModule*
				    (void*)kernel.c_str(), // const void*
				    0, // unsigned numoptions
				    0, // CUjit_option* options
				    0); // void** optionValues

  std::cout << "res is " << res << "\n";
  std::cout << ">>>" << bp::when<Array, _linearsize(bp::_value)>()(a) << "\n";
  std::cout << ">>> " << array_impl<float, 3, 4>::linear_size << "\n";
  a = a;

  //  std::cout << name_of<array<float, 3,4,5>>() << "\n";

  // std::vector<unsigned> v = {1,2,3};

  return 0;
}

