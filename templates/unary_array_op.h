namespace resophonic 
{
  namespace kamasu
  {
    void 
    unary_array_/*OP*/_/*N*/(float* data, 
			     std::size_t linear_size,
			     const factor_t* factors, 
			     const stride_t* strides,
			     cudaStream_t stream);
  }
}
