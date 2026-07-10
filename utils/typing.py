from typing import (
    Callable, 
    TypeAlias, 
    TypeVar,
    Literal,
)

from numpy import ndarray

#region =========================== generics ===================================

T_ = TypeVar("T_")
SingleOrList: TypeAlias = list[T_] | T_
F = TypeVar('F', bound=Callable)

#endregion =====================================================================


#region ========================= vector types =================================

PythonVector = tuple[float, ...]
NumpyVector = ndarray[tuple[int], float]
NumpyMatrix = ndarray[tuple[int, int], float]
DomainType: TypeAlias = list[float, float, int | None] | NumpyVector
PercentileType = list[int, int]

RealMapping: TypeAlias = Callable[[float], T_]  # R -> ran
TimeRealMapping: TypeAlias = Callable[[float, float], T_]  # R^>0 x R -> ran
VectorMapping: TypeAlias = (Callable[[*PythonVector], T_] | 
                            Callable[[NumpyVector], T_])  # R^n -> ran

# R^>0 x R^n -> ran
TimeVectorMapping: TypeAlias = Callable[[float, NumpyVector | PythonVector], T_]

# np.mean, np.min, np.max, etc...
StatisticsNumpyFunction: TypeAlias = Callable[[NumpyVector | PythonVector], float]

#endregion =====================================================================


#region ======================== plotting-types ================================

RGBColor: TypeAlias = tuple[float, float, float]
type HowPlotType = Literal['plot', 'scatter', 'lines', 'marker', 'lines+markers']

#endregion =====================================================================


#region ============================ errors ====================================

class ConvergenceError(RuntimeError):
    pass

#endregion =====================================================================