#include <resophonic/kamasu/linspace.hpp>
#include <resophonic/kamasu/array.hpp>
#include <resophonic/pfeilhecht.h>
#include <cudpp.h>

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

    /*
    template <typename T, typename RVal>
    array<T, boost::mpl::true_> 
    sum(array<T, RVal>& a)
    {
      array<T, boost::mpl::true_> tmp(a);
      
      // again only works on 

      CUDPPConfiguration config;
      config.op = CUDPP_ADD;
      config.datatype = CUDPP_FLOAT;
      config.algorithm = CUDPP_SCAN;
      config.options = CUDPP_OPTION_FORWARD;
      
      CUDPPHandle scanplan = 0;
      CUDPPResult result = cudppPlan(&scanplan, config, a.linear_size(), 1, 0); 

      cudppScan(scanplan, tmp.data(), a.data(), a.linear_size());
      return tmp;
    };

    template array<float, boost::mpl::true_> sum(array<float, boost::mpl::true_>&);
    template array<float, boost::mpl::true_> sum(array<float, boost::mpl::false_>&);
    */
  }
}

