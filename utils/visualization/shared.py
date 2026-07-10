from typing import Optional

import numpy as np
import plotly
from IPython.display import display, HTML

from utils.typing import (DomainType,
                          NumpyVector,
                          NumpyMatrix,
                          HowPlotType,)

#region =========================== globals  ===================================

GOLDEN_RATIO = 1.618033 
DARK_THEME = "plotly_dark"

#endregion =====================================================================


def init() -> None:
    """Set initial configurations for better plotting"""
    
    # https://stackoverflow.com/a/76599370/29272030
    plotly.offline.init_notebook_mode()
    display(HTML('<script type="text/javascript"'
                 'async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_SVG">'
                 '</script>'
    ))


def get_domain(domain: DomainType, dim: Optional[int] = None) -> NumpyVector:
    if isinstance(domain, list):        
        return np.linspace(*domain, dim)
    
    if isinstance(domain, np.ndarray):
        return domain
    
    raise TypeError(
        f"Only lists or numpy ndarrays are allowed. Got: '{type(domain)}'.")


def validate_plottable(
        x: NumpyVector,
        y: NumpyVector | NumpyMatrix,
) -> tuple[NumpyVector, NumpyVector | NumpyMatrix]:
    """
    Check that x, y have plottable dimensions. Returns x, y moved properly 
    formatted.

    Arguments
    ---------
    x
        A 1D `numpy.ndarray`.
    y
        A 1D or 2D `numpy.ndarray`. If the former, then `x` and `y` must have 
        the same shape. If the latter, then the number of columns or rows of `y`
        must have the same length as `x`. If the same number of rows is checked,
        then `y` is transposed.
    """
    if not (isinstance(x, np.ndarray) and isinstance(y, np.ndarray)):
        raise TypeError(
            f"Can't plot non-NumPy arrays. Got: {type(x)=}, {type(y)=}."
        )

    n, *_ = x.shape
    *rows, cols = y.shape
    check_depth = (x.ndim == 1) and (y.ndim in frozenset((1, 2)))
    if check_depth:
        if n == cols:
            return x, y
        elif n == rows[0]:
            # will this raise unwanted bugs?
            return x, y.T
    
    raise ValueError(
        "Can't plot arrays with missmatching dimensions: "
        f"{x.shape=} and {y.shape=}."
    )


def get_plotting_mode(how: HowPlotType) -> str:
    
    if not how or how in {'plot', 'lines'}:
        return 'lines'
    if how in {'scatter', 'markers'}:
        return 'markers'
    if how == 'lines+markers':
        return how

    raise ValueError(f"Rule must hold: {how=!r} \\in {HowPlotType!r}.")
