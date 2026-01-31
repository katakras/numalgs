#include <nanobind/nanobind.h>

namespace nb = nanobind;

void bind_functions(nb::module_&);

NB_MODULE(numalgs_py, m) {
  bind_functions(m);
  // bind_aaa(m);
  // bind_bbb(m);
  // ...
}