
cuda_add_library(resophonic_barracuda SHARED

  # gpuvector.cu
  kernel.cu
  sadd.cu
  smul.cu
  sdiv.cu
  ssub.cu

  holder.cpp
  mirror.cpp
  rval.cpp
  make_vector.cpp

  array.cpp
  array_impl.cpp

  transforms.cpp

  logging.cpp

  vector_splay.cu
  vector_vector_mul.cu
  vector_vector_div.cu
  vector_vector_add.cu
  vector_vector_sub.cu
  )

add_custom_target(gencode
  COMMAND ./gencode.py
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_link_libraries(resophonic_barracuda
  ${CUBLAS_TARGET_LINK})
  
