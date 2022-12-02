#!/usr/bin/env python

import optparse
import numpy
import pandas
import imageio
import h5py
import json
import neuon.details.preprocessing


def main():
    parser = optparse.OptionParser()
    parser.add_option("-l", "--list", dest="datalist", help="data sample list from feature extractor tool", metavar="FILE")
    parser.add_option("-d", "--dataset", dest="dataset", help="HDF5 Dataset storage file", metavar="FILE")

    (options, args) = parser.parse_args()

    datalist = pandas.read_csv(options.datalist, header=None, delim_whitespace=True, low_memory=False)

    n = datalist.shape[0]

    with h5py.File(options.dataset, mode='w') as dataset:
        video_dataset = dataset.require_dataset('video', shape=(n, 9, 60, 100, 1), dtype='uint8', chunks=(32, 9, 60, 100, 1), maxshape=(None, 9, 60, 100, 1), compression="gzip", compression_opts=2)
        video_dataset.dims[0].label = 'n'
        video_dataset.dims[1].label = 'time'
        video_dataset.dims[2].label = 'height'
        video_dataset.dims[3].label = 'width'
        video_dataset.dims[4].label = 'channels'

        audio_dataset = dataset.require_dataset('audio', shape=(n, 3, 45, 15, 1), dtype='float',  chunks=(32, 3, 45, 15, 1), maxshape=(None, 3, 45, 15, 1), compression="gzip", compression_opts=2)
        audio_dataset.dims[0].label = 'n'
        audio_dataset.dims[1].label = 'derivation'
        audio_dataset.dims[2].label = 'time'
        audio_dataset.dims[3].label = 'coefficients'
        audio_dataset.dims[4].label = 'channels'

        distance_dataset = dataset.require_dataset('distance', shape=(n, ), dtype='uint8',  chunks=True, maxshape=(None, ), compression="gzip", compression_opts=9)
        distance_dataset.dims[0].label = 'n'

        timestamp_dataset = dataset.require_dataset('timestamps', shape=(n, 4), dty