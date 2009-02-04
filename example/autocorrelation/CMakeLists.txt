add_executable(autocorrelation
  main.cpp
  )

target_link_libraries(autocorrelation
  resophonic_barracuda 
  ${FOUND_CUDART}
  ${BOOST_LIBRARIES}
  ${CUDA_CUTIL_LIB}
  )

