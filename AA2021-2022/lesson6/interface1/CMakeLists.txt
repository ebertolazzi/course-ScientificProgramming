cmake_minimum_required(VERSION 3.10)

set( CMAKE_VERBOSE_MAKEFILE ON )

# set the project name
project( TestProject )

# add search path for headers
include_directories( /usr/local/include/eigen3 )

# add the executable
add_executable( main main.cc minq.cc )
