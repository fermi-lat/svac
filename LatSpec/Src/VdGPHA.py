#!/usr/bin/env python

## @file "VdGPHA.py"
## @brief Create a PHA file from Van de Graaff data (or a Monte-Carlo).
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC
##
## @todo Take inputs from a JobOptions file, instead of hardcoding them.

import Numeric as num

import glastFits
import histogram
import tableIo
import WrtPHA

specDataFile = "../Data/vdg_em_4M_ene.dat"
phaFile = "VdG.pha"

# define reconstructed energy "channels"
eReconMin = 7.0
eReconMax = 35.0
nChan = 100

# set up reconstructed energy channels
step = (eReconMax - eReconMin) / nChan
epsilon = step / 2.0
edges = num.arange(eReconMin, eReconMax+epsilon, step)

# read data
data = tableIo.readTable(specDataFile)
eRecon = data[0]

# histogram data
binner = histogram.Histogram(edges)
binner += eRecon

# output
status = 0
st, fptr = glastFits.createFile(phaFile)
status |= st
st, chdu = WrtPHA.createSpecHdu(fptr, binner.histogram)
status |= st
status |= glastFits.closeFile(fptr)

if status:
    raise IOError, "CFITSIO problem."

