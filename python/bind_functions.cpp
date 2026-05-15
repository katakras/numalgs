#include <math.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/shared_ptr.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

#include <memory>
#include <numalgs/functions.hpp>

namespace nb = nanobind;

using Fn = functions::Function;

namespace {
std::string function_to_str(const functions::Polynomial& p) {
  const auto& coeffs = p.coefficients();
  std::string result;
  result.reserve(coeffs.size() * 20);

  if (fabs(coeffs[0u]) > 1e-13) result += std::to_string(coeffs[0u]);

  for (size_t i = 1u; i < coeffs.size(); ++i) {
    if (fabs(coeffs[i]) > 1e-13) {
      if (coeffs[i] > 0.0) {
        result +=
            " +" + std::to_string(coeffs[i]) + "*" + "x^" + std::to_string(i);
      } else {
        result +=
            " " + std::to_string(coeffs[i]) + "*" + "x^" + std::to_string(i);
      }
    }
  }
  return result;
}

std::string function_to_str(const functions::Exponential&) { return "exp(x)"; }

std::string function_to_str(const functions::Sin&) { return "sin(x)"; }

std::string function_to_str(const functions::Cos&) { return "cos(x)"; }

std::string function_to_str(const functions::Tan&) { return "tan(x)"; }
}  // namespace

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
             return functions::add_functions(f, g);
           })
      .def("__sub__",
           [](std::shared_ptr<const Fn> f, std::shared_ptr<const Fn> g) {
             return functions::subtract_functions(f, g);
           })
      .def("__mul__",
           [](std::shared_ptr<const Fn> f, std::shared_ptr<const Fn> g) {
             return functions::multiply_functions(f, g);
           })
      .def("__truediv__",
           [](std::shared_ptr<const Fn> f, std::shared_ptr<const Fn> g) {
             return functions::divide_functions(f, g);
           })
      .def("derivative", [](std::shared_ptr<const Fn> f) {
        return functions::derivative(f);
      });

  m.def(
      "derivative",
      [](std::shared_ptr<const Fn> f) { return functions::derivative(f); },
      nb::arg("f"));

  nb::class_<functions::Polynomial, Fn>(m, "Polynomial")
      .def(nb::init<std::vector<double>>(), nb::arg("coefficients"))
      .def("__str__",
           nb::overload_cast<const functions::Polynomial&>(&function_to_str));

  nb::class_<functions::Exponential, Fn>(m, "Exponential")
      .def(nb::init<>())
      .def("__str__",
           nb::overload_cast<const functions::Exponential&>(&function_to_str));

  nb::class_<functions::Sin, Fn>(m, "Sin")
      .def(nb::init<>())
      .def("__str__",
           nb::overload_cast<const functions::Sin&>(&function_to_str));

  nb::class_<functions::Cos, Fn>(m, "Cos")
      .def(nb::init<>())
      .def("__str__",
           nb::overload_cast<const functions::Cos&>(&function_to_str));

  nb::class_<functions::Tan, Fn>(m, "Tan")
      .def(nb::init<>())
      .def("__str__",
           nb::overload_cast<const functions::Tan&>(&function_to_str));

  nb::class_<functions::ComposedFunction, Fn>(m, "_ComposedFunction");

  nb::class_<functions::AddFunctions, Fn>(m, "_AddFunctions");

  nb::class_<functions::SubtractFunctions, Fn>(m, "_SubtractFunctions");

  nb::class_<functions::MultiplyFunctions, Fn>(m, "_MultiplyFunctions");

  nb::class_<functions::DivideFunctions, Fn>(m, "_DivideFunctions");
}
