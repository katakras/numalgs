#include <nanobind/nanobind.h>

#include <numalgs/hello.hpp>

namespace nb = nanobind;

NB_MODULE(numalgs_py, m) { m.def("hello", &numalgs::hello); }