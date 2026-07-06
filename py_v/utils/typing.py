from typing import (
    Callable, 
    TypeAlias, 
    TypeVar,
    Literal
)

from numpy import ndarray, float64
from matplotlib.figure import Figure
from matplotlib.axes import Axes

#region =========================== generics ===================================

T_ = TypeVar("T_")
SingleOrList: TypeAlias = list[T_] | T_

F = TypeVar('F', bound=Callable)

NumericType: TypeAlias = int | float | float64

#endregion =====================================================================


#region ========================= numpy-types  =================================

NumpyVector = ndarray[tuple[int], float64]
NumpyMatrix = ndarray[tuple[int, int], float64]
DomainType: TypeAlias = list[NumericType, NumericType, int | None] | NumpyVector
PercentileType = list[int, int]


# f: R -> R
Real2Real: TypeAlias = Callable[[float], NumericType]
# f: R x R -> R
TimeXReal2Real: TypeAlias = Callable[[float, float], NumericType]

# a function f : R -> R^n
Real2Vector: TypeAlias = Callable[[float], NumpyVector]

# a function f: R^n -> R^n
Vector2Vector: TypeAlias = (Callable[[NumpyVector], NumpyVector] | 
                            Callable[[*tuple[float, ...]], float])

# a function f: R^n -> R^(n x n)
Vector2Matrix: TypeAlias = Callable[[NumpyVector], NumpyMatrix]

# a function f: R x R^n -> R^n
TimeXVector2Vector: TypeAlias = Callable[[float, NumpyVector], NumpyVector]

# np.mean, np.min, np.max, etc...
StatisticsNumpyFunction: TypeAlias = Callable[[ndarray], float64]

#endregion =====================================================================


#region ======================== plotting-types ================================

PltSubplotsType = tuple[Figure, Axes]
RGBColor: TypeAlias = tuple[float, float, float]
HowPlotType = Literal['plot', 'scatter', 'lines', 'marker', 'lines+markers']

#endregion =====================================================================


#region ============================ errors ====================================

class ConvergenceError(RuntimeError):
    pass

#endregion =====================================================================