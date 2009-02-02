include_directories(.)

add_executable(test
  main.cpp
  one.cpp
  array.cpp
  3d.cpp
  ops.cpp
  testing_util.cpp
  )

set(boost_libraries
  ${BOOST_SYSTEM}
  ${BOOST_PROGRAM_OPTIONS}
  ${BOOST_FILESYSTEM}
  )  

target_link_libraries(test
  resophonic_barracuda ${FOUND_CUDART}
  ${boost_libraries}
  ${CUDA_CUTIL_LIB}
  )

