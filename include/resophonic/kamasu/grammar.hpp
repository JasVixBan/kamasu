#ifndef RESOPHONIC_KAMASU_GRAMMAR_HPP_INCLUDED
#define RESOPHONIC_KAMASU_GRAMMAR_HPP_INCLUDED

#include <resophonic/kamasu/array_impl.hpp>
#include <resophonic/kamasu/state.hpp>
#include <resophonic/kamasu/data.hpp>
#include <resophonic/kamasu/tag.hpp>
#include <boost/proto/proto.hpp>

#include <boost/numeric/ublas/matrix.hpp>

#include <resophonic/kamasu/generated/UnaryFunctionTags.hpp>
#include <resophonic/kamasu/stream_impl.hpp>
#include <cuda_runtime.h>

namespace resophonic 
{
  namespace kamasu 
  {
    namespace bp = boost::proto;
    namespace rk = resophonic::kamasu;

    bp::terminal<tag::pow>::type const pow = {{}};

    template <typename T> class array;

    struct ArrayArrayOp : bp::callable
    {
      typedef rk::array_impl<float> result_type;

      template <typename Op>
      result_type 
      operator()(Op, 
		 const rk::array_impl<float>&, 
		 const rk::array_impl<float>&,
		 const state_t&,
		 data_t&);
    };

    struct ArrayScalarOp : bp::callable
    {
      typedef rk::array_impl<float> result_type;

      template <typename Op>
      result_type 
      operator()(Op, 
		 const rk::array_impl<float>& v, const float& f,
		 const state_t&,
		 data_t&);
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

    struct StreamTerminal 
      : bp::when<bp::terminal<rk::stream_impl>, bp::_value>
    { };

    struct CopyLValue : bp::callable
    {
      typedef array_impl<float> result_type;

      result_type
      operator()(const array_impl<float>& a, data_t& data)
      {
	if (data.tmp == &a)
	  {
	    data.tmp = 0;
	    return a;
	  }
	else
	  return a.clone();
      }
    };

    struct RkArrayTerminal 
      : bp::when<bp::terminal<rk::array_impl<float> >, CopyLValue(bp::_value, bp::_data)>
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
			       Array(bp::_left, bp::_state, bp::_data), Scalar(bp::_right),
			       bp::_state, bp::_data)>
      { };

      template <int _> 
      struct case_<bp::tag::plus, _>
      : bp::when<bp::plus<Array, Scalar>,
		 ArrayScalarOp(bp::tag::plus(), 
			       Array(bp::_left, bp::_state, bp::_data), Scalar(bp::_right),
			       bp::_state, bp::_data)>
      { };

      template <int _> 
      struct case_<bp::tag::minus, _>
      : bp::when<bp::minus<Array, Scalar>,
		 ArrayScalarOp(bp::tag::minus(), 
			       Array(bp::_left, bp::_state, bp::_data), Scalar(bp::_right),
			       bp::_state, bp::_data)>
      { };

      template <int _> 
      struct case_<bp::tag::divides, _>
      : bp::when<bp::divides<Array, Scalar>,
		 ArrayScalarOp(bp::tag::divides(), 
			       Array(bp::_left, bp::_state, bp::_data), Scalar(bp::_right),
			       bp::_state, bp::_data)>
      { };

      template <int _> 
      struct case_<bp::tag::plus_assign, _>
	: bp::when<bp::plus_assign<Array, Scalar>,
		   ArrayScalarOp(bp::tag::plus_assign(), Array(bp::_child0), 
				 Scalar(bp::_child1), bp::_data)>
      { };
      
      template <int _> 
      struct case_<bp::tag::function, _>
	: bp::when<bp::function<bp::terminal<tag::pow>, Array, Scalar>,
		   ArrayScalarOp(tag::pow(), Array(bp::_child1, bp::_state, bp::_data), 
				 Scalar(bp::_child2),
				 bp::_state, bp::_data)>
      { };
      
    };
  }
}

#include <resophonic/kamasu/generated/UnaryFunctionCalls.hpp>

namespace resophonic {
  namespace kamasu {

    struct ArrayScalarOps : bp::switch_<ArrayScalarOpsCases> { };

    struct ArrayArrayOpsCases 
    {
      template <typename Tag, int _=0>
      struct case_ : boost::proto::not_<boost::proto::_> { };

      template <int _>
      struct case_<bp::tag::plus, _>
	: bp::when<bp::plus<Array, Array>,
		   ArrayArrayOp(bp::tag::plus(), 
				Array(bp::_left, bp::_state, bp::_data), Array(bp::_right, bp::_state, bp::_data),
				bp::_state, bp::_data)>
      { };

      template <int _>
      struct case_<bp::tag::plus_assign, _>
	: bp::when<bp::plus<Array, Array>,
		   ArrayArrayOp(bp::tag::plus_assign(), 
				Array(bp::_left, bp::_state, bp::_data), Array(bp::_right, bp::_state, bp::_data),
				bp::_state, bp::_data)>
      { };

      template <int _>
      struct case_<bp::tag::multiplies, _>
	: bp::when<bp::multiplies<Array, Array>,
		   ArrayArrayOp(bp::tag::multiplies(), 
				Array(bp::_left, bp::_state, bp::_data), Array(bp::_right, bp::_state, bp::_data),
				bp::_state, bp::_data)>
      { };

      template <int _>
      struct case_<bp::tag::divides, _>
	: bp::when<bp::divides<Array, Array>,
		   ArrayArrayOp(bp::tag::divides(), 
				Array(bp::_left, bp::_state, bp::_data), Array(bp::_right, bp::_state, bp::_data),
				bp::_state, bp::_data)>
      { };

      template <int _>
      struct case_<bp::tag::minus, _>
	: bp::when<bp::minus<Array, Array>,
		   ArrayArrayOp(bp::tag::minus(), 
				Array(bp::_left, bp::_state, bp::_data), Array(bp::_right, bp::_state, bp::_data),
				bp::_state, bp::_data)>
      { };
    };
    struct ArrayArrayOps : bp::switch_<ArrayArrayOpsCases> { };

    struct Vector
      : StdVectorTerminal
    { };

    struct Array
      : bp::or_<ArrayScalarOps,
		ArrayArrayOps,
		RkArrayTerminal,
		UnaryFunctionCalls
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
      : bp::domain<bp::pod_generator<Expression>, Grammar>
    { };

    template <typename Expr>
    struct Expression 
    {
      BOOST_PROTO_EXTENDS(Expr, Expression<Expr>, Domain);
    };
    
  }
}

#include <resophonic/kamasu/generated/UnaryFunctions.hpp>

#endif
