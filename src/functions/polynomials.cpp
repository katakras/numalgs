#include <numalgs/functions.hpp>

namespace functions {

Polynomial::Polynomial(std::vector<double> coefficients)
    : coefficients_(std::move(coefficients)) {}

double Polynomial::operator()(const double x) const {
  if (coefficients_.size() == 1u) return coefficients_.front();
  double s = coefficients_.back() * x;
  for (size_t i = coefficients_.size() - 2u; i > 0u; --i) {
    s += coefficients_[i];
    s *= x;
  }
  return s + coefficients_[0u];
}

}  // namespace functions