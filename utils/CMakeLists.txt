add_executable(gpumeminfo
  gpumeminfo.c)

target_link_libraries(gpumeminfo
  ${CUDART_LIBRARY}
  )
  