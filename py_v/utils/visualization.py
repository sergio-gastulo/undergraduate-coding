import numpy as np
import matplotlib.pyplot as plt
from matplotlib.figure import Figure
from matplotlib.image import AxesImage

PercentileType = list[float | int]

def matrix_plot(
        mat: np.ndarray,
        percentiles: PercentileType = [0, 100],
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
            f"Different shapes {mat1.shape} and {mat2.shape}: can't substract.")

    mabs = np.abs(mat1 - mat2)
    fig, im = matrix_plot(mabs, 
                          percentiles, 
                          cmap=plt.get_cmap('hot'), 
                          **kwargs)
    fig.colorbar(im)
    fig.suptitle("Plot: np.abs(mat1 - mat2)")
    return fig
