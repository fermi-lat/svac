## @file 
## @brief Calculate event times from low-level variables.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

"""@brief Calculate event times from low-level variables.

"""

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

    fourGib = 2.0 ** 32
    ppcRate = 16e6
    tickRate = 20e6
    rollPpsSeconds = 2 ** 7
    rollPpsTime = 2 ** 25

    columns = ('GemTriggerTime', 'GemOnePpsSeconds', 'GemOnePpsTime',
               'EvtUpperTime', 'EvtLowerTime')

    triggerTime, ppsSeconds, ppsTime, upper, lower = \
                 readColumns.readColumns(fileName, columns)

    ulTime = (upper * fourGib + lower) / ppcRate
    ultBase = ulTime[0] - ppsSeconds[0]
    ulTime -= ultBase
    nRoll = numarray.around(ulTime / rollTime)
    
    triggerTime[where(triggerTime < ppsTime)] += rollPpsTime

    evtTicks = (nRoll * rollPpsSeconds + ppsSeconds) * tickRate \
               + triggerTime - ppsTime

    return evtTicks
