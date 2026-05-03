import math


def assert_relative_close(actual, expected, rel_tol=1e-12, abs_tol=1e-12):
    assert math.isclose(actual, expected, rel_tol=rel_tol, abs_tol=abs_tol), (
        f"{actual} is not close to {expected}"
    )
