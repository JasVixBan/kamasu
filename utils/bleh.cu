#include <resophonic/kamasu/array_impl.hpp>
#include <resophonic/kamasu/view_params.hpp>

#include "kernel_util.hpp"


namespace resophonic
{

  namespace kamasu
  {
    //
    // array-scalar
    //  
    __global__ void 
    kuhkuhknl(view_params a)
    {
      a.nd = 2;
      /*
      if (INDEX >= linear_size)
	return;

      unsigned thisthread_offset = actual_index<N>(factors, strides);

      data[thisthread_offset] = data[thisthread_offset] * data[thisthread_offset];
      */
    }

    template <typename T>
    void 
    bang(array_impl<T> a)
    {
      bd_t bd = gridsize(a.linear_size());
      
      // argpack<std::size_t, N> factors_(factors);
      //      //      argpack<int, N> strides_(strides);
      //      knl<T, N, Tag><<<bd.first, bd.second>>>(data, linear_size, factors_, strides_, scalar);
      //      blonk b;
      view_params vp;

      kuhkuhknl<<<bd.first, bd.second>>>(vp);
    }

    template void bang(array_impl<float>);

  }
}

