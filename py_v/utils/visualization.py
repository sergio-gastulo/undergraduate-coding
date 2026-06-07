from typing import Optional, Any, Literal, Callable

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.figure import Figure
from matplotlib.image import AxesImage
from matplotlib.axes import Axes

from .utils import SingleOrList, dl_to_ld
from .typing import (
    PercentileType, 
    RescaleType, 
    ODESolution1D,
    DomainType
)



def matrix_plot(
        mat: np.ndarray,
        percentiles: PercentileType,
        **kwargs,
) -> tuple[Figure, AxesImage]:
    """
    Plot a matrix, clipping the colormap range to i-th and j-th percentile 
    to reduce distortion.
    
    Arguments
    ---------
    mat
        The numpy.array to be plotted.
    percentiles
        The percentiles to clip the range
    kwargs
        Passed to `matplotlib.axes.Axes.imshow`.
    """

    i, j = percentiles
    pi, pj = np.percentile(mat, percentiles)
    fig, ax = plt.subplots()
    im = ax.imshow(
        mat, 
        vmin=pi, 
        vmax=pj,
        aspect='auto',
        **kwargs,
    )
    title = (
        f"Statistics:"
        f"\nmax = {np.max(mat):.2e}"
        f"\nmean = {np.mean(mat):.2e}"
        f"\np{i} = {pi:.2e}"
        f"\np{j} = {pj:.2e}"
    )
    fig.suptitle("Matrix plot")
    fig.supxlabel(title, x=0.5, fontsize=10, ha='center')
    fig.tight_layout(rect=[0, 0.1, 1, 0.95])
    return fig, im


def matrix_diff_plot(
        mat1: np.ndarray,
        mat2: np.ndarray,
        percentiles: PercentileType,
        **kwargs,
) -> Figure:
    """
    Arguments
    ---------
    mat1, mat2
        `numpy.array`s with same shape (`ValueError` raised otherwise).
    kwargs
        Key-word arguments passed to `mat_plot`.
    """

    if mat1.shape != mat2.shape: 
        raise ValueError(
            f"Different shapes {mat1.shape} and {mat2.shape}: can't substract."
        )

    mabs = np.abs(mat1 - mat2)
    fig, im = matrix_plot(mabs, 
                          percentiles, 
                          cmap=plt.get_cmap('hot'), 
                          **kwargs)
    fig.colorbar(im)
    fig.suptitle("Plot: np.abs(mat1 - mat2)")
    return fig


def get_domain(
        dim: int,
        rescale: RescaleType,
) -> np.ndarray:
    
    if isinstance(rescale, np.ndarray):
        dimdom, = rescale.shape
        if dim == dimdom:
            return rescale 
        raise ValueError("Domain and array do not have the same length.")

    try:
        min_, max_ = rescale
    except TypeError:
        raise ValueError(f"Could not unpack (min, max) from {rescale}.")
    return np.linspace(min_, max_, dim)


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
        rescale: Optional[RescaleType] = None,
        how: Literal['plot', 'scatter'] = 'plot',
        lkwargs: list[dict[str, Any]] = None,
) -> tuple[Figure, Axes]:
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


def _core_plot_kwargs(
        method: Callable,
        x: np.ndarray,
        y: np.ndarray,
        kwargs: dict,
        /,
) -> None:
    """Handle kwargs when `ax.plot|scatter`'ing."""
        
    if y.ndim == 1:
        method(x, y, **kwargs)
    elif y.ndim == 2:
        as_ld = dl_to_ld(kwargs)
        if isinstance(as_ld, dict):
            for arr in y:
                method(x, arr, **kwargs)
        else:
            for arr, kwarg in zip(y, as_ld):
                method(x, arr, **kwarg)
    else:
        raise ValueError(
            f"Only 1D/2D plotting is supported. Got the arrays"
            f"with the shapes: '{x.shape=}', '{y.shape=}'."
        )


def map_plot(
        func: ODESolution1D,
        dom: DomainType,
        /,
        ax: Optional[Axes] = None,
        **kwargs,
) -> Axes:
    if isinstance(dom, list):
        dom = np.linspace(*dom)
    if not ax:
        _, ax = plt.subplots()
    
    _core_plot_kwargs(
        ax.plot, 
        dom, 
        func(dom), 
        kwargs
    )
    return ax


def map_scatter(
        x: np.ndarray,
        y: np.ndarray,
        /,
        ax: Optional[Axes] = None,
        **kwargs
) -> tuple[Figure, Axes]:
    
    n, = x.shape
    try:
        _, m = y.shape
    except ValueError:
        m, = y.shape
    if n != m:
        raise ValueError(
            "Can't plot arrays with missmatching dimensions:"
            f"{x.shape=} and {y.shape=}."
        )
    if not ax:
        _, ax = plt.subplots()
    _core_plot_kwargs(ax.scatter, x, y, kwargs)
    return ax


def continuum_discretized_plot(
        dom: np.ndarray,
        solution: Callable,
        discretized: np.ndarray | list[np.ndarray, np.ndarray],
) -> tuple[Figure, Axes]:
    """
    Plot a continous function against it's discretization obtained by a given 
    numerical method. Useful for plotting exact solutions vs ODE / integration 
    methods.

    Arguments
    ---------
    dom
        Domain for which `solution` will be applied to discretize.
    solution
        The function to be plotted via `Axes.plot`.
    discretized
        Scatter points in (x, y) coordinates stored in a numpy.ndarray. It can
        be passed as a (2, n) or (n, 2) numpy.ndarray.

    """

    if isinstance(discretized, list):
        discretized = np.array(discretized)

    # check that discretized is a np.array of the form (2, data) or (data, 2)
    n, m = discretized.shape
    if 2 not in [n, m]:
        raise ValueError(
            "Only a (2, n) or (n, 2) array is allowed as a discretized domain.")

    fig, ax = plt.subplots()
    ax.plot(dom, solution(dom), label="Analytical")
    if n == 2:
        ax.scatter(*discretized, label="Numerical", color='red')
    else:
        ax.scatter(*discretized.T, label="Numerical", color='red')

    fig.suptitle("Numerical vs. Analytical Solution")
    ax.set_xlabel("$t$")
    ax.set_ylabel(f"${solution.__name__}(t)$")
    ax.legend()

    return fig, ax


#TODO: code a custom macro to set nice title for scientific papers