cmake_minimum_required(VERSION 3.16)
project(FmtLesson LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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

add_executable(fmt_demo src/main.cpp)

target_include_directories(fmt_demo
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(fmt_demo
  PRIVATE
    fmt::fmt
)

target_compile_options(fmt_demo
  PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-O2;-Wall;-Wextra>
    $<$<CXX_COMPILER_ID:MSVC>:/O2;/W4>
)
