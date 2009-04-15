add_executable(fir-kamasu
  kamasu.cpp
  )

target_link_libraries(fir-kamasu
  resophonic_kamasu
  ${CUDA_RT_LIBRARY}
  ${CUDA_DRIVER_LIBRARY}
  ${BOOST_LIBRARIES}
  )

add_executable(fir-cpu
  cpu.cpp
  )
target_link_libraries(fir-cpu
  ${BOOST_LIBRARIES}
  )



