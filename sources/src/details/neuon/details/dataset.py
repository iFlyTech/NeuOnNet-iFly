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

    with h5py.File(options.dataset, mode='w') 