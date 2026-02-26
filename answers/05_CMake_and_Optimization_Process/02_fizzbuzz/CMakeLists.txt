cmake_minimum_required(VERSION 3.26)
project(test_fizzbuzz LANGUAGES CXX)

add_subdirectory(fizzbuzz)

# Single file include from https://github.com/catchorg/Catch2/blob/v2.x/single_include/catch2/catch.hpp
add_subdirectory(catch)

add_executable(test_fizzbuzz catch_main.cpp catch_tests_fizzbuzz.cpp)

target_link_libraries(test_fizzbuzz PRIVATE fizzbuzz PRIVATE catch)