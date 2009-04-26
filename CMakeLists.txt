cmake_minimum_required(VERSION 2.6)

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

# Boost:  set these if you need 
#
set(BOOST_INCLUDEDIR "/home/troy/Projects/boost/1.39.0/src")
set(BOOST_LIBRARYDIR "/home/troy/Projects/boost/1.39.0/build/lib")
#
find_package(Boost 1.38.0 REQUIRED COMPONENTS python system filesystem program_options)
if (NOT Boost_FOUND)
  message(FATAL_ERROR "Boost not found")
endif(NOT Boost_FOUND)

message(STATUS "Found boost version ${Boost_VERSION}")

add_definitions(-DBOOST_SP_USE_QUICK_ALLOCATOR)
add_definitions(-DRESOPHONIC_WHITEBOX_TESTING)
include_directories(${Boost_INCLUDE_DIR})

find_package(PythonLibs)
if (NOT PYTHONLIBS_FOUND)
  message(FATAL_ERROR "Python libs not found")
endif(NOT PYTHONLIBS_FOUND)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DRESOPHONIC_KAMASU_DEBUG)
endif ()

include_directories(include)
include_directories(${FOUND_CUDA_NVCC_INCLUDE})

set(BOOST_LIBRARIES ${Boost_LIBRARIES})

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

include_directories(${CUDA_INCLUDE_DIRECTORY})

add_subdirectory(src)
add_subdirectory(python)
add_subdirectory(test)
add_subdirectory(example)
add_subdirectory(benchmark)
add_subdirectory(utils)

add_executable(proto proto.cpp)


