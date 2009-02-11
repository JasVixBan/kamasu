
#include <cmath>
#include <boost/math/constants/constants.hpp>

struct hann_window
{
  const unsigned N;

  hann_window(unsigned size) : N(size) { }

  float operator()(unsigned n)
  {
    return 0.5 * (1.0 - std::cos(2 * boost::math::constants::pi<float>() * n / (N-1)));
  }

};

