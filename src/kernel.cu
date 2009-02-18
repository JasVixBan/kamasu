#define BOOST_NO_EXCEPTIONS

#include <resophonic/kamasu/config.hpp>
#include "kernel.h"
#include "cutil.h"
#include <stdio.h>
#include <cublas.h>

#include <boost/preprocessor.hpp>

#define BOOST_PP_ITERATION_LIMITS (1, KAMASU_MAX_ARRAY_DIM-1)
#define BOOST_PP_FILENAME_1 "kernel.ipp"
#include BOOST_PP_ITERATE()

#undef RESOPHONIC_OP
#define RESOPHONIC_OP exp
#define BOOST_PP_ITERATION_LIMITS (1, KAMASU_MAX_ARRAY_DIM-1)
#define BOOST_PP_FILENAME_1 "elementwise_array_op.ipp"
#include BOOST_PP_ITERATE()

#undef RESOPHONIC_OP
#define RESOPHONIC_OP exp2
#define BOOST_PP_ITERATION_LIMITS (1, KAMASU_MAX_ARRAY_DIM-1)
#define BOOST_PP_FILENAME_1 "elementwise_array_op.ipp"
#include BOOST_PP_ITERATE()

#undef RESOPHONIC_OP
#define RESOPHONIC_OP log10
#define BOOST_PP_ITERATION_LIMITS (1, KAMASU_MAX_ARRAY_DIM-1)
#define BOOST_PP_FILENAME_1 "elementwise_array_op.ipp"
#include BOOST_PP_ITERATE()

