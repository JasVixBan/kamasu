#ifndef RESOPHONIC_KAMASU_SHARED_PTR_HACK_INCLUDED
#define RESOPHONIC_KAMASU_SHARED_PTR_HACK_INCLUDED

#ifdef __CUDACC__

namespace boost 
{
    template <typename T>
    struct shared_ptr
    {
      T* px;
      void *count; // egh
    };
}

#else

#include <boost/shared_ptr.hpp>

#endif

#endif

