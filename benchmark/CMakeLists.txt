include_directories(.)

macro(add_bmark_impl NAME TYPE)
  add_executable(${NAME}-${TYPE} ${NAME}.cpp)
  set_target_properties(${NAME}-${TYPE}
    PROPERTIES
    COMPILE_FLAGS "-DNAME=${NAME} -DTYPE=${TYPE}"
    )
  target_link_libraries(${NAME}-${TYPE}
    resophonic_kamasu ${FOUND_CUDART}
    ${BOOST_LIBRARIES}
    ${CUDA_CUTIL_LIB}
    )
endmacro(add_bmark_impl NAME TYPE)

macro(add_bmark NAME)
  add_bmark_impl(${NAME} kamasu)
  add_bmark_impl(${NAME} cpu)
  add_custom_target(${NAME})
  add_dependencies(${NAME} ${NAME}-kamasu ${NAME}-cpu)
endmacro(add_bmark NAME)

add_bmark(scalarmult)
add_bmark(deepexpr)
add_bmark(deepexpr_streamed)
add_bmark(sine)
add_bmark(matrix_multiply)
add_bmark(matrix_multiply_2)
add_bmark(synthesis)



