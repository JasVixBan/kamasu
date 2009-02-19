
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
cuda_include_directories(${CMAKE_CURRENT_SOURCE_DIR})

cuda_add_library(resophonic_barracuda SHARED

  # gpuvector.cu
  kernel.cu
  unary_array_op.cu

  # sadd.cu
  # smul.cu
  # sdiv.cu
  # ssub.cu

  holder.cpp
  rval.cpp
  make_vector.cpp

  array.cpp
  array_impl.cpp

  transforms.cpp

  logging.cpp

  #  vector_splay.cu
  #  vector_vector_mul.cu
  #  vector_vector_div.cu
  #  vector_vector_add.cu
  #  vector_vector_sub.cu
  )

target_link_libraries(resophonic_barracuda
  ${CUBLAS_TARGET_LINK})
  
