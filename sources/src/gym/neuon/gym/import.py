#!/usr/bin/env python
from __future__ import absolute_import
from __future__ import print_function

import optparse
import numpy
import json
import os

import neuon.details.preprocessing
import neuon.details.primitives

import tensorflow as tf
from tensorflow.python.platform import gfile

def main():
    os.environ["CUDA_VISIBLE_DEVICES"] = "0"
    parser = optparse.OptionParser()
    parser.add_option("-m", "--model", dest="model", help="model", metavar="FILE")
    parser.add_option("-d", "--datalist", dest="datalist", help="data", metavar="FIL