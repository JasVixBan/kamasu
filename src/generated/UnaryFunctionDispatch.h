//
//
// this is a generated file
//
//

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::sqrt, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_sqrt_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_sqrt_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_sqrt_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_sqrt_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_sqrt_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::rsqrt, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_rsqrt_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_rsqrt_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_rsqrt_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_rsqrt_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_rsqrt_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::cbrt, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_cbrt_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_cbrt_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_cbrt_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_cbrt_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_cbrt_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::exp, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_exp_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_exp_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_exp_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_exp_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_exp_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::exp2, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_exp2_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_exp2_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_exp2_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_exp2_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_exp2_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::exp10, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_exp10_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_exp10_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_exp10_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_exp10_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_exp10_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::expm1, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_expm1_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_expm1_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_expm1_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_expm1_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_expm1_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::log, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_log_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_log_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_log_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_log_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_log_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::log2, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_log2_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_log2_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_log2_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_log2_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_log2_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::log10, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_log10_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_log10_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_log10_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_log10_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_log10_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::log1p, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_log1p_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_log1p_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_log1p_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_log1p_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_log1p_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::sin, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_sin_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_sin_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_sin_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_sin_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_sin_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::cos, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_cos_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_cos_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_cos_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_cos_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_cos_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::tan, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_tan_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_tan_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_tan_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_tan_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_tan_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::asin, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_asin_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_asin_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_asin_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_asin_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_asin_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::acos, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_acos_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_acos_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_acos_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_acos_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_acos_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::atan, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_atan_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_atan_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_atan_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_atan_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_atan_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::sinh, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_sinh_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_sinh_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_sinh_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_sinh_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_sinh_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::cosh, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_cosh_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_cosh_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_cosh_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_cosh_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_cosh_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::tanh, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_tanh_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_tanh_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_tanh_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_tanh_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_tanh_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::asinh, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_asinh_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_asinh_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_asinh_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_asinh_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_asinh_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::acosh, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_acosh_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_acosh_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_acosh_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_acosh_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_acosh_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::atanh, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_atanh_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_atanh_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_atanh_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_atanh_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_atanh_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::erf, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_erf_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_erf_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_erf_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_erf_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_erf_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::erfc, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_erfc_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_erfc_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_erfc_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_erfc_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_erfc_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::lgamma, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_lgamma_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_lgamma_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_lgamma_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_lgamma_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_lgamma_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::tgamma, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_tgamma_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_tgamma_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_tgamma_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_tgamma_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_tgamma_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::logb, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_logb_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_logb_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_logb_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_logb_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_logb_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::ilogb, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_ilogb_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_ilogb_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_ilogb_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_ilogb_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_ilogb_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::trunc, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_trunc_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_trunc_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_trunc_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_trunc_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_trunc_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::round, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_round_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_round_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_round_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_round_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_round_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::rint, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_rint_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_rint_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_rint_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_rint_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_rint_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::nearbyint, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_nearbyint_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_nearbyint_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_nearbyint_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_nearbyint_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_nearbyint_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::ceil, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_ceil_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_ceil_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_ceil_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_ceil_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_ceil_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::floor, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_floor_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_floor_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_floor_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_floor_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_floor_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::lrint, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_lrint_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_lrint_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_lrint_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_lrint_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_lrint_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::lround, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_lround_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_lround_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_lround_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_lround_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_lround_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::llrint, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_llrint_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_llrint_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_llrint_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_llrint_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_llrint_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::llround, 
				  const rk::array_impl<float, boost::mpl::true_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_llround_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_llround_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_llround_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_llround_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_llround_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::sqrt, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_sqrt_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_sqrt_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_sqrt_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_sqrt_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_sqrt_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::rsqrt, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_rsqrt_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_rsqrt_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_rsqrt_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_rsqrt_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_rsqrt_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::cbrt, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_cbrt_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_cbrt_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_cbrt_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_cbrt_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_cbrt_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::exp, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_exp_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_exp_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_exp_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_exp_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_exp_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::exp2, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_exp2_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_exp2_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_exp2_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_exp2_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_exp2_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::exp10, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_exp10_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_exp10_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_exp10_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_exp10_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_exp10_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::expm1, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_expm1_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_expm1_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_expm1_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_expm1_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_expm1_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::log, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_log_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_log_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_log_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_log_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_log_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::log2, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_log2_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_log2_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_log2_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_log2_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_log2_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::log10, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_log10_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_log10_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_log10_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_log10_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_log10_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::log1p, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_log1p_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_log1p_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_log1p_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_log1p_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_log1p_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::sin, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_sin_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_sin_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_sin_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_sin_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_sin_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::cos, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_cos_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_cos_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_cos_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_cos_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_cos_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::tan, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_tan_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_tan_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_tan_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_tan_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_tan_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::asin, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_asin_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_asin_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_asin_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_asin_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_asin_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::acos, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_acos_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_acos_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_acos_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_acos_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_acos_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::atan, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_atan_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_atan_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_atan_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_atan_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_atan_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::sinh, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_sinh_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_sinh_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_sinh_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_sinh_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_sinh_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::cosh, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_cosh_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_cosh_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_cosh_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_cosh_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_cosh_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::tanh, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_tanh_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_tanh_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_tanh_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_tanh_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_tanh_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::asinh, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_asinh_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_asinh_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_asinh_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_asinh_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_asinh_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::acosh, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_acosh_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_acosh_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_acosh_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_acosh_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_acosh_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::atanh, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_atanh_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_atanh_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_atanh_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_atanh_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_atanh_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::erf, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_erf_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_erf_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_erf_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_erf_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_erf_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::erfc, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_erfc_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_erfc_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_erfc_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_erfc_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_erfc_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::lgamma, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_lgamma_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_lgamma_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_lgamma_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_lgamma_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_lgamma_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::tgamma, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_tgamma_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_tgamma_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_tgamma_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_tgamma_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_tgamma_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::logb, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_logb_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_logb_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_logb_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_logb_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_logb_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::ilogb, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_ilogb_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_ilogb_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_ilogb_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_ilogb_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_ilogb_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::trunc, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_trunc_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_trunc_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_trunc_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_trunc_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_trunc_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::round, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_round_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_round_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_round_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_round_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_round_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::rint, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_rint_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_rint_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_rint_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_rint_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_rint_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::nearbyint, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_nearbyint_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_nearbyint_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_nearbyint_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_nearbyint_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_nearbyint_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::ceil, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_ceil_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_ceil_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_ceil_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_ceil_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_ceil_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::floor, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_floor_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_floor_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_floor_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_floor_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_floor_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::lrint, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_lrint_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_lrint_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_lrint_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_lrint_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_lrint_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::lround, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_lround_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_lround_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_lround_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_lround_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_lround_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::llrint, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_llrint_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_llrint_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_llrint_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_llrint_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_llrint_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

template <>
ArrayScalarOp::result_type
UnaryFunctionDispatch::operator()(resophonic::kamasu::tag::llround, 
				  const rk::array_impl<float, boost::mpl::false_>& v) 
{
  rk::array_impl<float, boost::mpl::true_> rv(v);
  
  log_trace("dispatch: %s", __PRETTY_FUNCTION__); 

  switch (rv.nd) {					     
    case 1: kamasu_unary_array_llround_1(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 2: kamasu_unary_array_llround_2(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 3: kamasu_unary_array_llround_3(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 4: kamasu_unary_array_llround_4(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
case 5: kamasu_unary_array_llround_5(rv.data() + rv.offset, 
	rv.linear_size, rv.factors, rv.strides); break;
      
    default:							
      throw std::runtime_error("kamasu internal error");		
    }								

  return rv;
}

