from typing import Optional, Callable

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.axes import Axes
from matplotlib import rcParams
import plotly
from IPython.display import display, HTML
import plotly.graph_objects as go
from plotly.graph_objects import Figure
from plotly.graph_objs import Scatter3d
import plotly.io as pio

from .utils import SingleOrList, dl_to_ld
from .typing import (
    DomainType, 
    Real2Real,
    Real2Vector,
    NumpyVector,
    NumpyMatrix,
    PltSubplotsType,
    Vector2Vector,
    HowPlotType
)
from .colors import modified_ax_color, wrapper


GOLDEN_RATIO = 1.618033 
DARK_THEME = "plotly_dark"


def init() -> None:
    """Set initial configurations for better plotting"""

    plt.style.use('dark_background')
    rcParams['text.usetex'] = True
    rcParams['font.family'] = 'serif'
    rcParams['text.latex.preamble'] = r'\usepackage{amsmath}'
    
    # https://stackoverflow.com/a/76599370/29272030
    plotly.offline.init_notebook_mode()
    display(HTML('<script type="text/javascript"'
                 'async src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-MML-AM_SVG">'
                 '</script>'
    ))


def get_domain(
        domain: DomainType,
) -> NumpyVector:
    
    if isinstance(domain, list):
        return np.linspace(*domain)

    if isinstance(domain, np.ndarray):
        return domain
    
    raise TypeError(
        f"Only lists or numpy ndarrays are allowed. Got: '{type(domain)}'.")


def list_plot(
        data: NumpyVector | NumpyMatrix,
        /,
        *,
        domain: DomainType | None = None,
        label: SingleOrList[str] | None = None,
        how: HowPlotType = 'plot',
        dark: bool = True,
) -> Figure:
    """
    Plot or scatter a list of `numpy.ndarray`s or a 2D `numpy.ndarray` over 
    `domain` if specified.

    Arguments
    ---------
    data
        Plotted argument.
    domain
        Specify X axis (if specified).
    how
        Defaults to 'plot'.
    """

    rows, cols = data.shape
    if not domain:
        domain = np.arange(cols)
    else:
        domain = get_domain(domain)

    if not how or how in {'plot', 'lines'}:
        mode = 'lines'
    elif how in {'scatter', 'markers'}:
        mode = 'markers'
    elif how == 'lines+markers':
        mode = how

    labels = label if label else [None] * rows
    template = DARK_THEME if dark else "default"

    fig = go.Figure(data=[go.Scatter(x=domain, 
                                     y=y, 
                                     mode=mode, 
                                     name=lab) 
                          for lab, y in zip(labels, data)],
                    layout=dict(template=template))
    return fig


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



def plot(
        func: Real2Vector,
        domain: DomainType,
        *,
        dark: bool = True,
        interactive: bool = False,
        color: Optional[SingleOrList[str]] = None,
        label: Optional[SingleOrList[str]] = None,
) -> Figure:
    
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


def plot_3d(
        multif: Vector2Vector,
        xdomain: DomainType,
        ydomain: DomainType,
        /,
        *, 
        opacity: float = 0.3,
        uniformcolors: Optional[SingleOrList[str]] = None,
        dark: bool = False,
        interactive: bool = False
) -> Figure:
    
    x = np.linspace(*xdomain)
    y = np.linspace(*ydomain)
    x, y = np.meshgrid(x, y)
    z = multif(x, y)

    data = [
        go.Surface(x=x, y=y, z=arr,
                   showscale=False, 
                   opacity=opacity)
        for arr in z
    ]

    if uniformcolors:
        for surf, color in zip(data, uniformcolors):
            surf.colorscale = [[0, color], [1, color]]
            surf.showscale = False

    figkwargs = {
        "scene": {
            "aspectmode": "manual",
            "aspectratio": {
                "x": 1,
                "y": 1 / GOLDEN_RATIO,
                "z": 1 / GOLDEN_RATIO
            }
        },
        "hovermode": interactive,
        "template": DARK_THEME if dark else "default"
    }
    fig = go.Figure(data=data, layout=figkwargs)
    return fig


def gen_root_path_3d(
        multif: Callable[[*tuple[float, ...]], float],
        steps: NumpyMatrix,
        /,
        *,
        showroot: bool = True,
        colors: Optional[list[str]] = None,
        labels: Optional[list[str]] = None,
) -> list[Scatter3d]:
    match steps.shape:
        case 2, _:
            pass
        case _, 2:
            steps = steps.T
        case _:
            raise TypeError(
                f"Can't scatter-path an array with shape={steps.shape!r}")
    
    data = multif(*steps)
    size = 3
    paths = [
        go.Scatter3d(
            x=steps[0], y=steps[1], z=zres, 
            mode='lines+markers', 
            marker={'size': size}, 
            line={'width': 2},
        )
        for zres in data
    ]

    if colors:
        for path, color in zip(paths, colors):
            path.marker.color = color
            path.line.color = color
    if labels:
        for path, label in zip(paths, labels):
            path.name = label
    
    if showroot:
        for zres in data:
            paths.append(
                go.Scatter3d(x=[steps[0, -1]], 
                             y=[steps[1, -1]], 
                             z=[zres[-1]],
                             mode="markers+text",
                             text="Root",
                             showlegend=False,
                             textposition="top right",
                             textfont={"color": "white"},
                             marker={'color': 'white', 
                                     'size': 1.5 * size})
            )
            
    return paths



def gen_disc_scatter(
        fig: Figure,
        tt: NumpyVector,
        discretization: NumpyMatrix,
        /,
        *,
        opacity: float = 0.5,
        fetch_colors: bool = False
) -> Figure:
    
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
    
    markersize = 6
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