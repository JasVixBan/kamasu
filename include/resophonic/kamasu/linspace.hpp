#ifndef RESOPHONIC_KAMASU_LINSPACE_HPP_INCLUDED
#define RESOPHONIC_KAMASU_LINSPACE_HPP_INCLUDED

#include <resophonic/kamasu/array.hpp>

namespace resophonic {
  namespace kamasu {

    // forwards to pfeilhecht
    template <typename T>
    array<T>
    linspace(T start, T stop, std::size_t n_entries);

  }
}

#endif



