import sys
sys.path.append("build")

from helpers import assert_relative_close
import numalgs_py

def test_bisection():
    slope = 0.5
    intercept = 1.0
    p = numalgs_py.Polynomial([intercept,slope])

    bisection_config = numalgs_py.RootFindingConfigBisection(-5.5, 5.0)

    result = numalgs_py.find_root(p, bisection_config)

    assert result.status() == numalgs_py.ResultStatus.success
    assert_relative_close(p(result.value()), 0.0, abs_tol=1e-8)

def test_newton_rhapson():
    slope = 0.5
    intercept = 1.0
    p = numalgs_py.Polynomial([intercept,slope])

    newton_rhapson_config = numalgs_py.RootFindingConfigNewton(1.0, 1e-12, 400)

    result = numalgs_py.find_root(p, newton_rhapson_config)

    assert result.status() == numalgs_py.ResultStatus.success
    assert_relative_close(p(result.value()), 0.0, abs_tol=1e-8)

