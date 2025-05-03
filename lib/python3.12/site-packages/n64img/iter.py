from itertools import zip_longest
from math import ceil
from typing import Iterable, Tuple


def iter_image_indexes(
    width: int,
    height: int,
    bytes_per_pixel: float = 1,
    flip_h: bool = False,
    flip_v: bool = False,
) -> Iterable[Tuple[int, int, int]]:
    w = int(width * bytes_per_pixel)
    h = int(height * 1)

    xrange = (
        range(w - ceil(bytes_per_pixel), -1, -ceil(bytes_per_pixel))
        if flip_h
        else range(0, w, ceil(bytes_per_pixel))
    )
    yrange = range(h - 1, -1, -1) if flip_v else range(0, h, 1)

    for y in yrange:
        for x in xrange:
            yield x, y, (y * w) + x
