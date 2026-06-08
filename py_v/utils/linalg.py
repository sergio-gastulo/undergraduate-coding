import numpy as np
from scipy import sparse


def tridiag(
        n: int, 
        diag: float, 
        band: float, 
        **kwargs
) -> sparse.dia_matrix:
    band_arr = np.full(n-1, band)
    diag_arr = np.full(n, diag)
    offset = [-1, 0, 1]
    data = [band_arr, diag_arr, band_arr]
    res = sparse.diags(data, offset, **kwargs)
    return res


def gen_ab(
        n: int, 
        param: float
) -> np.ndarray:
    band = np.full(n-1, -param)
    diag = np.full(n, 1+2*param)
    ab = np.vstack((
        np.append(0, band),
        diag,
        np.append(band, 0)
    ))
    return ab