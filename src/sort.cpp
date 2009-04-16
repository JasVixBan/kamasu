#include <resophonic/kamasu/sort.hpp>
#include <komrade/sort.h>
#include <komrade/sorting/detail/device/cuda/stable_radix_sort.h>

namespace resophonic {
  namespace kamasu {

    template <>
    void sort(array<float>& a)
    {
      //      komrade::stable_sort(a.data(), a.data()+a.linear_size(), 
      //			   komrade::random_access_device_iterator_tag());
      komrade::sorting::detail::device::cuda::stable_radix_sort_key_dev<float>(a.data(), a.linear_size());
    }

  }
}


