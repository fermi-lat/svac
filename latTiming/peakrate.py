#!/usr/bin/env python

import os, sys

try:
    import numarray as num
except ImportError:
    import Numeric as num

import tableio
#import qdfits

## configuration
nanoscale = 1e9 # cycles/s of the nano clock
nanogran = 60. # bins/s of the nano clock

#cyclescale = 16e6 # wrong!
#cyclescale = 2.**24 # also wrong
cyclescale = 1 / 60e-9 # cycles/s and bins/s of the cycle clock
upperscale = 2.**32

nominal_ratio = 60.0 # nominal value of nanoscale/cyclescale

peakcut = 0.002

chunk = 2**14

ratfile = 'inpeak.qdp'
## end config


## get input and output names
infiles = sys.argv[1:]

aside = sys.stderr

def readtimes(timefile):
    try:
        reader = timefile.readlines
    except AttributeError:
        reader = open(timefile).readlines

    lines = reader()
    nlines = len(lines)
    ncols = len(lines[0].split())

    data = num.zeros((nlines, ncols), num.Float64)

    for iline in xrange(len(lines)):
        data[iline] = map(float, lines[iline].split())

    data = num.transpose(data)
    return data


def howmany(seq):
    seq = num.asarray(seq)
    seq = seq.astype(num.Int32)
    many = num.add.reduce(seq)
    return many


def peakrate(data, cut=peakcut):
    delta = data[1:] - data[:-1]
    time = data[-1] - data[0]

    total = float(len(delta))
    dt = num.sqrt(total + 1)
    rate = total / time
    drate = dt / time

    inpeak = float(howmany(delta < cut))
    dip = num.sqrt(inpeak + 1)
    fraction = inpeak / total
    if inpeak:
        dfrac = fraction * num.sqrt((dip/inpeak)**2 + (dt/total)**2)
    else:
        dfrac = 1.0 / total

    return rate, drate, fraction, dfrac


def divvy(data, chunk=chunk):
    npts = len(data)
    nseg = int(num.ceil(float(npts) / chunk))
    edges = num.arange(nseg + 1) * chunk
    info = []
    for iseg in xrange(nseg):
        segment = data[edges[iseg]:edges[iseg+1]+1]
        info.append(peakrate(segment))
    return info


data = []
for file in infiles:
    # read some data
    aside.write("Reading data from %s ... \n" % file)

    # ASCII from txtdmp
    seconds, nanoseconds, upper, lower = readtimes(file)
    cycles = (upper - upper[0]) * upperscale + lower
    times = cycles / cyclescale

    data += divvy(times)

data.sort()

ofp = open(ratfile, 'w')
ofp.write("read serr 1 2\n")
tableio.writetable(data, ofp, transpose=0)
ofp.close()
