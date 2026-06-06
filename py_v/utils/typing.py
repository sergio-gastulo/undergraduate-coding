from typing import (
    Optional, 
    Callable, 
    TypeAlias, 
    TypeVar
)

from numpy import ndarray, float64


StatisticsNumpyFunction: TypeAlias = Callable[[ndarray], float64]

T_ = TypeVar("T_")
SingleOrList: TypeAlias = list[T_] | T_

F = TypeVar('F', bound=Callable)
