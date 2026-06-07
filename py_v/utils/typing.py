from typing import (
    Optional, 
    Callable, 
    TypeAlias, 
    TypeVar
)

from numpy import ndarray, float64



#region =========================== generics ===================================

T_ = TypeVar("T_")
SingleOrList: TypeAlias = list[T_] | T_
F = TypeVar('F', bound=Callable)

#endregion =====================================================================


#region ========================= numpy-types  =================================

PercentileType = list[int]
StatisticsNumpyFunction: TypeAlias = Callable[[ndarray], float64]
DomainType: TypeAlias = list[int, int] | ndarray

#endregion =====================================================================