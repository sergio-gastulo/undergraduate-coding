from typing import (
    Callable, 
    TypeAlias, 
    TypeVar
)

from numpy import ndarray, float64
from matplotlib.figure import Figure
from matplotlib.axes import Axes

#region =========================== generics ===================================

T_ = TypeVar("T_")
SingleOrList: TypeAlias = list[T_] | T_

F = TypeVar('F', bound=Callable)

NumericType: TypeAlias = int | float

#endregion =====================================================================


#region ========================= numpy-types  =================================

NumpyVector = ndarray[tuple[int], float64]
NumpyMatrix = ndarray[tuple[int, int], float64]
DomainType: TypeAlias = list[NumericType, NumericType, int | None] | NumpyVector
PercentileType = list[int, int]

# a function f : R -> R^n
ODESolution1D: TypeAlias = Callable[[float], NumpyMatrix | NumpyVector]

# np.mean, np.min, np.max, etc...
StatisticsNumpyFunction: TypeAlias = Callable[[ndarray], float64]

#endregion =====================================================================


#region ======================== plotting-types ================================

PltSubplotsType = tuple[Figure, Axes]
RGBColor: TypeAlias = tuple[float, float, float]

#endregion =====================================================================