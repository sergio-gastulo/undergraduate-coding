from typing import Optional, Any, Literal, Callable

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.figure import Figure
from matplotlib.image import AxesImage
from matplotlib.axes import Axes
from matplotlib import rcParams

from .utils import SingleOrList, dl_to_ld
from .typing import (
    PercentileType, 
    DomainType, 
    ODESolution1D,
    NumpyVector,
    NumpyMatrix,
    PltSubplotsType,
)
from .colors import ax_lighten


def init() -> None:
    """Set initial configurations for better plotting"""

    plt.style.use('dark_background')
    rcParams['text.usetex'] = True
    rcParams['font.family'] = 'serif'
    rcParams['text.latex.preamble'] = r'\usepackage{amsmath}'


def latex_float(
        f: float, 
        prec: int = 2
) -> str:
    """Convert a float into its latex representation base \\cdot 10^exp."""
    float_str = f"{f:.{prec}e}"
    base, exponent = float_str.split('e')
    latex = f"{base} \\cdot 10^{{{exponent}}}"
    return latex


def matrix_plot(
        mat: NumpyMatrix,
        percentiles: PercentileType = None,
        **kwargs,
) -> PltSubplotsType:
    """
    Plot a matrix, clipping the colormap range to i-th and j-th percentile 
    to reduce distortion.
    
    Arguments
    ---------
    mat
        The `numpy.ndarray` of depth 2 to be plotted (not type-checked).
    percentiles
        The percentiles to clip the range. If `None` is provided, no statistical
        information is shown on the plot.
    kwargs
        Directly passed to `matplotlib.axes.Axes.imshow`.
    """

    if percentiles is not None:
        i, j = percentiles
        pi, pj = np.percentile(mat, percentiles)
    else:
        pi = pj = None
    mean = np.mean(mat)
    fig, ax = plt.subplots()
    im = ax.imshow(
        mat, 
        vmin=pi, 
        vmax=pj,
        aspect='auto',
        **kwargs,
    )
    if percentiles:
        xlabel = f"Stats: \
            $p_{{{i}}}={latex_float(pi)}$, \
            $\\mathrm{{mean}}={latex_float(mean)}$, \
            $p_{{{j}}}={latex_float(pj)}$"
        fig.supxlabel(xlabel, ha='center')

    fig.colorbar(im)
    fig.suptitle("Matrix Plot")
    return fig, ax


def matrix_diff_plot(
        mat1: NumpyMatrix,
        mat2: NumpyMatrix,
        percentiles: PercentileType,
        **kwargs,
) -> PltSubplotsType:
    """
    Arguments
    ---------
    mat1, mat2
        `numpy.ndarray`s with same shape (`ValueError` raised otherwise).
    kwargs
        Key-word arguments passed to `mat_plot`.
    """

    if mat1.shape != mat2.shape: 
        raise ValueError(
            f"Different shapes {mat1.shape} and {mat2.shape} found."
        )

    mabs = np.abs(mat1 - mat2)
    fig, ax = matrix_plot(
        mabs, percentiles, 
        cmap=plt.get_cmap('hot'), **kwargs
    )
    i, *_, j = percentiles
    title = f"Elementwise Difference " \
            f"$\\|A_1 - A_2\\|_2$ " \
            f"(Clipped to $[p_{{{i}}},\\, p_{{{j}}}]$)"
    fig.suptitle(title)
    return fig, ax


def get_domain(
        dim: int,
        domain: DomainType,
) -> NumpyVector:
    
    if isinstance(domain, list):
        linspace = np.linspace(*domain)
        return linspace

    n_domain, = domain.shape
    if dim == n_domain:
        return domain 
    raise ValueError(
        f"Domain and array do not have the same length: {dim=}, {n_domain=}."
    )



def _check_same_dims(
        x: list[np.ndarray]
) -> None:
    dimx, _ = x[0].shape
    for arr in x:
        if (arr.shape != dimx):
            raise ValueError("Lists of np.arrays 'x' do not agree in shape.")
    

def _validate_listplot_data(
        x: Any,
) -> None:
    """
    Check that the argument is 'plottable': same dimensions accross all rows.
    Raises an error if conditions are not satisfied.
    """
    if isinstance(x, list):
        _check_same_dims(x)
        return
    if isinstance(x, np.ndarray):
        if x.ndim != 2:
            raise ValueError("Invalid 2D array.")
        return
    e = "Argument is not a list of numpy.ndarrays or a single numpy.ndarray."
    raise TypeError(e)


def list_plot(
        x: SingleOrList[np.ndarray],
        rescale: Optional[DomainType] = None,
        how: Literal['plot', 'scatter'] = 'plot',
        lkwargs: list[dict[str, Any]] = None,
) -> PltSubplotsType:
    """
    Plot or scatter a list of `numpy.ndarray` or a 2D `numpy.ndarray` and 
    rescale its domain or join them if needed.

    Arguments
    ---------
    x
        2D data to be plotted.
    rescale
        Specify the domain of the X axis (if necessary)
    how
        Defaults to 'plot'. Set to 'scatter' to scatter instead.
    ylim
        Set a Y axis limit via ax.`set_ylim`.
    lkwargs
        A list of kwargs that is going to be passed individually to each 
        `ax.plot` called. Must be of the same size as `x`
    """

    _validate_listplot_data(x)
    fig, ax = plt.subplots()
    plotter = getattr(ax, how)
    
    if rescale:
        if isinstance(x, list):
            dimx, _ = x[0].shape
        if isinstance(x, np.ndarray):
            _, dimx = x.shape
        dom = get_domain(dimx, rescale)
        for arr, kwargs in zip(x, lkwargs):
            plotter(dom, arr, **kwargs)
        ax.set_xlim([dom.min(), dom.max()])
    
    else:
        if isinstance(arr, np.ndarray) and not lkwargs:
            plotter(arr.T)
        else:
            for arr, kwargs in zip(x, lkwargs):
                plotter(arr, **kwargs)
    
    return fig, ax


