#!/afs/slac/g/ek/bin/python

"""Usage: newTimes.py inFile outFile

"""

def getTicks(inFile):
    theTuple = readColumns.readTuple(inFile)

    ppss = theTuple['ContextLsfTimeTimeToneCurrentTimeSecs']
    dppss = ppss[1:] - ppss[:-1]
    toneMask = num.concatenate(([False], dppss>0))
    
    ppst = theTuple['ContextLsfTimeTimeToneCurrentGemTimeTicks']
    dppst = ppst[1:] - ppst[:-1]
    dppst[dppst < 0] += 2**25
    dppst = num.concatenate(([0], dppst))
    ppst = num.add.accumulate(dppst)
    
    seconds = ppss[toneMask]
    delta = dppst[toneMask]
    ticks = ppst[toneMask]
    
    deltadelta = delta[1:] - delta[:-1]

    seconds = seconds[1:]
    delta = delta[1:]
    ticks = ticks[1:]

    return seconds, ticks, delta, deltadelta


import code
import sys

import numarray as num

import tableio

#import hqPlot
import readColumns

if len(sys.argv) >= 3:
    inFiles = sys.argv[1:-1]
    outFile = sys.argv[-1]
else:
    print >> sys.stderr, __doc__
    sys.exit()
    pass

datas = []
for inFile in inFiles:
    print >> sys.stderr, inFile
    data = getTicks(inFile)
    datas.append(num.transpose(data))
    pass
seconds, ticks, delta, deltadelta = num.transpose(num.concatenate(datas))

# put a fake but only semi-bogus value in first delta
# no, don't
#avgDelta = num.sum(delta) / (len(delta) - 1)
#delta[0] = avgDelta

# shift origin to save bits
middle = len(seconds) / 2
seconds -= seconds[middle]
ticks -= ticks[middle]

# Shift to middle of bin
ticks -= 0.5

data = num.array((seconds, ticks, delta, deltadelta))
title = 'Clock skew'
colNames = ('Seconds', 'Ticks', 'Cycles / PPS', 'DeltaDelta')

tableio.writehippo(data, outFile, title, colNames)
