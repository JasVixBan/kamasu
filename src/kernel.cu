#define BOOST_NO_EXCEPTIONS

#include <resophonic/kamasu/config.hpp>
#include "kernel.h"
#include "cutil.h"
#include "cuda_runtime.h"

#include <cublas.h>

#include "generated/elementwise_array_scalar.cu"
#include "generated/elementwise_array_array.cu"
