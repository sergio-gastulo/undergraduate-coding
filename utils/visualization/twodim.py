from typing import Optional

import numpy as np
import plotly.graph_objects as go
import plotly.io as pio

from utils.typing import (DomainType,
                          NumpyVector,
                          NumpyMatrix,
                          SingleOrList,
                          HowPlotType,
                          RealMapping,)
from utils.colors import wrapper

from .shared import (DARK_THEME,
                     get_domain, 
                     validate_plottable,
                     get_plotting_mode,)


def gen_disc_scatter(
        fig: go.Figure,
        tt: NumpyVector,
        discretization: NumpyMatrix,
        /,
        *,
        opacity: float = 0.5,
        markersize: int = 6,
        fetch_colors: bool = False
) -> go.Figure:
    """
    Plots a discretization on top of fig.
    """

    tt, ys = validate_plottable(tt, discretization)
    if ys.ndim == 1: 
        ys = [ys]

    if fetch_colors:
        colors = [trace.line.color for trace in fig.data]
    else:
        colors = pio.templates[pio.templates.default].layout.colorway
    ncols = len(colors)

    for i, trace in enumerate(fig.data):
        if (line := trace.line):
            c = wrapper(colors[i % ncols], opacity)
            line.color = f"rgb{c}"
    
    for y, c in zip(ys, colors):
        fig.add_trace(go.Scatter(x=tt, 
                                y=y, 
                                mode='markers+lines',
                                marker=dict(color=c,
                                            size=markersize),
                                line=dict(color=c,
                                          width=markersize / 4.5,
                                          shape='hvh'),
                                showlegend=False))
    fig.data = fig.data[::-1]
    return fig


def list_plot(
        data: NumpyVector | NumpyMatrix,
        /,
        *,
        how: HowPlotType = 'plot',
        domain: Optional[DomainType] = None,
        label: Optional[list[str]] = None,
        color: Optional[list[str]] = None,
) -> list[go.Scatter]:
    """
    Plot or scatter an array of y coords or an array of 2D points. 

    Arguments
    ---------
    data
        Plotted argument. It can match any of the following cases:
        * XY: `[[..., [xi, yi], ...], ...]`
        * Y: `y = [..., yi ...]` such that `y.ndim in {1, 2}` holds
        * Xy: `[x, ..., yi, ...]` such that `yi.ndim == 1` holds.
    domain
        Specifies the domain for `y | yi` on the Y case. If None, 
        XY pattern will be checked and the domain for each `yi` will 
        be gathered from it. If it fails, then the Xy pattern is assumed.
    how
        Specifies plotting mode.

    Notes
    -----
    * The fact that `data` is forced to be a `np.ndarray` from the 
    docstring, should reveal that dimensionality checks are not 
    performed.
    """    

    nlines, *_ = data.shape
    if domain is None and data.ndim == 2:  # compensate [x, ..., yi, ...] case
        nlines -= 1
    none_rows = [None] * nlines

    mode = get_plotting_mode(how)
    labels = label if label else none_rows
    colors = color if color else none_rows

    if data.ndim == 3:
        paths = [
            go.Scatter(x=dataplot[:, 0], y=dataplot[:, 1], 
                       mode=mode,
                       name=label,
                       marker=dict(color=color)) 
            for dataplot, label, color in zip(data, labels, colors)
        ]
        return paths

    if data.ndim == 1:
        data = data.reshape(1, -1)
    _, dim = data.shape

    if domain is None:
        # Xy case
        [xrange], dataplot = np.split(data, [1])
    else:
        # Y case
        xrange = get_domain(domain, dim)
        dataplot = data

    paths = [go.Scatter(x=xrange,
                        y=y,
                        mode=mode,
                        name=label,
                        marker=dict(color=color))
             for y, label, color in zip(dataplot, labels, colors)]

    return paths


def plot(
        func: RealMapping[NumpyVector],
        domain: DomainType,
        /,
        *,
        dark: bool = True,
        interactive: bool = False,
        color: Optional[SingleOrList[str]] = None,
        label: Optional[SingleOrList[str]] = None,
) -> go.Figure:
    
    x = get_domain(domain)
    yy = np.array(func(x))
    x, yy = validate_plottable(x, yy)

    colors = [color] if isinstance(color, str) and yy.ndim == 1 else color
    labels = [label] if isinstance(label, str) and yy.ndim == 1 else label
    ys = [yy] if yy.ndim == 1 else yy

    data = [go.Scatter(x=x, y=y, mode='lines') for y in ys]
    if color:
        for line, c in zip(data, colors):
            line.line = dict(color=c)
    if label:
        for line, l in zip(data, labels):
            line.name = l

    fig = go.Figure(data=data)
    template = DARK_THEME if dark else "default"
    fig.update_layout(hovermode=interactive, 
                      template=template,
                      showlegend=label is not None,)
    return fig