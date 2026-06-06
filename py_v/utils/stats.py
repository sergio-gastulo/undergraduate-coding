from typing import Optional

import numpy as np
import pandas as pd

from .typing import (
    StatisticsNumpyFunction,
    SingleOrList,
)


def _percentile(p: int) -> StatisticsNumpyFunction:
    def f(x: np.ndarray) -> np.float64:
        return np.percentile(x, p)
    return f


def _parse_stat(
        stat: SingleOrList[int | str]
) -> dict[str, StatisticsNumpyFunction] | tuple[str, StatisticsNumpyFunction]:

    if isinstance(stat, list):
        return dict(map(_parse_stat, stat))

    if isinstance(stat, int):
        label = f"p_{stat}"
        return label, _percentile(stat)
    
    return stat, getattr(np, stat)


# TODO: migrate to pandas to use df.to_markdown()
def pprint_stats(
    x: np.ndarray,
    stats: Optional[list[str]] = None,
    *, 
    prec: int = 3,
) -> None:
    """
    Pretty print basic stats related to a given vector: min, p50 (median), 
    mean, p95, max.

    Arguments
    ---------
    x
        The array in question
    prec
        Floating point precision for printing the statistics: `f"{x:.{prec}e}"`.
    stats
        List of *additional* statistics to pretty-print. It must exist under the
        convention f'np.{stat}'. Integers are supported and are converted to 
        `np.percentile(:, int)`.

    Examples
    --------
    >>> import numpy as np
    >>> x = np.arange(0,1,0.1)
    >>> pprint_stats(x)
    ------------------------
    Statistics
    ------------------------
    min   |  0.00e+00
    mean  |  4.50e-01
    p_50  |  4.50e-01
    p_95  |  8.55e-01
    max   |  9.00e-01
    ------------------------
    >>> pprint_stats(x, ["std", 60])
    ------------------------
    Statistics
    ------------------------
    min   |  0.00e+00
    mean  |  4.50e-01
    p_50  |  4.50e-01
    p_95  |  8.55e-01
    max   |  9.00e-01
    std   |  2.87e-01
    p_60  |  5.40e-01
    ------------------------
    >>> pprint_stats(x, 5, ["std"])
    ------------------------
    Statistics
    ------------------------
    min   |  0.00000e+00
    mean  |  4.50000e-01
    p_50  |  4.50000e-01
    p_95  |  8.55000e-01
    max   |  9.00000e-01
    std   |  2.87228e-01
    ------------------------
    """

    statistics = ["min", "mean", 50, 95, "max"]
    if stats:
        statistics = [*statistics, *stats]

    print("-" * 24)
    print("Statistics")
    print("-" * 24)

    w = max(len(s) for s in statistics if isinstance(s, str))
    label_stats = _parse_stat(statistics)
    for label, stat in label_stats.items():
        print(f"  {label:<{w}}  |  {stat(x):.{prec}}")

    print("-" * 24)
