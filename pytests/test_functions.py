import sys
sys.path.append("build")

import numalgs_py

def test_linear_polynomial():
    slope = 0.5
    intercept = 1.0
    p = numalgs_py.LinearPolynomial(slope, intercept)
    assert p(0.1) == slope * 0.1 + 1.0

def test_compose_functions():
    p1 = numalgs_py.LinearPolynomial(0.5, 1.0)
    p2 = numalgs_py.LinearPolynomial(0.3, 0.7)

    assert (p1(p2))(2.0) == p1(p2(2.0))

def test_add_functions():
    p1 = numalgs_py.LinearPolynomial(0.5, 1.0)
    p2 = numalgs_py.LinearPolynomial(0.3, 0.7)

    assert (p1 + p2)(2.0) == p1(2.0) + p2(2.0)

def test_add_linear_polynomials_types():
    p1 = numalgs_py.LinearPolynomial(0.5, 1.0)
    p2 = numalgs_py.LinearPolynomial(0.3, 0.7)

    assert type(p1 + p2) == type(p1)
    assert type(p1(p2)) != type (p1)    # we may want to change this