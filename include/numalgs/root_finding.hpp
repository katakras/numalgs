#pragma once

#include <numalgs/functions.hpp>

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

using RootFindingConfig =
    std::variant<std::shared_ptr<const RootFindingConfigBisection>>;

std::shared_ptr<const Result<double>> find_root(
    const std::shared_ptr<const functions::Function>& f,
    const RootFindingConfig& config);

double bisection(const std::shared_ptr<const functions::Function>& f, double a,
                 double b);

}  // namespace root_finding