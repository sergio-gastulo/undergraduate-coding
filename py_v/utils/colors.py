import colorsys

import matplotlib.colors as mc
from matplotlib.axes import Axes

from .typing import RGBColor


# https://stackoverflow.com/a/49601444/29272030
def _core_transform(
        color: str, 
        factor: float = 0.4
) -> RGBColor:
    """
    Convert a color to its darker/lighter version. For some reason, for values 
    between [0, 1] the color is lightened, but for [1, 2] is darken. In any 
    other case whether it's converted to white or black. 
    """
    rgb = mc.to_rgb(color)
    h, l, s = colorsys.rgb_to_hls(*rgb)
    l = min(1., 1 - factor * (1 - l))
    lighter = colorsys.hls_to_rgb(h, l, s)
    return lighter


def lighten(
        color: str,
        factor: float,
) -> RGBColor:
    if not 0 <= factor <= 1:
        raise ValueError(f"Argument {factor=} must be in [0, 1].")
    c = _core_transform(color, factor)
    return c


def darker(
        color: str,
        factor: float,
) -> RGBColor:
    if not 0 <= factor <= 1:
        raise ValueError(f"Argument {factor=} must be in [0, 1].")
    c = _core_transform(color, factor + 1)
    return c


def wrapper(
        color: str,
        factor: float
) -> RGBColor:
    """
    Darken o lighten a color based on the factor. Positive sets the color to a 
    lighter value and negative darkens it.
    """

    if 0 < factor <= 1:
        newcolor = lighten(color, factor)
        return newcolor
    elif 0 > factor >= -1:
        newcolor = darker(color, -factor)
        return newcolor
    elif factor == 0:
        return newcolor

    raise ValueError(
        f"Factor '{factor}' must lie in the range [-1 , 1]."
    )


def modified_ax_color(
        ax: Axes,
        /,
        factor: float,
) -> RGBColor:
    """
    Modify the color of all the lines for a given axis.
    """
    for line in ax.get_lines():
        color = line.get_color()
        newcolor = wrapper(color, factor)
        line.set_color(newcolor)