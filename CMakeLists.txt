cmake_minimum_required(VERSION 2.6)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(BOOST_ROOT 
  "${CMAKE_SOURCE_DIR}/../boost" CACHE PATH "where is boost")

add_definitions(-DBOOST_SP_USE_QUICK_ALLOCATOR)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DRESOPHONIC_KAMASU_DEBUG)
  add_definitions(-DRESOPHONIC_WHITEBOX_TESTING)
endif ()



#
#  This should contain common/inc/cutil.h, common/lib/libcutil.a, etc.
#
set(NVIDIA_CUDA_SDK_DIR 
  "${CMAKE_CURRENT_SOURCE_DIR}/../NVIDIA_CUDA_SDK"
  CACHE PATH "where is dir 'NVIDIA_CUDA_SDK'")

#
#  Options here are "Device" or "Emulation"
#
set(CUDA_BUILD_TYPE "Device")



include(${CMAKE_SOURCE_DIR}/CMake/cuda/FindCuda.cmake)
include_directories(include)
include_directories(${BOOST_ROOT}/src)
include_directories(${FOUND_CUDA_NVCC_INCLUDE})

cuda_include_directories(${BOOST_ROOT}/src)
cuda_include_directories(${CMAKE_SOURCE_DIR}/include)

set(RESOPHONIC_PFEILHECHT_DIR "${CMAKE_SOURCE_DIR}/../backend-build" CACHE FILEPATH "pfeilhecht yo")

find_library(RESOPHONIC_PFEILHECHT_LIB
  resophonic_pfeilhecht
  PATHS ${RESOPHONIC_PFEILHECHT_DIR}/lib
  NO_DEFAULT_PATH
  )

include_directories(${RESOPHONIC_PFEILHECHT_DIR}/include)

#
#  Used by test driver
#
find_library(BOOST_SYSTEM 
  boost_system-mt-d
  PATHS ${BOOST_ROOT}/lib
  NO_DEFAULT_PATH
  )

find_library(BOOST_PYTHON 
  boost_python-mt-d
  PATHS ${BOOST_ROOT}/lib
  NO_DEFAULT_PATH
  )

find_library(BOOST_PROGRAM_OPTIONS
  boost_program_options-mt-d
  PATHS ${BOOST_ROOT}/lib
  NO_DEFAULT_PATH
  )

find_library(BOOST_FILESYSTEM
  boost_filesystem-mt-d
  PATHS ${BOOST_ROOT}/lib
  NO_DEFAULT_PATH
  )

set(BOOST_LIBRARIES
  ${BOOST_SYSTEM}
  ${BOOST_PROGRAM_OPTIONS}
  ${BOOST_FILESYSTEM}
  )  

if(NOT EXISTS ${NVIDIA_CUDA_SDK_DIR}/common/inc/cutil.h)
  message(FATAL_ERROR "cutil.h not found in <NVIDIA_CUDA_SDK_DIR>/common/inc")
endif(NOT EXISTS ${NVIDIA_CUDA_SDK_DIR}/common/inc/cutil.h)

find_library(CUDA_CUTIL_LIB
  cutil
  PATHS ${NVIDIA_CUDA_SDK_DIR}/lib
  NO_DEFAULT_PATH
  )

find_library(CUFFT_LIBRARY
  cufft
  PATHS /usr/local/cuda/lib
  NO_DEFAULT_PATH
  )

find_library(CUDPP_LIBRARY
  cudpp64
  PATHS ${CMAKE_SOURCE_DIR}/../cudpp_1.0a/lib
  NO_DEFAULT_PATH
  )

find_file(CUDPP_INCLUDE_FILE
  cudpp.h
  PATHS ${CMAKE_SOURCE_DIR}/../cudpp_1.0a/cudpp/include
  NO_DEFAULT_PATH
  )

get_filename_component(CUDPP_INCLUDE_DIR
  ${CUDPP_INCLUDE_FILE}
  PATH
  )

include_directories(${CUDPP_INCLUDE_DIR})

# contains cutil.h
include_directories(${NVIDIA_CUDA_SDK_DIR}/common/inc)
cuda_include_directories(${NVIDIA_CUDA_SDK_DIR}/common/inc
  /home/troy/Projects/boost/trunk
  )

add_subdirectory(src)
add_subdirectory(python)
add_subdirectory(test)
add_subdirectory(example)
add_subdirectory(benchmark)

add_executable(proto proto.cpp)


