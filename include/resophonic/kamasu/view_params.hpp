#ifndef RESOPHONIC_KAMASU_VIEW_PARAMS_HPP_INCLUDED
#define RESOPHONIC_KAMASU_VIEW_PARAMS_HPP_INCLUDED

#include <stdint.h>
#include <resophonic/kamasu/config.hpp>

namespace resophonic 
{
  namespace kamasu 
  {
    typedef std::size_t offset_t;
    typedef uint32_t dim_t;
    typedef uint32_t factor_t;
    typedef int32_t stride_t;

    struct view_params {


      dim_t dims[KAMASU_MAX_ARRAY_DIM];
      factor_t factors[KAMASU_MAX_ARRAY_DIM];
      stride_t strides[KAMASU_MAX_ARRAY_DIM];

      std::size_t linear_size;
      offset_t offset;
      unsigned char nd;
    };
  }
}
#endif
