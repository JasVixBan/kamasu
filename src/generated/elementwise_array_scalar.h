//
//
// this is a generated file
//
//


template <>
ArrayScalarOp::result_type
ArrayScalarOp::operator()(boost::proto::tag::plus, 
			  const rk::array_impl<float, boost::mpl::true_>& v, 
			  const float& scalar)
{
  rk::array_impl<float, boost::mpl::true_> rv(v);

  switch (rv.nd) {
    case 1:  kamasu_elementwise_array_scalar_1(op_map<boost::proto::tag::plus>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 2:  kamasu_elementwise_array_scalar_2(op_map<boost::proto::tag::plus>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 3:  kamasu_elementwise_array_scalar_3(op_map<boost::proto::tag::plus>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 4:  kamasu_elementwise_array_scalar_4(op_map<boost::proto::tag::plus>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 5:  kamasu_elementwise_array_scalar_5(op_map<boost::proto::tag::plus>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;

  default:
    throw std::runtime_error("kamasu internal error");
  }

      
  return rv;
}


template <>
ArrayScalarOp::result_type
ArrayScalarOp::operator()(boost::proto::tag::minus, 
			  const rk::array_impl<float, boost::mpl::true_>& v, 
			  const float& scalar)
{
  rk::array_impl<float, boost::mpl::true_> rv(v);

  switch (rv.nd) {
    case 1:  kamasu_elementwise_array_scalar_1(op_map<boost::proto::tag::minus>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 2:  kamasu_elementwise_array_scalar_2(op_map<boost::proto::tag::minus>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 3:  kamasu_elementwise_array_scalar_3(op_map<boost::proto::tag::minus>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 4:  kamasu_elementwise_array_scalar_4(op_map<boost::proto::tag::minus>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 5:  kamasu_elementwise_array_scalar_5(op_map<boost::proto::tag::minus>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;

  default:
    throw std::runtime_error("kamasu internal error");
  }

      
  return rv;
}


template <>
ArrayScalarOp::result_type
ArrayScalarOp::operator()(boost::proto::tag::divides, 
			  const rk::array_impl<float, boost::mpl::true_>& v, 
			  const float& scalar)
{
  rk::array_impl<float, boost::mpl::true_> rv(v);

  switch (rv.nd) {
    case 1:  kamasu_elementwise_array_scalar_1(op_map<boost::proto::tag::divides>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 2:  kamasu_elementwise_array_scalar_2(op_map<boost::proto::tag::divides>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 3:  kamasu_elementwise_array_scalar_3(op_map<boost::proto::tag::divides>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 4:  kamasu_elementwise_array_scalar_4(op_map<boost::proto::tag::divides>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 5:  kamasu_elementwise_array_scalar_5(op_map<boost::proto::tag::divides>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;

  default:
    throw std::runtime_error("kamasu internal error");
  }

      
  return rv;
}


template <>
ArrayScalarOp::result_type
ArrayScalarOp::operator()(boost::proto::tag::multiplies, 
			  const rk::array_impl<float, boost::mpl::true_>& v, 
			  const float& scalar)
{
  rk::array_impl<float, boost::mpl::true_> rv(v);

  switch (rv.nd) {
    case 1:  kamasu_elementwise_array_scalar_1(op_map<boost::proto::tag::multiplies>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 2:  kamasu_elementwise_array_scalar_2(op_map<boost::proto::tag::multiplies>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 3:  kamasu_elementwise_array_scalar_3(op_map<boost::proto::tag::multiplies>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 4:  kamasu_elementwise_array_scalar_4(op_map<boost::proto::tag::multiplies>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 5:  kamasu_elementwise_array_scalar_5(op_map<boost::proto::tag::multiplies>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;

  default:
    throw std::runtime_error("kamasu internal error");
  }

      
  return rv;
}


template <>
ArrayScalarOp::result_type
ArrayScalarOp::operator()(resophonic::kamasu::tag::pow, 
			  const rk::array_impl<float, boost::mpl::true_>& v, 
			  const float& scalar)
{
  rk::array_impl<float, boost::mpl::true_> rv(v);

  switch (rv.nd) {
    case 1:  kamasu_elementwise_array_scalar_1(op_map<resophonic::kamasu::tag::pow>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 2:  kamasu_elementwise_array_scalar_2(op_map<resophonic::kamasu::tag::pow>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 3:  kamasu_elementwise_array_scalar_3(op_map<resophonic::kamasu::tag::pow>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 4:  kamasu_elementwise_array_scalar_4(op_map<resophonic::kamasu::tag::pow>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 5:  kamasu_elementwise_array_scalar_5(op_map<resophonic::kamasu::tag::pow>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;

  default:
    throw std::runtime_error("kamasu internal error");
  }

      
  return rv;
}


template <>
ArrayScalarOp::result_type
ArrayScalarOp::operator()(boost::proto::tag::plus, 
			  const rk::array_impl<float, boost::mpl::false_>& v, 
			  const float& scalar)
{
  rk::array_impl<float, boost::mpl::true_> rv(v);

  switch (rv.nd) {
    case 1:  kamasu_elementwise_array_scalar_1(op_map<boost::proto::tag::plus>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 2:  kamasu_elementwise_array_scalar_2(op_map<boost::proto::tag::plus>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 3:  kamasu_elementwise_array_scalar_3(op_map<boost::proto::tag::plus>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 4:  kamasu_elementwise_array_scalar_4(op_map<boost::proto::tag::plus>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 5:  kamasu_elementwise_array_scalar_5(op_map<boost::proto::tag::plus>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;

  default:
    throw std::runtime_error("kamasu internal error");
  }

      
  return rv;
}


template <>
ArrayScalarOp::result_type
ArrayScalarOp::operator()(boost::proto::tag::minus, 
			  const rk::array_impl<float, boost::mpl::false_>& v, 
			  const float& scalar)
{
  rk::array_impl<float, boost::mpl::true_> rv(v);

  switch (rv.nd) {
    case 1:  kamasu_elementwise_array_scalar_1(op_map<boost::proto::tag::minus>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 2:  kamasu_elementwise_array_scalar_2(op_map<boost::proto::tag::minus>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 3:  kamasu_elementwise_array_scalar_3(op_map<boost::proto::tag::minus>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 4:  kamasu_elementwise_array_scalar_4(op_map<boost::proto::tag::minus>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 5:  kamasu_elementwise_array_scalar_5(op_map<boost::proto::tag::minus>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;

  default:
    throw std::runtime_error("kamasu internal error");
  }

      
  return rv;
}


template <>
ArrayScalarOp::result_type
ArrayScalarOp::operator()(boost::proto::tag::divides, 
			  const rk::array_impl<float, boost::mpl::false_>& v, 
			  const float& scalar)
{
  rk::array_impl<float, boost::mpl::true_> rv(v);

  switch (rv.nd) {
    case 1:  kamasu_elementwise_array_scalar_1(op_map<boost::proto::tag::divides>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 2:  kamasu_elementwise_array_scalar_2(op_map<boost::proto::tag::divides>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 3:  kamasu_elementwise_array_scalar_3(op_map<boost::proto::tag::divides>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 4:  kamasu_elementwise_array_scalar_4(op_map<boost::proto::tag::divides>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 5:  kamasu_elementwise_array_scalar_5(op_map<boost::proto::tag::divides>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;

  default:
    throw std::runtime_error("kamasu internal error");
  }

      
  return rv;
}


template <>
ArrayScalarOp::result_type
ArrayScalarOp::operator()(boost::proto::tag::multiplies, 
			  const rk::array_impl<float, boost::mpl::false_>& v, 
			  const float& scalar)
{
  rk::array_impl<float, boost::mpl::true_> rv(v);

  switch (rv.nd) {
    case 1:  kamasu_elementwise_array_scalar_1(op_map<boost::proto::tag::multiplies>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 2:  kamasu_elementwise_array_scalar_2(op_map<boost::proto::tag::multiplies>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 3:  kamasu_elementwise_array_scalar_3(op_map<boost::proto::tag::multiplies>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 4:  kamasu_elementwise_array_scalar_4(op_map<boost::proto::tag::multiplies>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 5:  kamasu_elementwise_array_scalar_5(op_map<boost::proto::tag::multiplies>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;

  default:
    throw std::runtime_error("kamasu internal error");
  }

      
  return rv;
}


template <>
ArrayScalarOp::result_type
ArrayScalarOp::operator()(resophonic::kamasu::tag::pow, 
			  const rk::array_impl<float, boost::mpl::false_>& v, 
			  const float& scalar)
{
  rk::array_impl<float, boost::mpl::true_> rv(v);

  switch (rv.nd) {
    case 1:  kamasu_elementwise_array_scalar_1(op_map<resophonic::kamasu::tag::pow>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 2:  kamasu_elementwise_array_scalar_2(op_map<resophonic::kamasu::tag::pow>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 3:  kamasu_elementwise_array_scalar_3(op_map<resophonic::kamasu::tag::pow>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 4:  kamasu_elementwise_array_scalar_4(op_map<resophonic::kamasu::tag::pow>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;
case 5:  kamasu_elementwise_array_scalar_5(op_map<resophonic::kamasu::tag::pow>::value, rv.data() + rv.offset, rv.linear_size, rv.factors, rv.strides, scalar); break;

  default:
    throw std::runtime_error("kamasu internal error");
  }

      
  return rv;
}

