cmake_minimum_required(VERSION 3.14)
project(StringCalculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Production library
add_library(StringCalculatorLib StringCalculator.cpp StringCalculator.h)

# Test executable
add_executable(StringCalculatorTest StringCalculatorTest.cpp)
target_link_libraries(StringCalculatorTest PRIVATE StringCalculatorLib GTest::gtest_main)

# Discover tests
include(GoogleTest)
gtest_discover_tests(StringCalculatorTest)
