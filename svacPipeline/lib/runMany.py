## @file runMany.py
## @brief Manage multiple external processes.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

"""@brief Manage multiple external processes.

"""

import os
import threading
import time

FAILURE = 1
defaultPoll = 1

#
def pollMany(function, allArgs, pollInt=defaultPoll):
    """@brief Run a function for many sets arguments,
    polling to see when they are all done.

    @arg function The function to be run.

    @arg allArgs A squence of argument tuples.  @a function will be run in a separate thread
    for each set of arguments in this sequence.

    """

    threads = []

    for argSet in allArgs:
        thread = threading.Thread(target=function, args=argSet)
        threads.append(thread)
        thread.start()
        pass

    while threads:
        time.sleep(pollInt)
        newThreads = []
        for thread in threads:
            if thread.isAlive():
                newThreads.append(thread)
                pass
            pass
        threads = newThreads
        pass

    return


#
def pollManyResult(function, allArgs, pollInt=defaultPoll):
    """@brief Run a function for many sets arguments,
    polling to see when they are all done.

    @arg function The function to be run.

    @arg allArgs A squence of argument tuples.  @a function will be run in a separate thread
    for each set of arguments in this sequence.

    """

    nThreads = len(allArgs)

    threads = []
    wrappers = []
    for argSet in allArgs:
        wrapper = Wrapper(function, argSet, default=FAILURE)
        thread = threading.Thread(target=wrapper)
        threads.append(thread)
        wrappers.append(wrapper)
        thread.start()
        pass

    results = [1] * nThreads
    liveThreads = range(nThreads)
    while liveThreads:
        time.sleep(pollInt)
        newThreads = []
        for iThread in liveThreads:
            if threads[iThread].isAlive():
                newThreads.append(iThread)
            else:
                results[iThread] = wrappers[iThread].result
                pass
            pass
        liveThreads = newThreads
        pass

    return results


#
class Wrapper:
    """@brief This just wraps up a function so you can get its return value later.

    """

    #
    def __init__(self, func, args, default=None):
        self.func = func
        self.args = args
        self.result = default
        return

    #
    def __call__(self):
        self.result = self.func(*self.args)
        return

    pass

#
def spawn(command, args):
    args = (command,) + args
    os.spawnv(os.P_WAIT, command, args)
    return

#
def bsub(command, args):
    return
