cmake_minimum_required(VERSION 3.16)

project(lesson1_cpp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

add_executable(lesson
  main_complete.cpp
)

target_include_directories(lesson
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(lesson
  PRIVATE
    Threads::Threads
)

target_compile_options(lesson
  PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-O2;-Wall;-Wextra>
    $<$<CXX_COMPILER_ID:MSVC>:/O2;/W4>
)
