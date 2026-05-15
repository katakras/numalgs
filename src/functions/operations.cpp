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

SubtractFunctions::SubtractFunctions(std::shared_ptr<const Function> lhs,
                                     std::shared_ptr<const Function> rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

double SubtractFunctions::operator()(const double x) const {
  return (*lhs_)(x) - (*rhs_)(x);
}

MultiplyFunctions::MultiplyFunctions(std::shared_ptr<const Function> lhs,
                                     std::shared_ptr<const Function> rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

double MultiplyFunctions::operator()(const double x) const {
  return (*lhs_)(x) * (*rhs_)(x);
}

DivideFunctions::DivideFunctions(std::shared_ptr<const Function> lhs,
                                 std::shared_ptr<const Function> rhs)
    : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

double DivideFunctions::operator()(const double x) const {
  return (*lhs_)(x) / (*rhs_)(x);
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

struct subtract_functions_visitor {
  const std::shared_ptr<const Function>& lhs;
  const std::shared_ptr<const Function>& rhs;

  // Case of subtracting two polynomials
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
      coefficients[i] = coeffs_lhs[i] - coeffs_rhs[i];

    if (coeffs_lhs.size() == n_max) {
      for (size_t i = n_min; i < n_max; ++i) coefficients[i] = coeffs_lhs[i];
    } else {
      for (size_t i = n_min; i < n_max; ++i) coefficients[i] = -coeffs_rhs[i];
    }

    return std::make_shared<Polynomial>(std::move(coefficients));
  }

  // Generic case
  template <typename L, typename R>
  std::shared_ptr<const Function> operator()(const L&, const R&) const {
    return std::make_shared<const SubtractFunctions>(lhs, rhs);
  }
};

struct multiply_functions_visitor {
  const std::shared_ptr<const Function>& lhs;
  const std::shared_ptr<const Function>& rhs;

  // Case of multiplying two polynomials
  std::shared_ptr<const Function> operator()(
      const std::reference_wrapper<const Polynomial>&,
      const std::reference_wrapper<const Polynomial>&) const {
    const auto& lhs_as_p = std::static_pointer_cast<const Polynomial>(lhs);
    const auto& rhs_as_p = std::static_pointer_cast<const Polynomial>(rhs);

    const auto& coeffs_lhs = lhs_as_p->coefficients();
    const auto& coeffs_rhs = rhs_as_p->coefficients();

    std::vector<double> coefficients(coeffs_lhs.size() + coeffs_rhs.size() - 1u,
                                     0.0);
    for (size_t i = 0u; i < coeffs_lhs.size(); ++i) {
      for (size_t j = 0u; j < coeffs_rhs.size(); ++j) {
        coefficients[i + j] += coeffs_lhs[i] * coeffs_rhs[j];
      }
    }

    return std::make_shared<Polynomial>(std::move(coefficients));
  }

  // Generic case
  template <typename L, typename R>
  std::shared_ptr<const Function> operator()(const L&, const R&) const {
    return std::make_shared<const MultiplyFunctions>(lhs, rhs);
  }
};

std::shared_ptr<const Function> add_functions(
    const std::shared_ptr<const Function>& lhs,
    const std::shared_ptr<const Function>& rhs) {
  return std::visit(add_functions_visitor{lhs, rhs}, lhs->as_fvariant(),
                    rhs->as_fvariant());
}

std::shared_ptr<const Function> subtract_functions(
    const std::shared_ptr<const Function>& lhs,
    const std::shared_ptr<const Function>& rhs) {
  return std::visit(subtract_functions_visitor{lhs, rhs}, lhs->as_fvariant(),
                    rhs->as_fvariant());
}

std::shared_ptr<const Function> multiply_functions(
    const std::shared_ptr<const Function>& lhs,
    const std::shared_ptr<const Function>& rhs) {
  return std::visit(multiply_functions_visitor{lhs, rhs}, lhs->as_fvariant(),
                    rhs->as_fvariant());
}

std::shared_ptr<const Function> divide_functions(
    const std::shared_ptr<const Function>& lhs,
    const std::shared_ptr<const Function>& rhs) {
  return std::make_shared<const DivideFunctions>(lhs, rhs);
}

struct derivative_visitor {
  const std::shared_ptr<const Function>& f;

  std::shared_ptr<const Function> operator()(
      const std::reference_wrapper<const ComposedFunction>& ref) const {
    const auto& composed = ref.get();
    const auto& outer_derivative = std::make_shared<const ComposedFunction>(
        derivative(composed.outer()), composed.inner());
    return multiply_functions(outer_derivative, derivative(composed.inner()));
  }

  std::shared_ptr<const Function> operator()(
      const std::reference_wrapper<const AddFunctions>& ref) const {
    const auto& add = ref.get();
    return add_functions(derivative(add.lhs()), derivative(add.rhs()));
  }

  std::shared_ptr<const Function> operator()(
      const std::reference_wrapper<const SubtractFunctions>& ref) const {
    const auto& subtract = ref.get();
    return subtract_functions(derivative(subtract.lhs()),
                              derivative(subtract.rhs()));
  }

  std::shared_ptr<const Function> operator()(
      const std::reference_wrapper<const MultiplyFunctions>& ref) const {
    const auto& multiply = ref.get();
    return add_functions(
        multiply_functions(derivative(multiply.lhs()), multiply.rhs()),
        multiply_functions(multiply.lhs(), derivative(multiply.rhs())));
  }

  std::shared_ptr<const Function> operator()(
      const std::reference_wrapper<const DivideFunctions>& ref) const {
    const auto& divide = ref.get();
    const auto& numerator = subtract_functions(
        multiply_functions(derivative(divide.lhs()), divide.rhs()),
        multiply_functions(divide.lhs(), derivative(divide.rhs())));
    const auto& denominator = multiply_functions(divide.rhs(), divide.rhs());
    return divide_functions(numerator, denominator);
  }

  std::shared_ptr<const Function> operator()(
      const std::reference_wrapper<const Exponential>&) const {
    return f;
  }

  std::shared_ptr<const Function> operator()(
      const std::reference_wrapper<const Sin>&) const {
    return std::make_shared<const Cos>();
  }

  std::shared_ptr<const Function> operator()(
      const std::reference_wrapper<const Cos>&) const {
    const auto& minus_one =
        std::make_shared<const Polynomial>(std::vector{-1.0});
    const auto& sin = std::make_shared<const Sin>();
    return multiply_functions(minus_one, sin);
  }

  std::shared_ptr<const Function> operator()(
      const std::reference_wrapper<const Tan>&) const {
    const auto& one = std::make_shared<const Polynomial>(std::vector{1.0});
    const auto& cos = std::make_shared<const Cos>();
    return divide_functions(one, multiply_functions(cos, cos));
  }

  std::shared_ptr<const Function> operator()(
      const std::reference_wrapper<const Polynomial>& ref) const {
    const auto& coefficients = ref.get().coefficients();
    if (coefficients.size() == 1u) {
      return std::make_shared<const Polynomial>(std::vector{0.0});
    }

    std::vector<double> derivative_coefficients(coefficients.size() - 1u, 0.0);
    for (size_t i = 1u; i < coefficients.size(); ++i) {
      derivative_coefficients[i - 1u] =
          static_cast<double>(i) * coefficients[i];
    }
    return std::make_shared<const Polynomial>(
        std::move(derivative_coefficients));
  }
};

std::shared_ptr<const Function> derivative(
    const std::shared_ptr<const Function>& f) {
  return std::visit(derivative_visitor{f}, f->as_fvariant());
}

}  // namespace functions
