#include <I3Test.h>

#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

// includes, project

#include <resophonic/kamasu.hpp>

#include "cuda_runtime_api.h"
#include "cutil.h"

#include <vector>
#include <cassert>

namespace ks = resophonic::kamasu;
namespace bu = boost::numeric::ublas;

using namespace resophonic::kamasu;

TEST_GROUP();
/*
TEST(vecmultandadd)
{
  const std::size_t l = 16 * 1713;
  std::vector<float> ones_(l, 1.0), twos_(l, 2.0), threes_(l, 3.0), 
    fours_(l, 4.0), fives_(l, 5.0), ints_(l);
  ks::vector<float> ones, twos, threes, fours, fives, ints, result;
  for (unsigned i=0; i<l; i++)
    ints_[i] = i;

  ones << ones_;
  twos << twos_;
  threes << threes_;
  fours << fours_;
  fives << fives_;
  ints << ints_;

  result = fours / twos * ints + threes / twos * ints;

  std::vector<float> result_;
  result >> result_;
  assert(result_.size() == l);

  for (unsigned i=0; i<l; i++)
    {
      //       LOG("result_[i] == ") << result_[i];
      assert(result_[i] == 4.0f / 2.0f * i + 3.0f / 2.0f * i);
    }
}

TEST(scalars)
{

  const unsigned l = 32;

  ks::vector<float> gv1, gv2;
  std::vector<float> tmp1(l, 3.5);
  std::vector<float> tmp2;

  gv1 << tmp1;
  assert(gv1.size() == tmp1.size());

  gv2 = ((((gv1 * 3.5f) / 3.5f) + 8.25f) - 8.25f) * 2.0f;
  gv2 >> tmp2;

  LOG("sizes") << "gv1=" << gv1.size() << " gv2=" << gv2.size();
  assert(gv2.size() == gv1.size());


  assert(tmp2.size() == tmp1.size());
  for (int i=0; i < l; i++)
    {
      LOG(">>>") << i << " tmp2=" << tmp2[i] << " tmp1=" << tmp1[i];
      assert(tmp2[i] == tmp1[i] * 2.0f);
    }

}

TEST(scalar0)
{
  const unsigned l = 32;

  ks::vector<float> gv;
  std::vector<float> sv(l), sv2;

  for (int i=0; i<l; i++)
    sv[i] = i;

  gv << sv;

  for (int i=0; i<l; i++)
    {
      LOG("on gpu:") << i << "=" << gv[i];
      assert(gv[i] == float(i));
    }

  gv >> sv2;

  for (int i=0; i<l; i++)
    {
      LOG("back on host:") << sv[i] << "=" << sv2[i];
      assert(sv[i] == sv2[i]);
    }

}

TEST(scalars2)
{
  const unsigned l = 32;

  ks::vector<float> gv1, gv2, gv3;
  std::vector<float> tmp1(l, 3.5);
  std::vector<float> tmp2, tmp3;

  gv1 << tmp1;
  assert(gv1.size() == tmp1.size());

  gv2 = (gv1 * 2.5f) + (gv1 * 2.5f) + (gv1 * 2.5f);
  assert(gv2.size() == gv1.size());

  gv2 >> tmp2;
  assert(tmp2.size() == tmp1.size());

  LOG("sizes") << "gv1=" << gv1.size() << " gv2=" << gv2.size();

  for (int i=0; i < l; i++)
    {
      LOG(">>>") << i << " tmp2=" << tmp2[i] << " tmp1=" << tmp1[i];
      assert(tmp2[i] == (tmp1[i] * 2.5f) * 3.0f);
    }
}

*/
