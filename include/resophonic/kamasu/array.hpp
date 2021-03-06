#ifndef RESOPHONIC_KAMASU_ARRAY_HPP_INCLUDED
#define RESOPHONIC_KAMASU_ARRAY_HPP_INCLUDED

#ifndef __CUDACC__

#include <stdio.h>
#include <vector>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/preprocessor.hpp>

#include <resophonic/kamasu.hpp>
#include <resophonic/kamasu/config.hpp>
#include <resophonic/kamasu/exception.hpp>
#include <resophonic/kamasu/logging.hpp>
#include <resophonic/kamasu/rval.hpp>
#include <resophonic/kamasu/index_range.hpp>


#include <resophonic/kamasu/grammar.hpp>
#include <resophonic/kamasu/stream_impl.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <boost/proto/proto.hpp>


namespace resophonic {
  namespace kamasu {
    
    template <typename T>
    class array 
      : public Expression<typename boost::proto::terminal<array_impl<T> >::type>
    {
      typedef array_impl<T> impl_t;
      typedef Expression<typename boost::proto::terminal<impl_t>::type> base_t;

      impl_t& self_;

      data_t data_;
      int state_;

    public:
    
      array& operator=(const array& rhs);

      array();

      array(const std::vector<std::size_t>& shape);
      array(const array<T>& rhs);

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
	    array<T> operator()(BOOST_PP_ENUM_PARAMS(N, const index_range& Arg)) const; \
	    std::size_t index_of(BOOST_PP_ENUM_PARAMS(N, std::size_t Arg)) const;
      
      BOOST_PP_REPEAT_FROM_TO(1, KAMASU_MAX_ARRAY_DIM, VARARG_DECL, ~);

#undef VARARG_DECL

      std::size_t index_of(const std::vector<size_t>& indexes) const;
      array slice(const std::vector<index_range>& ranges) const;

      array clone() const;

      std::size_t nd() const { return self().nd(); }

      dim_t& dim(std::size_t index)
      { 
	return self().dim(index); 
      }

      dim_t dim(std::size_t index) const 
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


      factor_t& factor(std::size_t index)
      { 
	return self().factor(index); 
      }

      factor_t factor(std::size_t index) const 
      { 
	return self().factor(index); 
      }

      std::size_t linear_size() const
      {
	return self().linear_size();
      };
      std::size_t offset() const
      {
	return self().offset();
      };

      void show() const;

      T* data() { return self().data(); }

      template <typename Expr>
      array& operator=(Expr const& expr)
      {
	this->assign(boost::proto::as_expr<Domain>(expr));
	data_.si.value = 0;
	return *this;
      }

      array& operator=(T value)
      {
	ArrayScalarOp()(boost::proto::tag::assign(), self(), value, state_t(), data_);
	return *this;
      }

      array& operator<<(const boost::numeric::ublas::matrix<T, boost::numeric::ublas::column_major>&); 
      array& operator<<(const std::vector<T>&); 
      void operator>>(boost::numeric::ublas::matrix<T, boost::numeric::ublas::column_major>&); 
      void operator>>(std::vector<T>&); 

      template <typename Expr>
      void 
      operator+=(const Expr& expr)
      {
	BOOST_MPL_ASSERT(( boost::proto::matches<Expr, Grammar> ));
	typedef typename boost::result_of<Grammar(Expr const&, const state_t&, data_t&)>::type result_t;
	result_t rhs_evaluated = Grammar()(expr, state_t(), data_);
	ArrayArrayOp()(boost::proto::tag::plus_assign(), self(), rhs_evaluated, state_t(), data_);
      }

      array& on(const stream& s)
      {
	data_.si.value = s.value;
	return *this;
      }

      array& on()
      {
	data_.si.value = 0;
	return *this;
      }

    private:
      
      impl_t& self() { return self_; }
      const impl_t& self() const { return self_; }

      template <typename Expr>
      void assign(Expr const& expr)
      {
	// if this mpl assert trips, there's something wrong with the grammar
	// of your expression.
	BOOST_MPL_ASSERT(( boost::proto::matches<Expr, Grammar> ));

	log_trace("%s fn %s", "not what we want" % __PRETTY_FUNCTION__);

	data_.tmp = &self();

	typename boost::result_of<Grammar(Expr const&, const state_t&, data_t&)>::type thingy 
	  = Grammar()(expr, state_t(), data_);

	cuda_check(cudaThreadSynchronize());

	this->self_.copy_from(thingy);
      }
    };

    template <typename T>
    std::ostream& operator<<(std::ostream&,  const array<T>&);

  }  
}
#endif

#endif
