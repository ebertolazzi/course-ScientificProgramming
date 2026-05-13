# ============================================================================
# CMAKE TESTING WITH CTEST
# ============================================================================

cmake_minimum_required(VERSION 3.14)
project(CalculatorTest LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# Enable CTest
enable_testing()

# Library
add_library(calculator STATIC src/calculator.h)

# Main app
add_executable(calc_app src/main.cpp)
target_link_libraries(calc_app PRIVATE calculator)

# Test executable
add_executable(test_calculator test/test_calculator.cpp)
target_link_libraries(test_calculator PRIVATE calculator)

# Register tests with CTest
add_test(NAME CalculatorTests COMMAND test_calculator)

# Test properties
set_tests_properties(CalculatorTests PROPERTIES
    TIMEOUT 10
    LABELS "unit"
)

# Custom target to run tests
add_custom_target(check
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS test_calculator
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

message(STATUS "Run tests: ctest --output-on-failure")
message(STATUS "Or: make check")
