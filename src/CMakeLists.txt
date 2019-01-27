cmake_minimum_required(VERSION 3.0)
project(linalg VERSION 1.0.1 DESCRIPTION "linear algebra library")

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++11 -g ${CMAKE_CXX_FLAGS}")
endif()

add_library(linalg STATIC
    lib/MachineEpsilon.hpp
    lib/MachineEpsilon.cpp
)

# TODO: move the tests to test directory not lib
add_executable(LinAlgTester
    lib/test_main.cpp
)

set_target_properties(linalg PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(LinAlgTester linalg)
