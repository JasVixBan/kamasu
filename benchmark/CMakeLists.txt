include_directories(.)
include_directories(..)

add_custom_target(benchmarks)

macro(add_bmark_impl NAME)
  add_executable(${NAME} ${NAME}.cpp main.cpp)
  set_target_properties(${NAME}
    PROPERTIES
    COMPILE_FLAGS "-DNAME=${NAME}"
    )
  target_link_libraries(${NAME}
    resophonic_kamasu ${CUDART_LIBRARY}
    ${BOOST_LIBRARIES}
    ${CUDA_CUTIL_LIB}
    )

endmacro(add_bmark_impl NAME TYPE)

macro(add_bmark NAME)
  add_bmark_impl(${NAME})
  add_dependencies(benchmarks ${NAME})
endmacro(add_bmark NAME)

add_bmark(scalarmult)
# add_bmark(deepexpr)
# add_bmark(deepexpr_streamed)
add_bmark(sine)
add_bmark(matrix_multiply)

add_executable(create create.cpp)
target_link_libraries(create 
  resophonic_kamasu
  ${CUDART_LIBRARY}
  ${BOOST_LIBRARIES}
  ${CUDA_CUTIL_LIB}
  )



# add_bmark(matrix_multiply_2)
# add_bmark(synthesis)



