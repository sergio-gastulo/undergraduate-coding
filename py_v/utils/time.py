from typing import Callable, Literal
import time

import numpy as np


def _get_timer(
        how: Literal['perf', 'proc'] = 'perf',
        nano: bool = False,
) -> float:
    
    if how == 'perf':
        timer = 'perf_counter'
    elif how == 'proc':
        timer = 'process_time'
    else:
        raise ValueError(f"Invalid {how=}.")
    
    if nano:
        timer = f"{timer}_ns"
    
    return getattr(time, timer)


def timeit(
        process: Callable,
        n: int,
        how: Literal['perf', 'how'] = 'perf',
        nano: bool = False,
) -> np.ndarray:
    """
    Excute a `process` `n` times and return the time of each execution. By 
    default the chosen timer is `perf_counter`.

    Arguments
    ---------
    process: Callable
        The process that will be executed to be timed.
    n: int
        The number times process will be executed and measured.
    how
        `how='proc'` sets `process_time` as timer.
    nano 
        Set `nano`= True to return as nanoseconds.

    Examples
    --------
    >>> process = lambda: time.sleep(0.5)
    >>> timeit(process, 5)
    array([0.5003669, 0.500513 , 0.5001234, 0.5002876, 0.5004058])
    >>> timeit(process, 5, nano=True)
    array([500810800, 500657900, 500329600, 500583900, 500189800])
    """
    timer = _get_timer(how, nano)
    def _t():
        t1 = timer()
        process()
        t2 = timer()
        return t2 - t1
    
    dtype = np.int64 if nano else np.float64
    return np.array([_t() for _ in range(n)], dtype)


def map_timeit(
        processes: list[Callable],
        n: int,
        **kwargs,
) -> np.ndarray:
    """
    Time a list of processes. A `numpy.array` is returned -- each rows 
    corresponds to each process in order. 

    Arguments
    ---------
    processes
        A list of processes that will be measured via `timeit`.
    iters
        How many times each process will be iterated. It's passed to `timeit`.
    kwargs  
        Passed to `timeit` to change the default timer.

    Examples
    --------
    >>> p1 = lambda: time.sleep(0.5)                   
    >>> p2 = lambda: time.sleep(0.2)
    >>> map_timeit([p1, p2], 3)
    array([[0.5002884, 0.5003938, 0.5005349],
        [0.2001706, 0.2001238, 0.2003273]])
    """
    if not isinstance(processes, list):
        raise TypeError("Argument 'processes' should be a list.")
    
    res = np.array([timeit(proc, n, **kwargs) 
                    for proc in processes])
    return res