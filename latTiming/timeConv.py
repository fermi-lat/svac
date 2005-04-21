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
    triggerTime, ppsSeconds, ppsTime, = \
                 readColumns.readColumns(fileName, columns)

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
    sys.stderr.write("%s extra PPS rollovers detected.\n" %
                     numarray.add.reduce(extraRolls))
    nRoll[1:] += numarray.add.accumulate(extraRolls)

    evtTicks = (nRoll * rollPpsSeconds + ppsSeconds) * tickRate + \
                (triggerTime - ppsTime)

    return evtTicks


#
def evtTicksSerial(fileName):
    """@brief Like evtTicks, but works one event at a time.

    """

    columns = ('GemTriggerTime', 'GemOnePpsSeconds', 'GemOnePpsTime',
               'EvtSecond', 'EvtNanoSecond')
    triggerTime, ppsSeconds, ppsTime, seconds, nanoSeconds = \
                 readColumns.readColumns(fileName, columns)

    ticks = numarray.zeros(len(seconds), numarray.Float64)

    for event in range(len(seconds)):
        ticks[event] = oneTick(triggerTime[event],
                               ppsSeconds[event], ppsTime[event],
                               seconds[event], nanoSeconds[event])
        pass

    return ticks

firstEvent = 1
firstSecond = 0
lastPps = 0
lastTime = 0
lastTicks = 0

#
def oneTick(triggerTime, ppsSeconds, ppsTime, seconds, nanoSeconds):

    global firstEvent
    global firstSecond
    global lastPps
    global lastTime
    global lastTicks

    nRoll = 0
    if firstEvent:
        firstEvent = 0
        firstSecond = seconds
    else:
        if ppsSeconds < lastPps:
            # obvious pps rollover
            nRoll = 1
            pass
        pass

    # timebase rollover
    if triggerTime < ppsTime:
        triggerTime += rollPpsTime
        pass

    ticks = (nRoll * rollPpsSeconds + ppsSeconds) * tickRate + \
            (triggerTime - ppsTime)

    rtcTime = (seconds - firstSecond) + nanoSeconds * 1e-9
    if not firstEvent:
        # find less-obvious pps rollovers
        trialDelta = (ticks - lastTicks) / tickRate
        rtcDelta = rtcTime - lastTime
        nRoll += numarray.around((rtcDelta - trialDelta) / rollPpsSeconds)
        
        ticks = (nRoll * rollPpsSeconds + ppsSeconds) * tickRate + \
                (triggerTime - ppsTime)
        pass

    lastPps = ppsSeconds
    lastTime = rtcTime
    lastTicks = ticks

    return ticks


#
def vxRealTime(fileName):
    """@brief Get the VXWorks realtime clock data.

    @arg fileName the name of an svacTuple file.

    @ret A tuple containing an array of double-precision times for each event
    (arbitrary zero point) and a double-precision scalar which can be added to
    the array to get absolute times.

    """
    
    columns = ('EvtSecond', 'EvtNanoSecond')
    seconds, nanoSeconds = readColumns.readColumns(fileName, columns)
    vxTime = (seconds - seconds[0]) + nanoSeconds / 1e9
    return vxTime, seconds[0]


#
def sbcCycles(fileName):
    """@brief Get data from the CPU cycle counter on the SBC.

    @arg fileName the name of an svacTuple file.

    @ret A double-precision array containing a whole number of SBC CPU cycles
    for each event.  The zero point is arbitrary.

    """
    
    columns = ('EvtUpperTime', 'EvtLowerTime')
    upper, lower = readColumns.readColumns(fileName, columns)
    upper -= upper[0]
    sbcCycles = upper * fourGib + lower
    return sbcCycles
