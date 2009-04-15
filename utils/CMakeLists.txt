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
  )

add_executable(sgemm sgemm.c)
target_link_libraries(sgemm ${CUDA_CUBLAS_LIBRARY})