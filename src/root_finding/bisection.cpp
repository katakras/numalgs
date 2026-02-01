#include <numalgs/functions.hpp>
#include <numalgs/root_finding.hpp>

namespace root_finding {

double bisection(const std::shared_ptr<const functions::Function>& f_ptr,
                 double a, double b) {
  const auto& f = *f_ptr;
  double f_a = f(a);
  double f_b = f(b);

  constexpr double tol = 1e-12;

  // TODO: errors when not found
  if (f_a == 0) return a;
  if (f_b == 0) return b;

  if (f_a * f_b > 0) throw std::exception();

  double mid, f_mid;
  while (fabs(f_a - f_b) >= tol) {
    mid = (a + b) / 2.0;
    f_mid = f(mid);
    if (f_mid * f_a <= 0) {
      b = mid;
      f_b = f_mid;
    } else {
      a = mid;
      f_a = f_mid;
    }
  }
  return mid;
}

}  // namespace root_finding