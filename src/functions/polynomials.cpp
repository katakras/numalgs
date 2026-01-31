#include <numalgs/functions.hpp>

namespace functions {

ComposedFunction::ComposedFunction(std::shared_ptr<const Function> outer,
                                   std::shared_ptr<const Function> inner)
    : outer_(std::move(outer)), inner_(std::move(inner)) {}

double ComposedFunction::operator()(const double x) const {
  return (*outer_)((*inner_)(x));
}

AddFunctions::AddFunctions(std::shared_ptr<const Function> lhs,
                           std::shared_ptr<const Function> rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

double AddFunctions::operator()(const double x) const {
  return (*lhs_)(x) + (*rhs_)(x);
}

LinearPolynomial::LinearPolynomial(const double slope, const double intercept)
    : slope_(slope), intercept_(intercept) {}

double LinearPolynomial::operator()(const double x) const {
  return slope_ * x + intercept_;
}

}  // namespace functions