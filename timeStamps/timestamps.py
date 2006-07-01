#!/usr/bin/env python

import math
import sys

import numarray as num

import Model
import models
import tableio

class accumulator:

    def __init__(self, offset=0.0):
        self.remainder = offset
        return

    def add(self, value):
        sum = self.remainder + value
        whole = math.ceil(sum)
        self.remainder = sum - whole
        return whole

    pass


def constant(parms, t):
    (rate,) = parms
    return rate

def linear((con, lin), t):
    rate = con + lin * t
    return rate

if __name__ == '__main__':

    outFile = sys.argv[1]

    #parms = (2e7 + 94.3,)
    #parms = (20000092., -0.00424959)
    #parms = (2e7+100, -6.6e-3, 6.1e-7)
    parms = (0.37, 2e7+100, -3.3e-3, 2.0e-7)
    fun = models.poly

    #acc = accumulator(-0.37)

    times = num.arange(1800.)

    nParm = len(parms)
    nPts = len(times)

    #truth = num.zeros((nPts,), num.Float64)
    #rep = num.zeros((nPts,), num.Float64)
    #for iTime, time in enumerate(times):
    #    trueStep = fun(parms, time)
    #    truth[iTime] = trueStep
    #    repStep = acc.add(trueStep)
    #    rep[iTime] = repStep
    #    pass

    truth = fun(parms, times)
    rep = num.ceil(truth)

    fitter = Model.Model(fun, parms, times, rep)
    fitParm, chiSquare, covar = fitter.fit()
    fitParm[0] -= 0.5
    errors = num.sqrt(num.diagonal(covar))

    print 'Chi**2 (dof):', chiSquare, nPts-nParm

    print 'True\tFit\terror\tdelta\tscaled'
    for ii in range(nParm):
        delta = parms[ii] - fitParm[ii]
        scalDelt = delta / errors[ii]
        cols = (parms[ii], fitParm[ii], errors[ii], delta, scalDelt)
        print '\t'.join(['%g'] * len(cols)) % cols
        pass

    fitTicks = fun(fitParm, times)
    obsFit = num.ceil(fitTicks)
    resid = truth - fitTicks
    repResid = rep - fitTicks
    obsResid = rep - obsFit

    title = 'Fake'
    columns = ('Time', 'True Ticks', 'Measured Ticks', 'Fit Ticks', \
               'Residual', 'repResid', 'obsResid')
    data = (times, truth, rep, fitTicks, resid, repResid, obsResid)
    tableio.writehippo(data, outFile, title, columns)

    pass
