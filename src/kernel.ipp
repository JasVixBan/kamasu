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
  if (INDEX >= linear_size)
    return;

#define CALC_INDEX(Z, N_, DATA) + unsigned(INDEX/factor ## N_)*stride ## N_

    unsigned actual_index = 0 BOOST_PP_REPEAT(N, CALC_INDEX, ~);
#undef CALC_INDEX

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
  if (INDEX >= linear_size)
    return;

#define CALC_INDEX(Z, N_, DATA) + unsigned(INDEX/factor ## DATA ## N_)*stride ## DATA ## N_

    unsigned actual_index_l = 0 BOOST_PP_REPEAT(N, CALC_INDEX, _l);
    unsigned actual_index_r = 0 BOOST_PP_REPEAT(N, CALC_INDEX, _r);

#undef CALC_INDEX

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
