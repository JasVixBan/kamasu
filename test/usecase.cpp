#include <iostream>
#include <resophonic/kamasu.hpp>
#include <resophonic/kamasu/name_of.hpp>

namespace rk = resophonic::kamasu;
using resophonic::name_of;

template <typename Expr>
void doit (const Expr& expr)
{
  std::cout << "itis: " << name_of(expr) << "\n";

  BOOST_MPL_ASSERT(( boost::proto::matches<Expr, rk::Grammar> ));
  typedef typename boost::result_of<rk::Grammar(Expr const&, const rk::state_t&, rk::data_t&)>::type res_t;

}


int main(int, char**)
{
  rk::array<float> a(4,4), b(4,4), c(4,4);

  c = exp(b) + log(a);

  std::cout << "hi\n";

}
