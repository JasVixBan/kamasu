#define N BOOST_PP_ITERATION()

#define DEREF(Z,N_,DATA) DATA[N_]

#define FNTAG BOOST_PP_CAT(RESOPHONIC_OP,BOOST_PP_CAT(_,N))

//
//
//  ops
//
//

__global__ void
BOOST_PP_CAT(kamasu_elementwise_array_knl_,FNTAG)(float* data,
						  unsigned linear_size,
						  BOOST_PP_ENUM_PARAMS(N, const std::size_t factor),
						  BOOST_PP_ENUM_PARAMS(N, const int stride))
{
  if (INDEX >= linear_size)
    return;

#define CALC_INDEX(Z, N_, DATA) + unsigned(INDEX/factor ## N_)*stride ## N_

  unsigned actual_index = 0 BOOST_PP_REPEAT(N, CALC_INDEX, ~);
#undef CALC_INDEX

  data[actual_index] = RESOPHONIC_OP(data[actual_index]);
}

void 
BOOST_PP_CAT(kamasu_elementwise_array_, FNTAG)(float* data, 
					       std::size_t linear_size,
					       const std::size_t* factors, 
					       const int* strides)
{
  bd_t bd = gridsize(linear_size);

  BOOST_PP_CAT(kamasu_elementwise_array_knl_, FNTAG)<<<bd.first, bd.second>>>
    (data,
     linear_size,
     BOOST_PP_ENUM(N, DEREF, factors),
     BOOST_PP_ENUM(N, DEREF, strides));
}

