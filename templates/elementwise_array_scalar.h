#include <resophonic/kamasu/config.hpp>
#include "kernel.h"

void kamasu_elementwise_array_scalar_/*N*/(Op op,
					   /*T*/* data,
					   std::size_t linear_size,
					   const std::size_t* factors,
					   const int* strides,
					   /*T*/ scalar);

