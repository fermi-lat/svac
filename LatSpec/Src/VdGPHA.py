#!/usr/bin/env python

## @file "VdGPHA.py"
## @brief Create a PHA file from Van de Graaff data (or a Monte-Carlo).
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

import Numeric as num

import glastFits
import histogram
import tableIo
import WrtPHA

# get config data from here
import mainpage

# set up reconstructed energy channels
step = (mainpage.eReconMax - mainpage.eReconMin) / mainpage.nChan
epsilon = step / 2.0
edges = num.arange(mainpage.eReconMin, mainpage.eReconMax+epsilon, step)

# read data
data = tableIo.readTable(mainpage.specDataFile)
eRecon = data[0]

# histogram data
binner = histogram.Histogram(edges)
binner += eRecon

# output
status = 0
st, fptr = glastFits.createFile(mainpage.phaFile)
status |= st
st, chdu = WrtPHA.createSpecHdu(fptr, binner.histogram)
status |= st
status |= glastFits.closeFile(fptr)

if status:
    raise IOError, "CFITSIO problem."

