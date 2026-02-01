#include <math.h>

#include <catch2/catch_test_macros.hpp>
#include <numalgs/functions.hpp>
#include <numalgs/root_finding.hpp>

TEST_CASE("test_basic_bisection") {
  const double slope = 0.5;
  const double intercept = 1.0;
  const auto& p =
      std::make_shared<const functions::LinearPolynomial>(slope, intercept);

  const double sol = root_finding::bisection(p, -5.0, 5.5);
  const double f_sol = (*p)(sol);

  REQUIRE(fabs(f_sol) < 1e-8);
}