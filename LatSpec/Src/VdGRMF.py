#!/usr/bin/env python

## @file "VdGRMF.py"
## @brief Create am RMF file from Monte-Carlo data.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC
##
## @todo Take inputs from a JobOptions file, instead of hardcoding them.

import Numeric as num

import glastFits
import histogram
import tableIo
import WrtRMF

infile = "../Data/gamma_9_25_198M_ene.dat"
outfile = "VdG.rmf"

# define true energy "bins"
eTrueMin = 9.0
eTrueMax = 25.0
nBin = 160

# define reconstructed energy "channels"
eReconMin = 7.0
eReconMax = 35.0
nChan = 100

# set up bin and channel edges
step = (eTrueMax - eTrueMin) / 160
epsilon = step / 2
trueEdges = num.arange(eTrueMin, eTrueMax+epsilon, step)

step = (eReconMax - eReconMin) / nChan
epsilon = step / 2
reconEdges = num.arange(eReconMin, eReconMax+epsilon, step)

# read data
data = tableIo.readTable(infile)
eRecon, eTrue = data[:2]
nTuple = num.transpose((eTrue, eRecon))

# histogram data
matrixBinner = histogram.Histogram((trueEdges, reconEdges))
matrixBinner += nTuple

normBinner = histogram.Histogram(trueEdges)
normBinner += eTrue

# normalize matrix so it contains probabilities
matrix = matrixBinner.histogram / normBinner.histogram[:, num.NewAxis]

# output
status = 0
st, fptr = glastFits.createFile(outfile)
status |= st
st, chdu = WrtRMF.createMatrixHdu(fptr, matrix, trueEdges)
status |= st
st, chdu = WrtRMF.createEboundsHdu(fptr, reconEdges)
status |= st
status |= glastFits.closeFile(fptr)

if status:
    raise IOError, "CFITSIO problem."
