# ============================================================================
# CMAKE ADVANCED FEATURES
# ============================================================================

cmake_minimum_required(VERSION 3.14)
project(CMakeAdvanced VERSION 2.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# 1. Object library (compile once, reuse)
add_library(common_objects OBJECT src/main.cpp)

# 2. Interface library (header-only)
add_library(my_header_lib INTERFACE)

# 3. Use objects in multiple targets
add_executable(app1 $<TARGET_OBJECTS:common_objects>)
add_executable(app2 $<TARGET_OBJECTS:common_objects>)

# 4. Compile features
target_compile_features(common_objects PUBLIC cxx_std_17)

# 5. Compiler cache (ccache)
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "ccache found - enabling")
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif()

# 6. Sanitizers (optional)
option(ENABLE_ASAN "Enable AddressSanitizer" OFF)
if(ENABLE_ASAN)
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address)
    message(STATUS "AddressSanitizer: ON")
endif()

option(ENABLE_UBSAN "Enable UBSan" OFF)
if(ENABLE_UBSAN)
    add_compile_options(-fsanitize=undefined)
    add_link_options(-fsanitize=undefined)
    message(STATUS "UndefinedBehaviorSanitizer: ON")
endif()

# 7. Custom target
add_custom_target(info
    COMMAND ${CMAKE_COMMAND} -E echo "Project: ${PROJECT_NAME} v${PROJECT_VERSION}"
    COMMAND ${CMAKE_COMMAND} -E echo "Compiler: ${CMAKE_CXX_COMPILER_ID}"
    VERBATIM
)

# 8. Default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

message(STATUS "")
message(STATUS "=== Build Configuration ===")
message(STATUS "Project:    ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++:        ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler:   ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "===========================")
