#include <nanobind/nanobind.h>
#include <nanobind/stl/optional.h>
#include <nanobind/stl/shared_ptr.h>

#include <numalgs/results.hpp>

namespace nb = nanobind;

void bind_results(nb::module_& m) {
  nb::enum_<ResultStatus>(m, "ResultStatus")
      .value("success", ResultStatus::success)
      .value("error", ResultStatus::error)
      .value("not_converged", ResultStatus::not_converged);

  nb::class_<Result<double>>(m, "DoubleResult")
      .def("value", &Result<double>::value)
      .def("status", &Result<double>::status);
}