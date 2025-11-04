cmake_minimum_required(VERSION 3.10)
project(OpenMPTest)

set(CMAKE_CXX_STANDARD 11)

# Setze GCC als Compiler (passe die Version an, z. B. gcc-14)
set(CMAKE_CXX_COMPILER "/opt/homebrew/bin/g++-15")

find_package(OpenMP REQUIRED)

add_executable(test pi_monte_carlo.cpp)

if(OpenMP_CXX_FOUND)
    target_link_libraries(test PRIVATE OpenMP::OpenMP_CXX)
endif()