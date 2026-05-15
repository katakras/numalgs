import sys
sys.path.append("build")

import math
from helpers import assert_relative_close
import numalgs_py

def test_polynomial():
    slope = 0.5
    intercept = 1.0
    p = numalgs_py.Polynomial([intercept,slope])
    assert_relative_close(p(0.1), slope * 0.1 + 1.0)

def test_polynomial_str():
    p = numalgs_py.Polynomial([1.0, 0.0, 2.0])
    p_str = str(p)
    assert p_str == "1.000000 +2.000000*x^2"

def test_compose_functions():
    p1 = numalgs_py.Polynomial([1.0, 0.5])
    p2 = numalgs_py.Polynomial([0.7, 0.3])

    assert_relative_close((p1(p2))(2.0), p1(p2(2.0)))

def test_exponential():
    e = numalgs_py.Exponential()

    assert_relative_close(e(5.0), math.exp(5.0))

def test_exponential_str():
    e = numalgs_py.Exponential()

    assert str(e) == "exp(x)"

def test_exponential_composition():
    e = numalgs_py.Exponential()
    p = numalgs_py.Polynomial([1.0, 2.0])

    assert_relative_close(e(p)(3.0), math.exp(p(3.0)))

def test_trigonometric_functions():
    sin = numalgs_py.Sin()
    cos = numalgs_py.Cos()
    tan = numalgs_py.Tan()

    assert_relative_close(sin(0.5), math.sin(0.5))
    assert_relative_close(cos(0.5), math.cos(0.5))
    assert_relative_close(tan(0.5), math.tan(0.5))

def test_trigonometric_functions_str():
    sin = numalgs_py.Sin()
    cos = numalgs_py.Cos()
    tan = numalgs_py.Tan()

    assert str(sin) == "sin(x)"
    assert str(cos) == "cos(x)"
    assert str(tan) == "tan(x)"

def test_trigonometric_composition():
    sin = numalgs_py.Sin()
    cos = numalgs_py.Cos()
    tan = numalgs_py.Tan()
    p = numalgs_py.Polynomial([1.0, 2.0])

    assert_relative_close(sin(p)(0.5), math.sin(p(0.5)))
    assert_relative_close(cos(p)(0.5), math.cos(p(0.5)))
    assert_relative_close(tan(p)(0.5), math.tan(p(0.5)))

def test_add_functions():
    p1 = numalgs_py.Polynomial([1.0, 0.5])
    p2 = numalgs_py.Polynomial([0.7, 0.3])

    assert_relative_close((p1 + p2)(2.0), p1(2.0) + p2(2.0))

def test_add_polynomials_types():
    p1 = numalgs_py.Polynomial([1.0, 0.5])
    p2 = numalgs_py.Polynomial([0.7, 0.3])

    assert type(p1 + p2) == type(p1)
    assert type(p1(p2)) != type (p1)    # we may want to change this

def test_mult_functions():
    p1 = numalgs_py.Polynomial([1.0, 0.5])
    p2 = numalgs_py.Polynomial([0.7, 0.3])

    assert_relative_close((p1 * p2)(2.0), p1(2.0) * p2(2.0))
    assert type(p1 * p2) == type(p1)

def test_subtract_functions():
    p1 = numalgs_py.Polynomial([1.0, 0.5])
    p2 = numalgs_py.Polynomial([0.7, 0.3])

    assert_relative_close((p1 - p2)(2.0), p1(2.0) - p2(2.0))
    assert type(p1 - p2) == type(p1)

def test_divide_functions():
    p1 = numalgs_py.Polynomial([1.0, 0.5])
    p2 = numalgs_py.Polynomial([0.7, 0.3])

    assert_relative_close((p1 / p2)(2.0), p1(2.0) / p2(2.0))
    assert type(p1 / p2) != type(p1)

def test_polynomial_derivative():
    p = numalgs_py.Polynomial([1.0, 2.0, 3.0])

    assert_relative_close(p.derivative()(2.0), 14.0)
    assert_relative_close(numalgs_py.derivative(p)(2.0), 14.0)

    constant = numalgs_py.Polynomial([5.0])
    assert_relative_close(constant.derivative()(2.0), 0.0)

def test_basic_function_derivatives():
    exponential = numalgs_py.Exponential()
    sin = numalgs_py.Sin()
    cos = numalgs_py.Cos()
    tan = numalgs_py.Tan()

    assert_relative_close(exponential.derivative()(0.5), math.exp(0.5))
    assert_relative_close(sin.derivative()(0.5), math.cos(0.5))
    assert_relative_close(cos.derivative()(0.5), -math.sin(0.5))
    assert_relative_close(tan.derivative()(0.5), 1.0 / (math.cos(0.5) ** 2))

def test_expression_derivatives():
    x = 0.5
    p = numalgs_py.Polynomial([1.0, 2.0])
    q = numalgs_py.Polynomial([3.0, 4.0])
    exponential = numalgs_py.Exponential()
    sin = numalgs_py.Sin()

    assert_relative_close((p + exponential).derivative()(x), 2.0 + math.exp(x))
    assert_relative_close((p - exponential).derivative()(x), 2.0 - math.exp(x))
    assert_relative_close(
        (p * exponential).derivative()(x),
        2.0 * math.exp(x) + p(x) * math.exp(x),
    )

    expected_divide = (2.0 * q(x) - p(x) * 4.0) / (q(x) * q(x))
    assert_relative_close((p / q).derivative()(x), expected_divide)
    assert_relative_close(sin(p).derivative()(x), math.cos(p(x)) * 2.0)
