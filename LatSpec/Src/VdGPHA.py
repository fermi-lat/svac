#!/usr/bin/env python

## @file "VdGPHA.py"
## @brief Create a PHA file from Van de Graaff data (or a Monte-Carlo).
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

import sys

import Numeric as num

import glastFits
import histogram
import tableIo
import WrtPHA

# get config data from here
import JobOptions

# try to open output files first, so we fail early if there's a problem
status = 0
st, phaptr = glastFits.createFile(JobOptions.phaFile)
status |= st

# set up reconstructed energy channels
step = float(JobOptions.eReconMax - JobOptions.eReconMin) / JobOptions.nChan
epsilon = step / 2.0
edges = num.arange(JobOptions.eReconMin, JobOptions.eReconMax+epsilon, step)

# read data
sys.stderr.write("Reading data from %s ... " % JobOptions.specDataFile)
data = tableIo.readTable(JobOptions.specDataFile)
eRecon = data[0]
sys.stderr.write("ok.\n")

sys.stderr.write("Calculating ... ")

# histogram data
binner = histogram.Histogram(edges)
binner += eRecon
sys.stderr.write("ok.\n")

# output
sys.stderr.write("Writing PHA to %s ... " % JobOptions.phaFile)
st, chdu = WrtPHA.createSpecHdu(phaptr, binner.histogram)
status |= st
status |= glastFits.closeFile(phaptr)

if status:
    raise IOError, "CFITSIO problem."
sys.stderr.write("ok.\n")

