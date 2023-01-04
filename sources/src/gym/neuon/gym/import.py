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
    parser.add_option("-d", "--datalist", dest="datalist", help="data", metavar="FILE")
    parser.add_option("-n", "--normale", dest="normale", help="data", metavar="FILE")

    (options, args) = parser.parse_args()

    with open(options.normale, "r") as normale:
        statistic = json.load(normale)
        video_scale = neuon.details.preprocessing.standardization_t(statistic['video']['mean'], statistic['video']['std'])
        audio_scale = neuon.details.preprocessing.standardization_t(statistic['audio']['mean'], statistic['audio']['std'])

    try:
        datalist = neuon.details.primitives.datalist_t(options.datalist, video_scale, audio_scale)
        distance = datalist.distance
        timestamps = datalist.timestamps[:, 0]
    except ValueError as e:
        print("WARN: It seems no data samples were extracted from the file to use to make a prediction so we just exit.")
        print("WARN: Please contact to the author and share your movie clip to help with improving this product.")
        return

    with tf.Session(graph=tf.Graph()) as sess:
        with gfile.FastGFile(options.model, 'rb') as model:
            graph_def = tf.GraphDef()
            graph_def.ParseFromString(model.read())
          