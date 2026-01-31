#include <memory>

namespace functions {

// Base class for function representations
class Function {
 public:
  virtual ~Function() = default;
  virtual double operator()(const double x) const = 0;
};

// Allows the evaluation of expressions of the kind f1(f2)(x)
class ComposedFunction : Function {
 public:
  ComposedFunction(std::shared_ptr<const Function> outer,
                   std::shared_ptr<const Function> inner);

  double operator()(const double x) const override;

 private:
  std::shared_ptr<const Function> outer_;
  std::shared_ptr<const Function> inner_;
};

// Allows the evaluation of expressions of the kind (f1 + f2)(x)
class AddFunctions : Function {
 public:
  AddFunctions(std::shared_ptr<const Function> lhs,
               std::shared_ptr<const Function> rhs);

  double operator()(const double x) const override;

 private:
  std::shared_ptr<const Function> lhs_;
  std::shared_ptr<const Function> rhs_;
};

// Simple polynomial y = a*x + b
class LinearPolynomial : public Function {
 public:
  LinearPolynomial(const double slope, const double intercept);

  double operator()(const double x) const override;

 private:
  double slope_;
  double intercept_;
};

}  // namespace functions