## @file mappings.py
## @brief Functions to translate register settings into a useful form.
## @author Warren Focke <focke@slac.stanford.edu> SLAC - GLAST I&T/SVAC

#

"""@brief Functions to translate register settings into a useful form.

"""


#
def mapTkrDac(dac):
    """@brief """
    return '%s,%s' % (getThrDACRange(dac), getThrDAC(dac))

#
def getThrDAC(dac):
    """@brief Get threshhold from GTFE dac"""
    b0 = dac & 0x40
    b1 = dac & 0x20
    b2 = dac & 0x10
    b3 = dac & 0x8
    b4 = dac & 0x4
    b5 = dac & 0x2
    return (b0>>6) + (b1>>4) + (b2>>2) + b3 + (b4<<2) + (b5<<4)

#
def getThrDACRange(dac):
    """@brief Get range from GTFE dac"""
    return dac & 0x1
