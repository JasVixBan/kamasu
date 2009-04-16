include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/komrade)

macro(generate X WHERETO)
  add_custom_command(OUTPUT ${CMAKE_SOURCE_DIR}/${WHERETO}/${X}
    DEPENDS ../templates/${X} ../templates/${X}.py
    COMMAND 
    ${CMAKE_SOURCE_DIR}/templates/gen.py 
    ${CMAKE_SOURCE_DIR}/templates/${X}.py 
    ${CMAKE_SOURCE_DIR}/templates/${X}
    ${CMAKE_SOURCE_DIR}/${WHERETO}/${X}
    COMMENT "Generating ${WHERETO}/${X}"
    )
endmacro(generate X)

set(GENERATED_SRC
  elementwise_array_array.cu
  unary_array_op.cu

  UnaryFunctionDispatch.cpp
  ArrayScalarOp.cpp
)

set(GENERATED_PRIVATE_HEADERS 
  unary_array_op.h
  )

set(GENERATED_PUBLIC_HEADERS 
  UnaryFunctions.hpp
  UnaryFunctionTags.hpp
  UnaryFunctionCalls.hpp
  UnaryFunctionExpressions.hpp
  )

foreach(X ${GENERATED_SRC} ${GENERATED_PRIVATE_HEADERS})
  generate(${X} src/generated)
  set(GENERATED_SRC_LIST ${GENERATED_SRC_LIST} generated/${X}) 
endforeach()


foreach(X ${GENERATED_PUBLIC_HEADERS})
  generate(${X} include/resophonic/kamasu/generated)
  list(APPEND GENERATED_HEADERS_LIST 
    ${CMAKE_SOURCE_DIR}/include/resophonic/kamasu/generated/${X})
endforeach()

add_custom_target(generated_public_headers
  DEPENDS ${GENERATED_HEADERS_LIST}
  )

add_library(resophonic_kamasu SHARED

  assign.cu
  linspace.cu

  elementwise_array_scalar.cu

  sort.cpp
  sort.cu

  init.cpp
  array.cpp
  array_impl.cpp
 
  linspace.cpp

  holder.cpp
  rval.cpp
  make_vector.cpp

  transforms.cpp

  logging.cpp
  testing.cpp


  ${GENERATED_SRC_LIST}
  )

target_link_libraries(resophonic_kamasu
  ${CUDA_CUBLAS_LIBRARY}
  )
  
add_dependencies(resophonic_kamasu generated_public_headers)