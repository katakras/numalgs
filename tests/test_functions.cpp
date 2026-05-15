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

TEST_CASE("test_trigonometric_functions") {
  const functions::Sin sin;
  const functions::Cos cos;
  const functions::Tan tan;

  REQUIRE(fabs(std::sin(0.5) - sin(0.5)) < 1e-12);
  REQUIRE(fabs(std::cos(0.5) - cos(0.5)) < 1e-12);
  REQUIRE(fabs(std::tan(0.5) - tan(0.5)) < 1e-12);
}

TEST_CASE("test_trigonometric_composition") {
  const auto& sin = std::make_shared<const functions::Sin>();
  const auto& cos = std::make_shared<const functions::Cos>();
  const auto& tan = std::make_shared<const functions::Tan>();
  const auto& polynomial =
      std::make_shared<const functions::Polynomial>(std::vector{1.0, 2.0});

  const auto& sin_composed = functions::ComposedFunction(sin, polynomial);
  const auto& cos_composed = functions::ComposedFunction(cos, polynomial);
  const auto& tan_composed = functions::ComposedFunction(tan, polynomial);

  REQUIRE(fabs(std::sin((*polynomial)(0.5)) - sin_composed(0.5)) < 1e-12);
  REQUIRE(fabs(std::cos((*polynomial)(0.5)) - cos_composed(0.5)) < 1e-12);
  REQUIRE(fabs(std::tan((*polynomial)(0.5)) - tan_composed(0.5)) < 1e-12);
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

  const auto& c = functions::multiply_functions(p, q);
  const double expected = 4 * 0.1 * 0.1 - 0.25;
  const double actual = (*c)(0.1);
  REQUIRE(fabs(expected - actual) < 1e-12);
  REQUIRE(std::dynamic_pointer_cast<const functions::Polynomial>(c) != nullptr);
}

TEST_CASE("test_generic_multiplication") {
  const auto& p =
      std::make_shared<const functions::Polynomial>(std::vector{0.5, 2.0});
  const auto& e = std::make_shared<const functions::Exponential>();

  const auto& c = functions::multiply_functions(p, e);
  const double expected = (*p)(0.1) * (*e)(0.1);
  const double actual = (*c)(0.1);
  REQUIRE(fabs(expected - actual) < 1e-12);
  REQUIRE(std::dynamic_pointer_cast<const functions::MultiplyFunctions>(c) !=
          nullptr);
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

TEST_CASE("test_polynomial_derivative") {
  const auto& p =
      std::make_shared<const functions::Polynomial>(std::vector{1.0, 2.0, 3.0});
  const auto& dp = functions::derivative(p);

  REQUIRE(fabs((*dp)(2.0) - 14.0) < 1e-12);
  REQUIRE(std::dynamic_pointer_cast<const functions::Polynomial>(dp) != nullptr);

  const auto& constant =
      std::make_shared<const functions::Polynomial>(std::vector{5.0});
  const auto& d_constant = functions::derivative(constant);
  REQUIRE(fabs((*d_constant)(2.0)) < 1e-12);
}

TEST_CASE("test_basic_function_derivatives") {
  const auto& exponential = std::make_shared<const functions::Exponential>();
  const auto& sin = std::make_shared<const functions::Sin>();
  const auto& cos = std::make_shared<const functions::Cos>();
  const auto& tan = std::make_shared<const functions::Tan>();

  REQUIRE(fabs((*functions::derivative(exponential))(0.5) - std::exp(0.5)) <
          1e-12);
  REQUIRE(fabs((*functions::derivative(sin))(0.5) - std::cos(0.5)) < 1e-12);
  REQUIRE(fabs((*functions::derivative(cos))(0.5) + std::sin(0.5)) < 1e-12);
  REQUIRE(fabs((*functions::derivative(tan))(0.5) -
               1.0 / (std::cos(0.5) * std::cos(0.5))) < 1e-12);
}

TEST_CASE("test_expression_derivatives") {
  const double x = 0.5;
  const auto& p =
      std::make_shared<const functions::Polynomial>(std::vector{1.0, 2.0});
  const auto& q =
      std::make_shared<const functions::Polynomial>(std::vector{3.0, 4.0});
  const auto& exponential = std::make_shared<const functions::Exponential>();
  const auto& sin = std::make_shared<const functions::Sin>();

  const auto& add = functions::add_functions(p, exponential);
  REQUIRE(fabs((*functions::derivative(add))(x) - (2.0 + std::exp(x))) <
          1e-12);

  const auto& subtract = functions::subtract_functions(p, exponential);
  REQUIRE(fabs((*functions::derivative(subtract))(x) - (2.0 - std::exp(x))) <
          1e-12);

  const auto& multiply = functions::multiply_functions(p, exponential);
  REQUIRE(fabs((*functions::derivative(multiply))(x) -
               (2.0 * std::exp(x) + (*p)(x) * std::exp(x))) < 1e-12);

  const auto& divide = functions::divide_functions(p, q);
  const double expected_divide = (2.0 * (*q)(x) - (*p)(x) * 4.0) /
                                 ((*q)(x) * (*q)(x));
  REQUIRE(fabs((*functions::derivative(divide))(x) - expected_divide) < 1e-12);

  const auto& composed =
      std::make_shared<const functions::ComposedFunction>(sin, p);
  REQUIRE(fabs((*functions::derivative(composed))(x) -
               std::cos((*p)(x)) * 2.0) < 1e-12);
}
