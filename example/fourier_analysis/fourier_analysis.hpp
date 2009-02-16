#include <cmath>
#include <boost/math/constants/constants.hpp>

const float sr = 48000.0;
const unsigned winlen = sr/10;

const unsigned fftsize = 8192;
const unsigned stepsize = 64;
const unsigned nfreqs = div(fftsize, 2).quot + 1;

struct hann_window
{
  const unsigned N;
  std::vector<float> v;

  hann_window(unsigned size) : N(size), v(size) 
  { 
    for (unsigned i=0; i<N; i++)
      v[i] = 0.5 * (1.0 - std::cos(2 * boost::math::constants::pi<float>() * i / (N-1)));
  }

  float operator()(unsigned n)
  {
    return v[n];
  }

};

