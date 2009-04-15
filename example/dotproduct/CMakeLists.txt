add_executable(dotproduct-kamasu
  kamasu.cpp
  )
target_link_libraries(dotproduct-kamasu
  resophonic_kamasu
  ${CUDA_RT_LIBRARY}
  ${BOOST_LIBRARIES}
  )

add_executable(dotproduct-cpu
  cpu.cpp
  )
target_link_libraries(dotproduct-cpu
  ${BOOST_LIBRARIES}
  )



