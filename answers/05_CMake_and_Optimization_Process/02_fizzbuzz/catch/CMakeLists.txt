cmake_minimum_required(VERSION 3.26)
project(catch LANGUAGES CXX)

add_library(catch INTERFACE)

target_link_directories(catch INTERFACE include)
target_compile_features(catch INTERFACE cxx_std_11)