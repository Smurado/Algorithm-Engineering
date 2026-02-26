cmake_minimum_required(VERSION 3.26)
project(lodepng)

set(LODEPNG_SOURCES
        lodepng.h
        lodepng.cpp
)

add_library(lodepng STATIC ${LODEPNG_SOURCES})

target_link_directories(lodepng PUBLIC ./)