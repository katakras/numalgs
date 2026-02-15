#include <math.h>

#include <catch2/catch_test_macros.hpp>
#include <numalgs/functions.hpp>
#include <numalgs/results.hpp>
#include <numalgs/root_finding.hpp>

namespace {
std::shared_ptr<const functions::Polynomial> dummy_polynomial() {
  const double slope = 0.5;
  const double intercept = 1.0;
  return std::make_shared<const functions::Polynomial>(std::vector{0.5, 1.0});
}
}  // namespace

TEST_CASE("test_basic_bisection") {
  const auto& p = dummy_polynomial();

  const double sol = root_finding::bisection(p, -5.0, 5.5);
  const double f_sol = (*p)(sol);

  REQUIRE(fabs(f_sol) < 1e-8);
}

TEST_CASE("test_basic_bisection_via_generic_interface") {
  const auto& p = dummy_polynomial();
  const auto& bisection_config =
      std::make_shared<const root_finding::RootFindingConfigBisection>(-5.0,
                                                                       5.5);
  const auto& result = root_finding::find_root(p, bisection_config);

  const double f_sol = (*p)(result->value().value());

  REQUIRE(fabs(f_sol) < 1e-8);
}