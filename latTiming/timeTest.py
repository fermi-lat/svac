#!/afs/slac/g/ek/bin/python

import code
import sys

import numarray
import timeConv
import readColumns

# get the name of a file to read from command-line arguments
if len(sys.argv) == 2:
    inFile = sys.argv[1]
else:
    sys.stderr.write("Usage: %s svacTuple.root\n" % sys.argv[0])
    sys.exit(1)
    pass

# read in the data
ticks = timeConv.evtTicks(inFile)
sbcCycles = timeConv.sbcCycles(inFile)
vxTime, firstSecond = timeConv.vxRealTime(inFile)
serialTicks = timeConv.evtTicksSerial(inFile)

rootTicks = readColumns.readColumns(inFile, 'EvtTicks')

# print "Got %d events." % len(ticks)

# delta = ticks[1:] - ticks[:-1]
# minDelta = numarray.minimum.reduce(delta)
# maxDelta = numarray.maximum.reduce(delta)
# print "Min: %s, Max: %s" % (minDelta, maxDelta)

if numarray.alltrue(serialTicks == ticks):
    print "Serialized ticks pass."
else:
    print "Serialized ticks fail."
    pass

if numarray.alltrue(rootTicks == ticks):
    print "Root ticks pass."
else:
    print "Root ticks fail."
    pass

import hqPlot
hqPlot.plot(( ticks,   sbcCycles,   vxTime,   serialTicks,   rootTicks),
            ('ticks', 'sbcCycles', 'vxTime', 'serialTicks', 'rootTicks'))

banner = 'sys.exit() or EOF (^D on UNIX, ^Z on windos) to quit.'
code.interact(banner, local=locals())
