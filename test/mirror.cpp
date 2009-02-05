#include <I3Test.h>
#include "testing_util.hpp"

#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

// includes, project

#include <resophonic/kamasu.hpp>
#include <resophonic/kamasu/mirror.hpp>

#include <vector>
#include <cassert>

namespace ks = resophonic::kamasu;

using namespace resophonic::kamasu;

TEST_GROUP();

TEST(create_destroy){
  mirror<int> m;
}

TEST(create_destroy2){
  mirror<unsigned> m;
}

TEST(assign){
  mirror<unsigned> m;

  m.resize(3);
  m.set((unsigned)0,10);
  m.set((unsigned)1,11);
  m.set((unsigned)2,12);

  ENSURE_EQUAL(m.get(0), 10);
  ENSURE_EQUAL(m.get(1), 11);
  ENSURE_EQUAL(m.get(2), 12);

  std::vector<unsigned> v;
  v.push_back(20);
  v.push_back(21);
  v.push_back(22);

  m.set(v);
  ENSURE_EQUAL(m.get(0), 20);
  ENSURE_EQUAL(m.get(1), 21);
  ENSURE_EQUAL(m.get(2), 22);

}
