#define BOOST_NO_EXCEPTIONS

#include <resophonic/kamasu/config.hpp>
#include "kernel.h"
#include "cutil.h"
#include "cuda_runtime.h"

#include <cublas.h>

#include <boost/preprocessor.hpp>

#define BOOST_PP_ITERATION_LIMITS (1, KAMASU_MAX_ARRAY_DIM-1)
#define BOOST_PP_FILENAME_1 "kernel.ipp"
#include BOOST_PP_ITERATE()

#include "elementwise_array_scalar.cu.generated"
