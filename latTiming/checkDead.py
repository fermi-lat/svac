#!/usr/bin/env python

"""usage: checkDead.py inFile1 ...

"""

import code
import sys

import numarray as num

import hqPlot
import readColumns
import timeConv

nArgs = len(sys.argv) - 1
if nArgs >= 1:
    inFiles = sys.argv[1:]
else:
    print __doc__
    sys.exit(1)
    pass


columns = ('GemDeltaEventTime', 'EvtTicks')
saturated = 2**16 - 1
oneTick = 50e-9

def reportRate(nEvents, nTicks):
    deltaT = nTicks * oneTick
    print "%d Events / %g ticks => %g +/- %g Hz" % \
          (nEvents, nTicks, nEvents/deltaT, num.sqrt(nEvents)/deltaT)
    return

def rdr(x, dx):
    "@brief Calculate rate and error from exponential decay constant and its error."
    r = 1.0 / (x * oneTick)
    dr = r * dx / x
    return r, dr

gemDeltas = []
tickDeltas = []
tickDeltaShorts = []
totalEvents = 0
totalTicks = 0
for inFile in inFiles:
    print inFile
    
    gemDelta, ticks = readColumns.readColumns(inFile, columns)

    nEvents = len(gemDelta) - 1
    totalEvents += nEvents
    nTicks = ticks[-1] - ticks[1]
    totalTicks += nTicks

    reportRate(nEvents, nTicks)

    gemDelta = gemDelta[1:]
    tickDelta = ticks[1:] - ticks[:-1]
    
    unSaturated = num.nonzero(gemDelta != saturated)[0]
    gemDelta = num.take(gemDelta, unSaturated)
    tickDeltaShort = num.take(tickDelta, unSaturated)

    gemDeltas.append(gemDelta)
    tickDeltas.append(tickDelta)
    tickDeltaShorts.append(tickDeltaShort)
    pass

gemDelta = num.concatenate(gemDeltas)
del gemDeltas
tickDelta = num.concatenate(tickDeltas)
del tickDeltas
tickDeltaShort = num.concatenate(tickDeltaShorts)
del tickDeltaShorts

print len(tickDelta), len(gemDelta)
reportRate(totalEvents, totalTicks)

if num.alltrue(tickDeltaShort == gemDelta):
    print "Pass"
else:
    print "Fail"
    pass

minGemSep = num.minimum.reduce(gemDelta)
minGST = minGemSep * oneTick
print "Shortest gemDeltaEventTime: %d ticks = %g s." % (minGemSep, minGST)

minEvtSep = num.minimum.reduce(tickDeltaShort)
minEST = minEvtSep * oneTick
print "Shortest EVT separation: %d ticks = %g s." % (minEvtSep, minEST)

#hqPlot.plot((gemDelta, tickDelta), ('gemDelta', 'tickDelta'))
hqPlot.plot((tickDelta,), ('tickDelta',))

banner = 'sys.exit() or EOF (^D on UNIX, ^Z on windos) to quit.'
code.interact(banner, local=locals())
