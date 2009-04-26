include_directories(${PYTHON_INCLUDE_PATH})

add_library(kamasu SHARED
  module.cpp
  )

target_link_libraries(kamasu
  resophonic_kamasu
  ${Boost_PYTHON}
  ${CUBLAS_TARGET_LINK})
  
set_target_properties(kamasu
  PROPERTIES PREFIX ""
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/resophonic/
  )

configure_file(__init__.py.in ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/resophonic/__init__.py)
configure_file(load_pybindings.py ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/resophonic/load_pybindings.py
  COPYONLY)

execute_process(COMMAND ln -fsn ${CMAKE_CURRENT_SOURCE_DIR}/kamasu ${CMAKE_BINARY_DIR}/lib/resophonic)
