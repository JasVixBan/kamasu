add_executable(dotproduct-kamasu
  kamasu.cpp
  )
target_link_libraries(dotproduct-kamasu
  resophonic_barracuda 
  ${FOUND_CUDART}
  ${BOOST_LIBRARIES}
  ${CUDA_CUTIL_LIB}
  )

add_executable(dotproduct-cpu
  cpu.cpp
  )
target_link_libraries(dotproduct-cpu
  ${BOOST_LIBRARIES}
  )



