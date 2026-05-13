cmake_minimum_required(VERSION 3.20)

project(UnitTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================
# GoogleTest

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

# ============================================
# Configure source files

file(GLOB SRC_FILES CONFIGURE_DEPENDS ../src/*.cpp)
add_library(core ${SRC_FILES})

target_include_directories(core
    PUBLIC ../inc
)

include(GoogleTest)

# ============================================
# Tests for class Point2D

add_executable(test_Point2D
    test_Point2D.cpp
)

target_link_libraries(test_Point2D
    core
    GTest::gtest_main
    GTest::gmock
)

gtest_discover_tests(test_Point2D)

# ============================================
# Tests for class Grid2D

add_executable(test_Grid2D
    test_Grid2D.cpp
)

target_link_libraries(test_Grid2D
    core
    GTest::gtest_main
    GTest::gmock
)

gtest_discover_tests(test_Grid2D)