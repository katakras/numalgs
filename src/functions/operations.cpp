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

MultiplyFunctions::MultiplyFunctions(std::shared_ptr<const Function> lhs,
                                     std::shared_ptr<const Function> rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

double MultiplyFunctions::operator()(const double x) const {
  return (*lhs_)(x) * (*rhs_)(x);
}

struct add_functions_visitor {
  const std::shared_ptr<const Function>& lhs;
  const std::shared_ptr<const Function>& rhs;

  // Case of adding two polynomials
  std::shared_ptr<const Function> operator()(
      const std::reference_wrapper<const Polynomial>&,
      const std::reference_wrapper<const Polynomial>&) const {
    const auto& lhs_as_p = std::static_pointer_cast<const Polynomial>(lhs);
    const auto& rhs_as_p = std::static_pointer_cast<const Polynomial>(rhs);

    const auto& coeffs_lhs = lhs_as_p->coefficients();
    const auto& coeffs_rhs = rhs_as_p->coefficients();

    const size_t n_min = std::min(coeffs_lhs.size(), coeffs_rhs.size());
    const size_t n_max = std::max(coeffs_lhs.size(), coeffs_rhs.size());

    std::vector<double> coefficients(n_max, 0.0);
    for (size_t i = 0u; i < n_min; ++i)
      coefficients[i] = coeffs_lhs[i] + coeffs_rhs[i];

    if (coeffs_lhs.size() == n_max) {
      for (size_t i = n_min; i < n_max; ++i) coefficients[i] = coeffs_lhs[i];
    } else {
      for (size_t i = n_min; i < n_max; ++i) coefficients[i] = coeffs_rhs[i];
    }

    return std::make_shared<Polynomial>(std::move(coefficients));
  }

  // Generic case
  template <typename L, typename R>
  std::shared_ptr<const Function> operator()(const L&, const R&) const {
    return std::make_shared<const AddFunctions>(lhs, rhs);
  }
};

std::shared_ptr<const Function> add_functions(
    const std::shared_ptr<const Function>& lhs,
    const std::shared_ptr<const Function>& rhs) {
  return std::visit(add_functions_visitor{lhs, rhs}, lhs->as_fvariant(),
                    rhs->as_fvariant());
}

std::shared_ptr<const Function> multiply_functions(
    const std::shared_ptr<const Function>& lhs,
    const std::shared_ptr<const Function>& rhs) {
  return std::make_shared<const MultiplyFunctions>(lhs, rhs);
}

}  // namespace functions