cmake_minimum_required(VERSION 3.20)

project(SearchAlgorithms LANGUAGES CXX)

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

file(GLOB SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

add_executable(generate_plans
    generate_plans.cpp
    ${SRC_FILES}
)

target_include_directories(generate_plans
    PRIVATE inc
)

add_executable(astar
    astar.cpp
    ${SRC_FILES}
)

target_include_directories(astar
    PRIVATE inc
)

add_executable(bfs
    bfs.cpp
    ${SRC_FILES}
)

target_include_directories(bfs
    PRIVATE inc
)

# ============================================
# Configure source files

file(GLOB SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
add_library(core ${SRC_FILES})

target_include_directories(core
    PUBLIC inc
)

include(GoogleTest)

# ============================================
# Tests for class Point2D

add_executable(test_Point2D
    unit_tests/test_Point2D.cpp
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
    unit_tests/test_Grid2D.cpp
)

target_link_libraries(test_Grid2D
    core
    GTest::gtest_main
    GTest::gmock
)

gtest_discover_tests(test_Grid2D)

# ============================================
# Tests for class GeneratePlan

add_executable(test_GeneratePlan
    unit_tests/test_GeneratePlan.cpp
)

target_link_libraries(test_GeneratePlan
    core
    GTest::gtest_main
    GTest::gmock
)

gtest_discover_tests(test_GeneratePlan)

# ============================================
# Tests for class AStar

add_executable(test_AStar2D
    unit_tests/test_AStar2D.cpp
)

target_link_libraries(test_AStar2D
    core
    GTest::gtest_main
    GTest::gmock
)

gtest_discover_tests(test_AStar2D)