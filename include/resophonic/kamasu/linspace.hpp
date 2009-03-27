#ifndef RESOPHONIC_KAMASU_LINSPACE_HPP_INCLUDED
#define RESOPHONIC_KAMASU_LINSPACE_HPP_INCLUDED

#include <resophonic/kamasu/array.hpp>

namespace resophonic {
  namespace kamasu {

    template <typename T>
    array<T, boost::mpl::true_>
    linspace(T start, T stop, std::size_t n_entries);


    template <typename T, typename RVal>
    T
    sum(const array<T, RVal>& a);

  }
}

#endif



