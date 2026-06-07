import colorsys

import matplotlib.colors as mc
from matplotlib.axes import Axes


# https://stackoverflow.com/a/49601444/29272030
def lighten(
        color: str, 
        factor: float = 0.4
):
    rgb = mc.to_rgb(color)
    h, l, s = colorsys.rgb_to_hls(*rgb)
    l = min(1., 1 - factor * (1 - l))
    lighter = colorsys.hls_to_rgb(h, l, s)
    return lighter


def ax_lighten(
        ax: Axes,
        factor: float = 0.4
) -> None:
    for line in ax.get_lines():
        color = line.get_color()
        lighter = lighten(color, factor)
        line.set_color(lighter)

    