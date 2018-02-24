
#include <pybind11/pybind11.h>            // Pybind11 import to define Python bindings
#include <xtensor/xmath.hpp>              // xtensor import for the C++ universal functions

#define FORCE_IMPORT_ARRAY
#include <xtensor-python/pyarray.hpp>     // Numpy bindings
#include <xtensor-python/pytensor.hpp>    // Numpy bindings

#include "cpptools/cpptools.hpp"
#include "cpptools/cpptools_config.hpp"


#include <numeric>                        // Standard library import for std::accumulate

void export_core(pybind11::module &);

PYBIND11_MODULE(_cpptools, py_module)
{
    xt::import_numpy();



    py_module.doc() = "cpptools: the  cpptools python bindings";

    // defined in py_core.cpp
    export_core(py_module);
}