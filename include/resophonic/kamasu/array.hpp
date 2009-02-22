#ifndef RESOPHONIC_KAMASU_ARRAY_HPP_INCLUDED
#define RESOPHONIC_KAMASU_ARRAY_HPP_INCLUDED

#include <stdio.h>
#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <resophonic/kamasu/config.hpp>
#include <resophonic/kamasu/logging.hpp>
#include <resophonic/kamasu/rval.hpp>
#include <resophonic/kamasu/grammar.hpp>
#include <resophonic/kamasu/index_range.hpp>
#include <resophonic/kamasu/dumper_context.hpp>
#include <boost/proto/proto.hpp>
#include <boost/multi_array.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/preprocessor.hpp>

namespace resophonic {
  namespace kamasu {
    
    template <typename T,
	      typename RVal>
    class array 
      : public Expression<typename boost::proto::terminal<array_impl<T, RVal> >::type>
    {
      typedef array<T, boost::mpl::true_> rval_t;
      typedef array<T, typename boost::mpl::not_<RVal>::type> other_t;

      typedef array_impl<T, RVal> impl_t;
      typedef Expression<typename boost::proto::terminal<impl_t>::type> base_t;

      impl_t& self_;

      friend class array<T, typename boost::mpl::not_<RVal>::type>;

    public:
    
      array& operator=(const array& rhs);
      array& operator=(const other_t& rhs);

      array();

      array(const std::vector<std::size_t>& shape);
      array(const array<T, boost::mpl::true_>& rhs);

      template <typename Expr>
      array(Expr const& expr, typename boost::disable_if<boost::is_pod<Expr> >::type* = 0) 
	: self_(boost::proto::value(*this))
      {
	this->assign(expr);
      }

      ~array();

#define VARARG_DECL(Z, N, DATA)						\
      array(BOOST_PP_ENUM_PARAMS(N, std::size_t Arg));			\
	    T operator()(BOOST_PP_ENUM_PARAMS(N, std::size_t Arg)) const; \
	    rval<T> operator()(BOOST_PP_ENUM_PARAMS(N, std::size_t Arg)); \
	    array<T,boost::mpl::true_> slice(BOOST_PP_ENUM_PARAMS(N, const index_range& Arg)) const; \
	    std::size_t index_of(BOOST_PP_ENUM_PARAMS(N, std::size_t Arg)) const;
      
      BOOST_PP_REPEAT_FROM_TO(1, KAMASU_MAX_ARRAY_DIM, VARARG_DECL, ~);

#undef VARARG_DECL

      std::size_t index_of(const std::vector<size_t>& indexes) const;
      rval_t slice(const std::vector<index_range>& ranges) const;


      rval_t copy() const;

      std::size_t nd() const { return self().nd; }

      std::size_t& dim(std::size_t index) 
      { 
	return self().dim(index); 
      }
      std::size_t dim(std::size_t index) const 
      { 
	return self().dim(index); 
      }

      int& stride(std::size_t index)
      { 
	return self().stride(index); 
      }
      int stride(std::size_t index) const 
      { 
	return self().stride(index); 
      }

      std::size_t& factor(std::size_t index)
      { 
	return self().factor(index); 
      }
      std::size_t factor(std::size_t index) const 
      { 
	return self().factor(index); 
      }

      std::size_t linear_size() const
      {
	return self().linear_size;
      };
      std::size_t offset() const
      {
	return self().offset;
      };

      void show() const;

      T* data() { return self().data(); }

      template <typename Expr>
      array& operator=(Expr const& expr)
      {
	this->assign(expr);
	return *this;
      }

      array& operator<<(const boost::numeric::ublas::matrix<T, boost::numeric::ublas::column_major>&); 
      void operator>>(boost::numeric::ublas::matrix<T, boost::numeric::ublas::column_major>&); 

      template <typename Expr>
      void 
      operator+=(const Expr& expr)
      {
	BOOST_MPL_ASSERT(( boost::proto::matches<Expr, Grammar> ));
	typedef typename boost::result_of<Grammar(Expr const&)>::type result_t;
	result_t rhs_evaluated = Grammar()(expr);
	ArrayArrayOp()(boost::proto::tag::plus_assign(), self(), rhs_evaluated);
      }

    private:
      
      impl_t& self() { return self_; }
      const impl_t& self() const { return self_; }

      void take(const std::vector<T>& rhs);
      void take(const array_impl<T, boost::mpl::true_>& rhs);
      void take(const array_impl<T, boost::mpl::false_>& rhs);

      template <typename Expr>
      void assign(Expr const& expr)
      {
	// if this mpl assert trips, there's something wrong with the grammar
	// of your expression.
	BOOST_MPL_ASSERT(( boost::proto::matches<Expr, Grammar> ));
	typename boost::result_of<Grammar(Expr const&)>::type thingy 
	  = Grammar()(expr);
	this->take(thingy);
      }
    };

  }  
}

#endif
