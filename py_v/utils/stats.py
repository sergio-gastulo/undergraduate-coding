from typing import Optional, Iterator

import numpy as np
import pandas as pd

from .typing import (
    StatisticsNumpyFunction,
    SingleOrList,
)


def _percentile(p: int) -> StatisticsNumpyFunction:
    def f(x: np.ndarray) -> np.float64:
        return np.percentile(x, p, axis=1)
    return f


def _parse_stat(
        stat: SingleOrList[int | str]
) -> Iterator[str, StatisticsNumpyFunction] | tuple[str, StatisticsNumpyFunction]:

    if isinstance(stat, list):
        return map(_parse_stat, stat)

    if isinstance(stat, int):
        label = f"p_{stat}"
        return label, _percentile(stat)
    
    def statf(x: np.ndarray) -> np.ndarray:
        func = getattr(np, stat)
        return func(x, axis=1)

    return stat, statf


def stats_df(
    x: SingleOrList[np.ndarray],
    stats: Optional[list[str]] = None,
) -> pd.DataFrame:
    """
    Construct a DataFrame reporting the min, max, mean, median (p50) and p95 for 
    each row of the 2D-array-like argument `x`.

    Arguments
    ---------
    x
        2D array on which the stastisticals functions will be mapped to.
    stats
        List of *additional* statistics to pretty-print. It must exist under the
        convention f'np.{stat}'. Integers are supported and are converted to 
        `np.percentile(:, int)`.

    Examples
    --------
    >>> import numpy as np
    >>> x = np.random.randn(3, 10)
    >>> pprint_stats(x)
            min      mean      p_50      p_95       max
    0 -1.696715  0.434434  0.438967  1.619619  1.702160
    1 -0.773983  0.305247  0.016222  1.831369  1.914967
    2 -1.210344 -0.050692 -0.352881  1.383726  1.525139
    >>> pprint_stats(x, [60, "std"])   
            min      mean      p_50      p_95       max      p_60       std
    0 -1.696715  0.434434  0.438967  1.619619  1.702160  1.042889  1.083228
    1 -0.773983  0.305247  0.016222  1.831369  1.914967  0.132857  0.832727
    2 -1.210344 -0.050692 -0.352881  1.383726  1.525139 -0.003831  0.890660
    """
    
    if isinstance(x, list):
        x = np.array(x)
    if x.ndim != 2:
        raise ValueError("Support for 2D arrays only.")

    statistics = ["min", "mean", 50, 95, "max"]
    if stats:
        # show interesting stats first
        statistics = [*stats, *statistics]

    df = pd.DataFrame({
        label: statf(x)
        for label, statf in _parse_stat(statistics)
    })
    return df
    