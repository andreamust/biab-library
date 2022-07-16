cmake_minimum_required(VERSION 3.4...3.18)
project(biab_library)

add_subdirectory(pybind11)
add_subdirectory(pybind11/pybind11)
pybind11_add_module(biab src/main.cpp)

# EXAMPLE_VERSION_INFO is defined by setup.py and passed into the C++ code as a
# define (VERSION_INFO) here.
target_compile_definitions(biab
                           PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})
