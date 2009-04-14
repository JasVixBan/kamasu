###############################################################################
#  For more information, please see: http://software.sci.utah.edu
#
#  The MIT License
#
#  Copyright (c) 2007-2008
#  Scientific Computing and Imaging Institute, University of Utah
#
#  License for the specific language governing rights and limitations under
#  Permission is hereby granted, free of charge, to any person obtaining a
#  copy of this software and associated documentation files (the "Software"),
#  to deal in the Software without restriction, including without limitation
#  the rights to use, copy, modify, merge, publish, distribute, sublicense,
#  and/or sell copies of the Software, and to permit persons to whom the
#  Software is furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included
#  in all copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
#  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#  DEALINGS IN THE SOFTWARE.
#
# This script locates the Nvidia Compute Unified Driver Architecture (CUDA) 
# tools. It should work on linux, windows, and mac and should be reasonably 
# up to date with cuda releases.
#
# The script will prompt the user to specify CUDA_INSTALL_PREFIX if the 
# prefix cannot be determined by the location of nvcc in the system path. To
# use a different installed version of the toolkit set the environment variable
# CUDA_BIN_PATH before running cmake (e.g. CUDA_BIN_PATH=/usr/local/cuda1.0 
# instead of the default /usr/local/cuda).
#
# Set CUDA_BUILD_TYPE to "Device" or "Emulation" mode.
# _DEVICEEMU is defined in "Emulation" mode.
#
# Set CUDA_BUILD_CUBIN to "ON" or "OFF" to enable and extra compilation pass
# with the -cubin option in Device mode. The output is parsed and register, 
# shared memory usage is printed during build. Default ON.
# 
# The script creates the following macros:
# CUDA_INCLUDE_DIRECTORIES( path0 path1 ... )
# -- Sets the directories that should be passed to nvcc 
#    (e.g. nvcc -Ipath0 -Ipath1 ... ). These paths usually contain other .cu 
#    files.
# 
# CUDA_ADD_LIBRARY( cuda_target file0 file1 ... )
# -- Creates a shared library "cuda_target" which contains all of the source 
#    (*.c, *.cc, etc.) specified and all of the nvcc'ed .cu files specified.
#    All of the specified source files and generated .cpp files are compiled 
#    using the standard CMake compiler, so the normal INCLUDE_DIRECTORIES, 
#    LINK_DIRECTORIES, and TARGET_LINK_LIBRARIES can be used to affect their
#    build and link.
#
# CUDA_ADD_EXECUTABLE( cuda_target file0 file1 ... )
# -- Same as CUDA_ADD_LIBRARY except that an exectuable is created.
#
# CUDA_COMPILE( cuda_files file0 file1 ... )
# -- Returns a list of build commands in the first argument to be used with 
#    ADD_LIBRARY or ADD_EXECUTABLE.
# 
# The script defines the following variables:
#
# ( Note CUDA_ADD_* macros setup cuda/cut library dependencies automatically. 
# These variables are only needed if a cuda API call must be made from code in 
# a outside library or executable. )
#
# CUDA_INCLUDE         -- Include directory for cuda headers.
# CUDA_TARGET_LINK     -- Cuda RT library. 
# CUDA_CUT_INCLUDE     -- Include directory for cuda SDK headers (cutil.h).   
# CUDA_CUT_TARGET_LINK -- SDK libraries.
# CUDA_NVCC_FLAGS      -- Additional NVCC command line arguments. NOTE: 
#                         multiple arguments must be semi-colon delimited 
#                         e.g. --compiler-options;-Wall
# CUBLAS_TARGET_LINK-- cublas library name.
# CUFFT_TARGET_LINK -- cubfft library name.
# 
# The nvcc flag "--host-compilation;c++" should be used if functions declared
# as __host__ contain C++ code.
#
# It might be necessary to set CUDA_INSTALL_PATH manually on certain platforms,
# or to use a cuda runtime not installed in the default location. In newer 
# versions of the toolkit the cuda library is included with the graphics 
# driver- be sure that the driver version matches what is needed by the cuda 
# runtime version.
# 
# -- Abe Stephens SCI Institute -- http://www.sci.utah.edu/~abe/FindCuda.html
###############################################################################

# FindCuda.cmake
CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

INCLUDE(${CMAKE_SOURCE_DIR}/CMake/cuda/CudaDependency.cmake)

###############################################################################
###############################################################################
# Locate CUDA, Set Build Type, etc.
###############################################################################
###############################################################################

