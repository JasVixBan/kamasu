#define N BOOST_PP_ITERATION()

#define INDEX_OF_TERM(Z, N, DATA) + (Arg##N * stride(N))

template <typename T>				
std::size_t							
array<T>::index_of(BOOST_PP_ENUM_PARAMS(N, std::size_t Arg)) const 
{								
  return 0 BOOST_PP_REPEAT(N, INDEX_OF_TERM, ~);		
}


#undef INDEX_OF_TERM



#define CHECK_DIM(Z, N, DATA) RESOPHONIC_KAMASU_THROW(DATA##N == 0, zero_dim(N));

template <typename T>					
array<T>::array(BOOST_PP_ENUM_PARAMS(N, std::size_t Arg)) :	
self_(boost::proto::value(*this))					
{									
  BOOST_PP_REPEAT(N, CHECK_DIM, Arg);				
  std::vector<std::size_t> shape = KAMASU_MAKE_VECTOR(N, Arg);	
  self().reshape(shape);						
}						

#undef CHECK_DIM

#if N > 1
template <typename T>
array<T>
array<T>::operator()(BOOST_PP_ENUM_PARAMS(N, const index_range& Arg)) const
{
  return slice(KAMASU_MAKE_VECTOR(N, Arg));
}
#endif

#ifdef RESOPHONIC_KAMASU_DEBUG
#define DIM_CHECK(Z, N, DATA) RESOPHONIC_KAMASU_THROW(DATA##N >= dim(N), bad_index());
#else
#define DIM_CHECK(Z, N, DATA) ;
#endif

#define STRIDE_TERM(Z, N, DATA)	+ DATA ## N * stride(N)

template <typename T>				
T									
array<T>::operator()(BOOST_PP_ENUM_PARAMS(N, std::size_t Arg)) const 
{									
  RESOPHONIC_KAMASU_THROW(N != self().nd, dimensions_dont_match());	
  BOOST_PP_REPEAT(N, DIM_CHECK, Arg);				
  int index = 0 BOOST_PP_REPEAT(N, STRIDE_TERM, Arg);		
  log_trace("getting lvalue from offset %d",  (self().offset + index)); 
  return self().data_->get(index);					
}

template <typename T>				
rval<T>								
array<T>::operator()(BOOST_PP_ENUM_PARAMS(N, std::size_t Arg)) 
{									
  RESOPHONIC_KAMASU_THROW(N != self().nd, dimensions_dont_match());	
  BOOST_PP_REPEAT(N, DIM_CHECK, Arg);				
  int index = 0 BOOST_PP_REPEAT(N, STRIDE_TERM, Arg);		
  log_trace("getting rvalue offset=%u index=%d",  self().offset % index); 
  return rval<T>(self().data_, index + self().offset);		
}

