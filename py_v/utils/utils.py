from pathlib import Path
from typing import TypeVar, TypeAlias

import matplotlib.pyplot as plt
import pandas as pd


T_ = TypeVar("T_")
SingleOrList: TypeAlias = list[T_] | T_


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

    datadir = Path('data')

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

