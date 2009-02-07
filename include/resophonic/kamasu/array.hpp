#ifndef RESOPHONIC_KAMASU_ARRAY_HPP_INCLUDED
#define RESOPHONIC_KAMASU_ARRAY_HPP_INCLUDED

#include <stdio.h>
#include <vector>
#include <resophonic/kamasu/config.hpp>
#include <resophonic/kamasu/logging.hpp>
#include <resophonic/kamasu/rval.hpp>
#include <resophonic/kamasu/grammar.hpp>
#include <resophonic/kamasu/index_range.hpp>
#include <resophonic/kamasu/dumper_context.hpp>
#include <boost/proto/proto.hpp>
#include <boost/multi_array.hpp>
#include <boost/preprocessor.hpp>

namespace resophonic {
  namespace kamasu {
    
    template <typename T,
	      typename RVal>
    class array 
      : public Expression<typename boost::proto::terminal<array_impl<T, RVal> >::type>
    {
      typedef array_impl<T, RVal> impl_t;
      typedef Expression<typename boost::proto::terminal<impl_t>::type> base_t;

    public:
    
      array& operator=(const array& rhs);

      array();
      array(const std::vector<std::size_t>& shape);
      ~array();

#define VARARG_DECL(Z, N, DATA)						\
      array(BOOST_PP_ENUM_PARAMS(N, std::size_t Arg));			\
	    T operator()(BOOST_PP_ENUM_PARAMS(N, std::size_t Arg)) const; \
	    rval<T> operator()(BOOST_PP_ENUM_PARAMS(N, std::size_t Arg)); \
	    array slice(BOOST_PP_ENUM_PARAMS(N, const index_range& Arg)) const; \
	    std::size_t index_of(BOOST_PP_ENUM_PARAMS(N, std::size_t Arg)) const;

      BOOST_PP_REPEAT_FROM_TO(1, KAMASU_MAX_ARRAY_DIM, VARARG_DECL, ~);

      std::size_t index_of(const std::vector<size_t>& indexes) const;
      array slice(const std::vector<index_range>& ranges) const;

#undef VARARG_DECL

      std::size_t n_dims() const { return self().nd; }
      std::size_t n_strides() const { return self().nd; }
      std::size_t n_factors() const { return self().nd; }
      // const typename impl_t::dims_t& dims() const { return self().dims; }
      std::size_t dim(std::size_t index) const { return self().dims->get(index); }
      std::size_t stride(std::size_t index) const { return self().strides->get(index); }
      std::size_t factor(std::size_t index) const { return self().factors->get(index); }
      std::size_t linear_size() const;

      void show() const;

      template <typename Expr>
      array& operator=(Expr const& expr)
      {
	log_trace("expr is %s") % name_of(boost::proto::as_expr<Domain>(expr));
	
	this->assign(expr);
	return *this;
      }

      impl_t& self() { return boost::proto::value(*this); }
      const impl_t& self() const { return boost::proto::value(*this); }

    private:
      
      void take(const std::vector<T>& rhs);
      void take(const array_impl<T, boost::mpl::true_>& rhs);
      void take(const array_impl<T, boost::mpl::false_>& rhs);

      template <typename Expr>
      void assign(Expr const& expr)
      {
	log_trace("START EVAL/TRANSFORM");
	typename boost::result_of<Grammar(Expr const&)>::type thingy 
	  = Grammar()(expr);
	log_trace("END EVAL/TRANSFORM");
	log_trace("thingy is %s") % name_of(thingy);
	this->take(thingy);
      }
    };

  }  
}

#endif
