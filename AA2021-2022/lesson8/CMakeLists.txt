cmake_minimum_required(VERSION 3.10)

#SET( CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE )
#SET( CMAKE_VERBOSE_MAKEFILE            TRUE )

# set the project name
project( Lesson7 )

include( ./CMakeLists-cflags.txt )
message( STATUS "Compiler used: ${CMAKE_CXX_COMPILER_ID}" )

SET( CMAKE_C_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE} )
SET( CMAKE_C_FLAGS_DEBUG   ${CMAKE_CXX_FLAGS_DEBUG} )

SET( CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE )
SET( CMAKE_VERBOSE_MAKEFILE            TRUE )

# add search path for headers
include_directories( /usr/local/include/eigen3 )

# add the executable
add_executable( test1 1_string.cc )
add_executable( test2 2_exception.cc )
add_executable( test3 3_thread_pthread.cc )
add_executable( test4 4_thread_c++11-ver1.cc )
add_executable( test5 5_thread_c++11-ver2.cc )
add_executable( test6 6_thread_c++11-ver3.cc )
add_executable( test7 7_thread_c++11-philosophe.cc )
