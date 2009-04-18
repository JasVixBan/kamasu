#if 0
#include <iostream>
#include <stdexcept>
#include <resophonic/kamasu.hpp>
//#include "bleh.h"

/*
  template <typename T, typename Tag>
  T rduce(const resophonic::kamasu::array<float>& a, T start, Tag)
  {
    return start;
  }
*/

#include <boost/shared_ptr.hpp>

template <typename T>
struct blahzzy
{

  T* px;
  void *count; // egh
};

// BOOST_DETAIL_ATOMIC_COUNT_PTHREADS_HPP_INCLUDED
//BOOST_DETAIL_ATOMIC_COUNT_HPP_INCLUDED
//BOOST_SHARED_PTR_HPP_INCLUDED

#ifdef BOOST_DETAIL_ATOMIC_COUNT_GCC_X86_HPP_INCLUDED
#error yup
#endif



int main(int, char**)
{
  resophonic::kamasu::array<float> a(10);

  //  float result = rduce(a, 0.0f, boost::proto::tag::plus());

  //  std::cout << "result=" << result << "\n";
  boost::shared_ptr<int> i;
  blahzzy<int> b;
  std::cout << sizeof(i) << " " << sizeof(b);

  throw std::runtime_error("EEK");
}
#endif
