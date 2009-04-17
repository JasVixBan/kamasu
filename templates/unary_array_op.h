namespace resophonic 
{
  namespace kamasu
  {
    void 
    unary_array_/*OP*/_/*N*/(float* data, 
			     std::size_t linear_size,
			     const std::size_t* factors, 
			     const int* strides,
			     cudaStream_t stream);
  }
}
