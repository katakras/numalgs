import sys
sys.path.append("build")

import numpy as np
import numalgs_py

def test_bisection():
    slope = 0.5
    intercept = 1.0
    p = numalgs_py.Polynomial([intercept,slope])

    bisection_config = numalgs_py.RootFindingConfigBisection(-5.5, 5.0)

    result = numalgs_py.find_root(p, bisection_config)

    assert result.status() == numalgs_py.ResultStatus.success
    assert np.fabs(p(result.value())) < 1e-8


