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

#infile = "../Data/vdg_em_4M_ene.dat"
infile = "../Data/gamma_9_25_198M_ene.dat"
outfile = "VdG.pha"

minE = 7.0
maxE = 27.0
nbin = 100

# set up energy bins
step = (maxE - minE) / nbin
epsilon = step / 2.0
edges = num.arange(minE, maxE+epsilon, step)

# read data
obsE, trueE = tableIo.readTable(infile)

# histogram data
binner = histogram.Histogram(edges)
binner += obsE

# output
status = 0
st, fptr = glastFits.createFile(outfile)
status |= st
st, chdu = WrtPHA.createSpecHdu(fptr, binner.histogram)
status |= st
status |= glastFits.closeFile(fptr)

if status:
    raise IOError, "CFITSIO problem."

