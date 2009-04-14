include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(fft-kamasu
  kamasu.cpp
  )


target_link_libraries(fft-kamasu
  resophonic_kamasu 
  ${CUDART_LIBRARY}
  ${BOOST_LIBRARIES}
  ${CUDA_CUTIL_LIB}
  ${CUDA_CUFFT_LIBRARY}
  )

find_library(FFTW3_LIBRARY
  fftw3 
  )
find_library(FFTW3F_LIBRARY
  fftw3f 
  )
find_library(MATH_LIBRARY
  m 
  )

add_executable(fft-cpu
  cpu.cpp
  )
target_link_libraries(fft-cpu
  ${BOOST_LIBRARIES}
  ${FFTW3_LIBRARY}
  ${FFTW3F_LIBRARY}
  ${MATH_LIBRARY}
  )
