cmake_minimum_required(VERSION 3.20)

project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

add_executable(generate_plans
    generate_plans.cpp
    ${SRC_FILES}
)

target_include_directories(generate_plans
    PRIVATE inc
)

add_executable(search_base
    search_base.cpp
    ${SRC_FILES}
)

target_include_directories(search_base
    PRIVATE inc
)