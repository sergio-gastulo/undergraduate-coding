from typing import Optional, Callable

import numpy as np
import plotly.graph_objects as go

from utils.typing import (DomainType,
                          SingleOrList,
                          PythonVector,
                          NumpyVector,
                          NumpyMatrix,
                          VectorMapping,)
from .shared import (GOLDEN_RATIO,
                     DARK_THEME,
                     get_domain,)


def plot_3d(
        multif: VectorMapping[NumpyVector],
        xdomain: DomainType,
        ydomain: DomainType,
        /,
        *, 
        opacity: float = 0.3,
        uniformcolors: Optional[SingleOrList[str]] = None,
        dark: bool = False,
        interactive: bool = False
) -> go.Figure:
    
    x = get_domain(xdomain)
    y = get_domain(ydomain)
    x, y = np.meshgrid(x, y)
    z = multif(x, y)

    data = [go.Surface(x=x, y=y, z=arr,
                   showscale=False, 
                   opacity=opacity)
            for arr in z]

    if uniformcolors:
        for surf, color in zip(data, uniformcolors):
            surf.colorscale = [[0, color], [1, color]]
            surf.showscale = False

    layoutkwargs = {
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
    fig = go.Figure(data=data, layout=layoutkwargs)
    return fig


def gen_root_path_3d(
        multif: Callable[[*PythonVector], float],
        steps: NumpyMatrix,
        /,
        *,
        showroot: bool = True,
        psize: int = 3,
        colors: Optional[list[str]] = None,
        labels: Optional[list[str]] = None,
) -> list[go.Scatter3d]:
    
    match steps.shape:
        case 2, _:
            pass
        case _, 2:
            steps = steps.T
        case _:
            raise TypeError(
                f"Can't scatter-path an array with shape={steps.shape!r}")
    
    data = multif(*steps)
    paths = [
        go.Scatter3d(
            x=steps[0], y=steps[1], z=zres, 
            mode='lines+markers', 
            marker={'size': psize}, 
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
                                     'size': 1.5 * psize})
            )
            
    return paths