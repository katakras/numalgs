#pragma once

#include <functional>
#include <memory>
#include <variant>

namespace functions {

class ComposedFunction;
class AddFunctions;
class LinearPolynomial;
using FVariant = std::variant<std::reference_wrapper<const ComposedFunction>,
                              std::reference_wrapper<const AddFunctions>,
                              std::reference_wrapper<const LinearPolynomial>>;

// Base class for function representations
class Function {
 public:
  virtual ~Function() = default;
  virtual double operator()(const double x) const = 0;
  virtual FVariant as_fvariant() const = 0;
};

// Allows the evaluation of expressions of the kind f1(f2)(x)
class ComposedFunction : public Function {
 public:
  ComposedFunction(std::shared_ptr<const Function> outer,
                   std::shared_ptr<const Function> inner);

  double operator()(const double x) const override;
  FVariant as_fvariant() const override { return std::cref(*this); }

 private:
  std::shared_ptr<const Function> outer_;
  std::shared_ptr<const Function> inner_;
};

// Allows the evaluation of expressions of the kind (f1 + f2)(x)
class AddFunctions : public Function {
 public:
  AddFunctions(std::shared_ptr<const Function> lhs,
               std::shared_ptr<const Function> rhs);

  double operator()(const double x) const override;
  FVariant as_fvariant() const override { return std::cref(*this); }

 private:
  std::shared_ptr<const Function> lhs_;
  std::shared_ptr<const Function> rhs_;
};

// Simple polynomial y = a*x + b
class LinearPolynomial : public Function {
 public:
  LinearPolynomial(const double slope, const double intercept);

  double operator()(const double x) const override;
  FVariant as_fvariant() const override { return std::cref(*this); }

  double slope() const { return slope_; }
  double intercept() const { return intercept_; }

 private:
  double slope_;
  double intercept_;
};

// Returns a function that adds two different functions together.
std::shared_ptr<const Function> add_functions(
    const std::shared_ptr<const Function>& lhs,
    const std::shared_ptr<const Function>& rhs);

}  // namespace functions