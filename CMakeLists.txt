cmake_minimum_required(VERSION 3.10)
project(CoffeeShop)

set(CMAKE_CXX_STANDARD 11)

# GoogleTest
enable_testing()
add_subdirectory(googletest)  # assumes googletest is cloned locally
include_directories(googletest/googletest/include)

add_executable(runTests main.cpp)
target_link_libraries(runTests gtest gtest_main pthread)

add_test(NAME RunAllTests COMMAND runTests)
