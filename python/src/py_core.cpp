
#include <pybind11/pybind11.h>            // Pybind11 import to define Python bindings
#include <xtensor/xmath.hpp>              // xtensor import for the C++ universal functions

#include <xtensor-python/pyarray.hpp>     // Numpy bindings
#include <xtensor-python/pytensor.hpp>    // Numpy bindings

#include "cpptools/cpptools.hpp"
#include "cpptools/cpptools_config.hpp"


#include <numeric>                        // Standard library import for std::accumulate

double sum_of_sines(xt::pyarray<double>& m)
{
    auto sines = xt::sin(m);  // sines does not actually hold values.
    return std::accumulate(sines.begin(), sines.end(), 0.0);
}


void export_core(pybind11::module & py_module){
    py_module.def("sum_of_sines", sum_of_sines, "Sum the sines of the input values");
}
