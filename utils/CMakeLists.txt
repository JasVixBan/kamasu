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


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_definitions(-DBOOST_USER_CONFIG="boost_userconfig.hpp")
add_executable(bleh bleh.cpp bleh.cu)
target_link_libraries(bleh
  ${CUDA_DRIVER_LIBRARY}
  ${CUDA_RT_LIBRARY}
  )

