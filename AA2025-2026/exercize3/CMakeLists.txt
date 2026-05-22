# ============================================================================
# SIMPLE CMAKE - exercize3
# ============================================================================

#
# ask required minimum version of cmake
#
cmake_minimum_required(VERSION 3.14)

set( TARGET exercize3 )

project(${TARGET} VERSION 1.0.0 LANGUAGES CXX)

option(EXERCIZE3_BUILD_DOCS "Generate Doxygen documentation when available" ON)

#
# setup for C++ standard usage
#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# set where to search for Eigen
set(EXERCIZE3_EIGEN_DIR
  "${CMAKE_CURRENT_SOURCE_DIR}/../eigen-5.0.1"
  CACHE PATH "Path to the Eigen source tree"
)

# set where to search for {fmt}
set(EXERCIZE3_FMT_DIR
  "${CMAKE_CURRENT_SOURCE_DIR}/../fmt-12.1.0"
  CACHE PATH "Path to the fmt source tree"
)
set(EXERCIZE3_FMT_BUILD_DIR
  "${EXERCIZE3_FMT_DIR}/build"
  CACHE PATH "Path to a pre-built fmt CMake package"
)

if(EXISTS "${EXERCIZE3_EIGEN_DIR}/Eigen/Dense")
  set(EIGEN3_INCLUDE_DIR "${EXERCIZE3_EIGEN_DIR}")
else()
  find_package(Eigen3 CONFIG REQUIRED)
endif()

# for link with {FMT}
if(EXISTS "${EXERCIZE3_FMT_BUILD_DIR}/fmt-config.cmake")
  find_package(fmt CONFIG REQUIRED
    PATHS "${EXERCIZE3_FMT_BUILD_DIR}"
    NO_DEFAULT_PATH
  )
elseif(EXISTS "${EXERCIZE3_FMT_DIR}/CMakeLists.txt")
  add_subdirectory("${EXERCIZE3_FMT_DIR}" "${CMAKE_BINARY_DIR}/fmt-build")
else()
  find_package(fmt CONFIG REQUIRED)
endif()

# define executable with sources abd headers
add_executable(${TARGET} src/${TARGET}.cc include/${TARGET}.hh)

# extra directory to find header for the target
target_include_directories(${TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(TARGET Eigen3::Eigen)
  target_link_libraries(${TARGET} PRIVATE Eigen3::Eigen)
else()
  target_include_directories(${TARGET} PRIVATE ${EIGEN3_INCLUDE_DIR})
endif()

# extra library to link
target_link_libraries(${TARGET} PRIVATE fmt::fmt)

if (UNIX)
  # extra flags for link, increase paranoia of the compiler
  target_compile_options(${TARGET} PRIVATE -Wall -Wextra -Wpedantic )
endif()

if(EXERCIZE3_BUILD_DOCS)
  find_package(Doxygen QUIET)
  if(DOXYGEN_FOUND)
    configure_file(
      "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in"
      "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
      @ONLY
    )
    add_custom_target(docs
      COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
      WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
      COMMENT "Generating Doxygen documentation"
      VERBATIM
    )
  else()
    message(STATUS "Doxygen not found: target 'docs' will not be generated")
  endif()
endif()

# post build command, copy the executable to ${CMAKE_SOURCE_DIR}/exe
add_custom_command(TARGET ${TARGET} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory    "${CMAKE_SOURCE_DIR}/exe"
  COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:${TARGET}>" "${CMAKE_SOURCE_DIR}/exe/$<TARGET_FILE_NAME:${TARGET}>"
  COMMENT "Copying ${TARGET} executable to ${CMAKE_SOURCE_DIR}/exe"
)

message(STATUS "Project: ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
