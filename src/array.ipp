#define N BOOST_PP_ITERATION()

#define INDEX_OF_TERM(Z, N, DATA) + (Arg##N * strides.get(N))

template <typename T, typename RVal>				
std::size_t							
array<T, RVal>::index_of(BOOST_PP_ENUM_PARAMS(N, std::size_t Arg)) const 
{								
  const mirror<int>& strides(self().impl_->strides);	
  return 0 BOOST_PP_REPEAT(N, INDEX_OF_TERM, ~);		
}


#undef INDEX_OF_TERM



#define CHECK_DIM(Z, N, DATA) RESOPHONIC_KAMASU_THROW(DATA##N == 0, zero_dim(N));

template <typename T, typename RVal>					
array<T, RVal>::array(BOOST_PP_ENUM_PARAMS(N, std::size_t Arg)) :	
self_(boost::proto::value(*this))					
{									
  BOOST_PP_REPEAT(N, CHECK_DIM, Arg);				
  std::vector<std::size_t> shape = KAMASU_MAKE_VECTOR(N, Arg);	
  self().reshape(shape);						
}						

#undef CHECK_DIM

#if N > 1
template <typename T, typename RVal>
array<T, boost::mpl::true_>
array<T, RVal>::slice(BOOST_PP_ENUM_PARAMS(N, const index_range& Arg)) const
{
  return slice(KAMASU_MAKE_VECTOR(N, Arg));
}
#endif

#ifdef RESOPHONIC_KAMASU_DEBUG
#define DIM_CHECK(Z, N, DATA) RESOPHONIC_KAMASU_THROW(DATA##N >= self().impl_->dims.get(N), \
						      bad_index());
#else
#define DIM_CHECK(Z, N, DATA) ;
#endif

#define STRIDE_TERM(Z, N, DATA)	+ DATA ## N * self().impl_->strides.get(N)

template <typename T, typename RVal>				
T									
array<T, RVal>::operator()(BOOST_PP_ENUM_PARAMS(N, std::size_t Arg)) const 
{									
  RESOPHONIC_KAMASU_THROW(N != self().nd, dimensions_dont_match());	
  BOOST_PP_REPEAT(N, DIM_CHECK, Arg);				
  int index = 0 BOOST_PP_REPEAT(N, STRIDE_TERM, Arg);		
  log_trace("getting lvalue from offset %d",  (self().offset + index)); 
  return self().data_->get(index);					
}

template <typename T, typename RVal>				
rval<T>								
array<T, RVal>::operator()(BOOST_PP_ENUM_PARAMS(N, std::size_t Arg)) 
{									
  RESOPHONIC_KAMASU_THROW(N != self().nd, dimensions_dont_match());	
  BOOST_PP_REPEAT(N, DIM_CHECK, Arg);				
  int index = 0 BOOST_PP_REPEAT(N, STRIDE_TERM, Arg);		
  log_trace("getting rvalue offset=%u index=%d",  self().offset % index); 
  return rval<T>(self().data_, index + self().offset);		
}

// #if 0
// template <typename T, typename RVal>				
// array<T, RVal>							
// array<T, RVal>::slice(BOOST_PP_ENUM_PARAMS(N, const std::vector<index_range>& Arg)) const
// {									
//   log_trace("slicing!");						
//   RESOPHONIC_KAMASU_THROW(N != self().nd, dimensions_dont_match());

//   std::vector<std::size_t> newshape;				
//   for (unsigned i=0; i< ranges.size(); i++)
//     {
//       const index_range& ir = ranges[i];
//       if (! ir.is_degenerate())
// 	{								
// 	  int finish, start, diff;

// 	  if (ir.stride() > 0)
// 	    {
// 	      if (ir.start() != ir.from_start())
// 		start = ir.start();
// 	      else
// 		start = 0;

// 	      if (ir.finish() != ir.to_end())
// 		finish = ir.finish();
// 	      else
// 		finish = self().impl_->dims.get(i);
// 	    }
// 	  else
// 	    {
// 	      if (ir.start() != ir.to_end())
// 		start = ir.start();
// 	      else
// 		start = self().impl_->dims.get(i)-1;

// 	      if (ir.finish() != ir.from_start())
// 		finish = ir.finish();
// 	      else
// 		finish = -1;
// 	    }

// 	  diff = finish - start;		
	    
// 	  diff += diff % ir.stride();				
// 	  log_trace("diff %d - %d is %d",  finish % start % diff); 
// 	  unsigned newdim = std::abs(diff/ir.stride());		
// 	  newshape.push_back(newdim);					
// 	  log_trace("newdim is %u",  newdim);
// 	}
//     }
//   log_trace("make new array");
//   array new_array;
//   new_array.self().reshape(newshape, false);
//   log_trace("done make new array");
//   new_array.self().data_ = self().data_;
//   std::vector<std::size_t> starts;
//   for (unsigned i=0; i< ranges.size(); i++)
//     {
//       const index_range& ir = ranges[i];
//       if (!ir.is_degenerate())
// 	{
// 	  if (ir.stride() > 0)
// 	    starts.push_back(ir.start() == ir.from_start() 
// 			     ? 0 : ir.start());
// 	  else 
// 	    starts.push_back(ir.start() == ir.to_end() 
// 			     ? self().impl_->dims.get(i)-1 : ir.start());
// 	}
//       else
// 	{
// 	  starts.push_back(ir.start());
// 	}
//     }
//   new_array.self().offset = index_of(starts);
//   log_trace("offset is %d",  new_array.self().offset);

//   std::vector<int> new_strides;

//   for (unsigned i=0; i<ranges.size(); i++)
//     {
//       if (!ranges[i].is_degenerate())
// 	new_strides.push_back(self().impl_->strides.get(i) * ranges[i].stride());
//     }

//   new_array.self().impl_->strides.set(new_strides);
//   new_array.self().calculate_factors();
//   return new_array;	
// }
// #endif
