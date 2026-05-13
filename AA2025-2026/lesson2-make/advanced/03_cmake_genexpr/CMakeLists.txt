# ============================================================================
# CMAKE GENERATOR EXPRESSIONS
# ============================================================================
# Syntax: $<EXPRESSION>
# Evaluated at BUILD time, not configure time

cmake_minimum_required(VERSION 3.14)
project(GenExpr LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_executable(app src/main.cpp)

# Conditional definition (only in Debug)
target_compile_definitions(app PRIVATE
    $<$<CONFIG:Debug>:MY_DEFINE>
)

# Different flags per build type
target_compile_options(app PRIVATE
    $<$<CONFIG:Debug>:-g -O0>
    $<$<CONFIG:Release>:-O3 -DNDEBUG>
)

# Boolean condition
set(USE_FEATURE ON)
target_compile_definitions(app PRIVATE
    $<$<BOOL:${USE_FEATURE}>:USE_FEATURE=1>
)

# Platform detection
target_compile_definitions(app PRIVATE
    $<$<PLATFORM_ID:Linux>:OS_LINUX>
    $<$<PLATFORM_ID:Darwin>:OS_MACOS>
    $<$<PLATFORM_ID:Windows>:OS_WINDOWS>
)

# Compiler-specific flags
target_compile_options(app PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>
    $<$<CXX_COMPILER_ID:Clang>:-Wall -Weverything>
)

# String operations
set(MY_VAR "HelloWorld")
message(STATUS "Lower case: $<LOWER_CASE:${MY_VAR}>")
message(STATUS "Upper case: $<UPPER_CASE:${MY_VAR}>")

# Target file path
add_custom_target(print_info
    COMMAND ${CMAKE_COMMAND} -E echo "Binary: $<TARGET_FILE:app>"
    VERBATIM
)
