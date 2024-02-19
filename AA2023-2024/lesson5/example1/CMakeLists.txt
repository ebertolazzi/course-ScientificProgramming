cmake_minimum_required(VERSION 3.5)

set( CMAKE_VERBOSE_MAKEFILE ON )

# set the project name
project( TestProject )

# add search path for headers
include_directories( "../../eigen-3.4.0" )

# add the executable
add_executable( test_LS1 test_LS1.cc )
add_executable( test_LS2 test_LS2.cc )