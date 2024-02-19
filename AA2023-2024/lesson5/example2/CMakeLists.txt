cmake_minimum_required(VERSION 3.5)

# set the project name
project( LeastSquares )

set( CMAKE_VERBOSE_MAKEFILE ON )

# set RELEASE by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

# set for C++11 as default standard
set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

# add search path for headers
include_directories( "../../eigen-3.4.0" include )

# add the executable
add_executable( test_LS1  src_tests/test_LS1.cc src/LS_LU_solve.cc src/LS_QR_solve.cc )
add_executable( test_LS2  src_tests/test_LS2.cc src/LS_LU_solve.cc src/LS_QR_solve.cc )
add_executable( test_LS1b src_tests/test_LS1b.cc src/LS_LU_solve.cc src/LS_QR_solve.cc )
add_executable( test_LS2b src_tests/test_LS2b.cc src/LS_LU_solve.cc src/LS_QR_solve.cc )