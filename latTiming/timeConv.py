## @file timeConv.py
## @brief Calculate event times from low-level variables.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

"""@brief Calculate event times from low-level variables.

"""

import sys
import numarray
import readColumns


tickRate = 20e6
rollPpsSeconds = 2 ** 7
rollPpsTime = 2 ** 25

fourGib = 2.0 ** 32

#
def evtTicks(fileName):
    """@brief Calculate event ticks.

    @arg fileName the name of an svacTuple file.

    @ret A double-precision array containing a whole number of LAT ticks for
    each event.  This should be good for inter-event timing, but the 'zero
    point' is arbitrary.

    """

    columns = ('GemTriggerTime', 'GemOnePpsSeconds', 'GemOnePpsTime')
    triggerTime, ppsSeconds, ppsTime, = readColumns.readColumns(fileName, columns)

    # fix rollovers in 1PPS timebase
    triggerTime[numarray.where(triggerTime < ppsTime)] += rollPpsTime

    # find places where 1PPS seconds has obviously rolled
    nRoll = numarray.zeros(ppsSeconds.shape[0], numarray.Float64)
    obviousRolls = (ppsSeconds[1:] < ppsSeconds[:-1]).astype(numarray.Float64)
    nRoll[1:] += numarray.add.accumulate(obviousRolls)
    
    trialTime = (nRoll * rollPpsSeconds + ppsSeconds) + \
                (triggerTime - ppsTime) / tickRate

    # find less-obvious rollovers in 1PPS seconds
    vxTime, firstSecond = vxRealTime(fileName)
    vxDelta = vxTime[1:] - vxTime[:-1]
    trialDelta = trialTime[1:] - trialTime[:-1]
    deltaDiff = vxDelta - trialDelta
    extraRolls = numarray.around(deltaDiff / rollPpsSeconds)
    sys.stderr.write("%s extra PPS rollovers detected.\n" % numarray.add.reduce(extraRolls))
    nRoll[1:] += numarray.add.accumulate(extraRolls)

    evtTicks = (nRoll * rollPpsSeconds + ppsSeconds) * tickRate + \
                (triggerTime - ppsTime)

    return evtTicks


#
def vxRealTime(fileName):
    columns = ('EvtSecond', 'EvtNanoSecond')
    seconds, nanoSeconds = readColumns.readColumns(fileName, columns)
    vxTime = (seconds - seconds[0]) + nanoSeconds / 1e9
    return vxTime, seconds[0]


#
def sbcCycles(fileName):
    columns = ('EvtUpperTime', 'EvtLowerTime')
    upper, lower = readColumns.readColumns(fileName, columns)
    upper -= upper[0]
    sbcCycles = upper * fourGib + lower
    return sbcCycles
