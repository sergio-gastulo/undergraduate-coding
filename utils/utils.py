import sys
import re
from importlib import reload
from pathlib import Path
from typing import Any

import pandas as pd

from .typing import (
    SingleOrList, 
    F
)

ABSOLUTE_PY_V_PATH = Path(__file__).parent.parent


def fetch_dfs(
        dirpaths: SingleOrList[str], 
        fnames: SingleOrList[str],
        **kwargs
) -> SingleOrList[pd.DataFrame]:
    """
    Retrieve a (list of) DataFrame(s) from a sequence of nested directories, and
    a list of files.

    Arguments
    ---------
    dirpaths
        A list of nested directories starting from 'data'. Example: dirpaths = 
        ['foo', 'bar'] will resolve to "data\\foo\\bar".
    fnames
        A list of filenames from which, after nesting dirpaths, dataframes will
        be read. Example: fnames = ['train.csv', 'test.csv'] will return two
        DataFrames: df_train and df_test.
    headers
        Whether headers are going to be inferred from .csv. Defaults to True (
        useful for clean .csvs)
    kwargs
        Kwargs passed to `pd.read_csv`.
    """

    datadir = ABSOLUTE_PY_V_PATH / 'data'

    if not isinstance(dirpaths, list):
        dirpaths = [dirpaths]
    for path in dirpaths:
        datadir /= path
    if not datadir.exists():
        raise ValueError(f"Directory '{datadir}' does not exist.")

    if not isinstance(fnames, list):
        fnames = [fnames]

    res = []
    for fname in fnames:
        path = datadir / fname
        df = pd.read_csv(path, **kwargs)
        res.append(df)

    return res


def funcreload(func: F) -> F:
    """
    Reload a function to retrieve latest changes.
    """
    module_str = func.__module__
    module = reload(sys.modules[module_str])
    return getattr(module, func.__name__)


def dl_to_ld(
        d: dict[str, list]
) -> SingleOrList[dict[str, str]]:
    """
    Convert a dictionary of lists to a lists of dictionaries. If the dictionary
    contains no list, the dictionary itself is returned.

    Arguments
    ---------
    d
        The dictionary of list to be converted.

    Examples
    --------
    >>> dl = {'a': [0, 1], 'b': [2, 3]}
    >>> dl_to_ld(dl)
    [{'a': 0, 'b': 2}, {'a': 1, 'b': 3}]
    >>> dl = {'a': [0, 1], 'b': [2, 3], 'c': 1}
    >>> dl_to_ld(dl)
    [{'a': 0, 'b': 2, 'c': 1}, {'a': 1, 'b': 3, 'c': 1}]
    >>> dl = {'s': 10, 'zorder': 2, 'label': 'Numerical'}
    >>> dl_to_ld(dl)
    {'s': 10, 'zorder': 2, 'label': 'Numerical'}
    """

    single_keys = []
    lens = []
    for key, value in d.items():
        if isinstance(value, list):
            lens.append(len(value))
        else:
            single_keys.append(key)
    if not lens:
        # if all keys in the dictionary are simple key: val, return the 
        # dictionary directly
        return d
    
    n = min(lens)
    if n != max(lens):
        raise TypeError(
            "At least two lists in the dictionary have different length."
        )
    else:
        for key in single_keys:
            # map key: val to key: [val, val, ...]
            d[key] = [d[key]] * n

    # https://stackoverflow.com/a/33046935/29272030
    return [dict(zip(d,t)) for t in zip(*d.values())]


def mdir(
        expr: Any,
        strfilter: str
) -> list[str]:
    """
    Search for specific methods / attributes of a given python expression.

    Arguments
    ---------
    expr
        The Python expression to which `dir` will be evaluated on.
    strfilter
        The filter to pass to all the elements from `dir(expr)`.
    """
    dirs = dir(expr)
    pattern = re.compile(strfilter)
    matches = list(filter(pattern.match, dirs))
    return matches