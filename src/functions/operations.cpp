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

struct add_functions_visitor {
  const std::shared_ptr<const Function>& lhs;
  const std::shared_ptr<const Function>& rhs;

  // Case of adding two linear polynomials
  std::shared_ptr<const Function> operator()(
      const std::reference_wrapper<const LinearPolynomial>&,
      const std::reference_wrapper<const LinearPolynomial>&) const {
    const auto& lhs_as_lp =
        std::static_pointer_cast<const LinearPolynomial>(lhs);
    const auto& rhs_as_lp =
        std::static_pointer_cast<const LinearPolynomial>(rhs);

    return std::make_shared<LinearPolynomial>(
        lhs_as_lp->slope() + rhs_as_lp->slope(),
        lhs_as_lp->intercept() + rhs_as_lp->intercept());
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
}