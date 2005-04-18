#!/afs/slac/g/ek/bin/python

import code
import sys

import numarray
import timeConv

if len(sys.argv) == 2:
    inFile = sys.argv[1]
else:
    sys.stderr.write("Usage: %s svacTuple.root\n" % sys.argv[0])
    sys.exit(1)
    pass

ticks = timeConv.evtTicks(inFile)
sbcCycles = timeConv.sbcCycles(inFile)
vxTime, firstSecond = timeConv.vxRealTime(inFile)

print "Got %d events." % len(ticks)

delta = ticks[1:] - ticks[:-1]
minDelta = numarray.minimum.reduce(delta)
maxDelta = numarray.maximum.reduce(delta)
print "Min: %s, Max: %s" % (minDelta, maxDelta)

import hqPlot
hqPlot.plot((ticks, sbcCycles, vxTime), ('ticks', 'sbcCycles', 'vxTime'))

code.interact(local=locals())