# Parse CUDA build type.
if (NOT CUDA_BUILD_TYPE)
  set(CUDA_BUILD_TYPE "Device" CACHE STRING "Cuda build type: Emulation or Device")
  message(STATUS "CUDA_BUILD_TYPE = Device (default.  Other option: Emulation)")
else()
  message(STATUS "CUDA_BUILD_TYPE = ${CUDA_BUILD_TYPE}")
endif()

# Emulation if the card isn't present.
IF (CUDA_BUILD_TYPE MATCHES "Emulation")
  SET(nvcc_flags --device-emulation -D_DEVICEEMU -g)
ELSE(CUDA_BUILD_TYPE MATCHES "Emulation")
  # Device present.
  SET(nvcc_flags "")
ENDIF(CUDA_BUILD_TYPE MATCHES "Emulation")

# Search for the cuda distribution.
IF(NOT CUDA_DIRECTORY)
  message(STATUS "Set CUDA_DIRECTORY in environment if the default isn't right.")
  set(CUDA_DIRECTORY "/usr/local/cuda" CACHE FILEPATH "Cuda directory, containing include/ bind/nvcc, etc.")
endif()

message(STATUS "CUDA_DIRECTORY = ${CUDA_DIRECTORY}")

find_path(CMAKE_CUDA_COMPILER
  nvcc
  PATHS ${CUDA_DIRECTORY}
  PATH_SUFFIXES bin
  ENV CUDA_BIN_PATH
  DOC "The nvcc compiler"
  )

message(STATUS "CMAKE_CUDA_COMPILER = ${CMAKE_CUDA_COMPILER}")

FIND_PATH(FOUND_CUDA_NVCC_INCLUDE
  device_functions.h # Header included in toolkit
  PATHS ${CUDA_DIRECTORY}/include 
  )

IF(NOT FOUND_CUDA_NVCC_INCLUDE)
  MESSAGE(FATAL_ERROR "Could not find Cuda headers")
ELSE(NOT FOUND_CUDA_NVCC_INCLUDE)
  # Set the initial include dir.
  SET (CUDA_NVCC_INCLUDE_ARGS "-I"${FOUND_CUDA_NVCC_INCLUDE})
  SET (CUDA_INCLUDE ${FOUND_CUDA_NVCC_INCLUDE})

  MARK_AS_ADVANCED(
    FOUND_CUDA_NVCC_INCLUDE
    CUDA_NVCC_INCLUDE_ARGS
    )
ENDIF(NOT FOUND_CUDA_NVCC_INCLUDE)

# ENDIF(NOT FOUND_CUDA_NVCC_INCLUDE)


# CUDA_TARGET_LINK
IF (NOT CUDA_TARGET_LINK)

  FIND_LIBRARY(CUDART_LIBRARY
    cudart
    PATHS ${CUDA_DIRECTORY}/lib $ENV{CUDA_LIB_PATH}
    DOC "\"cudart\" library"
    )
  
  # Check to see if cudart library was found.
  IF(NOT CUDART_LIBRARY)
    MESSAGE(FATAL_ERROR "Could not find cudart library (cudart)")
  ENDIF(NOT CUDART_LIBRARY)  

  # 1.1 toolkit on linux doesn't appear to have a separate library on 
  # some platforms.
  FIND_LIBRARY(FOUND_CUDA
    cuda
    PATHS ${CUDA_DIRECTORY}/lib
    DOC "\"cuda\" library (older versions only)."
    NO_DEFAULT_PATH
    NO_CMAKE_ENVIRONMENT_PATH
    NO_CMAKE_PATH
    NO_SYSTEM_ENVIRONMENT_PATH
    NO_CMAKE_SYSTEM_PATH
    )

  # Add cuda library to the link line only if it is found.
  IF (FOUND_CUDA)
    SET(CUDA_TARGET_LINK ${FOUND_CUDA})
  ENDIF(FOUND_CUDA)

  # Always add cudart to the link line.
  IF(CUDART_LIBRARY)
    SET(CUDA_TARGET_LINK
      ${CUDA_TARGET_LINK} ${CUDART_LIBRARY}
      )
    MARK_AS_ADVANCED(
      CUDA_TARGET_LINK 
      CUDA_LIB
      FOUND_CUDA
      CUDART_LIBRARY
      )
  ELSE(CUDART_LIBRARY)
    MESSAGE(FATAL_ERROR "Could not find cuda libraries.")
  ENDIF(CUDART_LIBRARY)
  
ENDIF(NOT CUDA_TARGET_LINK)

