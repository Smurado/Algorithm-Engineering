cmake_minimum_required(VERSION 3.28)
project(Datasaurus_Cpp CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenMP REQUIRED)

# ==========================================
# Main executable
# ==========================================
add_executable(Datasaurus_Cpp
        main.cpp
        statistics.cpp
        statistics.h
        shapes.h
        config.h
)
target_link_libraries(Datasaurus_Cpp PUBLIC OpenMP::OpenMP_CXX)

# ==========================================
# Test executable
# ==========================================
enable_testing()

# Fetch Catch2 from GitHub
include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.2
)
FetchContent_MakeAvailable(Catch2)

add_executable(UnitTests
        tests.cpp
        statistics.cpp
        statistics.h
)
target_link_libraries(UnitTests PRIVATE Catch2::Catch2WithMain PUBLIC OpenMP::OpenMP_CXX)

# ==========================================
# Compiler flags
# ==========================================
if(MSVC)
    # MSVC
    target_compile_options(Datasaurus_Cpp PRIVATE /O2 /arch:AVX2 /openmp)
    target_compile_options(UnitTests PRIVATE /O2 /arch:AVX2 /openmp)
else()
    # Clang / GCC
    target_compile_options(Datasaurus_Cpp PRIVATE -fopenmp -O3)
    target_compile_options(UnitTests PRIVATE -fopenmp -O3)

    # Only use -march=native when not building a Universal Binary
    if(NOT CMAKE_OSX_ARCHITECTURES)
        target_compile_options(Datasaurus_Cpp PRIVATE -march=native)
        target_compile_options(UnitTests PRIVATE -march=native)
    endif()
endif()

# Make tests discoverable via CTest / IDE Test Explorer
include(Catch)
catch_discover_tests(UnitTests)