set(CMAKE_SHARED_LIBRARY_CUDA_FLAGS "-Xcompiler ${CMAKE_SHARED_LIBRARY_CXX_FLAGS}")

set(CMAKE_CUDA_COMPILE_OBJECT 
  "<CMAKE_CUDA_COMPILER> <DEFINES> -c <SOURCE> -o <OBJECT> -Xcompiler <FLAGS>"
  )

set(CMAKE_CUDA_FLAGS_DEBUG "-G -g" CACHE STRING "Generate debuggable device and host code")
set(CMAKE_CUDA_FLAGS_RELEASE "-O" CACHE STRING "Opt flags for nvcc")

find_library(CUDA_RT_LIBRARY
  cudart
  PATHS ${CUDA_DIRECTORY}/lib
  DOC "\"cudart\" library"
  )
  
find_library(CUDA_CUBLAS_LIBRARY
  cublas
  PATHS ${CUDA_DIRECTORY}/lib
  DOC "\"cublas\" library"
  )

find_library(CUDA_CUFFT_LIBRARY
  cufft
  PATHS ${CUDA_DIRECTORY}/lib $ENV{CUDA_LIB_PATH}
  DOC "\"cufft\" library"
  )

find_library(CUDA_DRIVER_LIBRARY
  cuda
  DOC "cuda driver library"
  )


message("
   CMAKE_CUDA_COMPILER    = ${CMAKE_CUDA_COMPILER}

   CUDA_INCLUDE_DIRECTORY = ${CUDA_INCLUDE_DIRECTORY}

   CUDA_RT_LIBRARY        = ${CUDA_RT_LIBRARY}
   CUDA_CUBLAS_LIBRARY    = ${CUDA_CUBLAS_LIBRARY}
   CUDA_CUFFT_LIBRARY     = ${CUDA_CUFFT_LIBRARY}

   CUDA_DRIVER_LIBRARY    = ${CUDA_DRIVER_LIBRARY}
")
