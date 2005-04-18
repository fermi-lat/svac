## @file 
## @brief Calculate event times from low-level variables.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

"""@brief Calculate event times from low-level variables.

"""

import sys
import numarray
import readColumns


#
def evtTicks(fileName):
    """@brief Calculate event ticks.

    @arg fileName the name of an svacTuple file.

    @ret A double-precision array containing a whole number of LAT ticks for
    each event.  This should be good for inter-event timing, but the 'zero
    point' is arbitrary.

    """

    tickRate = 20e6
    rollPpsSeconds = 2 ** 7
    rollPpsTime = 2 ** 25

    columns = ('GemTriggerTime', 'GemOnePpsSeconds', 'GemOnePpsTime',
               'EvtSecond', 'EvtNanoSecond')

    triggerTime, ppsSeconds, ppsTime, seconds, nanoSeconds = \
                 readColumns.readColumns(fileName, columns)

    seconds -= seconds[0]
    vxTime = seconds + nanoSeconds / 1e9

    nRoll = numarray.zeros(ppsSeconds.shape[0], numarray.Float64)
    
    triggerTimePlus = numarray.array(triggerTime)
    triggerTimePlus[numarray.where(triggerTime < ppsTime)] += rollPpsTime

    obviousRolls = (ppsSeconds[1:] < ppsSeconds[:-1]).astype(numarray.Float64)
    nRoll[1:] += numarray.add.accumulate(obviousRolls)
    
    trialTime = (nRoll * rollPpsSeconds + ppsSeconds) + \
                (triggerTimePlus - ppsTime) / tickRate

    vxDelta = vxTime[1:] - vxTime[:-1]
    trialDelta = trialTime[1:] - trialTime[:-1]
    deltaDiff = vxDelta - trialDelta
    extraRolls = numarray.around(deltaDiff / rollPpsSeconds)

    sys.stderr.write("%s extra PPS rollovers detected.\n" % numarray.add.reduce(extraRolls))

    nRoll[1:] += numarray.add.accumulate(extraRolls)

    evtTicks = (nRoll * rollPpsSeconds + ppsSeconds) * tickRate + \
                (triggerTimePlus - ppsTime)

    return evtTicks
