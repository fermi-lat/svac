#!/usr/bin/env python

import os
import sys

import numarray as num

import Model
import models
import orthoPoly
import tableio


inFile, outFile = sys.argv[1:]

base = os.path.basename(inFile)
base = base.split('.')[0]

data = tableio.readtable(inFile)
times, deltas, ticks = data[:3]

maxOrder = 10

tickError = 1 / num.sqrt(12)

xx = times
yy = ticks
#xx = times[1:]
#yy = deltas[1:]
yErr = tickError
    
colNames = ['Time', 'Ticks']
columns = [xx, yy]
for order in num.arange(maxOrder) + 1:

    print 'Order: %d ##################' % order

    nParm = order + 1

    # poly = orthoPoly.orthoPoly(order, times)
    # fun = poly.modelFunc
    # startParm = poly.basis.expand(ticks)
    # print startParm

    startParm = num.ones(nParm, num.Float64)
    startParm[1] = (yy[-1] - yy[0]) / (xx[-1] - xx[0])
    fun = models.poly
    
    fitter = Model.Model(fun, startParm, xx, yy, yErr)

    fitParm, chiSq, covar = fitter.fit()
    errors = num.sqrt(num.diagonal(covar))

    nDof = len(times) - nParm
    redChi = chiSq / nDof
    print 'Chi**2 (dof): %g (%g)' % (chiSq, nDof)

    for ii in range(nParm):
        cols = (fitParm[ii], errors[ii])
        print '\t'.join(['%.17g'] * len(cols)) % cols
        pass

    colNames.append('%d' % order)
    columns.append(yy - fitter())

    pass

title = base.join(('<', '>'))
tableio.writehippo(columns, outFile, title, colNames)
