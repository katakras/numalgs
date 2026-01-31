#include <math.h>

#include <catch2/catch_test_macros.hpp>
#include <numalgs/functions.hpp>

TEST_CASE("test_linear_polynomial") {
  const double slope = 0.5;
  const double intercept = 1.0;
  functions::LinearPolynomial p(slope, intercept);

  REQUIRE(slope * 0.1 + intercept == p(0.1));
}

TEST_CASE("test_composition") {
  // expected expression is y = 2*(2*x - 0.5) + 0.5 = 4*x -0.5
  const auto& p = std::make_shared<const functions::LinearPolynomial>(2.0, 0.5);
  const auto& q =
      std::make_shared<const functions::LinearPolynomial>(2.0, -0.5);

  const auto& c = functions::ComposedFunction(p, q);
  const double expected = 4 * 0.1 - 0.5;
  const double actual = c(0.1);
  REQUIRE(expected == actual);
}

TEST_CASE("test_addition") {
  // expected expression is y = 2*x - 0.5 + 2*x + 0.5 = 4*x
  const auto& p = std::make_shared<const functions::LinearPolynomial>(2.0, 0.5);
  const auto& q =
      std::make_shared<const functions::LinearPolynomial>(2.0, -0.5);

  const auto& c = functions::AddFunctions(p, q);
  const double expected = 4 * 0.1;
  const double actual = c(0.1);
  REQUIRE(fabs(expected - actual) < 1e-12);
}