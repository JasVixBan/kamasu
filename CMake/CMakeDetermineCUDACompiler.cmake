message(STATUS "Detecting CUDA compiler")

set(CUDA_DIRECTORY "/usr/local/cuda")

if(NOT CMAKE_CUDA_COMPILER)
  find_program(CMAKE_CUDA_COMPILER 
    nvcc 
    PATHS "${CUDA_DIRECTORY}/bin" 
    DOC "CUDA compiler" 
    NO_DEFAULT_PATH)
endif(NOT CMAKE_CUDA_COMPILER)

set(CUDA_INCLUDE_DIRECTORY ${CUDA_DIRECTORY}/include)


configure_file(${CMAKE_SOURCE_DIR}/CMake/CMakeCUDACompiler.cmake.in
  ${CMAKE_PLATFORM_ROOT_BIN}/CMakeCUDACompiler.cmake
  @ONLY IMMEDIATE
  )

set(CMAKE_CUDA_COMPILER_ENV_VAR "NVCC")



