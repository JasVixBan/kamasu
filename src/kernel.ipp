#define N BOOST_PP_ITERATION()

#define DEREF(Z,N_,DATA) DATA[N_]




__global__ void
BOOST_PP_CAT(kamasu_elementwise_array_scalar_knl_,N)(Op op,
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
BOOST_PP_CAT(kamasu_elementwise_array_scalar_,N)(Op op,
				    float* data, 
				    std::size_t linear_size,
				    const std::size_t* factors, 
				    const int* strides, 
				    float scalar)
{
  bd_t bd = gridsize(linear_size);

  printf ("GONNA LAUNCH>>> %s\n", __PRETTY_FUNCTION__);

  BOOST_PP_CAT(kamasu_elementwise_array_scalar_knl_,N)<<<bd.first, bd.second>>>
    (op,
     data,
     linear_size,
     BOOST_PP_ENUM(N, DEREF, factors),
     BOOST_PP_ENUM(N, DEREF, strides),
     scalar);
}



__global__ void
BOOST_PP_CAT(kamasu_elementwise_array_array_knl_,N)(Op op,
						    std::size_t linear_size,
						    float* data_l,
						    float* data_r,
						    BOOST_PP_ENUM_PARAMS(N, const std::size_t factor_l),
						    BOOST_PP_ENUM_PARAMS(N, const std::size_t factor_r),
						    BOOST_PP_ENUM_PARAMS(N, const int stride_l),
						    BOOST_PP_ENUM_PARAMS(N, const int stride_r))
{
  unsigned index_l = INDEX, index_r = INDEX;
  unsigned actual_index_l = 0, actual_index_r = 0;

  if (INDEX >= linear_size)
    return;

  std::size_t factors_l[N], factors_r[N];
  int strides_l[N], strides_r[N];
#define SET(Z,N_,DATA)			     \
  factors_l[N_] = BOOST_PP_CAT(factor_l,N_); \
  factors_r[N_] = BOOST_PP_CAT(factor_r,N_); \
  strides_l[N_] = BOOST_PP_CAT(stride_l,N_); \
  strides_r[N_] = BOOST_PP_CAT(stride_r,N_);

    BOOST_PP_REPEAT(N, SET, ~);

#undef SET


  for (int i = N-1; i>=0; i--)
    {
      unsigned this_component_l = index_l / factors_l[i];
      unsigned this_component_r = index_r / factors_r[i];
      actual_index_l += this_component_l * strides_l[i];
      actual_index_r += this_component_r * strides_r[i];
      index_l -= this_component_l * factors_l[i];
      index_r -= this_component_r * factors_r[i];
    }

  if (op == MULTIPLIES)
    data_l[actual_index_l] *= data_r[actual_index_r];
  else if (op == DIVIDES)
    data_l[actual_index_l] /= data_r[actual_index_r];
  else if (op == PLUS)
    data_l[actual_index_l] += data_r[actual_index_r];
  else if (op == MINUS)
    data_l[actual_index_l] -= data_r[actual_index_r];
}

void 
BOOST_PP_CAT(kamasu_elementwise_array_array_,N)(Op op,
						std::size_t linear_size,
						float* data_l,
						float* data_r,
						const std::size_t* factors_l,
						const std::size_t* factors_r,
						const int* strides_l,
						const int* strides_r)
{
  bd_t bd = gridsize(linear_size);
  //printf("%s with gridsize %u %u\n", __PRETTY_FUNCTION__, bd.first, bd.second);
  //printf("n_dims=%u linear_size=%zu", n_dims, linear_size);
  
  BOOST_PP_CAT(kamasu_elementwise_array_array_knl_,N)<<<bd.first, bd.second>>>
    (op, 
     linear_size,
     data_l,
     data_r,
     BOOST_PP_ENUM(N, DEREF, factors_l),
     BOOST_PP_ENUM(N, DEREF, factors_r),
     BOOST_PP_ENUM(N, DEREF, strides_l),
     BOOST_PP_ENUM(N, DEREF, strides_r)
     );
}
