

  template <typename T, typename RVal>					
  void									
  operator()(tag::/*OP*/, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      /*'\n'.join(['''case %u: kamasu_unary_array_%s_%d(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;''' % (n, OP, n) for n in one_to_n])*/
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }

