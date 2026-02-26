cmake_minimum_required(VERSION 3.26)
project(fizzbuzz LANGUAGES CXX)

add_library(fizzbuzz STATIC include/fizzbuzz.h src/fizzbuzz.cpp)

target_link_directories(fizzbuzz PUBLIC include)