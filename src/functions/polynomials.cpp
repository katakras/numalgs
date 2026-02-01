#include <numalgs/functions.hpp>

namespace functions {

LinearPolynomial::LinearPolynomial(const double slope, const double intercept)
    : slope_(slope), intercept_(intercept) {}

double LinearPolynomial::operator()(const double x) const {
  return slope_ * x + intercept_;
}

}  // namespace functions