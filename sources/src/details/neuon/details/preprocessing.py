import numpy
import dask
import dask.array


def statistic_t(data):
    data = dask.array.from_array(data, chunks=data.chunks)

    mean = dask.array.mean(data)