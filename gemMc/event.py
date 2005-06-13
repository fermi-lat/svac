## @file event.py
## @brief Event/trigger classes for timing Monte-Carlo.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

"""@brief Event/trigger classes for timing Monte-Carlo.

"""

import bisect


(COND_ROI, COND_TKR, COND_CALLE, COND_CALHE, COND_CNO, COND_PER, COND_SOL, COND_EXT) = \
           [1 << bit for bit in range(8)]

tWindow = 12
tDeadZone = 2
tBusy = 530

#
class Input:
    """This is any trigger input, whether or not it resulted in an evet or window open.

    """

    #
    def __init__(self, time=0.0, condition=0x0):
        self.time = time
        self.condition = condition
        return

    #
    def __cmp__(self, other):
        return cmp(self.time, other.time)

    #
    def __add__(self, other):
        # This should not work if inputs don't fall in the same window.
        # But it does :-(
        time = min(self.time, other.time)
        condition = self.condition | other.condition
        new = self.__class__(time, condition)
        return new

    #
    def __sub__(self, other):
        return self.time - other.time

    pass


#
class EventList:
    """This is a collection of Inputs.

    """

    #
    def __init__(self, events=None):
        if events is None:
            self.events = []
        else:
            self.events = list(events)
            pass
        self.events.sort()
        return

    #
    def __add__(self, other):
        new = self.__class__()
        new.events = list(self.events)
        if hasattr(other, events):
            new.insertList(other.events)
        else:
            new.insertEvent(other)
            pass
        return new

    #
    def insertList(self, other):
        for event in other:
            self.insertEvent(other)
        return

    #
    def insertEvent(self, other):
        bisect.insort(self.events, other)
        return

    #
    def __len__(self):
        return len(self.events)

    #
    def __getitem__(self, index):
        return self.events[index]

    pass
