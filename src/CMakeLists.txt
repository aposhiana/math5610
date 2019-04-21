cmake_minimum_required(VERSION 3.0)
project(linalg)

set(CMAKE_CXX_FLAGS "-std=c++11 -g -o0 ${CMAKE_CXX_FLAGS}")

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
    lib/ArrayInstantiations.hpp
    lib/ArrayInstantiations.cpp
    lib/VectorNorms.hpp
    lib/VectorNorms.cpp
    lib/MatrixNorms.hpp
    lib/MatrixNorms.cpp
    lib/Utils.hpp
    lib/Utils.cpp
    lib/LibLinAlg.hpp
    lib/LinearSolvers.cpp
    lib/LinearSolvers.hpp
)

# TODO: move the tests to test directory not lib
add_executable(LinAlgTester
    lib/test_main.cpp
)

target_include_directories(linalg INTERFACE ${CMAKE_CURRENT_LIST_DIR}/lib)

set_target_properties(linalg PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(LinAlgTester linalg)
