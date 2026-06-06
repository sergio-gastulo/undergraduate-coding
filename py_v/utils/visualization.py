from typing import Optional, TypeAlias, Any, Literal

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.figure import Figure
from matplotlib.image import AxesImage
from matplotlib.axes import Axes
from matplotlib.typing import ColorType

try:
    from utils import SingleOrList
except ImportError:
    from .utils import SingleOrList


PercentileType = list[int]
DomainType: TypeAlias = list[int, int] | np.ndarray


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
        rescale: DomainType,
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
    

def validate_plot_data(
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
        ylim: list[int, int] = None,
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

    validate_plot_data(x)
    if isinstance(x, list):
        dimx, _ = x[0].shape
    if isinstance(x, np.ndarray):
        _, dimx = x.shape

    fig, ax = plt.subplots()
    plotter = getattr(ax, how)
    
    if rescale:
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
    
    if ylim:
        ax.set_ylim(ylim)
    
    return fig, ax
