add_executable(matrixmul-kamasu
  kamasu.cpp
  )
target_link_libraries(matrixmul-kamasu
  resophonic_kamasu
  ${CUDART_LIBRARY}
  ${BOOST_LIBRARIES}
  ${CUDA_CUTIL_LIB}
  )

add_executable(matrixmul-cpu
  cpu.cpp
  )
target_link_libraries(matrixmul-cpu
  ${BOOST_LIBRARIES}
  )



