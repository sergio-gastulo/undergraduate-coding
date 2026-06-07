from typing import (
    Callable, 
    TypeAlias, 
    TypeVar
)

from numpy import ndarray, float64


#region =========================== generics ===================================

T_ = TypeVar("T_")
SingleOrList: TypeAlias = list[T_] | T_

F = TypeVar('F', bound=Callable)

NumericType: TypeAlias = int | float

#endregion =====================================================================


#region ========================= numpy-types  =================================

PercentileType = list[int, int]
StatisticsNumpyFunction: TypeAlias = Callable[[ndarray], float64]
RescaleType: TypeAlias = list[int, int] | ndarray

# a function f : R -> R^n
ODESolution1D: TypeAlias = Callable[[float], ndarray]

DomainType: TypeAlias = list[NumericType, NumericType, int | None] | ndarray


#endregion =====================================================================