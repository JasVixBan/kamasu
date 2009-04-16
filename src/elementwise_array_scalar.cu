
#include "elementwise_array_scalar.hpp"
#include "kernel_util.hpp"

#include <proto_tags_fwd.hpp>
#include <resophonic/kamasu/tag.hpp>

namespace resophonic {
  namespace kamasu {

    template <typename T>
    __device__ void 
    op_impl(T* t, const T& scalar, ::boost::proto::tag::plus)
    {
      (*t) += scalar;
    }

    template <typename T>
    __device__ void 
    op_impl(T* t, const T& scalar, ::boost::proto::tag::multiplies)
    {
      (*t) *= scalar;
    }

    template <typename T>
    __device__ void 
    op_impl(T* t, const T& scalar, ::boost::proto::tag::divides)
    {
      (*t) /= scalar;
    }

    template <typename T>
    __device__ void 
    op_impl(T* t, const T& scalar, ::boost::proto::tag::minus)
    {
      (*t) -= scalar;
    }

    template <typename T>
    __device__ void 
    op_impl(T* t, const T& scalar, resophonic::kamasu::tag::pow)
    {
      (*t) = pow(*t, scalar);
    }

    template <typename T, int Length>
    struct argpack
    {
      T data[Length];
      argpack(const T* d)
      {
	memcpy(data, d, Length * sizeof(T));
      }
      T& operator[](unsigned index)
      {
	return data[index];
      }
      const T& operator[](unsigned index) const
      {
	return data[index];
      }
      void touchme() { }

    };

    template <int N>
    __device__ unsigned actual_index(const argpack<std::size_t, N> &factors,
				     const argpack<int, N> &strides)
    {
      unsigned x = INDEX/factors[N-1] * strides[N-1];
							//      for (unsigned i=I-1; i<=0; i++)
#pragma unroll 10
      for (int i = N-1; i>0; i--)
	x += unsigned(INDEX % factors[i]) / factors[i-1] * strides[i-1];

      return x;

    }

    template <typename T, int N, typename Tag>
    __global__ void 
    doit(T* data, 
	 std::size_t linear_size, 
	 argpack<std::size_t, N> factors,
	 argpack<int, N> strides,
	 T scalar)
    {
      if (INDEX >= linear_size)
	return;

      unsigned thisthread_offset = actual_index<N>(factors, strides);

      op_impl(data + thisthread_offset, scalar, Tag()); 
    }

    template <typename T, int N, typename Tag>
    void 
    elementwise_array_scalar_op(T* data, 
				std::size_t linear_size, 
				const std::size_t* factors,
				const int* strides,
				T scalar)
    {
      bd_t bd = gridsize(linear_size);
      
      argpack<std::size_t, N> factors_(factors);
      argpack<int, N> strides_(strides);
      
      doit<T, N, Tag><<<bd.first, bd.second>>>(data, linear_size, factors_, strides_, scalar);
    }

    template <typename T, typename Tag>
    struct instantiate {
      instantiate()
      {
	elementwise_array_scalar_op<T, 1, Tag>(0, 0, 0, 0, 0.0f);
	elementwise_array_scalar_op<T, 2, Tag>(0, 0, 0, 0, 0.0f);
	elementwise_array_scalar_op<T, 3, Tag>(0, 0, 0, 0, 0.0f);
	elementwise_array_scalar_op<T, 4, Tag>(0, 0, 0, 0, 0.0f);
	elementwise_array_scalar_op<T, 5, Tag>(0, 0, 0, 0, 0.0f);
      }
    };

    template struct instantiate<float, boost::proto::tag::plus>;
    template struct instantiate<float, boost::proto::tag::minus>;
    template struct instantiate<float, boost::proto::tag::multiplies>;
    template struct instantiate<float, boost::proto::tag::divides>;
    template struct instantiate<float, resophonic::kamasu::tag::pow>;

  }
}

