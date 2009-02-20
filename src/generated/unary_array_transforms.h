//
//
// this is a generated file
//
//



  template <typename T, typename RVal>					
  void									
  operator()(tag::sqrt, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_sqrt_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_sqrt_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_sqrt_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_sqrt_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_sqrt_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::rsqrt, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_rsqrt_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_rsqrt_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_rsqrt_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_rsqrt_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_rsqrt_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::cbrt, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_cbrt_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_cbrt_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_cbrt_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_cbrt_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_cbrt_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::exp, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_exp_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_exp_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_exp_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_exp_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_exp_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::exp2, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_exp2_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_exp2_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_exp2_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_exp2_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_exp2_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::exp10, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_exp10_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_exp10_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_exp10_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_exp10_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_exp10_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::expm1, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_expm1_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_expm1_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_expm1_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_expm1_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_expm1_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::log, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_log_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_log_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_log_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_log_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_log_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::log2, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_log2_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_log2_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_log2_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_log2_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_log2_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::log10, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_log10_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_log10_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_log10_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_log10_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_log10_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::log1p, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_log1p_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_log1p_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_log1p_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_log1p_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_log1p_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::sin, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_sin_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_sin_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_sin_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_sin_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_sin_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::cos, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_cos_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_cos_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_cos_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_cos_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_cos_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::tan, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_tan_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_tan_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_tan_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_tan_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_tan_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::asin, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_asin_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_asin_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_asin_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_asin_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_asin_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::acos, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_acos_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_acos_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_acos_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_acos_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_acos_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::atan, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_atan_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_atan_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_atan_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_atan_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_atan_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::sinh, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_sinh_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_sinh_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_sinh_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_sinh_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_sinh_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::cosh, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_cosh_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_cosh_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_cosh_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_cosh_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_cosh_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::tanh, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_tanh_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_tanh_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_tanh_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_tanh_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_tanh_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::asinh, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_asinh_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_asinh_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_asinh_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_asinh_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_asinh_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::acosh, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_acosh_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_acosh_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_acosh_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_acosh_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_acosh_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::atanh, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_atanh_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_atanh_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_atanh_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_atanh_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_atanh_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::erf, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_erf_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_erf_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_erf_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_erf_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_erf_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::erfc, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_erfc_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_erfc_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_erfc_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_erfc_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_erfc_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::lgamma, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_lgamma_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_lgamma_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_lgamma_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_lgamma_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_lgamma_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::tgamma, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_tgamma_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_tgamma_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_tgamma_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_tgamma_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_tgamma_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::logb, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_logb_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_logb_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_logb_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_logb_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_logb_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::ilogb, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_ilogb_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_ilogb_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_ilogb_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_ilogb_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_ilogb_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::trunc, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_trunc_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_trunc_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_trunc_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_trunc_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_trunc_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::round, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_round_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_round_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_round_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_round_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_round_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::rint, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_rint_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_rint_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_rint_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_rint_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_rint_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::nearbyint, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_nearbyint_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_nearbyint_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_nearbyint_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_nearbyint_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_nearbyint_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::ceil, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_ceil_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_ceil_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_ceil_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_ceil_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_ceil_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::floor, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_floor_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_floor_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_floor_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_floor_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_floor_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::lrint, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_lrint_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_lrint_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_lrint_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_lrint_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_lrint_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::lround, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_lround_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_lround_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_lround_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_lround_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_lround_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::llrint, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_llrint_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_llrint_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_llrint_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_llrint_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_llrint_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }




  template <typename T, typename RVal>					
  void									
  operator()(tag::llround, const rk::array_impl<T, RVal>& a)		
  {									
    log_trace("%s", __PRETTY_FUNCTION__);				
    switch (a.nd) {					     
      std::cout<< "a.nd==" << a.nd << "\n";			
									
      case 1: kamasu_unary_array_llround_1(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 2: kamasu_unary_array_llround_2(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 3: kamasu_unary_array_llround_3(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 4: kamasu_unary_array_llround_4(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
case 5: kamasu_unary_array_llround_5(a.data() + a.offset, 
	a.linear_size, a.factors, a.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								
  }

