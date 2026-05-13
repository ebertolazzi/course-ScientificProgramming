# ============================================================================
# CMAKE WITH STATIC LIBRARY
# ============================================================================
# Shows: add_library, target_include_directories, target_link_libraries

cmake_minimum_required(VERSION 3.14)
project(StringUtils VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Create a static library ----
add_library(stringutils STATIC
    lib/stringutils.cpp
)

# ---- Set include directories ----
# PUBLIC = used by library AND its consumers
# PRIVATE = only used by this library
# INTERFACE = only used by consumers
target_include_directories(stringutils PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ---- Compiler options for the library ----
target_compile_options(stringutils PRIVATE -Wall -Wextra)

# ---- Create executable ----
add_executable(app src/main.cpp)

# ---- Link library to executable ----
target_link_libraries(app PRIVATE stringutils)

message(STATUS "Library: stringutils (static)")
message(STATUS "Executable: app")
