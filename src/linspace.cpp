#include <resophonic/kamasu/linspace.hpp>
#include <resophonic/kamasu/array.hpp>
#include "linspace.h"

namespace resophonic {
  namespace kamasu {

    template <typename T>
    array<T, boost::mpl::true_>
    linspace(T start, T stop, std::size_t n_entries)
    {
      array<T, boost::mpl::true_> v(n_entries);
      kamasu_linspace(v.data(), n_entries, 
		      v.stride(0),
		      start,
		      stop);
      return v;
    }

    template array<float, boost::mpl::true_> linspace(float, float, std::size_t);

  }
}

