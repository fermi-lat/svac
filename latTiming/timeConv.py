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

    # debug
    import hippo
    app = hippo.HDApp()
    canvas = app.canvas ()
    rc = hippo.RootController.instance()
    ntc = hippo.NTupleController.instance()
    ntuple = hippo.NumArrayTuple()
    ntuple.setName('nuggets')
    ntuple.setTitle('coconuts')
    ntc.registerNTuple(ntuple)

    fourGib = 2.0 ** 32
    # ppcRate = 16e6
    ppcRate = 1 / 60e-9
    tickRate = 20e6
    rollPpsSeconds = 2 ** 7
    rollPpsTime = 2 ** 25

    columns = ('GemTriggerTime', 'GemOnePpsSeconds', 'GemOnePpsTime',
               'EvtUpperTime', 'EvtLowerTime')

    triggerTime, ppsSeconds, ppsTime, upper, lower = \
                 readColumns.readColumns(fileName, columns)

    # debug
    ntuple.addColumn('triggerTime', triggerTime)
    ntuple.addColumn('ppsSeconds', ppsSeconds)
    ntuple.addColumn('ppsTime', ppsTime)
    ntuple.addColumn('upper', upper)
    ntuple.addColumn('lower', lower)

    ulTime = (upper * fourGib + lower) / ppcRate
    ultBase = ulTime[0] - ppsSeconds[0]
    ulTime -= ultBase
    nRoll = numarray.around(ulTime / rollPpsSeconds - 0.5)

    # debug
    ntuple.addColumn('ulTime', ulTime)
    ntuple.addColumn('nRoll', nRoll)
    # ntuple.addColumn('', )

    triggerTimePlus = numarray.array(triggerTime)
    triggerTimePlus[numarray.where(triggerTime < ppsTime)] += rollPpsTime

    # debug
    ntuple.addColumn('triggerTimePlus', triggerTimePlus)
    
    evtTicks = (nRoll * rollPpsSeconds + ppsSeconds) * tickRate \
               + triggerTimePlus - ppsTime

    # debug
    ntuple.addColumn('evtTicks', evtTicks)
    import code
    code.interact(local=locals())
    
    return evtTicks
