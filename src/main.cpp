#include <pybind11/pybind11.h>

float some_float(float float_1, float float_2) {
    return float_1 + float_2;
}

PYBIND11_MODULE(cmake_example, handle) {
    handle.def("abc", &some_float)
}
