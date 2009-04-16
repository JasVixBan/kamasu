#ifndef KAMASU_BOOST_USERCONFIG_HPP_DEFINED
#define KAMASU_BOOST_USERCONFIG_HPP_DEFINED


#ifdef __CUDACC__
#define BOOST_SHARED_PTR_HPP_INCLUDED

namespace boost {
  template <class T> struct shared_ptr;
}




#endif

#endif

