## @file event.py
## @brief Event/trigger classes for timing Monte-Carlo.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

"""@brief Event/trigger classes for timing Monte-Carlo.

"""

import bisect
import numarray as num
import numarray.random_array as ra


(COND_ROI, COND_TKR, COND_CALLE, COND_CALHE, COND_CNO, COND_PER, COND_SOL, COND_EXT) = \
           [1 << bit for bit in range(8)]

oneTick = 50e-9
tickRate = 20e6

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
class Window(Input):

    #
    def __init__(self, input, dwot=0):
        self.time = input.time
        self.condition = input.condition
        self.dwot = dwot
        return

    #
    def __iadd__(self, other):
        deltaT = other - self
        if deltaT < 0:
            raise ValueError
        elif deltaT < tWindow:
            self.condition |= other.condition
        else:
            raise ValueError
        return self

    pass


#
class Event(Window):

    def __init__(self, window, det=0):
        self.time = window.time
        self.condition = window.condition
        self.dwot = window.dwot
        self.det = det
        return

    pass


#
def aggregate(inputs):
    """Make Windows from Inputs."""

    windows = EventList()
    evIt = iter(inputs)

    try:
        nextInput = evIt.next()
        lastTime = 0
        while True:
            window = Window(nextInput)
            now = window.time
            include = now + tWindow
            dead = include + tDeadZone
            window.dwot = now - lastTime
            nextInput = evIt.next()
            while nextInput.time < include:
                window += nextInput
                nextInput = evIt.next()
                pass
            while nextInput.time < dead:
                nextInput = evIt.next()
                pass
            windows.append(window)
            lastTime = window.time
            pass
    except StopIteration:
        # It'd be sweet to use our own exception here that was a subclass of StopIteration.
        # To do that would take a fancier iterator for EventList.
        pass
        

    return windows


#
def trigger(windows):
    """Make Events from Windows."""

    events = EventList()
    winIt = iter(windows)

    return events


#
class MessageEngine:

    #
    def __init__(self, prescale=0, deadTime=tBusy):
        self.prescale = prescale
        self.count = 0
        self.deadTime = deadTime
        self.reset()
        return

    #
    def reset(self):
        self.count = self.prescale
        return

    #
    def hit(self):
        self.count -= 1
        if self.count:
            return False
        else:
            self.reset()
            return True
        return

    pass


#
class Scheduler:

    numEngines = 16
    numCond = 256

    #
    def __init__(self):
        self.engines = [MesageEngine() for xx in range(numEngines)]
        self.schedule = [0] * numEngines
        return

    #
    def lookup(window):
        engine = self.engines[self.schedule[window.condition]]
        if engine.hit():
            event = Event(window, engine.deadTime)
        else:
            event = False
            pass
        return event

    pass


#
class EventList:
    """This is a collection of Inputs, Windows, or Events.

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
    def append(self, event):
        self.events.append(event)
        return

    #
    def __len__(self):
        return len(self.events)

    #
    def __getitem__(self, index):
        return self.events[index]

    #
    def __iter__(self):
        return self.events.__iter__()

    pass


#
def makeTimes(rate, length):
    expected = float(rate) * length
    number = ra.poisson(expected)
    times = ra.random(number) * length
    times.sort()
    # quantize here, in windows, or?
    return times


#
def makeInputs(rate, length, condition):
    rate /= tickRate
    length *= tickRate
    times = makeTimes(rate, length)
    inputs = EventList()
    for thisTime in times:
        input = Input(thisTime, condition)
        inputs.append(input)
        pass
    return inputs



#
def test():
    ii = makeInputs(80, 1000, COND_TKR)
    print len(ii.events)
    ww = aggregate(ii)
    print len(ww.events)
    print ww[0].time, ww[-1].time
    return

if __name__ == "__main__":
    test()