# CUDA_CUT_INCLUDE
IF(NOT CUDA_CUT_INCLUDE)
  FIND_PATH(FOUND_CUT_INCLUDE
    cutil.h
    PATHS ${CUDA_DIRECTORY}/local/NVSDK0.2/common/inc
    ${CUDA_DIRECTORY}/NVSDK0.2/common/inc
    ${CUDA_DIRECTORY}/NV_CUDA_SDK/common/inc
    $ENV{HOME}/NVIDIA_CUDA_SDK/common/inc
    $ENV{HOME}/NVIDIA_CUDA_SDK_MACOSX/common/inc
    $ENV{NVSDKCUDA_ROOT}/common/inc
    DOC "Location of cutil.h"
    )
  IF(FOUND_CUT_INCLUDE)
    SET(CUDA_CUT_INCLUDE ${FOUND_CUT_INCLUDE})
    MARK_AS_ADVANCED(
      FOUND_CUT_INCLUDE
      )
  ENDIF(FOUND_CUT_INCLUDE)
ENDIF(NOT CUDA_CUT_INCLUDE)


# CUDA_CUT_TARGET_LINK
IF(NOT CUDA_CUT_TARGET_LINK)
  FIND_LIBRARY(FOUND_CUT
    cutil
    cutil32
    PATHS ${CUDA_DIRECTORY}/local/NVSDK0.2/lib
    ${CUDA_DIRECTORY}/NVSDK0.2/lib
    ${CUDA_DIRECTORY}/NV_CUDA_SDK/lib
    $ENV{HOME}/NVIDIA_CUDA_SDK/lib
    $ENV{HOME}/NVIDIA_CUDA_SDK_MACOSX/lib
    $ENV{NVSDKCUDA_ROOT}/common/lib
    NO_DEFAULT_PATH
    NO_CMAKE_ENVIRONMENT_PATH
    NO_CMAKE_PATH
    NO_SYSTEM_ENVIRONMENT_PATH
    NO_CMAKE_SYSTEM_PATH
    DOC "Location of cutil library"
    )
  IF(FOUND_CUT)
    SET(CUDA_CUT_TARGET_LINK ${FOUND_CUT})
    MARK_AS_ADVANCED(
      FOUND_CUT
      )
  ENDIF(FOUND_CUT)

  # Add variables for cufft and cublas target link
  FIND_LIBRARY(FOUND_CUFFTEMU
    cufftemu
    PATHS ${CUDA_DIRECTORY}/lib $ENV{CUDA_LIB_PATH}
    DOC "\"cufftemu\" library"
    )
  FIND_LIBRARY(FOUND_CUBLASEMU
    cublasemu
    PATHS ${CUDA_DIRECTORY}/lib $ENV{CUDA_LIB_PATH}
    DOC "\"cublasemu\" library"
    )
  FIND_LIBRARY(FOUND_CUFFT
    cufft
    PATHS ${CUDA_DIRECTORY}/lib $ENV{CUDA_LIB_PATH}
    DOC "\"cufft\" library"
    )
  FIND_LIBRARY(FOUND_CUBLAS
    cublas
    PATHS ${CUDA_DIRECTORY}/lib $ENV{CUDA_LIB_PATH}
    DOC "\"cublas\" library"
    )

  IF (CUDA_BUILD_TYPE MATCHES "Emulation")
    SET(CUFFT_TARGET_LINK  ${FOUND_CUFFTEMU})
    SET(CUBLAS_TARGET_LINK ${FOUND_CUBLASEMU})
  ELSE(CUDA_BUILD_TYPE MATCHES "Emulation")
    SET(CUFFT_TARGET_LINK  ${FOUND_CUFFT})
    SET(CUBLAS_TARGET_LINK ${FOUND_CUBLAS})
  ENDIF(CUDA_BUILD_TYPE MATCHES "Emulation")




ENDIF(NOT CUDA_CUT_TARGET_LINK)


###############################################################################
# Add include directories to pass to the nvcc command.
MACRO(CUDA_INCLUDE_DIRECTORIES)
  FOREACH(dir ${ARGN})
    SET(CUDA_NVCC_INCLUDE_ARGS ${CUDA_NVCC_INCLUDE_ARGS} -I${dir})
  ENDFOREACH(dir ${ARGN})
ENDMACRO(CUDA_INCLUDE_DIRECTORIES)


##############################################################################
##############################################################################
# This helper macro populates the following variables and setups up custom commands and targets to
# invoke the nvcc compiler. The compiler is invoked once with -M to generate a dependency file and
# a second time with -cuda to generate a .cpp file
# ${target_srcs}
# ${cuda_cu_sources}
##############################################################################
##############################################################################

