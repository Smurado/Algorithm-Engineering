cmake_minimum_required(VERSION 3.28) # [cite: 1]
project(Datasaurus_Cpp CXX)

# C++23 festlegen
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenMP suchen
find_package(OpenMP REQUIRED)

# ==========================================
# 1. Haupt-Programm definieren
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
# 2. Test-Programm definieren
# ==========================================
enable_testing()

# Catch2 automatisch von GitHub laden
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
# 3. Compiler-Flags für BEIDE Targets setzen
# ==========================================
if(MSVC)
    # Windows / Visual Studio Compiler
    target_compile_options(Datasaurus_Cpp PRIVATE /O2 /arch:AVX2 /openmp)
    target_compile_options(UnitTests PRIVATE /O2 /arch:AVX2 /openmp)
else()
    # Clang (Mac) oder echter GCC (Linux/Mac)
    target_compile_options(Datasaurus_Cpp PRIVATE -fopenmp -O3)
    target_compile_options(UnitTests PRIVATE -fopenmp -O3)

    # Nutze -march=native NUR, wenn wir KEIN Universal Binary für Mac bauen
    if(NOT CMAKE_OSX_ARCHITECTURES)
        target_compile_options(Datasaurus_Cpp PRIVATE -march=native)
        target_compile_options(UnitTests PRIVATE -march=native)
    endif()
endif()

# Tests für die IDE (Test Explorer) auffindbar machen
include(Catch)
catch_discover_tests(UnitTests)