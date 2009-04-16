#include <resophonic/kamasu/linspace.hpp>
#include <resophonic/kamasu/array.hpp>
#include <cudpp.h>

template <typename T>
void
kamasu_linspace(T* data, 
		std::size_t linear_size,
		const int stride,
		T start,
		T stop);

namespace resophonic {
  namespace kamasu {

    template <typename T>
    array<T>
    linspace(T start, T stop, std::size_t n_entries)
    {
      array<T> v(n_entries);
      kamasu_linspace(v.data(), n_entries, 
		      v.stride(0),
		      start,
		      stop);
      return std::move(v);
    }

    template array<float> linspace(float, float, std::size_t);

  }
}

