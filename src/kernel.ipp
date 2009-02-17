#define N BOOST_PP_ITERATION()




__global__ void
BOOST_PP_CAT(kamasu_elementwise_knl_,N)(Op op,
					float* data,
					unsigned linear_size,
					BOOST_PP_ENUM_PARAMS(N, const std::size_t factor),
					BOOST_PP_ENUM_PARAMS(N, const int stride),
					float scalar)
{
    unsigned index = INDEX;
    unsigned actual_index = 0;

    if (INDEX >= linear_size)
      return;

    std::size_t factors[N];
    int strides[N];
#define SET(Z,N_,DATA) factors[N_] = BOOST_PP_CAT(factor,N_); strides[N_]=BOOST_PP_CAT(stride,N_);
    BOOST_PP_REPEAT(N, SET, ~);
#undef SET

    for (int i = N-1; i>=0; i--)
    {
      unsigned this_component = index / factors[i];
      actual_index += this_component * strides[i];
      index -= this_component * factors[i];
    }

    if (op == MULTIPLIES)
      data[actual_index] *= scalar;
    else if (op == DIVIDES)
      data[actual_index] /= scalar;
    else if (op == PLUS)
      data[actual_index] += scalar;
    else if (op == MINUS)
      data[actual_index] -= scalar;
    else if (op == POW)
      data[actual_index] = pow(data[actual_index], scalar);
}

void 
BOOST_PP_CAT(kamasu_elementwise_,N)(Op op,
				    float* data, 
				    std::size_t linear_size,
				    const std::size_t* factors, 
				    const int* strides, 
				    float scalar)
{
  bd_t bd = gridsize(linear_size);

  printf ("GONNA LAUNCH>>> %s\n", __PRETTY_FUNCTION__);

#define DEREF(Z,N_,DATA) DATA[N_]

  BOOST_PP_CAT(kamasu_elementwise_knl_,N)<<<bd.first, bd.second>>>(op,
								   data,
								   linear_size,
								   BOOST_PP_ENUM(N, DEREF, factors),
								   BOOST_PP_ENUM(N, DEREF, strides),
								   scalar);
}