# commands cuda_target)
# 
# 
# "")
# 
# acro arguments and create custom
# he .cu files.
# )
#  ".*\\.cu$")
# 
# arget to generate a c file.
# le  "${CMAKE_BINARY_DIR}/src/cuda/${file}_${cuda_target}_generated.cpp")
# rget "${file}_target")
# 
# ORY ${CMAKE_BINARY_DIR}/src/cuda)
# 
# ${CMAKE_CURRENT_SOURCE_DIR}/${file})
# 
# A_NVCC} ${source_file} ${CUDA_NVCC_FLAGS} ${nvcc_flags} -cuda -o ${generated_file} ${CUDA_NVCC_INCLUDE_ARGS}")
# 
# ependencies.  Creates a variable CUDA_NVCC_DEPEND
# ency_file "${generated_file}.depend")
# C_DEPENDENCIES(${cmake_dependency_file})
# ed_dependency_file "${generated_file}.NVCC-depend")
# 
# 
#  made dependency file
# YPE MATCHES "Device" AND CUDA_BUILD_CUBIN)
# ated_cubin_file "${generated_file}.NVCC-cubin.txt")
# MAND(
# 
# he .cubin output.
# C_generated_cubin_file}
# DA_NVCC}
# e_file} 
# FLAGS}
# }
# 
# 
# nerated_cubin_file} 
# INCLUDE_ARGS}
# 
# e parser script.
# MAKE_COMMAND}
# 
# e="${NVCC_generated_cubin_file}"
# SOURCE_DIR}/CMake/cuda/parse_cubin.cmake"
# 
# 
# DENCY ${source_file}
# urce_file}
# DA_NVCC_DEPEND}
# 
# 
# 
# lding (${CUDA_BUILD_TYPE}) NVCC -cubin File: ${NVCC_generated_cubin_file}\n"
# 
# _TYPE MATCHES "Device" AND CUDA_BUILD_CUBIN)
# mething that will exist.
# ated_cubin_file "${source_file}")
# D_TYPE MATCHES "Device"AND CUDA_BUILD_CUBIN)
# 
#  made dependency file
# ND(
# generated_dependency_file}
# _NVCC}
# file} 
# AGS}
# 
# 
# 
# rated_dependency_file} 
# CLUDE_ARGS}
# NCY ${source_file}
# ce_file}
# _NVCC_DEPEND}
# ing (${CUDA_BUILD_TYPE}) NVCC Dependency File: ${NVCC_generated_dependency_file}\n"
# 
# 
# e readible dependency file
# ND(
# _dependency_file}
# E_COMMAND}
# 
# "${NVCC_generated_dependency_file}"
# ="${cmake_dependency_file}"
# URCE_DIR}/CMake/cuda/make2cmake.cmake"
# Y ${NVCC_generated_dependency_file}
# rting NVCC dependency to CMake (${cmake_dependency_file})"
# 
# 
# ND(
# ated_file}
# Y ${source_file} 
# _NVCC_DEPEND}
# e_dependency_file}
# _generated_cubin_file}
# _NVCC} 
# file} 
# AGS}
# 
# 
# 
# erated_file} 
# CLUDE_ARGS}
# ing (${CUDA_BUILD_TYPE}) NVCC ${source_file}: ${generated_file}\n"
# 
# 
# ces ${cuda_cu_sources} ${source_file})
# 
# ted file name to the source list.
# ${target_srcs} ${generated_file})
# 
# ES ".*\\.cu$")
# 
# the file name to the source list.
# ${target_srcs} ${file})
# 
# HES ".*\\.cu$")
# 
# 
# om_commands)
# 
# #########################################################
# #########################################################
# 
# #########################################################
# #########################################################
#  cuda_target)
# 
# ands and targets for each file.
# ands( ${cuda_target} ${ARGN} )  
# 
# 
# arget}
# 
# 
# 
# 
# S(${cuda_target}
# }
# 
# 
# ARY cuda_target)
# 
# 
# #########################################################
# #########################################################
# 
# #########################################################
# #########################################################
# BLE cuda_target)
# 
# ands and targets for each file.
# ands( ${cuda_target} ${ARGN} )
# 
# 
# a_target}
# 
# 
# 
# 
# S(${cuda_target}
# }
# 
# 
# 
# UTABLE cuda_target)
# 
# #########################################################
# #########################################################
# 
# #########################################################
# #########################################################
# e_variable)
# 
# ands and targets for each file.
# ands( cuda_compile ${ARGN} )
# 
# target_srcs} ${cuda_cu_sources})
# 
# 