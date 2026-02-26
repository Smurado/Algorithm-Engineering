cmake_minimum_required(VERSION 3.26)
project(01_quantpng)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenMP REQUIRED)

add_subdirectory(quantize)
add_subdirectory(lodepng)

add_executable(01_quantpng main.cpp)

target_link_libraries(01_quantpng PUBLIC OpenMP::OpenMP_CXX PRIVATE quantize PRIVATE lodepng)