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

#   ___
#  / __| ___ _  _ _ _ __ ___ ___
#  \__ \/ _ \ || | '_/ _/ -_|_-<
#  |___/\___/\_,_|_| \__\___/__/
#
set( SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src" )
set( HEADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include" )

set( SOURCES )
file( GLOB S ${SOURCE_DIR}/*.cc ${SOURCE_DIR}/**/*.cc )
foreach(F ${S})
  # build relative path respect to source directory
  file( RELATIVE_PATH RF ${SOURCE_DIR} "${F}" )
  list( APPEND SOURCES src/${RF} )
endforeach(F ${S})

message( STATUS "SOURCES = ${SOURCES}" )

# drop out files if needed
# list(FILTER SOURCES EXCLUDE REGEX ".*hsl_fake.cc$")

#   _  _             _
#  | || |___ __ _ __| |___ _ _ ___
#  | __ / -_) _` / _` / -_) '_(_-<
#  |_||_\___\__,_\__,_\___|_| /__/
#
set( PUBLIC_HEADERS )
file(
  GLOB S
  ${HEADER_DIR}/*.h*
  ${HEADER_DIR}/*/*.h*
)
foreach (F ${S})
  # build relative path respect to source directory
  file( RELATIVE_PATH RF ${HEADER_DIR} "${F}" )
  list( APPEND PUBLIC_HEADERS ${HEADER_DIR}/${RF} )
endforeach(F ${S})

set( PRIVATE_HEADERS )
# no private headers

# drop out files if needed
#list(FILTER PUBLIC_HEADERS EXCLUDE REGEX ".*.tmpl$")
#list(FILTER PRIVATE_HEADERS EXCLUDE REGEX ".*.tmpl$")

# add search path for headers
include_directories( "../../eigen-3.4.0" include )

# compile all the ${SOURCES} and produce .o files and store
# the list of objs into OBJS
add_library( OBJS OBJECT ${SOURCES} )

# add the executable
# $<TARGET_OBJECTS:OBJS> extratct the list of objs
add_executable( test_LS1  src_tests/test_LS1.cc $<TARGET_OBJECTS:OBJS> )
add_executable( test_LS2  src_tests/test_LS2.cc $<TARGET_OBJECTS:OBJS> )
add_executable( test_LS1b src_tests/test_LS1b.cc $<TARGET_OBJECTS:OBJS> )
add_executable( test_LS2b src_tests/test_LS2b.cc $<TARGET_OBJECTS:OBJS> )