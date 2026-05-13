# ============================================================================
# CMAKE INSTALL AND EXPORT
# ============================================================================
# Shows: install(), export(), find_package config generation

cmake_minimum_required(VERSION 3.14)
project(MyLib VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Library ----
add_library(mylib STATIC src/mylib.cpp)

# Generator expressions for build vs install paths
target_include_directories(mylib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# ---- Executable ----
add_executable(mylib_app src/main.cpp)
target_link_libraries(mylib_app PRIVATE mylib)

# ---- Install rules ----
include(GNUInstallDirs)

install(TARGETS mylib
    EXPORT mylib-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(TARGETS mylib_app
    DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ---- Export for find_package ----
install(EXPORT mylib-targets
    FILE mylib-targets.cmake
    NAMESPACE mylib::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/mylib
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/mylib-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/mylib-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/mylib
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/mylib-config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/mylib
)

message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
