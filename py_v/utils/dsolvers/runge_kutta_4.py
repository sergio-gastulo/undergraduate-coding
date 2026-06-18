import numpy as np

from ..typing import (
    NumpyVector,
    NumericType,
    Real2Real,
    Real2Vector,
)


def runge_kutta_4(
        f: Real2Real | Real2Vector,
        initialcond: NumericType | NumpyVector,
        tt: NumpyVector, # it better be a np.linspace
) -> np.ndarray:
    n, = tt.shape
    h = tt[1] - tt[0]  # it better be a np.linspace
    try:
        dim, = initialcond.shape
        udim = (n, dim)
    except AttributeError:
        udim = (n, )
    uu = np.empty(udim, np.float64)
    uu[0] = initialcond
    for i in range(n - 1):
        k1 = f(tt[i]      , uu[i])
        k2 = f(tt[i] + h/2, uu[i] + k1*h/2)
        k3 = f(tt[i] + h/2, uu[i] + k2*h/2)
        k4 = f(tt[i] + h  , uu[i] + k3*h)
        uu[i + 1] = uu[i] + (h / 6)*(k1 + 2*k2 + 2*k3 + k4)
    return uu