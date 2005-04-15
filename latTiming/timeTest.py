#!/afs/slac/g/ek/bin/python

import numarray
import timeConv

inFile = 'svac915.root'

ticks = timeConv.evtTicks(inFile)

print "Got %d events." % len(ticks)

delta = ticks[1:] - ticks[:-1]
minDelta = numarray.minimum.reduce(delta)
maxDelta = numarray.maximum.reduce(delta)
print "Min: %s, Max: %s" % (minDelta, maxDelta)
