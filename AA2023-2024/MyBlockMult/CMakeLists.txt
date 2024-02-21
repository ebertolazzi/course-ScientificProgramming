cmake_minimum_required(VERSION 3.10)

project(block_multiplication)

# set RELEASE by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

add_executable(block_multiplication
    block_multiplication_main.cpp
    block_multiplication.cpp
    my_block_multiplication.cpp
    ThreadPool1.cc
    ThreadUtils.cc
)

set_target_properties(block_multiplication PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

include_directories(
  ../eigen-3.4.0
)

# if (MSVC)
#     target_compile_options(block_multiplication PRIVATE /W4 /WX)
# else()
#     target_compile_options(block_multiplication PRIVATE -Wall -Wextra -pedantic)
# endif()
