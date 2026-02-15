#include <nanobind/nanobind.h>
#include <nanobind/stl/shared_ptr.h>
#include <nanobind/stl/variant.h>

#include <numalgs/results.hpp>
#include <numalgs/root_finding.hpp>

namespace nb = nanobind;

void bind_root_finding(nb::module_& m) {
  m.def("find_root", &root_finding::find_root, nb::arg("f"), nb::arg("config"));

  nb::class_<root_finding::RootFindingConfigBisection>(
      m, "RootFindingConfigBisection")
      .def(nb::init<double, double>(), nb::arg("a"), nb::arg("b"));
}