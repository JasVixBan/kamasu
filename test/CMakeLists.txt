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
  resophonic_kamasu ${FOUND_CUDART}
  ${BOOST_LIBRARIES}
  ${CUDA_CUTIL_LIB}
  )

add_executable(small
  small.cpp
  )

# add_executable(benchmark
#   main.cpp
#   benchmarks.cpp
#   testing_util.cpp
#   )
# 
# target_link_libraries(benchmark
#   resophonic_barracuda ${FOUND_CUDART}
#   ${BOOST_LIBRARIES}
#   ${CUDA_CUTIL_LIB}
#   )

