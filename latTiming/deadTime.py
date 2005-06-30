## @file deadTime.py
## @brief Measure deadtime.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

"""@brief Measure deadtime.

"""

import numarray as num

detSat = 2**16 - 1
ltRoll = 2**25

#
def deadDist(theTuple):

    det = theTuple['GemDeltaEventTime']
    dwot = theTuple['GemDeltaWindowOpenTime']
    lt = theTuple['GemLiveTime']

    mask = num.logical_and(det == dwot, det != detSat)
    if mask[0]:
        mask[0] = 0
        pass

    dlt = num.zeros(len(det))
    dlt[1:] = lt[1:] - lt[:-1]
    dlt[dlt < 0] += ltRoll

    deadTimes = det[mask] - dlt[mask]
    return deadTimes
