cmake_minimum_required(VERSION 3.16)
project(EigenLesson CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Eigen
set(EIGEN3_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../eigen-5.0.1")

# TinyAD
set(TINYAD_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../TinyAD-main/include")

# CppAD
set(CPPAD_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../CppAD-20260000.0/include")
set(CPPAD_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../CppAD-20260000.0/build/cppad_lib")
find_library(CPPAD_LIB cppad_lib
  PATHS "${CPPAD_LIBRARY_DIR}"
  NO_DEFAULT_PATH
  REQUIRED
)

# autodiff
set(AUTODIFF_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../autodiff-1.1.2")

# {fmt}
set(LOCAL_FMT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../fmt-12.1.0")
set(LOCAL_FMT_BUILD_DIR "${LOCAL_FMT_DIR}/build")

if(EXISTS "${LOCAL_FMT_BUILD_DIR}/fmt-config.cmake")
  find_package(fmt CONFIG REQUIRED
    PATHS "${LOCAL_FMT_BUILD_DIR}"
    NO_DEFAULT_PATH
  )
else()
  add_subdirectory("${LOCAL_FMT_DIR}" "${CMAKE_BINARY_DIR}/fmt-build")
endif()

find_package(Doxygen REQUIRED)

# Suppress common third-party warnings
add_compile_options(-Wno-deprecated-declarations -Wno-unused-variable)

# Dual-number validation executable
add_executable(test1 src/test1.cc)
target_include_directories(test1 PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${EIGEN3_INCLUDE_DIR}
)
target_link_libraries(test1 PRIVATE fmt::fmt)
target_compile_options(test1 PRIVATE -O2 -Wall -Wextra)

# Doxygen documentation
set(DOXYGEN_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/docs")
set(DOXYGEN_CONFIG_FILE "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in"
  "${DOXYGEN_CONFIG_FILE}"
  @ONLY
)

add_custom_target(doc
  COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_CONFIG_FILE}"
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  COMMENT "Generating Doxygen HTML documentation"
  VERBATIM
)

message(STATUS "Eigen: ${EIGEN3_INCLUDE_DIR}")
message(STATUS "TinyAD: ${TINYAD_INCLUDE_DIR}")
message(STATUS "CppAD: ${CPPAD_INCLUDE_DIR}")
message(STATUS "CppAD library: ${CPPAD_LIB}")
message(STATUS "autodiff: ${AUTODIFF_INCLUDE_DIR}")
message(STATUS "{fmt}: ${LOCAL_FMT_DIR}")
message(STATUS "Doxygen: ${DOXYGEN_EXECUTABLE}")
