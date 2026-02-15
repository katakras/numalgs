#include <numalgs/errors.hpp>
#include <numalgs/results.hpp>
#include <numalgs/root_finding.hpp>

namespace root_finding {

namespace {
struct RootFindingVisitor {
  RootFindingVisitor(const std::shared_ptr<const functions::Function>& f)
      : f_(f) {}

  double operator()(
      const std::shared_ptr<const RootFindingConfigBisection>& config) const {
    return bisection(f_, config->a(), config->b());
  }

  const std::shared_ptr<const functions::Function>& f_;
};
}  // namespace

std::shared_ptr<const Result<double>> find_root(
    const std::shared_ptr<const functions::Function>& f,
    const RootFindingConfig& config) {
  try {
    const auto& result = std::visit(RootFindingVisitor(f), config);

    return std::make_shared<const Result<double>>(result,
                                                  ResultStatus::success);
  } catch (const NumalgsError& error) {
    return std::make_shared<const Result<double>>(0.0, ResultStatus::error);
  }
}

}  // namespace root_finding