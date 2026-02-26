cmake_minimum_required(VERSION 3.10)
project(OpenMPTest)

set(CMAKE_CXX_STANDARD 17)  # Besser als 11 für moderne Features

# Setze GCC als Compiler (passe bei Bedarf an, z.B. g++-14 falls 15 nicht passt)
set(CMAKE_CXX_COMPILER "/opt/homebrew/bin/g++-15")

# WICHTIG: Setze den Pfad zu libomp, damit CMake OpenMP findet
set(OpenMP_ROOT "/opt/homebrew/opt/libomp")
# Optional: Für bessere Suche (falls nötig)
set(CMAKE_PREFIX_PATH "${OpenMP_ROOT};${CMAKE_PREFIX_PATH}")

find_package(OpenMP REQUIRED)

add_executable(pi_monte_carlo.cpp)

if(OpenMP_CXX_FOUND)
    target_link_libraries(test PRIVATE OpenMP::OpenMP_CXX)
    target_compile_options(test PRIVATE -fopenmp)
endif()