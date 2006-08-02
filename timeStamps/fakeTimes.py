#!/usr/bin/env python

import sys

import numarray as num
import numarray.random_array as nrand

import models
import tableio

outFile = sys.argv[1]

times = num.arange(-900., 900.)
parms = (0.37, 2e7+100, -3.3e-3, 2.0e-7)
noiseMean = 0.0
noiseAmp = 0.5
fun = models.poly

truth = fun(parms, times)
truth += nrand.normal(noiseMean, noiseAmp, truth.shape)

obs = num.ceil(truth) - 0.5

trueDelta = truth[1:] - truth[:-1]
obsDelta = obs[1:] - obs[:-1]

trueDelta = num.concatenate(([num.average(trueDelta)], trueDelta))
obsDelta = num.concatenate(([num.average(obsDelta)], obsDelta))

title = "Fake"
colNames = ['Time', 'Delta', 'Ticks', 'trueDelta', 'trueTicks']
data = [times, obsDelta, obs, trueDelta, truth]

tableio.writehippo(data, outFile, title, colNames)
