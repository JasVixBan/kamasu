add_executable(gpumeminfo
  gpumeminfo.c
  )

target_link_libraries(gpumeminfo
  ${CUDA_DRIVER_LIBRARY}
  )
  
add_executable(create create.cpp)

target_link_libraries(create 
  resophonic_kamasu
  ${CUDART_LIBRARY}
  ${BOOST_LIBRARIES}
  ${CUDA_CUTIL_LIB}
  )

