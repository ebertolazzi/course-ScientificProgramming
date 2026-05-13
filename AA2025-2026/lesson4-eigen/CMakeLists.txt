cmake_minimum_required(VERSION 3.16)
project(EigenLesson CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Eigen
set(EIGEN3_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../eigen-5.0.1")

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

# Suppress Eigen warnings
add_compile_options(-Wno-deprecated-declarations -Wno-unused-variable)

# Modular executable
add_executable(eigen_demo 
    src/main.cpp
    src/01_basics.cpp
    src/02_matrix_operations.cpp
    src/03_linear_systems.cpp
    src/04_eigenvalues.cpp
    src/05_geometry.cpp
    src/06_sparse.cpp
    src/07_advanced.cpp
    src/08_benchmarks.cpp
)

target_include_directories(eigen_demo PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${EIGEN3_INCLUDE_DIR}
)
target_link_libraries(eigen_demo PRIVATE fmt::fmt)
target_compile_options(eigen_demo PRIVATE -O2 -Wall -Wextra)

# Single-file version
add_executable(eigen_demo_single src/eigen_demo_single.cpp)
target_include_directories(eigen_demo_single PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${EIGEN3_INCLUDE_DIR}
)
target_link_libraries(eigen_demo_single PRIVATE fmt::fmt)
target_compile_options(eigen_demo_single PRIVATE -O2 -Wall -Wextra)

message(STATUS "Eigen:     ${EIGEN3_INCLUDE_DIR}")
message(STATUS "{fmt}:      ${LOCAL_FMT_DIR}")
