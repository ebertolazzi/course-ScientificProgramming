cmake_minimum_required(VERSION 3.5)

# set the project name
project( ThreadsCheck )

set( CMAKE_VERBOSE_MAKEFILE ON )

# set RELEASE by default
#
# to override cmake -DCMAKE_BUILD_TYPE=Debug
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
set( PRIVATE_HEADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include_private" )

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
file(
  GLOB S
  ${PRIVATE_HEADER_DIR}/*.h*
  ${PRIVATE_HEADER_DIR}/*/*.h*
)
foreach (F ${S})
  # build relative path respect to source directory
  file( RELATIVE_PATH RF ${PRIVATE_HEADER_DIR} "${F}" )
  list( APPEND PUBLIC_HEADERS ${PRIVATE_HEADER_DIR}/${RF} )
endforeach(F ${S})

# no private headers

# drop out files if needed
#list(FILTER PUBLIC_HEADERS EXCLUDE REGEX ".*.tmpl$")
#list(FILTER PRIVATE_HEADERS EXCLUDE REGEX ".*.tmpl$")

# add search path for headers
include_directories( "../../eigen-3.4.0" include )

# compile all the ${SOURCES} and produce .o files and store
# the list of objs into OBJS
add_library( OBJS OBJECT ${SOURCES} )

#   _____       _
#  |_   _|__ __| |_ ___
#    | |/ -_|_-<  _(_-<
#    |_|\___/__/\__/__/
#
# enable commant test to check che produced executable/library etc
enable_testing()

set( EXELISTBIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin" )
set( EXELISTCPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src_tests" )

# set list of test to be compiled
# set( EXELISTCPP test_LS1 test_LS2 test_LS1b test_LS2b )
#
# or build the list by get all the file *.cc in a specific dyrectory
set( EXELISTCPP )
file( GLOB S ${CMAKE_CURRENT_SOURCE_DIR}/src_tests/test*.cc )
foreach(F ${S})
  # build relative path respect to source directory
  file( RELATIVE_PATH RF "${CMAKE_CURRENT_SOURCE_DIR}/src_tests" "${F}" )
  string(REGEX REPLACE "\\.[^.]*$" "" RF1 ${RF}) # rimuove .cc
  list( APPEND EXELISTCPP ${RF1} )
endforeach(F ${S})

# list of extra library to link the executable
set( LIBS $<TARGET_OBJECTS:OBJS> )
set( TARGETS_TO_BE_INSTALLED )
set( INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR} )
foreach( S ${EXELISTCPP} )
  add_executable( ${S} ${CMAKE_CURRENT_SOURCE_DIR}/src_tests/${S}.cc )
  set( TARGETS_TO_BE_INSTALLED ${TARGETS_TO_BE_INSTALLED} ${S} )
  target_link_libraries( ${S} ${LIBS} )
  set_target_properties( ${S} PROPERTIES SUFFIX ".exe" )
  # add exectable to the list of test command
  add_test( NAME "${S}" COMMAND ./bin/${S}.exe WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )
endforeach()

#   ___         _        _ _
#  |_ _|_ _  __| |_ __ _| | |
#   | || ' \(_-<  _/ _` | | |
#  |___|_||_/__/\__\__,_|_|_|
#
install(
  TARGETS ${TARGETS_TO_BE_INSTALLED}
  # EXPORT (da definire)
  LIBRARY DESTINATION ${INSTALL_PREFIX}/dll
  ARCHIVE DESTINATION ${INSTALL_PREFIX}/lib
  RUNTIME DESTINATION ${INSTALL_PREFIX}/bin
  PUBLIC_HEADER DESTINATION ${PROJECT_PUBLIC_HEADER_DESTINATION}
)
