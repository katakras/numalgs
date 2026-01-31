#include <nanobind/nanobind.h>
#include <nanobind/stl/shared_ptr.h>

#include <memory>
#include <numalgs/functions.hpp>

namespace nb = nanobind;

using Fn = functions::Function;

void bind_functions(nb::module_& m) {
  nb::class_<Fn>(m, "Function")
      .def("__call__", [](const Fn& f, double x) { return f(x); })
      .def("__call__",
           [](std::shared_ptr<const Fn> f, std::shared_ptr<const Fn> g) {
             return std::make_shared<const functions::ComposedFunction>(
                 std::move(f), std::move(g));
           })
      .def("__add__",
           [](std::shared_ptr<const Fn> f, std::shared_ptr<const Fn> g) {
             return std::make_shared<const functions::AddFunctions>(f, g);
           });

  nb::class_<functions::LinearPolynomial, Fn>(m, "LinearPolynomial")
      .def(nb::init<double, double>(), nb::arg("slope"), nb::arg("intercept"));

  nb::class_<functions::ComposedFunction, Fn>(m, "_ComposedFunction");

  nb::class_<functions::AddFunctions, Fn>(m, "_AddFunctions");
}