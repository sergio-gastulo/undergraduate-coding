import numpy as np
import matplotlib.pyplot as plt
from matplotlib.figure import Figure


def darkmode() -> None:
    """Set matplotlib's darkmode mode."""
    plt.style.use('dark_background')
    plt.rcParams['font.family'] = 'monospace'
    plt.rcParams['font.size'] = 12


def plot_diff_matrices(
        mat1: np.ndarray,
        mat2: np.ndarray,
        **kwargs
) -> Figure:
    """
    
    Arguments
    ---------
    mat1, mat2
        Matrices with same shape (ValueError raised otherwise).
    kwargs
        Key-word arguments passed to `Axes.imshow`.
    """


    if mat1.shape != mat2.shape: 
        raise ValueError(
            f"Different shapes {mat1.shape} and {mat2.shape}: can't substract.")

    mabs = np.abs(mat1 - mat2)
    p5, p95 = np.percentile(mabs, [5, 95])

    fig, ax = plt.subplots()
    im = ax.imshow(
        mabs, 
        cmap=plt.get_cmap('hot'), 
        aspect='auto',
        vmin=p5, 
        vmax=p95,
        **kwargs,
    )
    fig.colorbar(im)

    title = (
        f" Statistics:"
        f"\nmax = {np.max(mabs):.2e}"
        f"\nmean = {np.mean(mabs):.2e}"
        f"\np95 = {p95:.2e}"
    )
    fig.supxlabel(title, x=0.5, fontsize=10, ha='center')
    fig.suptitle("Plot: np.abs(mat1 - mat2)")
    fig.tight_layout(rect=[0, 0.1, 1, 0.95])
    return fig
