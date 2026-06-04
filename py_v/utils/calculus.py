from typing import Callable

import numpy as np


def discretize(
        sol: Callable,
        xx: np.ndarray,
        tt: np.ndarray,
) -> np.ndarray:
    """
    Plot the discretized solution `sol(xx_i, tt_j)` for all i,j. After 
    discretizing `solution`, relies on `plot_diff_matrices` to plot the 
    differences.

    Arguments
    ---------
    xx:
        Discretized 1D domain as a numpy array.
    tt:
        Discretized time domain.
    sol:
        Function to be discretized.
    """    
    disc = sol(xx[:, np.newaxis], tt[np.newaxis, :])
    return disc