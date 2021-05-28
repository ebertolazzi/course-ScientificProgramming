cmake_minimum_required(VERSION 3.10)

set( CMAKE_VERBOSE_MAKEFILE ON )

# set the project name
project( TestProject )

# add search path for headers
include_directories( /usr/local/include/eigen3 )

# add the executable
add_executable( test1 test1.cc )
add_executable( test2 test2.cc )
add_executable( test_LS1 test_LS1.cc )
add_executable( test_LS2 test_LS2.cc )