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
               'EvtSecond', 'EvtNanoSecond')

    triggerTime, ppsSeconds, ppsTime, seconds, nanoSeconds = \
                 readColumns.readColumns(fileName, columns)

    # debug
    ntuple.addColumn('triggerTime', triggerTime)
    ntuple.addColumn('ppsSeconds', ppsSeconds)
    ntuple.addColumn('ppsTime', ppsTime)
    ntuple.addColumn('seconds', seconds)
    ntuple.addColumn('nanoSeconds', nanoSeconds)

    vxTime = seconds + nanoSeconds / 1e9

    nRoll = numarray.zeros(ppsSeconds.shape[0], numarray.Float64)
    
    # debug
    ntuple.addColumn('nRoll', nRoll)
    ntuple.addColumn('vxTime', vxTime)
    # ntuple.addColumn('', )

    triggerTimePlus = numarray.array(triggerTime)
    triggerTimePlus[numarray.where(triggerTime < ppsTime)] += rollPpsTime

    # debug
    ntuple.addColumn('triggerTimePlus', triggerTimePlus)

    obviousRolls = (ppsSeconds[1:] < ppsSeconds[:-1]).astype(numarray.Float64)
    nRoll[1:] += numarray.add.accumulate(obviousRolls)
    
    trialTime = (nRoll * rollPpsSeconds + ppsSeconds) + \
                (triggerTimePlus - ppsTime) / tickRate

    vxDelta = vxTime[1:] - vxTime[:-1]
    trialDelta = trialTime[1:] - trialTime[:-1]
    deltaDiff = vxDelta - trialDelta
    extraRolls = numarray.around(deltaDiff / rollPpsTime)

    print "%s extra PPS rollovers detected." % numarray.add.reduce(extraRolls)

    nRoll[1:] += numarray.add.accumulate(extraRolls)

    evtTicks = (nRoll * rollPpsSeconds + ppsSeconds) * tickRate + \
                (triggerTimePlus - ppsTime)

    # debug
    ntuple.addColumn('evtTicks', evtTicks)
    import code
    code.interact(local=locals())
    
    return evtTicks
