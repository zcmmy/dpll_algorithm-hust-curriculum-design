cmake_minimum_required(VERSION 3.28)
project(dpll_algorithm)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXE_LINKER_FLAGS -static)

add_executable(dpll_algorithm src/main.cpp
        src/GLobal.h
        src/dpll.cpp
        src/dpll.h
        src/dpll.cpp
        src/cnfparser.cpp
        src/cnfparser.h
)
