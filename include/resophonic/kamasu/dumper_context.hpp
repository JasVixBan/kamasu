#ifndef DUMPER_CONTEXT_HPP_INCLUDED
#define DUMPER_CONTEXT_HPP_INCLUDED

#include <boost/proto/proto.hpp>
#include <iostream>

// #define SHOW(ARG) std::cout << "\n" << __FILE__ << ":" << __LINE__ << ": " << ARG "" << " "<< __PRETTY_FUNCTION__ << std::endl
#define LOG(ARG) std::cout << "\n" << __FILE__ << ":" << __LINE__ << ": " << ARG "" << " "
#include <resophonic/kamasu/name_of.hpp>
using resophonic::name_of;

namespace proto = boost::proto;

struct dumper_context
{
  unsigned indent;

  dumper_context() { indent = 1; }

  template<
    typename Expr,
    typename Tag = typename Expr::proto_tag,
    typename Args = typename Expr::proto_args,
    long Arity = Expr::proto_arity::value
    > struct eval
  {
    typedef void result_type;
    result_type operator()(Expr& e, dumper_context& ctx)
    {
      std::cout << ">>> " << name_of<Expr>() << "\n";
    }
  };

  template <typename Expr, typename Tag, typename T>
  struct eval<Expr, Tag, boost::proto::term<T>, 0l>
  {
    typedef void result_type;
    result_type operator()(Expr& e, dumper_context& ctx)
    {
      std::cout << std::string(ctx.indent, ' ') << name_of<Tag>() 
		<< " type = " << name_of<T>() << "\n";
    }
  };

  template <typename Expr, typename Tag, typename Args>
  struct eval<Expr, Tag, Args, 1l>
  {
    typedef void result_type;
    result_type operator()(Expr& e, dumper_context& ctx)
    {
      std::cout << std::string(ctx.indent, ' ') << name_of<Tag>() << "\n";
      ctx.indent += 2;
      proto::eval(proto::child(e), ctx);
      ctx.indent -= 2;
    }
  };

  template <typename Expr, typename Tag, typename Args>
  struct eval<Expr, Tag, Args, 2l>
  {
    typedef void result_type;
    result_type operator()(Expr& e, dumper_context& ctx)
    {
      std::cout << std::string(ctx.indent, ' ') << name_of<Tag>() << "\n";
      ctx.indent += 2;
      proto::eval(proto::left(e), ctx);
      proto::eval(proto::right(e), ctx);
      ctx.indent -= 2;
    }
  };
};

template <typename Expr>
void dump(const Expr& expr)
{
  dumper_context d;
  proto::eval(expr, d);
}

#endif
