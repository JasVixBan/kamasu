add_executable(fir-kamasu
  kamasu.cpp
  )
target_link_libraries(fir-kamasu
  resophonic_kamasu
  ${CUDART_LIBRARY}
  ${BOOST_LIBRARIES}
  ${CUDA_CUTIL_LIB}
  )

add_executable(fir-cpu
  cpu.cpp
  )
target_link_libraries(fir-cpu
  ${BOOST_LIBRARIES}
  )



