## @file util.py
## @brief Random useful stuff.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#

"""@brief Random useful stuff.

"""

#
class SubField:

    #
    def __init__(self, low, high):
        self.low = low
        self.high = 2 ** high
        return

    #
    def __call__(self, field):
        field = field % self.high
        field = field >> self.low
        return field

