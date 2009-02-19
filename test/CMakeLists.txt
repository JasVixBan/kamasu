include_directories(.)

add_executable(test
  main.cpp
  conversion.cpp
  one.cpp
  mmul.cpp
  array.cpp
  3d.cpp
  ops.cpp
  elementwise.cpp
  testing_util.cpp
  )

target_link_libraries(test
  resophonic_barracuda ${FOUND_CUDART}
  ${BOOST_LIBRARIES}
  ${CUDA_CUTIL_LIB}
  )

add_executable(benchmark
  main.cpp
  benchmarks.cpp
  testing_util.cpp
  )

target_link_libraries(benchmark
  resophonic_barracuda ${FOUND_CUDART}
  ${BOOST_LIBRARIES}
  ${CUDA_CUTIL_LIB}
  )

