# ============================================================================
# CMAKE EXTERNAL DEPENDENCIES
# ============================================================================

cmake_minimum_required(VERSION 3.14)
project(ExternalDeps LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# METHOD 1: find_package (pre-installed)
find_package(Threads REQUIRED)
message(STATUS "Threads found: ${CMAKE_THREAD_LIBS_INIT}")

# METHOD 2: FetchContent (download at configure time)
include(FetchContent)
message(STATUS "FetchContent available for downloading deps")

# Example (commented):
# FetchContent_Declare(fmt
#     GIT_REPOSITORY https://github.com/fmtlib/fmt.git
#     GIT_TAG 10.0.0
# )
# FetchContent_MakeAvailable(fmt)

# METHOD 3: ExternalProject (download at build time)
include(ExternalProject)
message(STATUS "ExternalProject available for build-time downloads")

# METHOD 4: pkg-config
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    message(STATUS "pkg-config available")
endif()

# Our app
add_executable(app src/main.cpp)
target_link_libraries(app PRIVATE Threads::Threads)

message(STATUS "")
message(STATUS "Dependency methods demonstrated:")
message(STATUS "  1. find_package - for installed libraries")
message(STATUS "  2. FetchContent - download small/header-only libs")
message(STATUS "  3. ExternalProject - download large deps")
message(STATUS "  4. pkg-config - Unix system libraries")
