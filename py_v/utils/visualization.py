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

    diff = mat1 - mat2
    mabs = np.abs(diff)
    fig, ax = plt.subplots()
    im = ax.imshow(
        mabs, 
        cmap=plt.get_cmap('hot'), 
        aspect='auto',
        **kwargs
    )
    fig.colorbar(im)

    title = f'Residual |max|={np.max(mabs):.2e} |mean|={np.mean(mabs):.2e}'
    ax.set_title(
        title,
        fontsize=10, 
        pad=12
    )

    fig.tight_layout()
    return fig
