#!/usr/bin/env python

## @file "VdGRMF.py"
## @brief Create RMF and ARF files from Monte-Carlo data.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC
##
## @todo Take inputs from a JobOptions file, instead of hardcoding them.

import sys

import Numeric as num

import glastFits
import histogram
import spectralFuncs
import tableIo
import WrtARF
import WrtRMF

# # config
responseDataFile = "../Data/gamma_9_25_198M_ene.dat"
rmfFile = "VdG.rmf"
arfFile = "VdG.arf"

# define true energy "bins"
eTrueMin = 9.0
eTrueMax = 25.0
nBin = 160

# define reconstructed energy "channels"
eReconMin = 7.0
eReconMax = 35.0
nChan = 100

# input spectrum used to build the response set
offset = 8.0
slope = -1.0
norm = 198e6
def sourceSpectrum(edges):
    return spectralFuncs.powerlaw((offset, slope, norm), edges)
# # end config

# set up bin and channel edges
step = (eTrueMax - eTrueMin) / 160
epsilon = step / 2
trueEdges = num.arange(eTrueMin, eTrueMax+epsilon, step)

step = (eReconMax - eReconMin) / nChan
epsilon = step / 2
reconEdges = num.arange(eReconMin, eReconMax+epsilon, step)

# read data
sys.stderr.write("Reading data from %s ... " % responseDataFile)
data = tableIo.readTable(responseDataFile)
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
efficiency = accepted / sourceSpectrum(trueEdges)

sys.stderr.write("ok.\n")

# # output

# first the RMF
sys.stderr.write("Writing RMF to %s ... " % rmfFile)
status = 0
st, fptr = glastFits.createFile(rmfFile)
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
sys.stderr.write("Writing ARF to %s ... " % arfFile)
st, fptr = glastFits.createFile(arfFile)
status |= st
st, chdu = WrtARF.createArfHdu(fptr, efficiency, trueEdges*1000)
status |= st
status |= glastFits.closeFile(fptr)

if status:
    raise IOError, "CFITSIO problem."
sys.stderr.write("ok.\n")
