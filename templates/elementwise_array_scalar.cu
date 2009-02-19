__global__ void
kamasu_elementwise_array_scalar_/*N*/_knl
(Op op,
 float* data,
 unsigned linear_size,
 /*', '.join(['const std::size_t factor%d' % x for x in range(N)])*/,
 /*', '.join(['const int stride%d' % x for x in range(N)])*/,
 float scalar)
{
  if (INDEX >= linear_size)
    return;

  unsigned actual_index = 
    /* ' + '.join(['INDEX/factor%d*stride%d' % (N-1, N-1)]+[' unsigned(INDEX %% factor%d)/factor%d*stride%d' % (n+1,n,n) for n in range(N-1)]) */;

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
kamasu_elementwise_array_scalar_/*N*/(Op op,
				      float* data, 
				      std::size_t linear_size,
				      const std::size_t* factors, 
				      const int* strides,
				      float scalar)
{
  bd_t bd = gridsize(linear_size);

  kamasu_elementwise_array_scalar_/*N*/_knl<<<bd.first, bd.second>>>
    (op, 
     data,
     linear_size,
     /*','.join(['factors[%d]' % x for x in range(N)])*/,
     /*','.join(['strides[%d]' % x for x in range(N)])*/,
     scalar);
}

