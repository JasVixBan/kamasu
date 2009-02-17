#ifndef RESOPHONIC_KAMASU_GRAMMAR_HPP_INCLUDED
#define RESOPHONIC_KAMASU_GRAMMAR_HPP_INCLUDED

#include <resophonic/kamasu/array_impl.hpp>
#include <boost/proto/proto.hpp>

#include <boost/numeric/ublas/matrix.hpp>

namespace resophonic 
{
  namespace kamasu 
  {
    namespace bp = boost::proto;
    namespace rk = resophonic::kamasu;

    namespace tag {
      //      struct dot { };
      struct pow { };
    }
    //    struct DotTag : bp::terminal<tag::dot> { };
    struct PowTag : bp::terminal<tag::pow> { };

    PowTag::type const pow = {{}};

    template <typename T, typename RVal = boost::mpl::false_>
    class array;

    struct ArrayArrayOp : bp::callable
    {
      typedef rk::array_impl<float, boost::mpl::true_> result_type;

      template <typename Op, typename LhsIsRVal, typename RhsIsRVal>
      result_type 
      operator()(Op, 
		 const rk::array_impl<float, LhsIsRVal>&, 
		 const rk::array_impl<float, RhsIsRVal>&);
    };

    struct ArrayScalarOp : bp::callable
    {
      typedef rk::array_impl<float, boost::mpl::true_> result_type;

      template <typename Op, typename IsRVal>
      result_type 
      operator()(Op, const rk::array_impl<float, IsRVal>& v, const float& f);
    };

    struct Scalar
      : bp::or_<bp::when<bp::terminal<float>, bp::_value>, 
		bp::when<bp::terminal<int>, bp::_value>, 
		bp::when<bp::multiplies<Scalar, Scalar>, bp::_default<Scalar> >
		>
    { };

    struct StdVectorTerminal 
      : bp::when<bp::terminal<std::vector<float> >, bp::_value>
    { };

    struct RkArrayTerminal 
      : bp::when<bp::terminal<rk::array_impl<float,bp::_> >, bp::_value>
    { };

    struct BuMatrixTerminal 
      : bp::when<bp::terminal<boost::numeric::ublas::matrix<float,
							    boost::numeric::ublas::column_major> >, 
		 bp::_value>
    { }; 


    struct Array;

    struct Vector;

    struct ArrayScalarOpsCases
    { 
      template <typename Tag, int _=0>
      struct case_ : boost::proto::not_<boost::proto::_> { };

      template <int _> 
      struct case_<bp::tag::multiplies, _>
      : bp::when<bp::multiplies<Array, Scalar>,
		 ArrayScalarOp(bp::tag::multiplies(), 
			       Array(bp::_left), Scalar(bp::_right))>
      { };

      template <int _> 
      struct case_<bp::tag::plus, _>
      : bp::when<bp::plus<Array, Scalar>,
		 ArrayScalarOp(bp::tag::plus(), 
			       Array(bp::_left), Scalar(bp::_right))>
      { };

      template <int _> 
      struct case_<bp::tag::minus, _>
      : bp::when<bp::minus<Array, Scalar>,
		 ArrayScalarOp(bp::tag::minus(), 
			       Array(bp::_left), Scalar(bp::_right))>
      { };

      template <int _> 
      struct case_<bp::tag::divides, _>
      : bp::when<bp::divides<Array, Scalar>,
		 ArrayScalarOp(bp::tag::divides(), 
			       Array(bp::_left), Scalar(bp::_right))>
      { };

      template <int _> 
      struct case_<bp::tag::function, _>
	: bp::when<bp::function<PowTag, Array, Scalar>,
		   ArrayScalarOp(tag::pow(), 
				 Array(bp::_child1), Scalar(bp::_child2))>
      { };

    };
    
    struct ArrayScalarOps : bp::switch_<ArrayScalarOpsCases> { };

    struct ArrayArrayOpsCases 
    {
      template <typename Tag, int _=0>
      struct case_ : boost::proto::not_<boost::proto::_> { };

      template <int _>
      struct case_<bp::tag::plus, _>
	: bp::when<bp::plus<Array, Array>,
		   ArrayArrayOp(bp::tag::plus(), 
				Array(bp::_left), Array(bp::_right))>
      { };

      template <int _>
      struct case_<bp::tag::multiplies, _>
	: bp::when<bp::multiplies<Array, Array>,
		   ArrayArrayOp(bp::tag::multiplies(), 
				Array(bp::_left), Array(bp::_right))>
      { };

      template <int _>
      struct case_<bp::tag::divides, _>
	: bp::when<bp::divides<Array, Array>,
		   ArrayArrayOp(bp::tag::divides(), 
				Array(bp::_left), Array(bp::_right))>
      { };

      template <int _>
      struct case_<bp::tag::minus, _>
	: bp::when<bp::minus<Array, Array>,
		   ArrayArrayOp(bp::tag::minus(), 
				Array(bp::_left), Array(bp::_right))>
      { };
    };
    struct ArrayArrayOps : bp::switch_<ArrayArrayOpsCases> { };

    struct Vector
      : StdVectorTerminal
    { };

    struct Array
      : bp::or_<ArrayScalarOps,
		ArrayArrayOps,
		RkArrayTerminal
		>
    { };

    struct Matrix
      : bp::or_<BuMatrixTerminal>
    { };

    struct Grammar : 
      bp::or_<Scalar, Vector, Matrix, Array> 
    { }; 

    template <typename T> struct Expression;

    struct Domain
      : bp::domain<bp::generator<Expression>, Grammar>
    { };

    template <typename Expr>
    struct Expression : boost::proto::extends<Expr, Expression<Expr>, Domain>
    {
      explicit Expression(Expr const& expr = Expr())
	: boost::proto::extends<Expr, Expression<Expr>, Domain>(expr)
      { }
    };
  }
}
#endif
