#!/usr/bin/env python

## @file "VdGRMF.py"
## @brief Create RMF and ARF files from Monte-Carlo data.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

import sys

import Numeric as num

import glastFits
import histogram
import tableIo
import WrtARF
import WrtRMF

# get config data from here
import JobOptions

# set up bin and channel edges
step = float(JobOptions.eTrueMax - JobOptions.eTrueMin) / JobOptions.nBin
epsilon = step / 2
trueEdges = num.arange(JobOptions.eTrueMin, JobOptions.eTrueMax+epsilon, step)

step = float(JobOptions.eReconMax - JobOptions.eReconMin) / JobOptions.nChan
epsilon = step / 2
reconEdges = num.arange(JobOptions.eReconMin, JobOptions.eReconMax+epsilon,
                        step)

# read data
sys.stderr.write("Reading data from %s ... " % JobOptions.responseDataFile)
data = tableIo.readTable(JobOptions.responseDataFile)
eRecon, eTrue = data[:2]
nTuple = num.transpose((eTrue, eRecon))
sys.stderr.write("ok.\n")

sys.stderr.write("Calculating ... ")

# histogram data
# 2-d over true and recon energy to build the matrix
matrixBinner = histogram.Histogram((trueEdges, reconEdges))
matrixBinner += nTuple
matrix = matrixBinner.histogram.astype(num.Float32)

# 1-d over true energy of accepted events
# used to normalize the matrix and to build the ARF
acceptedBinner = histogram.Histogram(trueEdges)
acceptedBinner += eTrue
accepted = acceptedBinner.histogram.astype(num.Float32)

# normalize matrix so it contains probabilities
lowLimit = num.array(1.0, num.Float32)
matrix /= num.maximum(accepted[:, num.NewAxis], lowLimit)

# divide true spectrum of accepted events by generated spectrum to get an
# energy-dependent efficiency
efficiency = accepted / JobOptions.sourceSpectrum(trueEdges)

sys.stderr.write("ok.\n")

# # output

# first the RMF
sys.stderr.write("Writing RMF to %s ... " % JobOptions.rmfFile)
status = 0
st, fptr = glastFits.createFile(JobOptions.rmfFile)
status |= st
st, chdu = WrtRMF.createMatrixHdu(fptr, matrix, trueEdges*1000)
status |= st
st, chdu = WrtRMF.createEboundsHdu(fptr, reconEdges*1000)
status |= st
status |= glastFits.closeFile(fptr)

if status:
    raise IOError, "CFITSIO problem."
sys.stderr.write("ok.\n")

# then the ARF
sys.stderr.write("Writing ARF to %s ... " % JobOptions.arfFile)
st, fptr = glastFits.createFile(JobOptions.arfFile)
status |= st
st, chdu = WrtARF.createArfHdu(fptr, efficiency, trueEdges*1000)
status |= st
status |= glastFits.closeFile(fptr)

if status:
    raise IOError, "CFITSIO problem."
sys.stderr.write("ok.\n")
