#include <numalgs/errors.hpp>
#include <numalgs/functions.hpp>
#include <numalgs/root_finding.hpp>

namespace root_finding {

RootFindingConfigNewton::RootFindingConfigNewton(const double x0,
                                                 const double tol,
                                                 const size_t max_iters)
    : x0_(x0), tol_(tol), max_iters_(max_iters) {}

double newton(const std::shared_ptr<const functions::Function>& f_ptr,
              const double x0, const double tol, const size_t max_iters) {
  const auto& f = *f_ptr;
  const auto& df_ptr = functions::derivative(f_ptr);
  const auto& df = *df_ptr;

  double x = x0;
  size_t current_iter = 1u;
  while (f(x) >= tol && current_iter <= max_iters) {
    const double df_x = df(x);
    if (df_x < 1e-14) {
      THROW("Found 0 derivative in Newton-Rhapson.");
    }
    x = x - f(x) / df_x;
  }

  if (current_iter > max_iters) {
    // not converged exit
  }
  return x;
}
}  // namespace root_finding