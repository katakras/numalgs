#pragma once

#include <numalgs/functions.hpp>
#include <numalgs/macros.hpp>

template <typename TResult>
class Result;

namespace root_finding {

class RootFindingConfigBisection {
 public:
  RootFindingConfigBisection(const double a, const double b);

  double a() const { return a_; }
  double b() const { return b_; }

 private:
  double a_;
  double b_;
};

class RootFindingConfigNewton {
 public:
  RootFindingConfigNewton(const double x0, const double tol = 1e-12,
                          const size_t max_iters = 1000);

  double x0() const { return x0_; }
  double tol() const { return tol_; }
  size_t max_iters() const { return max_iters_; }

 private:
  double x0_;
  double tol_;
  size_t max_iters_;
};

using RootFindingConfig =
    ConfigVariant<RootFindingConfigBisection, RootFindingConfigNewton>;

std::shared_ptr<const Result<double>> find_root(
    const std::shared_ptr<const functions::Function>& f,
    const RootFindingConfig& config);

double bisection(const std::shared_ptr<const functions::Function>& f, double a,
                 double b);

double newton(const std::shared_ptr<const functions::Function>& f_ptr,
              const double x0, const double tol, const size_t max_iters);

}  // namespace root_finding