def coreplot_kwargs(
        method: Callable,
        x: NumpyVector,
        y: NumpyVector | NumpyMatrix,
        kwargs: dict,
        /,
) -> None:
    """
    Handle kwargs for `ax.plot` or `ax.scatter` and plot.

    Arguments
    ---------
    method
        The function call to plot.
    x, 
        The X axis data.
    y
        Data to be plotted | scattered against `x`. 
    kwargs
        Key-value arguments passed as *dictionary*, they're parsed via 
        `dl_to_ld`.

    Notes
    -----
    * Not a single type-check. All type-checks must be performed out of this 
    function (hence the `core` prefix).
    """
        
    if y.ndim == 1:
        method(x, y, **kwargs)
        return
    if y.ndim == 2:
        as_ld = dl_to_ld(kwargs)
        if isinstance(as_ld, dict):
            for arr in y:
                method(x, arr, **kwargs)
        else:
            for arr, kwarg in zip(y, as_ld):
                method(x, arr, **kwarg)
        return
    
    raise ValueError(
        f"Only 1D/2D plotting is supported. Got higher dimensional array:"
        f"{y.shape}."
    )


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


def map_plot(
        func: ODESolution1D,
        dom: DomainType,
        /,
        ax: Optional[Axes] = None,
        **kwargs,
) -> Axes:
    """
    Plot `func`: R -> R^n evaluated on a domain `dom`.
    
    Arguments
    ---------
    func
        Function that will be evaluated via `func(dom)`. This output is later
        compared against `dom` for dimensionality checks via 
        `validate_plottable`.
    dom
        Domain specification. It is later converted into a `np.linspace` via 
        `get_domain`.
    ax
        Optional. If `None` is provided then one is created with `plt.subplots`.
    """
    if isinstance(dom, list):
        dom = np.linspace(*dom)
    if not ax:
        _, ax = plt.subplots()
    
    discretized = func(dom)
    dom, discretized = validate_plottable(dom, discretized)
    
    coreplot_kwargs(
        ax.plot, 
        dom,
        discretized, 
        kwargs
    )
    return ax


def map_scatter(
        x: NumpyVector,
        y: NumpyVector | NumpyMatrix,
        /,
        ax: Optional[Axes] = None,
        **kwargs
) -> PltSubplotsType:
    """
    Plot a 1D vector against a 1D or 2D array.

    Arguments
    ---------
    x
        A 1D `numpy.ndarray`.
    y
        A 1D or 2D `numpy.ndarray`. If the former, then `x` and `y` must have 
        the same shape. If the latter, then the number of columns of `y` must 
        have the same length as `x`. 
    ax
        Optional. If `None` is provided then one is created with `plt.subplots`.
    kwargs
        Key-value arguments passed to `coreplot_kwargs`. 
    """
    if not ax:
        _, ax = plt.subplots()
    x, y = validate_plottable(x, y)
    coreplot_kwargs(ax.scatter, x, y, kwargs)
    return ax


def compare_numerical(
        fcontinuous: ODESolution1D,
        domain: DomainType,
        x: NumpyVector,
        y: NumpyMatrix,
        /,
        xlabel: str = "t",
        lighten: float = 0.3,
        labels: Optional[SingleOrList[str]] = None,
        colors: Optional[SingleOrList[str]] = None,
) -> PltSubplotsType:
    """
    Plot a continous function on a domain and scatter it's discretization (x, 
    y) on the same axis.

    Arguments
    ---------
    func
        Function that will be evaluated via `func(dom)`. This output is later
        compared against `dom` for dimensionality checks via 
        `validate_plottable`.
    dom
        Domain specification. It is later converted into a `np.linspace` via 
        `get_domain`.
    x
        A 1D `numpy.ndarray`.
    y
        A 1D or 2D `numpy.ndarray`. If the former, then `x` and `y` must have 
        the same shape. If the latter, then the number of columns of `y` must 
        have the same length as `x`. 
    xlabel
        The label of the X axis (passed via `ax.set_xlabel`).
    lighten
        Factor to pass to `ax_lighten`. It only lightens plotting lines, not
        scatter points.
    labels
        List of labels that are going to be passed to each plotting line, 
        respectively. 
    colors
        List of colors that are going to be passed to each `func(dom)[i]` 
        (`ax.plot`) and `[x, y[i]]` simoultaneously (`ax.scatter`).

    Returns
    -------
    fig, ax
        As a simple plt.subplots()
    """

    fig, ax = plt.subplots()
    map_plot(
        fcontinuous, domain, ax, 
        label=labels, color=colors
    )
    map_scatter(
        x, y, ax, 
        s=10, zorder=2, color=colors
    )
    
    # provide some style
    ax_lighten(ax, lighten)
    ax.legend()
    ax.set_xlabel(xlabel)
    ax.grid(True)
    fig.suptitle("Numerical (•) vs Exact solution")

    return fig, ax
