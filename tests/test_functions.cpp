#include <math.h>

#include <cmath>
#include <memory>

#include <catch2/catch_test_macros.hpp>
#include <numalgs/functions.hpp>

TEST_CASE("test_polynomial") {
  const auto& coefficients = std::vector{1.0, 0.0, 0.5};
  functions::Polynomial p(coefficients);

  REQUIRE(p(1.0) == 1.0 + 0.5);
  REQUIRE(p(2.0) == 1.0 + 0.5 * 2.0 * 2.0);
  REQUIRE(p(3.0) == 1.0 + 0.5 * 3.0 * 3.0);
}

TEST_CASE("test_composition") {
  // expected expression is y = 2*(2*x - 0.5) + 0.5 = 4*x -0.5
  const auto& p =
      std::make_shared<const functions::Polynomial>(std::vector{0.5, 2.0});
  const auto& q =
      std::make_shared<const functions::Polynomial>(std::vector{-0.5, 2.0});

  const auto& c = functions::ComposedFunction(p, q);
  const double expected = 4 * 0.1 - 0.5;
  const double actual = c(0.1);
  REQUIRE(expected == actual);
}

TEST_CASE("test_exponential") {
  const functions::Exponential exponential;
  const double expected = std::exp(5.0);
  const double actual = exponential(5.0);
  REQUIRE(fabs(expected - actual) < 1e-12);
}

TEST_CASE("test_exponential_composition") {
  const auto& exponential = std::make_shared<const functions::Exponential>();
  const auto& polynomial =
      std::make_shared<const functions::Polynomial>(std::vector{1.0, 2.0});

  const auto& composed = functions::ComposedFunction(exponential, polynomial);
  const double expected = std::exp((*polynomial)(3.0));
  const double actual = composed(3.0);
  REQUIRE(fabs(expected - actual) < 1e-12);
}

TEST_CASE("test_addition") {
  // expected expression is y = 2*x - 0.5 + 2*x + 0.5 = 4*x
  const auto& p =
      std::make_shared<const functions::Polynomial>(std::vector{0.5, 2.0});
  const auto& q =
      std::make_shared<const functions::Polynomial>(std::vector{-0.5, 2.0});

  const auto& c = functions::AddFunctions(p, q);
  const double expected = 4 * 0.1;
  const double actual = c(0.1);
  REQUIRE(fabs(expected - actual) < 1e-12);
}

TEST_CASE("test_multiplication") {
  // expected expression is y = (2*x - 0.5) * (2*x + 0.5) = 4*x^2 - 0.25
  const auto& p =
      std::make_shared<const functions::Polynomial>(std::vector{0.5, 2.0});
  const auto& q =
      std::make_shared<const functions::Polynomial>(std::vector{-0.5, 2.0});

  const auto& c = functions::MultiplyFunctions(p, q);
  const double expected = 4 * 0.1 * 0.1 - 0.25;
  const double actual = c(0.1);
  REQUIRE(fabs(expected - actual) < 1e-12);
}

TEST_CASE("test_subtraction") {
  // expected expression is y = 2*x + 0.5 - (2*x - 0.5) = 1
  const auto& p =
      std::make_shared<const functions::Polynomial>(std::vector{0.5, 2.0});
  const auto& q =
      std::make_shared<const functions::Polynomial>(std::vector{-0.5, 2.0});

  const auto& c = functions::subtract_functions(p, q);
  const double expected = 1.0;
  const double actual = (*c)(0.1);
  REQUIRE(fabs(expected - actual) < 1e-12);
}

TEST_CASE("test_division") {
  // expected expression is y = (2*x + 1) / (x + 1)
  const auto& p =
      std::make_shared<const functions::Polynomial>(std::vector{1.0, 2.0});
  const auto& q =
      std::make_shared<const functions::Polynomial>(std::vector{1.0, 1.0});

  const auto& c = functions::divide_functions(p, q);
  const double expected = (2.0 * 0.5 + 1.0) / (0.5 + 1.0);
  const double actual = (*c)(0.5);
  REQUIRE(fabs(expected - actual) < 1e-12);
}
