cmake_minimum_required(VERSION 3.0)
project(linalg VERSION 1.0.1 DESCRIPTION "linear algebra library")

set(CMAKE_CXX_FLAGS "-std=c++11 -g ${CMAKE_CXX_FLAGS}")

add_library(linalg STATIC
    lib/MachineEpsilon.hpp
    lib/MachineEpsilon.cpp
    lib/Array.hpp
    lib/ArrayUtils.cpp
    lib/ArrayUtils.hpp
    lib/DenseArray.hpp
    lib/DenseArray.ipp
    lib/Vector.hpp
    lib/Vector.ipp
    lib/VectorNorms.hpp
    lib/VectorNorms.cpp
    lib/MatrixNorms.hpp
    lib/MatrixNorms.cpp
    lib/Utils.hpp
    lib/Utils.cpp
)

# TODO: move the tests to test directory not lib
add_executable(LinAlgTester
    lib/test_main.cpp
)

set_target_properties(linalg PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(LinAlgTester linalg)
