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

infile = "../Data/vdg_em_4M_ene.dat"
#infile = "../Data/gamma_9_25_198M_ene.dat"
outfile = "VdG.pha"

# define reconstructed energy "channels"
eReconMin = 7.0
eReconMax = 35.0
nChan = 100

# set up energy bins
step = (eReconMax - eReconMin) / nChan
epsilon = step / 2.0
edges = num.arange(eReconMin, eReconMax+epsilon, step)

# read data
data = tableIo.readTable(infile)
eRecon = data[0]

# histogram data
binner = histogram.Histogram(edges)
binner += eRecon

# output
status = 0
st, fptr = glastFits.createFile(outfile)
status |= st
st, chdu = WrtPHA.createSpecHdu(fptr, binner.histogram)
status |= st
status |= glastFits.closeFile(fptr)

if status:
    raise IOError, "CFITSIO problem."

