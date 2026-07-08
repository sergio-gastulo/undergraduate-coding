import numpy as np

from ..typing import (
    Real2Real,
    NumericType,
    ConvergenceError,
)

def newton_raphson(
        f: Real2Real,
        fprime: Real2Real,
        guess: NumericType,
        /,
        *,
        iterations: int = 5,
        tol: float = 1e-6,
        all: bool = False,
) -> NumericType:
    x = np.empty((iterations, ), np.float64)
    x[0] = guess
    i = 0
    err = 1.
    while i < iterations - 1 and  err > tol:
        x[i + 1] = x[i] - f(x[i]) / fprime(x[i])
        err = np.abs(f(x[i + 1]))
        i += 1

    if i < iterations or np.abs(err) <= tol:
        return x[: i + 1] if all else x[i]
    raise ConvergenceError(
        f"Solution could not converge to 0 with an error tolerance smaller"
        f"than '{tol}' after {iterations} iterations."
    )
