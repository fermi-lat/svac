#!/afs/slac/g/ek/bin/python

"""Usage: newTimes.py inFile outFile

"""

import code
import sys

import numarray as num

import tableio

#import hqPlot
import readColumns

if len(sys.argv) == 3:
    inFile, outFile = sys.argv[1:]
else:
    print >> sys.stderr, __doc__
    sys.exit()
    pass

theTuple = readColumns.readTuple(inFile)

#ticks = theTuple['EvtTicks']
#tickDelta = ticks[1:] - ticks[:-1]

ppss = theTuple['ContextLsfTimeTimeToneCurrentTimeSecs']
dppss = ppss[1:] - ppss[:-1]
#dppss[dppss < 0] += 128

ppst = theTuple['ContextLsfTimeTimeToneCurrentGemTimeTicks']
dppst = ppst[1:] - ppst[:-1]
dppst[dppst < 0] += 2**25

mask = dppst > 1e7

seconds = num.add.accumulate(dppss[mask])

dppst = dppst[mask]
ticks = num.add.accumulate(dppst)

data = num.array((seconds, dppst, ticks))
title = 'Clock skew'
colNames = ('Seconds', 'Cycles / PPS', 'Ticks')

tableio.writehippo(data, outFile, title, colNames)
