import sys
sys.path.append("build")

import numalgs_py

def test_polynomial():
    slope = 0.5
    intercept = 1.0
    p = numalgs_py.Polynomial([intercept,slope])
    assert p(0.1) == slope * 0.1 + 1.0

def test_polynomial_str():
    p = numalgs_py.Polynomial([1.0, 0.0, 2.0])
    p_str = str(p)
    assert p_str == "1.000000 +2.000000*x^2"

def test_compose_functions():
    p1 = numalgs_py.Polynomial([1.0, 0.5])
    p2 = numalgs_py.Polynomial([0.7, 0.3])

    assert (p1(p2))(2.0) == p1(p2(2.0))

def test_add_functions():
    p1 = numalgs_py.Polynomial([1.0, 0.5])
    p2 = numalgs_py.Polynomial([0.7, 0.3])

    assert (p1 + p2)(2.0) == p1(2.0) + p2(2.0)

def test_add_polynomials_types():
    p1 = numalgs_py.Polynomial([1.0, 0.5])
    p2 = numalgs_py.Polynomial([0.7, 0.3])

    assert type(p1 + p2) == type(p1)
    assert type(p1(p2)) != type (p1)    # we may want to change this

def test_mult_functions():
    p1 = numalgs_py.Polynomial([1.0, 0.5])
    p2 = numalgs_py.Polynomial([0.7, 0.3])

    assert (p1 * p2)(2.0) == p1(2.0) * p2(2.0)