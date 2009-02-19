
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
cuda_include_directories(${CMAKE_CURRENT_SOURCE_DIR})

cuda_add_library(resophonic_barracuda SHARED

  kernel.cu

  linspace.cu
  linspace.cpp

  unary_array_op.cu

  holder.cpp
  rval.cpp
  make_vector.cpp

  array.cpp
  array_impl.cpp

  transforms.cpp

  logging.cpp
  testing.cpp
  )


target_link_libraries(resophonic_barracuda
  ${CUBLAS_TARGET_LINK})
  
