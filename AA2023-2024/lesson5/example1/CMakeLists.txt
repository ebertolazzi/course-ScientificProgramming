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
include_directories( "../../eigen-3.4.0" )

# add the executable
add_executable( test_LS1 test_LS1.cc )
add_executable( test_LS2 test_LS2.cc )
add_executable( test_LS1b test_LS1b.cc )
add_executable( test_LS2b test_LS2b.cc )