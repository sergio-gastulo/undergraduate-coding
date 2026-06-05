from typing import Optional

import numpy as np


# TODO: be able to parse p5 into np.percentile(x, 5)
def _parse_stats() -> None:
    pass


def pprint_stats(
    x: np.ndarray,
    stats: Optional[list[str]] = None
) -> None:
    """
    Pretty print basic stats related to a given vector: min, p50 (median), 
    mean, p95, max.

    Arguments
    ---------
    x
        The array in question
    stats
        List of *additional* statistics to pretty-print. It must exist under the
        convention f'np.{stat}'

    Examples
    --------
    >>> x = np.array([1,2,2,4,4,5,6])
    >>> pprint_stats(x)
    ----------
    Statistics
    ----------
    min:            1.00e+00
    median:         4.00e+00
    mean:           3.43e+00
    p95:            5.70e+00
    max:            6.00e+00
    >>> pprint_stats(x, ["cumsum", "std"])
    ----------
    Statistics
    ----------
    min:            1.00e+00
    median:         4.00e+00
    mean:           3.43e+00
    p95:            5.70e+00
    max:            6.00e+00
    cumsum:         [ 1  3  5  9 13 18 24]
    std:            1.6781914463529615
    """

    (min_, median, p95, max_) = np.percentile(x, [0, 50, 95, 100])
    text = (
        f"----------\n"
        f"Statistics\n"
        f"----------\n"
        f"min:\t\t{min_:.2e}\n"
        f"median:\t\t{median:.2e}\n"
        f"mean:\t\t{np.mean(x):.2e}\n"
        f"p95:\t\t{p95:.2e}\n"
        f"max:\t\t{max_:.2e}\n"
    )

    if stats:
        addstats = [
            f"{stat}:\t\t{getattr(np, stat)(x)}"
            for stat in stats
        ]
        as_text = "\n".join(addstats)
        text = f"{text}{as_text}"
    
    print(text)

