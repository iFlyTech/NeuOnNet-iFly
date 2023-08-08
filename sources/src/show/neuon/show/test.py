#!/usr/bin/env python
from __future__ import absolute_import
from __future__ import print_function

import keras.models
import optparse
import numpy
import json
import os

import neuon.details.primitives
import neuon.details.preprocessing


def main():
    os.environ["CUDA_VISIBLE_DEVICES"] = "0"
    parser = optparse.OptionParser()
    parser.add_option("-m", "--model", dest="model", help="model", metavar="FILE")
    parser.add_option("-d", "--dataset", dest="dataset", help="data", metavar="FILE")
    parser.add_option("-l", "--datalist", dest="datalist", help="data", metavar="FILE")
    parser.add_option("-n", "--normale", dest="normale", help="data", metavar="FILE")

    (options, args) = parser.parse_args()

    model = keras.models.load_model(options.model, custom_objects={'contrastive_loss': neuon.details.primitives.contrastive_loss, 'keras': keras}, compile=True)
    model.summary()

    with open(options.normale, "r") as normale:
        statistic = json.load(normale)
        video_scale = neuon.details.preprocessing.standardization_t(statistic['video']['mean'], statistic['video']['std'])
        audio_scale = neuon.details.preprocessing.standardization_t(statistic['audio']['mean'], statistic['audio']['std'])

    if options.dataset is not None:
        test_generator = neuon.details.primitives.predict_generator_t(options.dataset, 32)
        test_generator.vi