#include <numalgs/functions.hpp>

namespace functions {

Polynomial::Polynomial(std::vector<double> coefficients)
    : coefficients_(std::move(coefficients)) {}

double Polynomial::operator()(const double x) const {
  double s = coefficients_[0u];
  for (size_t i = 1u; i < coefficients_.size(); ++i) {
    s += coefficients_[i] * std::pow(x, i);
  }
  return s;
}

}  // namespace functions