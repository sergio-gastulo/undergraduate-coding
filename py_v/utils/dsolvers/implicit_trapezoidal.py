import numpy as np

from ..typing import (
    NumericType,
    NumpyVector,
    TimeXReal2Real,
)


def newton(
        f: TimeXReal2Real,
        fy: TimeXReal2Real,
        ti: NumericType,
        ti_: NumericType,  # t_{i+1}
        y: NumericType,
        /,
        *,
        iterations: int = 5,
) -> NumericType:

    stepsize = ti_ - ti
    x = y + stepsize * f(ti, y)
    for _ in range(iterations):
        numerator = -x + y + (.5 * stepsize) * (f(ti, y) + f(ti_, x))
        denominator = -1 + (.5 * stepsize) * (fy(ti_, x))
        x -= numerator/denominator
    return x


def trapezoidal_method(
        f: TimeXReal2Real,
        fy: TimeXReal2Real,
        init: NumericType,
        tt: NumpyVector, # it better be a linspace
        /,
        *,
        newtoniters: int = 6
) -> NumpyVector:
    """
    Solve the differential equation y' = f(t, y), with y(a) = init and a <= t 
    <= b.

    Arguments
    ---------
    f
        A mapping from `R x R` to `R`.
    fy
        The partial derivative of `f` with respect to `y`. A mapping from 
        `R x R` to `R`.
    init
        Initial condition `y(a) = init`.
    tt
        The discretized steps on which the iterative schema will be evaluated. 
        It must be a `np.linspace(a, b, points)`, but not type-checked.
    """
    n, _ = tt.shape
    y = np.empty(n, NumericType)
    y[0] = init
    for i in range(1, n):
        y[i] = newton(
            f, fy, tt[i-1], tt[i], y[i-1], 
            iterations=newtoniters,
        )
    return y