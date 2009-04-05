#ifndef RESOPHONIC_KAMASU_DATA_HPP_INCLUDED
#define RESOPHONIC_KAMASU_DATA_HPP_INCLUDED

#include <resophonic/kamasu/stream_impl.hpp>

namespace resophonic {
  namespace kamasu {

    template <typename T>
    class array_impl;


    struct data_t
    {
      stream_impl si;
      array_impl<float> *tmp;
    };
  }
}


#endif
