include_directories(.)

add_executable(test
  elementwise.cpp
  ops.cpp
  main.cpp
  conversion.cpp
  one.cpp
  mmul.cpp
  whitebox.cpp
  array.cpp
  3d.cpp
  testing_util.cpp
  )

target_link_libraries(test
  resophonic_kamasu 
  ${CUDA_RT_LIBRARY}
  ${BOOST_LIBRARIES}
  ${CUDA_CUTIL_LIB}
  )

#add_executable(small
#  small.cpp
#  )
#target_link_libraries(small resophonic_kamasu ${CUDART_LIBRARY})

add_executable(usecase
  usecase.cpp
  )
target_link_libraries(usecase 
  resophonic_kamasu
  ${CUDA_RT_LIBRARY}
  ${CUDA_DRIVER_LIBRARY}
  )

add_executable(blah
  blah.cpp
  )

add_executable(fleh
  fleh.cpp
  )

