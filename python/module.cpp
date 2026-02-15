#include <nanobind/nanobind.h>

namespace nb = nanobind;

void bind_functions(nb::module_&);
void bind_results(nb::module_&);
void bind_root_finding(nb::module_&);

NB_MODULE(numalgs_py, m) {
  bind_functions(m);
  bind_results(m);
  bind_root_finding(m);
}