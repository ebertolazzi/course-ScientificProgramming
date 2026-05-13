# ============================================================================
# SIMPLE CMAKE - Minimum Required
# ============================================================================

# 1. Always first: minimum CMake version
cmake_minimum_required(VERSION 3.14)

# 2. Project definition
project(Calculator VERSION 1.0.0 LANGUAGES CXX)

# 3. C++ standard (modern way: set at target level, not globally)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 4. Create executable from source files
add_executable(calculator
    src/main.cpp
    src/calculator.cpp
    src/calculator.h
)

# 5. Set compiler options for this target
target_compile_options(calculator PRIVATE -Wall -Wextra)

# 6. Print configuration info
message(STATUS "Project: ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
