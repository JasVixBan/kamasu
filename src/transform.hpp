#include <resophonic/kamasu/config.hpp>
#include <resophonic/kamasu/view_params.hpp>
#include "kernel_util.hpp"

namespace resophonic {
  namespace kamasu {

    // array-scalar
    template <typename T, typename Tag>
    void 
    transform(T* data, const view_params& vp, T scalar);

    // array-array
    template <typename T, typename Tag>
    void 
    transform(T* data_l, const view_params& vpl,
	      T* data_r, const view_params& vpr);

  }
}

