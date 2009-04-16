cmake_minimum_required(VERSION 2.6)

#
#  This should contain common/inc/cutil.h, common/lib/libcutil.a, etc.
#
#set(NVIDIA_CUDA_SDK_DIR 
#  "${CMAKE_CURRENT_SOURCE_DIR}/../NVIDIA_CUDA_SDK"
#  CACHE PATH "where is dir 'NVIDIA_CUDA_SDK'")

#
#  Options here are "Device" or "Emulation"
#
set(CUDA_BUILD_TYPE "Device")

# so's you can find the CUDA language when project() needs it
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
# this will trigger all the cuda detection stuff
project(kamasu C CXX CUDA)

# this must go after project()
set(CMAKE_CXX_FLAGS -std=c++0x) 
set(CMAKE_CUDA_COMPILE_FLAGS "-arch=sm_13")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(BOOST_ROOT 
  "${CMAKE_SOURCE_DIR}/../boost" CACHE PATH "where is boost")

add_definitions(-DBOOST_SP_USE_QUICK_ALLOCATOR)
add_definitions(-DRESOPHONIC_WHITEBOX_TESTING)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DRESOPHONIC_KAMASU_DEBUG)
endif ()

include_directories(include)
include_directories(${BOOST_ROOT}/src)
include_directories(${FOUND_CUDA_NVCC_INCLUDE})

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

#if(NOT EXISTS ${NVIDIA_CUDA_SDK_DIR}/common/inc/cutil.h)
#  message(FATAL_ERROR "cutil.h not found in <NVIDIA_CUDA_SDK_DIR>/common/inc")
#endif(NOT EXISTS ${NVIDIA_CUDA_SDK_DIR}/common/inc/cutil.h)

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

#include_directories(${NVIDIA_CUDA_SDK_DIR}/common/inc)
include_directories(${CUDA_INCLUDE_DIRECTORY})

add_subdirectory(src)
add_subdirectory(python)
add_subdirectory(test)
add_subdirectory(example)
add_subdirectory(benchmark)
add_subdirectory(utils)

add_executable(proto proto.cpp)


