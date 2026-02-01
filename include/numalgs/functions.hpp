#pragma once

#include <functional>
#include <memory>
#include <variant>

namespace functions {

class ComposedFunction;
class AddFunctions;
class Polynomial;
using FVariant = std::variant<std::reference_wrapper<const ComposedFunction>,
                              std::reference_wrapper<const AddFunctions>,
                              std::reference_wrapper<const Polynomial>>;

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

// Generic polynomial y = \sum_{i=0}^n a_i * x^i
class Polynomial : public Function {
 public:
  Polynomial(std::vector<double> coefficients);

  double operator()(const double x) const override;
  FVariant as_fvariant() const override { return std::cref(*this); }

  const auto& coefficients() const { return coefficients_; }

 private:
  std::vector<double> coefficients_;
};

// Returns a function that adds two different functions together.
std::shared_ptr<const Function> add_functions(
    const std::shared_ptr<const Function>& lhs,
    const std::shared_ptr<const Function>& rhs);

}  // namespace functions