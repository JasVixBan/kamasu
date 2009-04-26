#include <resophonic/kamasu/linspace.hpp>
#include <resophonic/kamasu/array.hpp>


namespace resophonic {
  namespace kamasu {

    template <typename T>
    void
    linspace(T* data, 
	     std::size_t linear_size,
	     const int stride,
	     T start,
	     T stop);

    template <typename T>
    array<T>
    linspace(T start, T stop, std::size_t n_entries)
    {
      array<T> v(n_entries);
      linspace(v.data(), n_entries, 
	       v.stride(0),
	       start,
	       stop);
      return std::move(v);
    }

    template array<float> linspace(float, float, std::size_t);

  }
}

