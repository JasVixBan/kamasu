
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
cuda_include_directories(${CMAKE_CURRENT_SOURCE_DIR})

macro(generate X WHERETO)
  add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${X}
    DEPENDS ../templates/${X} ../templates/${X}.py
    COMMAND 
    ${CMAKE_SOURCE_DIR}/templates/gen.py 
    ${CMAKE_SOURCE_DIR}/templates/${X}.py 
    ${CMAKE_SOURCE_DIR}/templates/${X}
    ${CMAKE_SOURCE_DIR}/${WHERETO}/${X}
    COMMENT "Generating ${X}"
    )
endmacro(generate X)

set(GENERATED_SRC 
  elementwise_array_scalar.cu 
  elementwise_array_array.cu
  unary_array_op.cu
)

foreach(X ${GENERATED_SRC})
  generate(${X} src)
endforeach(X ${GENERATED_SRC})

cuda_add_library(resophonic_barracuda SHARED

  kernel.cu

  linspace.cu
  linspace.cpp

  holder.cpp
  rval.cpp
  make_vector.cpp

  array.cpp
  array_impl.cpp

  transforms.cpp

  logging.cpp
  testing.cpp

  ${GENERATED_SRC}
  )

target_link_libraries(resophonic_barracuda
  ${CUBLAS_TARGET_LINK})
  
